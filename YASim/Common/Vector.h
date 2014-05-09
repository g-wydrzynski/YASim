#pragma once

namespace YASim
{
namespace Common
{

class Vector
{
public:
	typedef signed long value_type;
	
	Vector(void);
	Vector(value_type _x, value_type _y);
	~Vector(void);

	void setX(value_type _x) { x = _x; }
	void setY(value_type _y) { y = _y; }
	value_type getX() const { return x; }
	value_type getY() const { return y; }

	bool operator==(const Vector& rhs) const { return x == rhs.x && y == rhs.y; }
	Vector operator+(const Vector& rhs) const { return Vector(x + rhs.x, y + rhs.y); }
	void operator+=(const Vector& rhs) { x += rhs.x; y += rhs.y; }
	Vector operator-(const Vector& rhs) const { return Vector(x - rhs.x, y - rhs.y); }
	void operator-=(const Vector& rhs) { x -= rhs.x; y -= rhs.y; }

private:
	value_type x;
	value_type y;
};

}
}

