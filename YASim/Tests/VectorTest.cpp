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

