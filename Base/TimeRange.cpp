//
// Created by kiwi on 19-1-21.
//

#include "TimeRange.h"

Kiwi::TimeRange Kiwi::TimeRange::now()
{
	struct timeval tv{};
	gettimeofday(&tv, nullptr);
	int64_t seconds = tv.tv_sec;
	int64_t micro_seconds = tv.tv_usec;
	TimeRange res(seconds * SECOND_RATIO + micro_seconds);
	return res;
}

Kiwi::TimeRange operator "" ms(uint64_t milliseconds)
{
	return Kiwi::TimeRange(milliseconds * Kiwi::TimeRange::MILLISECOND_RATIO);
}

Kiwi::TimeRange operator "" s(uint64_t seconds)
{
	return Kiwi::TimeRange(seconds * Kiwi::TimeRange::SECOND_RATIO);
}

Kiwi::TimeRange operator "" min(uint64_t minutes)
{
	return Kiwi::TimeRange(minutes * Kiwi::TimeRange::MINUTE_RATIO);
}

Kiwi::TimeRange operator "" h(uint64_t hours)
{
	return Kiwi::TimeRange(hours * Kiwi::TimeRange::HOUR_RATIO);
}

Kiwi::TimeRange operator "" day(uint64_t days)
{
	return Kiwi::TimeRange(days * Kiwi::TimeRange::DAY_RATIO);
}