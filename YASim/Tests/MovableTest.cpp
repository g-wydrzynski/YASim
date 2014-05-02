#include "gtest/gtest.h"
#include "YASim/Common/Movable.h"

using YASim::Common::Movable;
using YASim::Common::Vector;

struct TestMovable : Movable
{
	TestMovable():Movable() {}
	TestMovable(const Vector& vec):Movable(vec){}

	virtual const Vector& getMaxAcceleration() const override {return v;}
	virtual const Vector& getMaxSpeed() const override {return v;}

	Vector v;
};

struct MovableTest : public testing::Test
{
	void set(TestMovable& m, Vector& position, Vector& target, Vector& acceleration, Vector& speed)
	{
		m.setPosition(position);
		m.setTarget(target);
		m.setAcceleration(acceleration);
		m.setSpeed(speed);
	}
	
	virtual void SetUp() override 
	{
		set(m1, Vector(4,8), Vector(7,5), Vector(2,4), Vector(6,3));
		set(m2, Vector(4,8), Vector(7,5), Vector(2,4), Vector(6,3));
	}
	TestMovable m1, m2;
};

TEST_F(MovableTest, IsDefaultInitializationCorrect)
{
	TestMovable m;
	EXPECT_EQ( Vector(0,0), m.getPosition() );
	EXPECT_EQ( Vector(0,0), m.getTarget() );
	EXPECT_EQ( Vector(0,0), m.getAcceleration() );
	EXPECT_EQ( Vector(0,0), m.getSpeed() );
}

TEST_F(MovableTest, IsInitializableCorrectly)
{
	TestMovable m(Vector(3, 5));
	EXPECT_EQ( Vector(3,5), m.getPosition() );
	EXPECT_EQ( Vector(0,0), m.getTarget() );
	EXPECT_EQ( Vector(0,0), m.getAcceleration() );
	EXPECT_EQ( Vector(0,0), m.getSpeed() );
}

TEST_F(MovableTest, IsSettingWorkingCorrectly)
{
	EXPECT_EQ( Vector(4,8), m1.getPosition() );
	EXPECT_EQ( Vector(7,5), m1.getTarget() );
	EXPECT_EQ( Vector(2,4), m1.getAcceleration() );
	EXPECT_EQ( Vector(6,3), m1.getSpeed() );
}

TEST_F(MovableTest, IsEqualityCorrect)
{
	EXPECT_EQ( m1.getPosition(), m2.getPosition() );
	EXPECT_EQ( m1.getTarget(), m2.getTarget() );
	EXPECT_EQ( m1.getAcceleration(), m2.getAcceleration() );
	EXPECT_EQ( m1.getSpeed(), m2.getSpeed() );
}
