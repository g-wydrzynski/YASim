#include "gtest/gtest.h"
#include "YASim/Common/Area.h"
#include "YASim/Common/Movable.h"

using YASim::Common::Area;
using YASim::Common::Movable;

struct AreaTest : public testing::Test
{
	typedef Area< Movable, 2 > Area2;
	typedef Area< Movable, 3 > Area3;
	typedef Area< Movable, 5 > Area5;

	Area2 a2;
	Area3 a3;
	Area5 a5;
};

template<typename T>
void testIndex()
{
	for(int i = 0; i < 120; ++i)
	{
		EXPECT_EQ( i / T::WIDTH, T::getIndex( i ) );
	}
};

template<typename T>
void testMin(T& a)
{
	for(int i = 0; i < 12; ++i)
	{
		a.setId(i);
		EXPECT_EQ( i==0?0:(i-1)*T::WIDTH, a.posMin() );
	}
};

template<typename T>
void testMax(T& a)
{
	for(int i = 0; i < 12; ++i)
	{
		a.setId(i);
		EXPECT_EQ( (i+1)*T::WIDTH, a.posMax() );
	}
};

template<int factor>
struct calc
{
	static const int res = calc<factor-1>::res * 2;
};

template<>
struct calc<1>
{
	static const int res = 2;
};

TEST_F(AreaTest, TestWidthCalculation)
{
	EXPECT_EQ( calc<2>::res, Area2::WIDTH );
	EXPECT_EQ( calc<3>::res, Area3::WIDTH );
	EXPECT_EQ( calc<5>::res, Area5::WIDTH );
}

TEST_F(AreaTest, TestGetIndex)
{
	testIndex<Area2>();
	testIndex<Area3>();
	testIndex<Area5>();
}

TEST_F(AreaTest, TestGetMin)
{
	testMin(a2);
	testMin(a3);
	testMin(a5);
}

TEST_F(AreaTest, TestGetMax)
{
	testMax(a2);
	testMax(a3);
	testMax(a5);
}

