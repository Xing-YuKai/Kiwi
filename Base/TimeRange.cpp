//
// Created by kiwi on 19-1-21.
//

#include "TimeRange.h"

using namespace Kiwi;

TimeRange TimeRange::now()
{
	struct timeval tv{};
	gettimeofday(&tv, nullptr);
	int64_t seconds = tv.tv_sec;
	int64_t micro_seconds = tv.tv_usec;
	TimeRange res(seconds * SECOND_RATIO + micro_seconds);
	return res;
}

TimeRange operator ""_ms(unsigned long long milliseconds)
{
	return TimeRange(milliseconds * TimeRange::MILLISECOND_RATIO);
}

TimeRange operator ""_s(unsigned long long seconds)
{
	return TimeRange(seconds * TimeRange::SECOND_RATIO);
}

TimeRange operator ""_min(unsigned long long minutes)
{
	return TimeRange(minutes * TimeRange::MINUTE_RATIO);
}

TimeRange operator ""_h(unsigned long long hours)
{
	return TimeRange(hours * TimeRange::HOUR_RATIO);
}

TimeRange operator ""_day(unsigned long long days)
{
	return TimeRange(days * TimeRange::DAY_RATIO);
}