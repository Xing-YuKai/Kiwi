//
// Created by kiwi on 19-1-21.
//

#include "TimePoint.h"

Kiwi::TimePoint Kiwi::TimePoint::now()
{
	struct timeval tv;
	gettimeofday(&tv, nullptr);
	int64_t seconds = tv.tv_sec;
	int64_t micro_seconds = tv.tv_usec;
	TimePoint res(seconds * MICRO_SECOND_RATIO + micro_seconds);
	return res;
}
