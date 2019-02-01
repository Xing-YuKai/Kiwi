//
// Created by kiwi on 19-1-23.
//

#ifndef KIWI_TIMERNODE_H
#define KIWI_TIMERNODE_H

#include <functional>
#include "Types.h"

namespace Kiwi
{
	class TimerNode
	{
		friend class TimerPool;

	public:
		TimerNode() = default;

		~TimerNode() = default;

	private:
		bool _stopped_;
		Type::TimerHandler _handler_;
		Type::TimerID _id_;
		uint64_t _expire_time_;
	};
}

#endif //KIWI_TIMERNODE_H
