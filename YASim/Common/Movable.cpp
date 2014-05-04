#include "Movable.h"

namespace YASim
{
namespace Common
{

Movable::Movable(void)
: position(0, 0), target(0, 0), acceleration(0, 0), speed(0, 0), accVecPosX(0), accVecPosY(0)
{
}

Movable::Movable(const Vector& _pos)
: position(_pos), target(0, 0), acceleration(0, 0), speed(0, 0), accVecPosX(0), accVecPosY(0)
{
}

Movable::~Movable(void)
{
}

void Movable::move()
{
	speed += acceleration;
	check_max<_speed>(speed);
	position += speed;
}

void Movable::tick()
{
	const AccVector& vec( getAccVector() );

	Vector::value_type resX(getAcceleration().getX()), resY(getAcceleration().getY());
	Vector::value_type spX(getSpeed().getX()), spY(getSpeed().getY());

	if( target.getX() == position.getX() )
	{
		resX = 0;
		accVecPosX = 0;
		spX = 0;
		//reset speed ?
	}
	else
	{
		if( abs(resX + speed.getX()) > abs(target.getX() - position.getX()) )//acc zeroing condition
		{
			resX = 0;
			accVecPosX = 0;
		}
		else if(accVecPosX < vec.size())//still accelerating
		{
			resX += (target.getX() < position.getX() ? -1 : 1) * vec[accVecPosX++];
		}
	}
	if(accVecPosY < vec.size())
	{
		resY += (target.getY() < position.getY() ? -1 : 1) * vec[accVecPosY++];
	}

	setAcceleration(Vector(resX, resY));
	setSpeed(Vector(spX, spY));//use acc ??
}

template<>
struct Movable::limits<Movable::_acceleration>
{
	static const Vector::value_type& get(const MovableI& m) { return m.getMaxAcceleration(); }
	static void setX(MovableI& m) {  m.setAcceleration(Vector(m.getMaxAcceleration(),m.getAcceleration().getY())); }
	static void setY(MovableI& m) {  m.setAcceleration(Vector(m.getAcceleration().getX(),m.getMaxAcceleration())); }
};

template<>
struct Movable::limits<Movable::_speed>
{
	static const Vector::value_type& get(const MovableI& m) { return m.getMaxSpeed(); }
	static void setX(MovableI& m) {  m.setSpeed(Vector(m.getMaxSpeed(),m.getSpeed().getY())); }
	static void setY(MovableI& m) {  m.setSpeed(Vector(m.getSpeed().getX(),m.getMaxSpeed())); }
};

template<enum Movable::max_limits l>
void Movable::check_max(const Vector& vec)
{
	if(vec.getX() > limits<l>::get(*this))
		limits<l>::setX(*this);
	if(vec.getY() > limits<l>::get(*this))
		limits<l>::setY(*this);
}

}
}
