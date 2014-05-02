#include "gtest/gtest.h"
#include "YASim/Util/ScopedStoper.h"

#include <thread>
#include <vector>

using YASim::Util::ScopedStoper;

struct ScopedStoperTest : public testing::Test
{
	typedef std::vector< std::chrono::milliseconds::rep > mvec;
	mvec vec;
	
	virtual void SetUp() override 
	{
	}
};

TEST_F(ScopedStoperTest, IsContainerSizeCorrect)
{
	EXPECT_EQ( 0, vec.size() );
	{	ScopedStoper<mvec> a(vec); 	}
	EXPECT_EQ( 1, vec.size() );
	{	ScopedStoper<mvec> a(vec); 	}
	EXPECT_EQ( 2, vec.size() );
}

TEST_F(ScopedStoperTest, AreContainerValuesCorrect)
{
	std::chrono::milliseconds mili_2(2);
	std::chrono::milliseconds mili_3(3);
	EXPECT_EQ( 0, vec.size() );
	{	ScopedStoper<mvec> a(vec); 	std::this_thread::sleep_for(mili_3); }
	EXPECT_EQ( 3, vec[0] );
	{	ScopedStoper<mvec> a(vec); std::this_thread::sleep_for(mili_2);	}
	EXPECT_EQ( 2, vec[1] );
	{	ScopedStoper<mvec> a(vec); }
	EXPECT_EQ( 0, vec[2] );
}
