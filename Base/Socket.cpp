//
// Created by kiwi on 19-1-6.
//

#include "Socket.h"

Kiwi::Socket::Socket(int socket_fd) :
		_socket_fd_(socket_fd) {}

void Kiwi::Socket::connect(const Kiwi::InetAddress &addr)
{
	sockaddr_in tmp = addr.get_sockaddr_in();
	int retval;
	flag:
	retval = ::connect(_socket_fd_, (const sockaddr *) &tmp, sizeof(tmp));
	if (retval < 0)
	{
		switch (errno)
		{
			case EINTR:
				goto flag;
			default:
				std::cerr << "Socket connect error : " << errno << " " << strerror(errno) << std::endl;
				std::terminate();
		}
	}
}

void Kiwi::Socket::bind(const Kiwi::InetAddress &addr)
{
	sockaddr_in tmp = addr.get_sockaddr_in();
	int retval = ::bind(_socket_fd_, (const sockaddr *) &tmp, sizeof(tmp));
	if (retval < 0)
	{
		std::cerr << "Socket bind error : " << errno << " " << strerror(errno) << std::endl;
		std::terminate();
	}
}

void Kiwi::Socket::listen()
{
	int retval = ::listen(_socket_fd_, BACKLOG_SIZE);
	if (retval < 0)
	{
		std::cerr << "Socket listen error : " << errno << " " << strerror(errno) << std::endl;
		std::terminate();
	}
}

Kiwi::Socket Kiwi::Socket::accept(Kiwi::InetAddress &addr)
{
	sockaddr_in tmp = addr.get_sockaddr_in();
	socklen_t len = sizeof(tmp);
	int retval;
	flag:
	retval = ::accept(_socket_fd_, (sockaddr *) &tmp, &len);
	if (retval < 0)
	{
		switch (errno)
		{
			case EAGAIN:
			case EWOULDBLOCK:
			case EINTR:
				goto flag;
			default:
				std::cerr << "Socket accept error : " << errno << " " << strerror(errno) << std::endl;
				std::terminate();
		}
	}
	Socket res(retval);
	return res;
}

Kiwi::Socket::~Socket()
{
	close(_socket_fd_);
}
