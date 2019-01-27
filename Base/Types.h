//
// Created by kiwi on 19-1-27.
//

#ifndef KIWI_TYPES_H
#define KIWI_TYPES_H

#include <functional>
#include <vector>
#include <map>
#include <memory>

namespace Kiwi
{
	class Channel;
	class TimerNode;

	namespace Type
	{
		using EventHandler = std::function<void()>;
		using ChannelList = std::vector<Channel *>;
		using ChannelMap = std::map<int, Channel *>;
		using EventList = std::vector<struct epoll_event>;
		using TimerNodePtr = std::shared_ptr<TimerNode>;
		using TimerList = std::vector<TimerNodePtr>;
		using TimerHandler = std::function<void()>;
		using TimerID = uint32_t;
	}
}
#endif //KIWI_TYPES_H
