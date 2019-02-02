//
// Created by kiwi on 19-1-10.
//

#include "../Kiwi/Reactor/EventLoop.h"
#include "../Kiwi/Reactor/Channel.h"
#include <iostream>
#include <sys/eventfd.h>
#include <cstring>
#include <zconf.h>


int create_eventfd()
{
	int fd = eventfd(0, EFD_CLOEXEC | EFD_NONBLOCK);
	if (fd < 0)
	{
		std::cerr << "create_eventfd error : " << errno << strerror(errno) << std::endl;
		std::terminate();
	}
	return fd;
}

void read_handler(int fd, Kiwi::TimeRange time)
{
	{
		uint64_t one = 1;
		ssize_t n = read(fd, &one, sizeof(one));
		if (n != sizeof(one))
		{
			std::cerr << "read " << n << "bytes instead of " << sizeof(one) << std::endl;
			std::terminate();
		}

		std::cout << "Read Handler " << std::endl
				  << "Receive time : " << time.get_micro_second_units() / Kiwi::TimeRange::SECOND_RATIO << std::endl
				  << "fd ID : " << fd << std::endl;
	};
}

void write_handler(int fd)
{
	uint64_t one = 1;
	ssize_t n = write(fd, &one, sizeof(one));
	if (n != sizeof(one))
	{
		std::cerr << "write " << n << "bytes instead of " << sizeof(one) << std::endl;
		std::terminate();
	}

	std::cout << "Write Handler " << std::endl
			  << "fd ID : " << fd << std::endl;
}

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

	int fd1 = create_eventfd();
	int fd2 = create_eventfd();
	int fd3 = create_eventfd();

	Kiwi::Channel ch1(&loop, fd1);
	Kiwi::Channel ch2(&loop, fd2);
	Kiwi::Channel ch3(&loop, fd3);

	ch1.set_read_handler(std::bind(read_handler, fd1, std::placeholders::_1));
	ch2.set_read_handler(std::bind(read_handler, fd2, std::placeholders::_1));
	ch3.set_read_handler(std::bind(read_handler, fd3, std::placeholders::_1));

	ch1.set_write_handler(std::bind(write_handler, fd1));
	ch2.set_write_handler(std::bind(write_handler, fd2));
	ch3.set_write_handler(std::bind(write_handler, fd3));

	ch1.enable_writing();
	ch1.enable_reading();
	ch1.update();
	ch2.enable_writing();
	ch2.enable_reading();
	ch2.update();
	ch3.enable_writing();
	ch3.enable_reading();
	ch3.update();

	//write_handler(fd1);
	//write_handler(fd2);
	//write_handler(fd3);

	loop.loop();
}

