#include "gtest/gtest.h"
#include "YASim/Common/Movable.h"

using YASim::Common::Movable;
using YASim::Common::MovableI;
using YASim::Common::Vector;

struct TestMovable : Movable
{
	TestMovable():Movable(), acc(15), sp(40) { /*init();*/ }
	TestMovable(const Vector& vec):Movable(vec){ /*init();*/ }

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
		set(m1, Vector(4,8), Vector(770,775), Vector(2,4), Vector(6,3));
		set(m2, Vector(4,8), Vector(770,775), Vector(2,4), Vector(6,3));
	}
	TestMovable m1, m2;
};

TEST_F(MovableTest, IsDefaultInitializationCorrect)
{
	TestMovable m;
	EXPECT_EQ( Vector(0,0), m.getPosition() );
	EXPECT_EQ( Vector(std::numeric_limits<Vector::value_type>::max(),std::numeric_limits<Vector::value_type>::max()), m.getTarget() );
	EXPECT_EQ( Vector(0,0), m.getAcceleration() );
	EXPECT_EQ( Vector(0,0), m.getSpeed() );
}

TEST_F(MovableTest, IsInitializableCorrectly)
{
	TestMovable m(Vector(3, 5));
	EXPECT_EQ( Vector(3,5), m.getPosition() );
	EXPECT_EQ( Vector(std::numeric_limits<Vector::value_type>::max(),std::numeric_limits<Vector::value_type>::max()), m.getTarget() );
	EXPECT_EQ( Vector(0,0), m.getAcceleration() );
	EXPECT_EQ( Vector(0,0), m.getSpeed() );

	TestMovable mcpy(m);
	EXPECT_EQ( Vector(3,5), mcpy.getPosition() );
	EXPECT_EQ( Vector(std::numeric_limits<Vector::value_type>::max(), std::numeric_limits<Vector::value_type>::max()), mcpy.getTarget() );
	EXPECT_EQ( Vector(0,0), mcpy.getAcceleration() );
	EXPECT_EQ( Vector(0,0), mcpy.getSpeed() );
}

TEST_F(MovableTest, IsSettingWorkingCorrectly)
{
	EXPECT_EQ( Vector(4,8), m1.getPosition() );
	EXPECT_EQ( Vector(770,775), m1.getTarget() );
	EXPECT_EQ( Vector(2,4), m1.getAcceleration() );
	EXPECT_EQ( Vector(6,3), m1.getSpeed() );
}

TEST_F(MovableTest, IsEqualityCorrect)
{
	EXPECT_EQ( m1.getPosition(), m2.getPosition() );
	EXPECT_EQ( m1.getPosition().getX(), m2.getPosition().getX() );
	EXPECT_EQ( m1.getPosition().getY(), m2.getPosition().getY() );
	EXPECT_EQ( m1.getTarget(), m2.getTarget() );
	EXPECT_EQ( m1.getTarget().getX(), m2.getTarget().getX() );
	EXPECT_EQ( m1.getTarget().getY(), m2.getTarget().getY() );
	EXPECT_EQ( m1.getAcceleration(), m2.getAcceleration() );
	EXPECT_EQ( m1.getAcceleration().getX(), m2.getAcceleration().getX() );
	EXPECT_EQ( m1.getAcceleration().getY(), m2.getAcceleration().getY() );
	EXPECT_EQ( m1.getSpeed(), m2.getSpeed() );
	EXPECT_EQ( m1.getSpeed().getX(), m2.getSpeed().getX() );
	EXPECT_EQ( m1.getSpeed().getY(), m2.getSpeed().getY() );
}

TEST_F(MovableTest, IsAccelerationLimitWorking)
{
	Vector acc1(m1.getMaxAcceleration() + 5, 3);
	Vector acc2(4,m1.getMaxAcceleration() + 4);
	Vector acc3(m1.getMaxAcceleration() + 6, m1.getMaxAcceleration() + 2);
	
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
	Vector acc1(43,3);
	Vector acc2(4,41);
	Vector acc3(44,41);
	
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
	EXPECT_EQ( m1.getPosition(), Vector(4,8) + m1.getSpeed() );
}

TEST_F(MovableTest, IsLimitInMoveWorking)
{
	m1.setSpeed(Vector(15,37));
	m1.setAcceleration(Vector(4,5));
	m1.move();

	EXPECT_EQ( m1.getSpeed(), Vector(19, m1.getMaxSpeed()) );
	EXPECT_EQ( m1.getAcceleration(), Vector(4, 5) );
	EXPECT_EQ( m1.getPosition(), Vector(4, 8) + m1.getSpeed() );
}

TEST_F(MovableTest, IsAccelerateWorking)
{
	TestMovable m;
	Vector target(3,5);
	m.setTarget(target);

	//const MovableI::AccVector& vec( m.getAccVector() );

	m.accelerate();
	EXPECT_EQ( m.getSpeed(), Vector(0, 0) );
	EXPECT_EQ( m.getAcceleration(), target );

	Vector fartarget(30,50);
	m.setTarget(fartarget);
	m.accelerate();
	EXPECT_EQ( m.getSpeed(), Vector(0, 0) );
	EXPECT_EQ( m.getAcceleration(), Vector(10, 15) );//instant acc change -> note its on same m
}

TEST_F(MovableTest, IsAccelerateRepeatableWorking)
{
	TestMovable m;
	Vector target(30,50);
	Vector acc(10,15);
	m.setTarget(target);

	//const MovableI::AccVector& vec( m.getAccVector() );

	m.accelerate();
	EXPECT_EQ( m.getAcceleration(), acc );
	EXPECT_EQ( m.getSpeed(), Vector(0, 0) );
	
	m.accelerate();
	m.accelerate();
	EXPECT_EQ( m.getAcceleration(), acc );
	EXPECT_EQ( m.getSpeed(), Vector(0, 0) );
}

TEST_F(MovableTest, IsAccelerateMoving)
{
	TestMovable m;
	m.setTarget(Vector(30,50));
	Vector acc(10,15);

	//const MovableI::AccVector& vec( m.getAccVector() );

	m.accelerate();
	m.move();
	
	EXPECT_EQ( m.getAcceleration(), acc );
	EXPECT_EQ( m.getSpeed(), acc );
	EXPECT_EQ( m.getPosition(), acc );
}

template<int I>
struct sum
{
	template< typename T >
	static T eval(const T& p)
	{
		return p + sum<I - 1>::eval(p);
	}
};

template<>
struct sum<1>
{
	template< typename T >
	static T eval(const T& p) 
	{
		return p;
	}
};

TEST_F(MovableTest, IsMovingRepeatable)
{
	TestMovable m;
	Vector target(30,50);
	m.setTarget(target);
	Vector acc(10,15);

	m.accelerate();
	m.move();
	
	EXPECT_EQ( m.getAcceleration(), acc );
	EXPECT_EQ( m.getSpeed(), acc );
	EXPECT_EQ( m.getPosition(), acc );

	m.move();
	
	EXPECT_EQ( m.getAcceleration(), acc );
	EXPECT_EQ( m.getSpeed(), sum<2>::eval(acc) );//or implement operator* and replace it with acc*2 ;)
	EXPECT_EQ( m.getPosition(), sum<3>::eval(acc) );

	m.move();

	EXPECT_EQ( m.getAcceleration(), Vector() );
	EXPECT_EQ( m.getSpeed(), Vector() );
	EXPECT_EQ( m.getPosition(), target );
}

TEST_F(MovableTest, IsAccelerateMovingRepeatable)
{
	TestMovable m;
	Vector target(30,50);
	m.setTarget(target);
	Vector acc(10,15);
	Vector rem(0,5);

	m.accelerate();
	m.move();
	
	EXPECT_EQ( m.getAcceleration(), acc );
	EXPECT_EQ( m.getSpeed(), acc );
	EXPECT_EQ( m.getPosition(), acc );

	m.accelerate();
	m.move();
	
	EXPECT_EQ( m.getAcceleration(), acc );
	EXPECT_EQ( m.getSpeed(), sum<2>::eval(acc) );
	EXPECT_EQ( m.getPosition(), sum<3>::eval(acc) );

	m.accelerate();
	EXPECT_EQ( m.getAcceleration(), rem );

	m.move();

	EXPECT_EQ( m.getAcceleration(), Vector() );
	EXPECT_EQ( m.getSpeed(), Vector() );
	EXPECT_EQ( m.getPosition(), target );
}


TEST_F(MovableTest, IsAccelerateMovingBackwards)
{
	TestMovable m;
	m.setPosition(Vector(30,50));
	m.setTarget(Vector(0,0));
	Vector acc(-10,-15);

	m.accelerate();
	m.move();
	
	EXPECT_EQ( m.getAcceleration(), acc );
	EXPECT_EQ( m.getSpeed(), acc );
	EXPECT_EQ( m.getPosition(), Vector( 30 + acc.getX(), 50 + acc.getY()) );
}

TEST_F(MovableTest, IsMovingWorkingNotFrom00)
{
	TestMovable m;
	Vector start(10,10);
	Vector target(19,60);
	m.setPosition(start);
	m.setTarget(target);
	Vector acc(3,15);
	Vector rem(0,5);

	m.accelerate();
	m.move();

	EXPECT_EQ( m.getAcceleration(), acc );
	EXPECT_EQ( m.getSpeed(), acc );
	EXPECT_EQ( m.getPosition(), start + acc );

	m.accelerate();
	m.move();

	EXPECT_EQ( m.getAcceleration(), acc );
	EXPECT_EQ( m.getSpeed(), sum<2>::eval(acc) );
	EXPECT_EQ( m.getPosition(), start + sum<3>::eval(acc) );

	m.accelerate();
	EXPECT_EQ( m.getAcceleration(), rem );
	m.move();

	EXPECT_EQ( m.getAcceleration(), Vector(0, 0) );
	EXPECT_EQ( m.getSpeed(), Vector(0, 0) );
	EXPECT_EQ( m.getPosition(), target );
}

TEST_F(MovableTest, IsMovingWorkingBackwardsNotFrom00)
{
	TestMovable m;
	Vector target(10,10);
	Vector start(19,60);
	m.setPosition(start);
	m.setTarget(target);
	Vector acc(-3,-15);
	Vector rem(0,-5);

	m.accelerate();
	m.move();

	EXPECT_EQ( m.getAcceleration(), acc );
	EXPECT_EQ( m.getSpeed(), acc );
	EXPECT_EQ( m.getPosition(), start + acc );

	m.accelerate();
	m.move();

	EXPECT_EQ( m.getAcceleration(), acc );
	EXPECT_EQ( m.getSpeed(), sum<2>::eval(acc) );
	EXPECT_EQ( m.getPosition(), start + sum<3>::eval(acc) );

	m.accelerate();
	EXPECT_EQ( m.getAcceleration(), rem );
	m.move();

	EXPECT_EQ( m.getAcceleration(), Vector(0, 0) );
	EXPECT_EQ( m.getSpeed(), Vector(0, 0) );
	EXPECT_EQ( m.getPosition(), target );
}

TEST_F(MovableTest, IsTurning)
{
	TestMovable m;

	Vector start(100,100);
	Vector target(300,700);
	m.setPosition(start);
	m.setTarget(target);

	Vector acc(5,15);

	m.accelerate();
	m.move();
	m.move();

	EXPECT_EQ( m.getAcceleration(), acc );
	EXPECT_EQ( m.getSpeed(), sum<2>::eval(acc) );
	EXPECT_EQ( m.getPosition(), start + sum<3>::eval(acc) );
	
	/*
	TODO
	Vector target2(10,500);
	m.setTarget(target2);

	m.accelerate();
	m.move();

	EXPECT_EQ( m.getAcceleration(), acc );
	EXPECT_EQ( m.getSpeed(), sum<2>::eval(acc) );
	EXPECT_EQ( m.getPosition(), start + sum<3>::eval(acc) );
	*/
}

//tick/move change target tick/move -> acc change?
//move -> when at target stop speed/acc, dont have to move full speed if would overjump target

