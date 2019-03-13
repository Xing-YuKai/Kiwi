//
// Created by kiwi on 19-1-27.
//

#ifndef KIWI_TYPES_H
#define KIWI_TYPES_H

#include <functional>
#include <vector>
#include <memory>
#include <unordered_map>

namespace Kiwi
{
	class Socket;

	class InetAddress;

	class Channel;

	class TimerNode;

	class TimeRange;

	class TcpConnection;

	class Buffer;

	class EventLoop;

	using namespace std::placeholders;

	namespace Type
	{
		using Functor = std::function<void()>;
		using EventHandler = std::function<void()>;
		using ReadEventHandler = std::function<void(TimeRange)>;
		using ChannelList = std::vector<Channel *>;
		using ChannelMap = std::unordered_map<int, Channel *>;
		using EventList = std::vector<struct epoll_event>;
		using TimerNodePtr = std::shared_ptr<TimerNode>;
		using TimerList = std::vector<TimerNodePtr>;
		using TimerHandler = std::function<void()>;
		using TimerID = uint32_t;
		using BufferPtr = std::shared_ptr<Buffer>;
		using TcpConnectionPtr = std::shared_ptr<TcpConnection>;
		using MessageHandler = std::function<void(const TcpConnectionPtr &, const BufferPtr &, const TimeRange &)>;
		using WriteCompleteHandler = std::function<void(const TcpConnectionPtr &)>;
		using CloseHandler = std::function<void(const TcpConnectionPtr &)>;
		using ConnectionHandler = std::function<void(const TcpConnectionPtr &)>;
		using NewConnectionHandler = std::function<void(const Socket &, const InetAddress &)>;
		using TcpConnectionID = uint32_t;
		using TcpConnectionMap = std::unordered_map<TcpConnectionID, TcpConnectionPtr>;
	}
}
#endif //KIWI_TYPES_H
