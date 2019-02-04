//
// Created by kiwi on 19-1-5.
//

#ifndef KIWI_SEMAPHORE_H
#define KIWI_SEMAPHORE_H

#include <semaphore.h>
#include <iostream>
#include <cerrno>
#include <cstring>

namespace Kiwi
{
	class Semaphore
	{
	public:
		Semaphore(const unsigned int &value = 0, bool pshared = false);

		void post();

		void wait();

		bool try_wait();

		int get_value();

		~Semaphore();

		Semaphore(const Semaphore &) = delete;

		Semaphore &operator=(const Semaphore &) = delete;

	private:
		sem_t _sem_;
	};
}

#endif //KIWI_SEMAPHORE_H
