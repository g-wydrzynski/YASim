#include "gtest/gtest.h"
#include "YASim/Util/AverageCounter.h"
#include "YASim/Util/ScopedStoper.h"

#include <thread>
#include <vector>

using YASim::Util::AverageCounter;
using YASim::Util::ScopedStoper;

struct AverageCounterTest : public testing::Test
{
	typedef std::vector< std::chrono::milliseconds::rep > mvec;
	mvec vec;
	AverageCounter< mvec > ac;

	AverageCounterTest() : ac(vec), testing::Test() {}
	
	virtual void SetUp() override 
	{
	}
};

TEST_F(AverageCounterTest, IsInitializedCorrectly)
{
	EXPECT_EQ( 0.0, ac.getAverage() );
	EXPECT_EQ( 0, vec.size() );
}

TEST_F(AverageCounterTest, IsInitializedCorrectlyWithContainer)
{
	vec.push_back(4);
	vec.push_back(5);
	AverageCounter< mvec > ac(vec);

	EXPECT_EQ( 4.5, ac.getAverage() );
	EXPECT_EQ( 2, vec.size() );
	ac.push_back( 2 );
	EXPECT_EQ( 11.0/3, ac.getAverage() );
	EXPECT_EQ( 3, vec.size() );
}

TEST_F(AverageCounterTest, PushesCorrectly)
{
	ac.push_back( 3 );
	EXPECT_EQ( 3.0, ac.getAverage() );
	EXPECT_EQ( 1, vec.size() );
	ac.push_back( 4 );
	EXPECT_EQ( 3.5, ac.getAverage() );
	EXPECT_EQ( 2, vec.size() );
}

TEST_F(AverageCounterTest, WorksWithScoped)
{
	typedef AverageCounter< mvec > ScopedType;
	ac.push_back( 3 );
	EXPECT_EQ( 3.0, ac.getAverage() );
	EXPECT_EQ( 1, vec.size() );
	{	ScopedStoper<ScopedType> a(ac); 	}
	EXPECT_EQ( 1.5, ac.getAverage() );
	EXPECT_EQ( 2, vec.size() );
	{	ScopedStoper<ScopedType> a(ac); 	}
	EXPECT_EQ( 1.0, ac.getAverage() );
	EXPECT_EQ( 3, vec.size() );
}

TEST_F(AverageCounterTest, WorksWithFluctuations)
{
	int cnt = 0;
	ac.push_back( 1 );
	EXPECT_EQ( 1.0, ac.getAverage() );
	EXPECT_EQ( ++cnt, vec.size() );
	ac.push_back( 41 );
	EXPECT_EQ( 21, ac.getAverage() );
	EXPECT_EQ( ++cnt, vec.size() );
	ac.push_back( 1 );
	EXPECT_EQ( 43.0/3, ac.getAverage() );
	EXPECT_EQ( ++cnt, vec.size() );
	ac.push_back( 996 );
	EXPECT_EQ( 259.75, ac.getAverage() );
	EXPECT_EQ( ++cnt, vec.size() );
}

