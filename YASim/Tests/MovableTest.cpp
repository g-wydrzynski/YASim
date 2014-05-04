#include "gtest/gtest.h"
#include "YASim/Common/Movable.h"

using YASim::Common::Movable;
using YASim::Common::MovableI;
using YASim::Common::Vector;

struct TestMovable : Movable
{
	TestMovable():Movable(), acc(15), sp(20) { init(); }
	TestMovable(const Vector& vec):Movable(vec){ init(); }

	virtual const Vector::value_type& getMaxAcceleration() const override {return acc;}
	virtual const Vector::value_type& getMaxSpeed() const override {return sp;}

	virtual const AccVector& getAccVector() const override { return avec;}

	Vector::value_type acc;
	Vector::value_type sp;
	AccVector avec;
	void init()
	{
		avec.push_back(1);avec.push_back(2);avec.push_back(1);
	}
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

TEST_F(MovableTest, IsTickWorking)
{
	TestMovable m;
	m.setTarget(Vector(3,5));

	const MovableI::AccVector& vec( m.getAccVector() );

	m.tick();
	EXPECT_EQ( m.getSpeed(), Vector(0, 0) );
	EXPECT_EQ( m.getAcceleration(), Vector(vec[0], vec[0]) );
}

TEST_F(MovableTest, IsTickRepeatableWorking)
{
	TestMovable m;
	m.setTarget(Vector(30,50));

	const MovableI::AccVector& vec( m.getAccVector() );

	m.tick();
	
	m.tick();
	EXPECT_EQ( m.getAcceleration(), Vector(vec[0] + vec[1], vec[0] + vec[1]) );
	EXPECT_EQ( m.getSpeed(), Vector(0, 0) );
	
	m.tick();
	EXPECT_EQ( m.getAcceleration(), Vector(vec[0] + vec[1] + vec[2], vec[0] + vec[1] + vec[2]) );
	EXPECT_EQ( m.getSpeed(), Vector(0, 0) );
	
	m.tick();
	EXPECT_EQ( m.getAcceleration(), Vector(vec[0] + vec[1] + vec[2], vec[0] + vec[1] + vec[2]) );
	EXPECT_EQ( m.getSpeed(), Vector(0, 0) );
}

TEST_F(MovableTest, IsTickMoving)
{
	TestMovable m;
	m.setTarget(Vector(30,50));

	const MovableI::AccVector& vec( m.getAccVector() );

	m.tick();
	m.move();
	
	EXPECT_EQ( m.getAcceleration(), Vector(vec[0], vec[0]) );
	EXPECT_EQ( m.getSpeed(), Vector(vec[0], vec[0]) );
	EXPECT_EQ( m.getPosition(), Vector(vec[0], vec[0]) );
}

TEST_F(MovableTest, IsTickMovingRepeatable)
{
	TestMovable m;
	m.setTarget(Vector(30,50));

	const MovableI::AccVector& vec( m.getAccVector() );

	m.tick();
	m.move();
	
	EXPECT_EQ( m.getAcceleration(), Vector(vec[0], vec[0]) );
	EXPECT_EQ( m.getSpeed(), Vector(vec[0], vec[0]) );
	EXPECT_EQ( m.getPosition(), Vector(vec[0], vec[0]) );

	m.tick();
	m.move();
	
	EXPECT_EQ( m.getAcceleration(), Vector(vec[0] + vec[1], vec[0] + vec[1]) );
	EXPECT_EQ( m.getSpeed(), Vector(vec[0] + vec[0] + vec[1], vec[0] + vec[0] + vec[1]) );
	EXPECT_EQ( m.getPosition(), Vector(vec[0] + vec[0] + vec[0] + vec[1], vec[0] + vec[0] + vec[0] + vec[1]) );

	m.tick();
	m.move();

	EXPECT_EQ( m.getAcceleration(), Vector(vec[0] + vec[1] + vec[2], vec[0] + vec[1] + vec[2]) );
	EXPECT_EQ( m.getSpeed(), Vector(vec[0] + vec[0] + vec[1] + vec[0] + vec[1] + vec[2]
				, vec[0] + vec[0] + vec[1] + vec[0] + vec[1] + vec[2]) );
	EXPECT_EQ( m.getPosition(), Vector(vec[0] + vec[0] + vec[0] + vec[1] + vec[0] + vec[0] + vec[1] + vec[0] + vec[1] + vec[2]
				, vec[0] + vec[0] + vec[0] + vec[1] + vec[0] + vec[0] + vec[1] + vec[0] + vec[1] + vec[2]) );

	m.tick();
	m.move();

	EXPECT_EQ( m.getAcceleration(), Vector(vec[0] + vec[1] + vec[2], vec[0] + vec[1] + vec[2]) );
	EXPECT_EQ( m.getSpeed(), Vector(vec[0] + vec[0] + vec[1] + vec[0] + vec[1] + vec[2] + vec[0] + vec[1] + vec[2]
				, vec[0] + vec[0] + vec[1] + vec[0] + vec[1] + vec[2] + vec[0] + vec[1] + vec[2]) );
	EXPECT_EQ( m.getPosition(), Vector(vec[0] + vec[0] + vec[0] + vec[1] + vec[0] + vec[0] + vec[1] + vec[0] + vec[1] + vec[2] + vec[0] + vec[0] + vec[1] + vec[0] + vec[1] + vec[2] + vec[0] + vec[1] + vec[2]
				, vec[0] + vec[0] + vec[0] + vec[1] + vec[0] + vec[0] + vec[1] + vec[0] + vec[1] + vec[2] + vec[0] + vec[0] + vec[1] + vec[0] + vec[1] + vec[2] + vec[0] + vec[1] + vec[2]) );
}

TEST_F(MovableTest, IsTickMovingBackwards)
{
	TestMovable m;
	m.setPosition(Vector(30,50));
	m.setTarget(Vector(0,0));

	const MovableI::AccVector& vec( m.getAccVector() );

	m.tick();
	m.move();
	
	EXPECT_EQ( m.getAcceleration(), Vector(-vec[0], -vec[0]) );
	EXPECT_EQ( m.getSpeed(), Vector(-vec[0], -vec[0]) );
	EXPECT_EQ( m.getPosition(), Vector( 30 - vec[0], 50 - vec[0]) );
}

TEST_F(MovableTest, IsTickStopping)
{
	TestMovable m;
	Vector start(10,10);
	Vector target(12,16);
	m.setPosition(start);
	m.setTarget(target);

	const MovableI::AccVector& vec( m.getAccVector() );

	m.tick();
	m.move();

	EXPECT_EQ( m.getAcceleration(), Vector(vec[0], vec[0]) );
	EXPECT_EQ( m.getSpeed(), Vector(vec[0], vec[0]) );
	EXPECT_EQ( m.getPosition(), start + Vector(vec[0], vec[0]) );

	m.tick();
	m.move();

	// TRICKY
	EXPECT_EQ( m.getAcceleration(), Vector(0, vec[0] + vec[1]) );
	EXPECT_EQ( m.getSpeed(), Vector(vec[0], vec[0] + vec[0] + vec[1]) );
	EXPECT_EQ( m.getPosition(), start + Vector(vec[0] + vec[0], vec[0] + vec[0] + vec[0] + vec[1]) );

	m.tick();
	m.move();

	EXPECT_EQ( m.getAcceleration(), Vector(0, vec[0] + vec[1] + vec[2]) );
	EXPECT_EQ( m.getSpeed(), Vector(0, vec[0] + vec[0] + vec[1] + vec[0] + vec[1] + vec[2]) );
	EXPECT_EQ( m.getPosition(), Vector(target.getX(), start.getX() + vec[0] + vec[0] + vec[0] + vec[1] + vec[0] + vec[0] + vec[1] + vec[0] + vec[1] + vec[2]) );
}

//tick/move change target tick/move -> acc change?
