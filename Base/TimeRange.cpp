//
// Created by kiwi on 19-1-21.
//

#include "TimeRange.h"

uint32_t Kiwi::TimeRange::cast_to_10_milliseconds() const
{
	int64_t tmp = _micro_second_units_ / MILLISECOND_RATIO / 10;
	if (tmp > UINT32_MAX)
	{
		std::cerr << "TimeRange cast_to_milliseconds error : " << "Overflow" << std::endl;
		std::terminate();
	}
	uint32_t res = static_cast<uint32_t >(tmp);
	return res;
}

Kiwi::TimeRange Kiwi::TimeRange::now()
{
	struct timeval tv;
	gettimeofday(&tv, nullptr);
	int64_t seconds = tv.tv_sec;
	int64_t micro_seconds = tv.tv_usec;
	TimeRange res(seconds * SECOND_RATIO + micro_seconds);
	return res;
}
