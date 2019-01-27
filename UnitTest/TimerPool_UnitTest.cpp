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
	nowtime = Kiwi::TimeRange::now();
	pool.start_timer(2s, [nowtime]
	{
		Kiwi::TimeRange current = Kiwi::TimeRange::now();
		std::cout << "Timer1" << current.get_micro_second_units() - nowtime.get_micro_second_units() << "us" << std::endl;
	});
	pool.update();

	nowtime = Kiwi::TimeRange::now();
	pool.start_timer(1s, [nowtime]
	{
		Kiwi::TimeRange current = Kiwi::TimeRange::now();
		std::cout << "Timer2" << current.get_micro_second_units() - nowtime.get_micro_second_units() << "us" << std::endl;
	});
	pool.update();

	nowtime = Kiwi::TimeRange::now();
	pool.start_timer(300ms, [nowtime]
	{
		Kiwi::TimeRange current = Kiwi::TimeRange::now();
		std::cout << "Timer3" << current.get_micro_second_units() - nowtime.get_micro_second_units() << "us" << std::endl;
	});
	nowtime = Kiwi::TimeRange::now();
	pool.start_timer(600ms, [nowtime]
	{
		Kiwi::TimeRange current = Kiwi::TimeRange::now();
		std::cout << "Timer4" << current.get_micro_second_units() - nowtime.get_micro_second_units() << "us" << std::endl;
	});
	pool.update();
	return 0;
}