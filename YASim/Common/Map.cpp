#include "Map.h"

#include <iostream>

#include "Area.h"
#include "Movable.h"

namespace YASim
{
namespace Common
{

const size_t Map::MAX = (1 << 13 /* 8192 */) / (LookUpList::value_type::WIDTH) + 1;//(128 + 127)


Map::Map(void) 
	: widthLookup(MAX)
	, heightLookup(MAX)
	, start(0, MAX * AreaType::WIDTH)
	, end(0, MAX * AreaType::WIDTH)
{
//	T test(MAX);
	/*for(int i = 0; i < MAX; ++i)
		test.push_back(i);*/
/*try{
	for(int i = 0; i < MAX; ++i)
	{
		if(i % 1000 == 0)
			std::cout << "i : " << i << std::endl;
		
		a[i] = test;
	}
} catch(std::exception ex)
{
	std::cout << "caught: " << ex.what() << std::endl;
}
*/

	init();
}

Map::~Map(void)
{
}

void Map::init()
{
	for(int i = 0; i < MAX; ++i)
	{
		widthLookup[i].setId(i);	
		heightLookup[i].setId(i);	
	}
}


}
}
