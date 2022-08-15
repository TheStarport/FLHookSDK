#include "FLHook.hpp"

namespace Hk::Time
{
	std::chrono::seconds Unix() { return ToSeconds(std::chrono::system_clock::now().time_since_epoch()); }
	std::chrono::milliseconds UnixMilliseconds() { return ToMilliseconds(std::chrono::system_clock::now().time_since_epoch()); }
} // namespace Hk::Time
