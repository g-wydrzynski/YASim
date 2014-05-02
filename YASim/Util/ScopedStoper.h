#pragma once
#include "Stoper.h"

namespace YASim
{
namespace Util
{

template< typename Container >
class ScopedStoper
{
public:
	ScopedStoper(Container& _container) : container(_container) {}

	~ScopedStoper(void)
	{
		st.stop();
		container.push_back(st.getMiliseconds().count());
	}

private:
	Container& container;
	Stoper st;
};

}
}
