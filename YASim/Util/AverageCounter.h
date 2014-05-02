#pragma once

#include <algorithm>

namespace YASim
{
namespace Util
{

template< typename Container >
class AverageCounter 
{
public:
	typedef typename Container::value_type element_type;

	AverageCounter(Container& _container);
	~AverageCounter(void) {}

	void push_back(const element_type& elem) { sum += elem; ++elements; container.push_back(elem); };
	double getAverage() const { if(elements) return static_cast<double>(sum) / elements; else return 0; }
	int getElements() const { return elements; }

private:
	Container& container;
	int elements;
	element_type sum;
};

template< typename Container >
AverageCounter<Container>::AverageCounter(Container& _container) 
: container(_container), elements(0), sum(0) 
{
	std::for_each(std::begin(container), std::end(container), [&](const element_type& elem) {
		++elements;
		sum += elem;
	});
}


}
}
