//
// Created by kiwi on 19-1-5.
//

#include "Semaphore.h"

using namespace Kiwi;

Semaphore::Semaphore(const unsigned int &value, bool pshared)
{
	int retval = sem_init(&_sem_, pshared, value);
	if (retval < 0)
	{
		std::cerr << "Semaphore construct error : " << errno << " " << strerror(errno) << std::endl;
		std::terminate();
	}
}

void Semaphore::post()
{
	int retval = sem_post(&_sem_);
	if (retval < 0)
	{
		std::cerr << "Semaphore post error : " << errno << " " << strerror(errno) << std::endl;
		std::terminate();
	}
}

void Semaphore::wait()
{
	int retval;
	int errno_backup = errno;
	flag:
	retval = sem_wait(&_sem_);
	if (retval < 0)
	{
		switch (errno)
		{
			case EINTR:
				errno = errno_backup;
				goto flag;
			default:
				std::cerr << "Semaphore wait error : " << errno << " " << strerror(errno) << std::endl;
				std::terminate();
		}
	}
}

bool Semaphore::try_wait()
{
	int retval;
	int errno_backup = errno;
	flag:
	retval = sem_trywait(&_sem_);
	if (retval < 0)
	{
		switch (errno)
		{
			case EAGAIN:
				errno = errno_backup;
				return false;
			case EINTR:
				errno = errno_backup;
				goto flag;
			default:
				std::cerr << "Semaphore try_wait error : " << errno << " " << strerror(errno) << std::endl;
				std::terminate();
		}
	}
	return true;
}

int Semaphore::get_value()
{
	int res;
	int retval = sem_getvalue(&_sem_, &res);
	if (retval < 0)
	{
		std::cerr << "Semaphore get_value error : " << errno << " " << strerror(errno) << std::endl;
		std::terminate();
	}
	return res;
}

Semaphore::~Semaphore()
{
	int retval = sem_destroy(&_sem_);
	if (retval < 0)
	{
		std::cerr << "Semaphore destruct error : " << errno << " " << strerror(errno) << std::endl;
		std::terminate();
	}
}
