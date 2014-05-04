#pragma once

#include <vector>
#include "Vector.h"

namespace YASim
{
namespace Common
{

class MovableI
{
public:

	typedef std::vector<Vector::value_type> AccVector;

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

	virtual const AccVector& getAccVector() const = 0;

	virtual void tick() = 0;// calculate acc from target
	virtual void move() = 0;// update speed from acc, move position from speed
};

}
}
