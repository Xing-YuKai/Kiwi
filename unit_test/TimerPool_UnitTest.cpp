//
// Created by kiwi on 19-1-21.
//

#include "../Kiwi/Base/TimerPool.h"
#include <iostream>

using namespace std;

int main()
{
	Kiwi::TimerPool pool;
	Kiwi::TimeRange nowtime;

	Kiwi::TimeRange time1 = Kiwi::TimeRange::now();

	nowtime = Kiwi::TimeRange::now();
	pool.start_timer(1_s, [nowtime]
	{
		Kiwi::TimeRange current = Kiwi::TimeRange::now();
		std::cout << "Timer1 " << current.get_micro_second_units() - nowtime.get_micro_second_units() << "us" << std::endl;
	});

	nowtime = Kiwi::TimeRange::now();
	pool.start_timer(2_s, [nowtime]
	{
		Kiwi::TimeRange current = Kiwi::TimeRange::now();
		std::cout << "Timer2 " << current.get_micro_second_units() - nowtime.get_micro_second_units() << "us" << std::endl;
	});

	nowtime = Kiwi::TimeRange::now();
	pool.start_timer(3_s, [nowtime]
	{
		Kiwi::TimeRange current = Kiwi::TimeRange::now();
		std::cout << "Timer3 " << current.get_micro_second_units() - nowtime.get_micro_second_units() << "us" << std::endl;
	});

	nowtime = Kiwi::TimeRange::now();
	pool.start_timer(4_s, [nowtime]
	{
		Kiwi::TimeRange current = Kiwi::TimeRange::now();
		std::cout << "Timer4 " << current.get_micro_second_units() - nowtime.get_micro_second_units() << "us" << std::endl;
	});

	nowtime = Kiwi::TimeRange::now();
	pool.start_timer(100_ms, [nowtime]
	{
		Kiwi::TimeRange current = Kiwi::TimeRange::now();
		std::cout << "Timer5 " << current.get_micro_second_units() - nowtime.get_micro_second_units() << "us" << std::endl;
	});

	nowtime = Kiwi::TimeRange::now();
	pool.start_timer(90_ms, [nowtime]
	{
		Kiwi::TimeRange current = Kiwi::TimeRange::now();
		std::cout << "Timer6 " << current.get_micro_second_units() - nowtime.get_micro_second_units() << "us" << std::endl;
	});

	nowtime = Kiwi::TimeRange::now();
	pool.start_timer(80_ms, [nowtime]
	{
		Kiwi::TimeRange current = Kiwi::TimeRange::now();
		std::cout << "Timer7 " << current.get_micro_second_units() - nowtime.get_micro_second_units() << "us" << std::endl;
	});

	Kiwi::Type::TimerID timer8 = pool.start_timer(200_ms, [nowtime]
	{
		std::cout << "Timer8 stop fail " << std::endl;
	});
	pool.stop_timer(timer8);

	while(true)
	{
		pool.update();
	}

	return 0;
}