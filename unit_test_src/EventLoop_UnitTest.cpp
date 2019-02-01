//
// Created by kiwi on 19-1-10.
//

#include "../Kiwi/Reactor/EventLoop.h"
#include <iostream>

int main()
{
	Kiwi::EventLoop loop;
	loop.run_in_loop([] { std::cout << "run_in_loop" << std::endl; });
	auto time = Kiwi::TimeRange::now();
	loop.run_after([time]
				   {
					   std::cout << Kiwi::TimeRange::now().cast_to_10_milliseconds() - time.cast_to_10_milliseconds()
								 << "ms10"
								 << std::endl;
				   }, 1_s);
	loop.loop();
}