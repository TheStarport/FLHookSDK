#include "FLHook.hpp"

namespace Helpers::Time
{
	std::chrono::seconds Unix() { return ToSeconds(std::chrono::system_clock::now()); }
	std::chrono::milliseconds UnixMilliseconds() { return ToMilliseconds(std::chrono::system_clock::now()); }
} // namespace Helpers::Time
