//
// Created by kiwi on 19-1-21.
//

#include "../Base/TimerPool.h"
#include <iostream>

using namespace std;

int main()
{
	Kiwi::TimerPool pool;
	Kiwi::TimeRange nowtime;

	Kiwi::TimeRange time1 = Kiwi::TimeRange::now();

	nowtime = Kiwi::TimeRange::now();
	pool.start_timer(1s, [nowtime]
	{
		Kiwi::TimeRange current = Kiwi::TimeRange::now();
		std::cout << "Timer1 " << current.get_micro_second_units() - nowtime.get_micro_second_units() << "us" << std::endl;
	});

	nowtime = Kiwi::TimeRange::now();
	pool.start_timer(2s, [nowtime]
	{
		Kiwi::TimeRange current = Kiwi::TimeRange::now();
		std::cout << "Timer2 " << current.get_micro_second_units() - nowtime.get_micro_second_units() << "us" << std::endl;
	});

	nowtime = Kiwi::TimeRange::now();
	pool.start_timer(3s, [nowtime]
	{
		Kiwi::TimeRange current = Kiwi::TimeRange::now();
		std::cout << "Timer3 " << current.get_micro_second_units() - nowtime.get_micro_second_units() << "us" << std::endl;
	});

	nowtime = Kiwi::TimeRange::now();
	pool.start_timer(4s, [nowtime]
	{
		Kiwi::TimeRange current = Kiwi::TimeRange::now();
		std::cout << "Timer4 " << current.get_micro_second_units() - nowtime.get_micro_second_units() << "us" << std::endl;
	});

	nowtime = Kiwi::TimeRange::now();
	pool.start_timer(100ms, [nowtime]
	{
		Kiwi::TimeRange current = Kiwi::TimeRange::now();
		std::cout << "Timer5 " << current.get_micro_second_units() - nowtime.get_micro_second_units() << "us" << std::endl;
	});

	nowtime = Kiwi::TimeRange::now();
	pool.start_timer(90ms, [nowtime]
	{
		Kiwi::TimeRange current = Kiwi::TimeRange::now();
		std::cout << "Timer6 " << current.get_micro_second_units() - nowtime.get_micro_second_units() << "us" << std::endl;
	});

	nowtime = Kiwi::TimeRange::now();
	pool.start_timer(80ms, [nowtime]
	{
		Kiwi::TimeRange current = Kiwi::TimeRange::now();
		std::cout << "Timer7 " << current.get_micro_second_units() - nowtime.get_micro_second_units() << "us" << std::endl;
	});

	Kiwi::TimerID timer8 = pool.start_timer(200ms, [nowtime]
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