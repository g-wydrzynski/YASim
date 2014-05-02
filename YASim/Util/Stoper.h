#pragma once

#include <chrono>

namespace YASim
{
namespace Util
{

class Stoper
{
public:
	Stoper(void);
	~Stoper(void);

	void stop();

	template< typename duration >
	duration getDuration() const;

	std::chrono::milliseconds getMiliseconds() const;

private:
	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point end;
};

}
}
