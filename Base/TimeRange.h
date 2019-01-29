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
		explicit TimeRange(uint64_t micro_seconds = 0) : _micro_second_units_(micro_seconds) {}

		uint64_t get_micro_second_units() const { return _micro_second_units_; }

		uint64_t cast_to_10_milliseconds() const { return _micro_second_units_ / MILLISECOND_RATIO / 10; }

		static TimeRange now();

	public:
		static const uint64_t MILLISECOND_RATIO = 1000ULL;
		static const uint64_t SECOND_RATIO = 1000ULL * 1000ULL;
		static const uint64_t MINUTE_RATIO = 60ULL * 1000ULL * 1000ULL;
		static const uint64_t HOUR_RATIO = 60ULL * 60ULL * 1000ULL * 1000ULL;
		static const uint64_t DAY_RATIO = 24ULL * 60ULL * 60ULL * 1000ULL * 1000ULL;
	private:
		uint64_t _micro_second_units_;
	};
}
Kiwi::TimeRange operator ""_ms(unsigned long long milliseconds);
Kiwi::TimeRange operator ""_s(unsigned long long seconds);
Kiwi::TimeRange operator ""_min(unsigned long long minutes);
Kiwi::TimeRange operator ""_h(unsigned long long hours);
Kiwi::TimeRange operator ""_day(unsigned long long days);

#endif //KIWI_TIMEPOINT_H
