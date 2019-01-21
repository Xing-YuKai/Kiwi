//
// Created by kiwi on 19-1-21.
//

#ifndef KIWI_TIMEPOINT_H
#define KIWI_TIMEPOINT_H

#include <sys/time.h>
#include <cstdint>

namespace Kiwi
{
	class TimePoint
	{
	public:
		TimePoint(int64_t micro_second_since_epoch) : _micro_second_since_epoch_(micro_second_since_epoch) {}

		int64_t time_since_epoch() const { return _micro_second_since_epoch_; }

		static TimePoint now();

	private:
		static const int64_t MICRO_SECOND_RATIO = 1000 * 1000;
		int64_t _micro_second_since_epoch_;
	};
}

#endif //KIWI_TIMEPOINT_H
