#include "gtest/gtest.h"
#include "YASim/Common/Vector.h"

#include <thread>
#include <vector>

using YASim::Common::Vector;

TEST(VectorTest, IsCorrectlyConstructed)
{
	Vector pos;
	Vector pos_(3, 5);
	EXPECT_EQ( 0, pos.getX() );
	EXPECT_EQ( 0, pos.getY() );

	EXPECT_EQ( 3, pos_.getX() );
	EXPECT_EQ( 5, pos_.getY() );
}

TEST(VectorTest, IsCorrectlyChanged)
{
	Vector pos;
	Vector pos_(3, 5);
	pos.setX(2);
	pos.setY(4);
	pos_.setX(6);
	pos_.setY(1);

	EXPECT_EQ( 2, pos.getX() );
	EXPECT_EQ( 4, pos.getY() );

	EXPECT_EQ( 6, pos_.getX() );
	EXPECT_EQ( 1, pos_.getY() );
}

TEST(VectorTest, IsEqual)
{
	Vector pos(3, 5);
	Vector pos_(3, 5);

	EXPECT_EQ( pos_, pos );
	EXPECT_EQ( pos_.getX(), pos.getX() );
	EXPECT_EQ( pos_.getY(), pos.getY() );

	pos.setX(2);
	pos.setY(4);
	pos_.setX(2);
	pos_.setY(4);

	EXPECT_EQ( pos_, pos );
	EXPECT_EQ( pos_.getX(), pos.getX() );
	EXPECT_EQ( pos_.getY(), pos.getY() );
}

TEST(VectorTest, IsAdditive)
{
	Vector pos(3, 5);
	Vector pos_(6, 2);
	Vector res = pos + pos_;

	EXPECT_EQ( res, Vector( 9, 7 ) );
	EXPECT_EQ( res.getX(), 9 );
	EXPECT_EQ( res.getY(), 7);
}

TEST(VectorTest, IsAdditiveToSelf)
{
	Vector pos(3, 5);
	Vector pos_(6, 2);
	Vector poscpy( pos );
	pos += pos_;

	EXPECT_EQ( pos, Vector( 9, 7 ) );
	EXPECT_EQ( pos.getX(), 9 );
	EXPECT_EQ( pos.getY(), 7 );
}

TEST(VectorTest, IsSubtractive)
{
	Vector pos(3, 5);
	Vector pos_(6, 1);
	Vector res = pos - pos_;

	EXPECT_EQ( res, Vector( -3, 4 ) );
	EXPECT_EQ( res.getX(), -3 );
	EXPECT_EQ( res.getY(), 4);
}

TEST(VectorTest, IsSubtractiveToSelf)
{
	Vector pos(3, 5);
	Vector pos_(6, 1);
	pos -= pos_;

	EXPECT_EQ( pos, Vector( -3, 4 ) );
	EXPECT_EQ( pos.getX(), -3 );
	EXPECT_EQ( pos.getY(), 4);
}
