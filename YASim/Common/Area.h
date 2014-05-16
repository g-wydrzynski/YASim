#pragma once

#include <list>
#include <memory>

namespace YASim
{
namespace Common
{

template< typename Entity, int MOVE >
class Area
{
public:
	static const size_t WIDTH = 1 << MOVE; // 32
	// one area covers 2*WIDTH, except for first and last WIDTH all other are double covered (with WIDTH offset)

	typedef Entity type;
	typedef std::shared_ptr<Entity> typePtr;

	Area(void) {}
	~Area(void) {}

	void setId(int i) { id = i;}
	int getId() const { return id; }

	int posMin() const { return (id==0?id:id-1) * WIDTH; }
	int posMax() const { return (id+1) * WIDTH; }

	static size_t getIndex(int pos) //both ret + ret+1, 0 is Width, 1 until last-1 is 2*Width
	{	return pos >> MOVE;	}

private:
	int id;
	std::list< typePtr > elements;
};

}
}
