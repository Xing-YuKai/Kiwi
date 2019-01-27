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

Kiwi::TimeRange operator "" ms(unsigned long long milliseconds)
{
	return Kiwi::TimeRange(milliseconds * Kiwi::TimeRange::MILLISECOND_RATIO);
}

Kiwi::TimeRange operator "" s(unsigned long long seconds)
{
	return Kiwi::TimeRange(seconds * Kiwi::TimeRange::SECOND_RATIO);
}

Kiwi::TimeRange operator "" min(unsigned long long minutes)
{
	return Kiwi::TimeRange(minutes * Kiwi::TimeRange::MINUTE_RATIO);
}

Kiwi::TimeRange operator "" h(unsigned long long hours)
{
	return Kiwi::TimeRange(hours * Kiwi::TimeRange::HOUR_RATIO);
}

Kiwi::TimeRange operator "" day(unsigned long long days)
{
	return Kiwi::TimeRange(days * Kiwi::TimeRange::DAY_RATIO);
}