#include "Movable.h"

namespace YASim
{
namespace Common
{

Movable::Movable(void)
: position(0, 0), target(std::numeric_limits<Vector::value_type>::max(), std::numeric_limits<Vector::value_type>::max()), acceleration(0, 0), speed(0, 0)//, accVecPosX(0), accVecPosY(0)
{
}

Movable::Movable(const Vector& _pos)
: position(_pos), target(std::numeric_limits<Vector::value_type>::max(), std::numeric_limits<Vector::value_type>::max()), acceleration(0, 0), speed(0, 0)//, accVecPosX(0), accVecPosY(0)
{
}

Movable::~Movable(void)
{
}

void Movable::move()
{
	speed += acceleration;
	check_max<_speed>(speed);
	Vector::value_type spX(getSpeed().getX()), spY(getSpeed().getY());
	
	if( abs(speed.getX()) > abs(target.getX() - position.getX()) )
	{
		acceleration.setX(0);
		speed.setX(0);
		spX = target.getX() - position.getX();
	}
	if( abs(speed.getY()) > abs(target.getY() - position.getY()) )
	{
		acceleration.setY(0);
		speed.setY(0);
		spY = target.getY() - position.getY();
	}

	position += Vector(spX, spY);
}

void Movable::accelerate()
{
	Vector diff = target - position;
	Vector::value_type bigger = std::max(abs(diff.getX()),abs(diff.getY()));
	if( bigger > getMaxAcceleration() )
	{
		Vector::value_type divider = bigger / getMaxAcceleration();
		setAcceleration(Vector(diff.getX() / divider, diff.getY() / divider ));
	}
	else
	{
		setAcceleration(diff);
	}
}

template<>
struct Movable::limits<Movable::_acceleration>
{
	static const Vector::value_type& get(const MovableI& m) { return m.getMaxAcceleration(); }
	static void setX(MovableI& m, int side = 1) {  m.setAcceleration(Vector(side*m.getMaxAcceleration(),m.getAcceleration().getY())); }
	static void setY(MovableI& m, int side = 1) {  m.setAcceleration(Vector(m.getAcceleration().getX(),side*m.getMaxAcceleration())); }
};

template<>
struct Movable::limits<Movable::_speed>
{
	static const Vector::value_type& get(const MovableI& m) { return m.getMaxSpeed(); }
	static void setX(MovableI& m, int side = 1) {  m.setSpeed(Vector(side*m.getMaxSpeed(),m.getSpeed().getY())); }
	static void setY(MovableI& m, int side = 1) {  m.setSpeed(Vector(m.getSpeed().getX(),side*m.getMaxSpeed())); }
};

template<enum Movable::max_limits l>
void Movable::check_max(const Vector& vec)
{
	if(vec.getX() > limits<l>::get(*this))
		limits<l>::setX(*this);
	if(vec.getY() > limits<l>::get(*this))
		limits<l>::setY(*this);
	
	if(vec.getX() < -limits<l>::get(*this))
		limits<l>::setX(*this, -1);
	if(vec.getY() < -limits<l>::get(*this))
		limits<l>::setY(*this, -1);
}

}
}
