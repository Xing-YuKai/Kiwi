//
// Created by kiwi on 19-1-21.
//

#ifndef KIWI_TIMEPOINT_H
#define KIWI_TIMEPOINT_H

#include <sys/time.h>
#include <cstdint>
#include <iostream>

namespace Kiwi
{
	class TimeRange
	{
	public:
		explicit TimeRange(int64_t micro_seconds) : _micro_second_units_(micro_seconds) {}

		TimeRange operator "" ms(int64_t milliseconds) { return TimeRange(milliseconds * MILLISECOND_RATIO); }

		TimeRange operator "" s(int64_t seconds) { return TimeRange(seconds * SECOND_RATIO); }

		TimeRange operator "" min(int64_t minutes) { return TimeRange(minutes * MINUTE_RATIO); }

		TimeRange operator "" h(int64_t hours) { return TimeRange(hours * HOUR_RATIO); }

		TimeRange operator "" day(int64_t days) { return TimeRange(days * DAY_RATIO); }

		int64_t get_micro_second_units() const { return _micro_second_units_; }

		uint32_t cast_to_10_milliseconds() const;

		static TimeRange now();

	private:
		static const int64_t MILLISECOND_RATIO = 1000;
		static const int64_t SECOND_RATIO = 1000 * 1000;
		static const int64_t MINUTE_RATIO = 60 * 1000 * 1000;
		static const int64_t HOUR_RATIO = 60 * 60 * 1000 * 1000;
		static const int64_t DAY_RATIO = 24 * 60 * 60 * 1000 * 1000;
	private:
		int64_t _micro_second_units_;
	};
}

#endif //KIWI_TIMEPOINT_H
