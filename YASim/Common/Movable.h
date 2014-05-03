#pragma once
#include "MovableI.h"
#include "Vector.h"

namespace YASim
{
namespace Common
{

class Movable : public MovableI
{
private:
	enum max_limits {
		_acceleration = 0,
		_speed = 1
	};
public:
	Movable(void);
	Movable(const Vector& vec);
	~Movable(void);

	virtual void setTarget(const Vector& vec) override { target = vec; }
	virtual const Vector& getTarget() const override { return target; }

	virtual void setPosition(const Vector& vec) override { position = vec; }
	virtual const Vector& getPosition() const override { return position; }

	virtual void setAcceleration(const Vector& vec) override { acceleration = vec; check_max<_acceleration>(vec); }
	virtual const Vector& getAcceleration() const override { return acceleration; }

	virtual void setSpeed(const Vector& vec) override { speed = vec; check_max<_speed>(vec); }
	virtual const Vector& getSpeed() const override { return speed; }

	virtual void move() override;

private:

	template< enum Movable::max_limits >
	struct limits;
	
	template<enum Movable::max_limits l>
	void check_max(const Vector& vec);

	Vector position;
	Vector target;
	Vector acceleration;
	Vector speed;
};

}
}
