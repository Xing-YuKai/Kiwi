//
// Created by kiwi on 19-1-6.
//

#include "Socket.h"

using namespace Kiwi;

Socket::Socket(int socket_fd) :
		_socket_fd_(socket_fd) {}

void Socket::connect(const InetAddress &addr)
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

void Socket::bind(const InetAddress &addr)
{
	sockaddr_in tmp = addr.get_sockaddr_in();
	int retval = ::bind(_socket_fd_, (const sockaddr *) &tmp, sizeof(tmp));
	if (retval < 0)
	{
		std::cerr << "Socket bind error : " << errno << " " << strerror(errno) << std::endl;
		std::terminate();
	}
}

void Socket::listen()
{
	int retval = ::listen(_socket_fd_, BACKLOG_SIZE);
	if (retval < 0)
	{
		std::cerr << "Socket listen error : " << errno << " " << strerror(errno) << std::endl;
		std::terminate();
	}
}

Socket Socket::accept(InetAddress &addr)
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

void Socket::set_tcp_no_delay(bool on)
{
	int optval = on ? 1 : 0;
	int retval = setsockopt(_socket_fd_, IPPROTO_TCP, TCP_NODELAY, &optval, static_cast<socklen_t >(sizeof(optval)));
	if (retval < 0)
	{
		std::cerr << "Socket set_tcp_no_delay error : " << errno << " " << strerror(errno) << std::endl;
		std::terminate();
	}
}

void Socket::set_keep_alive(bool on)
{
	int optval = on ? 1 : 0;
	int retval = setsockopt(_socket_fd_, SOL_SOCKET, SO_KEEPALIVE, &optval, static_cast<socklen_t >(sizeof(optval)));
	if (retval < 0)
	{
		std::cerr << "Socket set_keep_alive error : " << errno << " " << strerror(errno) << std::endl;
		std::terminate();
	}
}

void Socket::set_reuse_address(bool on)
{
	int optval = on ? 1 : 0;
	int retval = setsockopt(_socket_fd_, SOL_SOCKET, SO_REUSEADDR, &optval, static_cast<socklen_t >(sizeof(optval)));
	if (retval < 0)
	{
		std::cerr << "Socket set_reuse_address error : " << errno << " " << strerror(errno) << std::endl;
		std::terminate();
	}
}

void Socket::set_reuse_port(bool on)
{
	int optval = on ? 1 : 0;
	int retval = setsockopt(_socket_fd_, SOL_SOCKET, SO_REUSEPORT, &optval, static_cast<socklen_t >(sizeof(optval)));
	if (retval < 0)
	{
		std::cerr << "Socket set_reuse_port error : " << errno << " " << strerror(errno) << std::endl;
		std::terminate();
	}
}

Socket::~Socket()
{
	close(_socket_fd_);
}