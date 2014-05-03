#include "Movable.h"

namespace YASim
{
namespace Common
{

Movable::Movable(void)
: position(0, 0), target(0, 0), acceleration(0, 0), speed(0, 0)
{
}

Movable::Movable(const Vector& _pos)
: position(_pos), target(0, 0), acceleration(0, 0), speed(0, 0)
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
