#pragma once

#include <array>
#include <numeric>
#include <vector>

#include "Vector.h"
//#include "Area.h"
//#include "Movable.h"

namespace YASim
{
namespace Common
{

class Movable;
template<typename, int> class Area;

class Map
{
public:
	static const int AREA_WIDTH = 5;
	static const size_t MAX;

	Map(void);
	~Map(void);

	long getHeight() const { return end.getY() - start.getY(); }
	long getWidth() const { return end.getX() - start.getX(); }

	void apply();
	void init();

private:
	typedef Area< Movable, AREA_WIDTH > AreaType;
	typedef std::vector< AreaType > LookUpList;
	LookUpList widthLookup, heightLookup;

	Vector start;
	Vector end;
};

}
}
