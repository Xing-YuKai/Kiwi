//
// Created by kiwi on 19-1-19.
//

#include "../Kiwi/Reactor/EventLoopPool.h"
#include "../Kiwi/Reactor/EventLoop.h"

int main()
{
	Kiwi::EventLoop base_loop;
	Kiwi::EventLoopPool pool(&base_loop, 4);

	auto loop1 = pool.get_loop();
	auto loop2 = pool.get_loop();
	auto loop3 = pool.get_loop();
	auto loop4 = pool.get_loop();
	auto loop5 = pool.get_loop();
	auto loop6 = pool.get_loop();

	std::cout << loop1 << std::endl;
	std::cout << loop2 << std::endl;
	std::cout << loop3 << std::endl;
	std::cout << loop4 << std::endl;
	std::cout << loop5 << std::endl;
	std::cout << loop6 << std::endl;

	return 0;
}