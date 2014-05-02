#include "Vector.h"

namespace YASim
{
namespace Common
{

Vector::Vector(void)
: x(0), y(0)
{
}

Vector::Vector(value_type _x, value_type _y)
: x(_x), y(_y)
{
}

Vector::~Vector(void)
{
}

}
}
