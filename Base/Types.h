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

	class TimeRange
	class TcpConnection;

	class Buffer;

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
		using TcpConnectionPtr = std::shared_ptr<TcpConnection>;
		using BufferPtr = std::shared_ptr<Buffer>;
		using MessageHandler = std::function<void(const TcpConnectionPtr &)>;
		using ConnectionHandler = std::function<void(const TcpConnectionPtr &, const BufferPtr &, const TimeRange &)>;
		using WriteCompleteHandler = std::function<void(const TcpConnectionPtr &)>;
	}
}
#endif //KIWI_TYPES_H
