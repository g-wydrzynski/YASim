#include "gtest/gtest.h"
#include "YASim/Common/Movable.h"

using YASim::Common::Movable;
using YASim::Common::Vector;

struct TestMovable : Movable
{
	TestMovable():Movable(), acc(15), sp(20) {}
	TestMovable(const Vector& vec):Movable(vec){}

	virtual const Vector::value_type& getMaxAcceleration() const override {return acc;}
	virtual const Vector::value_type& getMaxSpeed() const override {return sp;}

	Vector::value_type acc;
	Vector::value_type sp;
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

TEST_F(MovableTest, IsAccelerationLimitWorking)
{
	Vector acc1(17,3);
	Vector acc2(4,19);
	Vector acc3(18,21);
	
	m1.setAcceleration(acc1);
	EXPECT_EQ( m1.getAcceleration(), Vector(m1.getMaxAcceleration(),3) );
	EXPECT_EQ( m1.getAcceleration().getX(), m1.getMaxAcceleration() );
	EXPECT_EQ( m1.getAcceleration().getY(), 3 );

	m1.setAcceleration(acc2);
	EXPECT_EQ( m1.getAcceleration(), Vector(4,m1.getMaxAcceleration()) );
	EXPECT_EQ( m1.getAcceleration().getX(), 4 );
	EXPECT_EQ( m1.getAcceleration().getY(), m1.getMaxAcceleration() );

	m1.setAcceleration(acc3);
	EXPECT_EQ( m1.getAcceleration(), Vector(m1.getMaxAcceleration(),m1.getMaxAcceleration()) );
	EXPECT_EQ( m1.getAcceleration().getX(), m1.getMaxAcceleration() );
	EXPECT_EQ( m1.getAcceleration().getY(), m1.getMaxAcceleration() );
}

TEST_F(MovableTest, IsSpeedLimitWorking)
{
	Vector acc1(23,3);
	Vector acc2(4,21);
	Vector acc3(24,21);
	
	m1.setSpeed(acc1);
	EXPECT_EQ( m1.getSpeed(), Vector(m1.getMaxSpeed(),3) );
	EXPECT_EQ( m1.getSpeed().getX(), m1.getMaxSpeed() );
	EXPECT_EQ( m1.getSpeed().getY(), 3 );

	m1.setSpeed(acc2);
	EXPECT_EQ( m1.getSpeed(), Vector(4,m1.getMaxSpeed()) );
	EXPECT_EQ( m1.getSpeed().getX(), 4 );
	EXPECT_EQ( m1.getSpeed().getY(), m1.getMaxSpeed() );

	m1.setSpeed(acc3);
	EXPECT_EQ( m1.getSpeed(), Vector(m1.getMaxSpeed(),m1.getMaxSpeed()) );
	EXPECT_EQ( m1.getSpeed().getX(), m1.getMaxSpeed() );
	EXPECT_EQ( m1.getSpeed().getY(), m1.getMaxSpeed() );
}

TEST_F(MovableTest, IsMoveWorking)
{
	Vector sp(15,12);
	Vector acc(4,5);
	m1.setSpeed(sp);
	m1.setAcceleration(acc);
	m1.move();

	EXPECT_EQ( m1.getSpeed(), sp + acc );
	EXPECT_EQ( m1.getAcceleration(), acc );
	EXPECT_EQ( m1.getPosition(), Vector(4, 8) + m1.getSpeed() );
}

TEST_F(MovableTest, IsLimitInMoveWorking)
{
	m1.setSpeed(Vector(15,17));
	m1.setAcceleration(Vector(4,5));
	m1.move();

	EXPECT_EQ( m1.getSpeed(), Vector(19, m1.getMaxSpeed()) );
	EXPECT_EQ( m1.getAcceleration(), Vector(4, 5) );
	EXPECT_EQ( m1.getPosition(), Vector(4, 8) + m1.getSpeed() );
}
