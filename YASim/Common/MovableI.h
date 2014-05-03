#pragma once

#include "Vector.h"

namespace YASim
{
namespace Common
{

class MovableI
{
public:
	MovableI(void);
	virtual ~MovableI(void);

	virtual void setTarget(const Vector&) = 0;
	virtual const Vector& getTarget() const = 0;

	virtual void setPosition(const Vector&) = 0;
	virtual const Vector& getPosition() const = 0;

	virtual void setAcceleration(const Vector&) = 0;
	virtual const Vector& getAcceleration() const = 0;

	virtual void setSpeed(const Vector&) = 0;
	virtual const Vector& getSpeed() const = 0;

	virtual const Vector::value_type& getMaxAcceleration() const = 0;
	virtual const Vector::value_type& getMaxSpeed() const = 0;

	virtual void move() = 0;
};

}
}
