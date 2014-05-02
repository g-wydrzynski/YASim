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

}
}
