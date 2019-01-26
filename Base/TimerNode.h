//
// Created by kiwi on 19-1-23.
//

#ifndef KIWI_TIMERNODE_H
#define KIWI_TIMERNODE_H

#include <functional>

namespace Kiwi
{
	using TimerHandler = std::function<void()>;
	using TimerID = uint32_t;

	class TimerNode
	{
	public:
		friend class TimerPool;

	public:
		TimerNode() = default;

	private:
		bool _stopped_;
		TimerHandler _handler_;
		TimerID _id_;
		uint64_t _expire_time_;
	};
}

#endif //KIWI_TIMERNODE_H
