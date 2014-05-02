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
	EXPECT_EQ( 0, ac.getElements() );
}

TEST_F(AverageCounterTest, IsInitializedCorrectlyWithContainer)
{
	vec.push_back(4);
	vec.push_back(5);
	AverageCounter< mvec > ac(vec);

	EXPECT_EQ( 4.5, ac.getAverage() );
	EXPECT_EQ( 2, vec.size() );
	EXPECT_EQ( 2, ac.getElements() );
	ac.push_back( 2 );
	EXPECT_EQ( 11.0/3, ac.getAverage() );
	EXPECT_EQ( 3, vec.size() );
	EXPECT_EQ( 3, ac.getElements() );
}

TEST_F(AverageCounterTest, PushesCorrectly)
{
	ac.push_back( 3 );
	EXPECT_EQ( 3.0, ac.getAverage() );
	EXPECT_EQ( 1, vec.size() );
	EXPECT_EQ( 1, ac.getElements() );
	ac.push_back( 4 );
	EXPECT_EQ( 3.5, ac.getAverage() );
	EXPECT_EQ( 2, vec.size() );
	EXPECT_EQ( 2, ac.getElements() );
}

TEST_F(AverageCounterTest, WorksWithScoped)
{
	typedef AverageCounter< mvec > ScopedType;
	ac.push_back( 3 );
	EXPECT_EQ( 3.0, ac.getAverage() );
	EXPECT_EQ( 1, vec.size() );
	EXPECT_EQ( 1, ac.getElements() );
	{	ScopedStoper<ScopedType> a(ac); 	}
	EXPECT_EQ( 1.5, ac.getAverage() );
	EXPECT_EQ( 2, vec.size() );
	EXPECT_EQ( 2, ac.getElements() );
	{	ScopedStoper<ScopedType> a(ac); 	}
	EXPECT_EQ( 1.0, ac.getAverage() );
	EXPECT_EQ( 3, vec.size() );
	EXPECT_EQ( 3, ac.getElements() );
}

TEST_F(AverageCounterTest, WorksWithHighFluctuations)
{
	int cnt = 0;
	ac.push_back( 1 );
	EXPECT_EQ( 1.0, ac.getAverage() );
	EXPECT_EQ( ++cnt, vec.size() );
	EXPECT_EQ( cnt, ac.getElements() );
	ac.push_back( 41 );
	EXPECT_EQ( 21, ac.getAverage() );
	EXPECT_EQ( ++cnt, vec.size() );
	EXPECT_EQ( cnt, ac.getElements() );
	ac.push_back( 1 );
	EXPECT_EQ( 43.0/3, ac.getAverage() );
	EXPECT_EQ( ++cnt, vec.size() );
	EXPECT_EQ( cnt, ac.getElements() );
	ac.push_back( 996 );
	EXPECT_EQ( 259.75, ac.getAverage() );
	EXPECT_EQ( ++cnt, vec.size() );
	EXPECT_EQ( cnt, ac.getElements() );
}

TEST_F(AverageCounterTest, WorksWithLowFluctuations)
{
	int cnt = 0;
	ac.push_back( 51 );
	EXPECT_EQ( 51.0, ac.getAverage() );
	EXPECT_EQ( ++cnt, vec.size() );
	EXPECT_EQ( cnt, ac.getElements() );
	ac.push_back( 52 );
	EXPECT_EQ( 51.5, ac.getAverage() );
	EXPECT_EQ( ++cnt, vec.size() );
	EXPECT_EQ( cnt, ac.getElements() );
	ac.push_back( 51 );
	EXPECT_EQ( 154.0/3, ac.getAverage() );
	EXPECT_EQ( ++cnt, vec.size() );
	EXPECT_EQ( cnt, ac.getElements() );
	ac.push_back( 51 );
	EXPECT_EQ( 205.0/4, ac.getAverage() );
	EXPECT_EQ( ++cnt, vec.size() );
	EXPECT_EQ( cnt, ac.getElements() );
}
