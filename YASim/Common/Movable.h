#pragma once
#include "MovableI.h"
#include "Vector.h"

namespace YASim
{
namespace Common
{

class Movable : public MovableI
{
public:
	Movable(void);
	Movable(const Vector& vec);
	~Movable(void);

	virtual void setTarget(const Vector& vec) override { target = vec; }
	virtual const Vector& getTarget() const override { return target; }

	virtual void setPosition(const Vector& vec) override { position = vec; }
	virtual const Vector& getPosition() const override { return position; }

	virtual void setAcceleration(const Vector& vec) override { acceleration = vec; }
	virtual const Vector& getAcceleration() const override { return acceleration; }

	virtual void setSpeed(const Vector& vec) override { speed = vec; }
	virtual const Vector& getSpeed() const override { return speed; }

private:
	Vector position;
	Vector target;
	Vector acceleration;
	Vector speed;
};

}
}
