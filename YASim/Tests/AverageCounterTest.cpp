#include "gtest/gtest.h"
#include "YASim/Util/AverageCounter.h"
#include "YASim/Util/ScopedStoper.h"

#include <thread>
#include <vector>
#include <algorithm>

using YASim::Util::AverageCounter;
using YASim::Util::ScopedStoper;

struct AverageCounterTest : public testing::Test
{
	typedef std::vector< std::chrono::milliseconds::rep > mvec;
	mvec vec; // underlying container for ac
	AverageCounter< mvec > ac; // test object
	std::vector< int > test_vector;// test data container - holds test data for ac
	
	void process(AverageCounter< mvec >& ac)
	{
		if(elements)
			EXPECT_EQ( static_cast<double>(sum) / elements, ac.getAverage() );
		else
			EXPECT_EQ( 0.0, ac.getAverage() );
		EXPECT_EQ( elements, vec.size() );
		EXPECT_EQ( elements, ac.getElements() );

		std::for_each(begin(test_vector), end(test_vector), [&](int el) {
			++elements;
			sum += el;
			ac.push_back( el );
			EXPECT_EQ( static_cast<double>(sum) / elements, ac.getAverage() );
			EXPECT_EQ( elements, vec.size() );
			EXPECT_EQ( elements, ac.getElements() );
		});
	}

	AverageCounterTest() : ac(vec), testing::Test() {}
	int elements;
	int sum;
	
	virtual void SetUp() override 
	{
		test_vector.clear();
		sum = 0;
		elements = 0;
	}
};

TEST_F(AverageCounterTest, IsInitializedCorrectly)
{
	process(ac);
}

TEST_F(AverageCounterTest, IsInitializedCorrectlyWithContainer)
{
	vec.push_back(4);
	vec.push_back(5);
	AverageCounter< mvec > ac(vec);

	elements = vec.size();
	std::for_each(begin(vec), end(vec), [&](int el) {
		sum += el;
	});
	test_vector.push_back(2);
	process(ac);
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

TEST_F(AverageCounterTest, PushesCorrectly)
{
	test_vector.push_back(3);
	test_vector.push_back(4);
	process(ac);
}

TEST_F(AverageCounterTest, WorksWithHighFluctuations)
{
	test_vector.push_back(1);
	test_vector.push_back(41);
	test_vector.push_back(1);
	test_vector.push_back(996);
	process(ac);
}

TEST_F(AverageCounterTest, WorksWithLowFluctuations)
{
	test_vector.push_back(51);
	test_vector.push_back(52);
	test_vector.push_back(51);
	test_vector.push_back(51);
	process(ac);
}
