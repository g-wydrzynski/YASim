#include "Stoper.h"

using namespace std::chrono;

namespace YASim
{
namespace Util
{

Stoper::Stoper()
	: start( steady_clock::now() )
{
	//std::cout << "It took me " << time_span.count() << " miliseconds." << std::endl;;
}

Stoper::~Stoper(void)
{
}

void Stoper::stop()
{
	end = steady_clock::now();
}

template< typename duration >
duration Stoper::getDuration() const
{
	duration time_span = duration_cast<duration>(end - start);
	return time_span;
}

milliseconds Stoper::getMiliseconds() const
{
	return getDuration< milliseconds >();
}

}
}
