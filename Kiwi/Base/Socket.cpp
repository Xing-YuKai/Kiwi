//
// Created by kiwi on 19-1-6.
//

#include "Socket.h"

using namespace Kiwi;

Socket Socket::nonblocking_socket()
{
	int retval = ::socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, IPPROTO_TCP);
	if (retval < 0)
	{
		std::cerr << "Socket nonblocking_socket error : " << errno << " " << strerror(errno) << std::endl;
		std::terminate();
	}
	return Socket(retval);
}

Socket::Socket(int socket_fd) :
		_socket_fd_(socket_fd) {}

void Socket::connect(const InetAddress &addr)
{
	sockaddr_in tmp = addr._inet_addr_;
	int retval;
	int errno_backup = errno;
	flag:
	retval = ::connect(_socket_fd_, static_cast<const sockaddr *>(&tmp), sizeof(tmp));
	if (retval < 0)
	{
		switch (errno)
		{
			case EINTR:
				errno = errno_backup;
				goto flag;
			default:
				std::cerr << "Socket connect error : " << errno << " " << strerror(errno) << std::endl;
				std::terminate();
		}
	}
}

void Socket::bind(const InetAddress &addr)
{
	sockaddr_in tmp = addr._inet_addr_;
	int retval = ::bind(_socket_fd_, static_cast<const sockaddr *>(&tmp), sizeof(tmp));
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

void Socket::close()
{
	::close(_socket_fd_);
}

Socket Socket::accept(InetAddress &addr)
{
	sockaddr_in tmp = addr._inet_addr_;
	socklen_t len = sizeof(tmp);
	int retval;
	int errno_backup = errno;
	flag:
	retval = ::accept(_socket_fd_, static_cast<sockaddr *>(&tmp), &len);
	if (retval < 0)
	{
		switch (errno)
		{
			case EWOULDBLOCK:
				errno = errno_backup;
				return Socket(-1);
			case EINTR:
				goto flag;
			default:
				std::cerr << "Socket accept error : " << errno << " " << strerror(errno) << std::endl;
				std::terminate();
		}
	}
	addr._inet_addr_ = tmp;
	Socket res(retval);
	return res;
}

void Socket::shutdown_write()
{
	int retval = shutdown(_socket_fd_, SHUT_WR);
	if (retval < 0)
	{
		std::cerr << "Socket shutdown_write error : " << errno << " " << strerror(errno) << std::endl;
		std::terminate();
	}
}

void Socket::shutdown_read()
{
	int retval = shutdown(_socket_fd_, SHUT_RD);
	if (retval < 0)
	{
		std::cerr << "Socket shutdown_read error : " << errno << " " << strerror(errno) << std::endl;
		std::terminate();
	}
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

InetAddress Socket::get_local_address() const
{
	sockaddr_in addr;
	bzero(&addr, sizeof(addr));
	socklen_t len = sizeof(addr);
	int retval = getsockname(_socket_fd_, static_cast<sockaddr *>(&addr), &len);
	if (retval < 0)
	{
		std::cerr << "Socket get_local_address error : " << errno << " " << strerror(errno) << std::endl;
		std::terminate();
	}
	InetAddress res(addr);
	return res;
}

InetAddress Socket::get_peer_address() const
{
	sockaddr_in addr;
	bzero(&addr, sizeof(addr));
	socklen_t len = sizeof(addr);
	int retval = getpeername(_socket_fd_, static_cast<sockaddr *>(&addr), &len);
	if (retval < 0)
	{
		std::cerr << "Socket get_local_address error : " << errno << " " << strerror(errno) << std::endl;
		std::terminate();
	}
	InetAddress res(addr);
	return res;
}

int Socket::get_socket_error() const
{
	int optval;
	socklen_t optlen = sizeof(optval);
	int retval = getsockopt(_socket_fd_, SOL_SOCKET, SO_ERROR, &optval, &optlen);
	if (retval < 0)
		return errno;
	else
		return optval;
}