//
// Created by kiwi on 19-1-10.
//

#include "InetAddress.h"

Kiwi::InetAddress::InetAddress()
{
	bzero(&_inet_addr_, sizeof(_inet_addr_));
	_inet_addr_.sin_family = AF_INET;
}

Kiwi::InetAddress::InetAddress(sockaddr_in sockaddr) :
		_inet_addr_(sockaddr) {}

Kiwi::InetAddress::InetAddress(uint16_t port, std::string address)
{
	bzero(&_inet_addr_, sizeof(_inet_addr_));
	_inet_addr_.sin_family = AF_INET;
}

void Kiwi::InetAddress::set_address(std::string address)
{
	int retval = inet_pton(AF_INET, address.data(), &_inet_addr_.sin_addr);
	if (retval == 0)
	{
		std::cerr << "InetAddress set_address error : input is not a valid presentation format" << std::endl;
		std::terminate();
	}
	if (retval < 0)
	{
		std::cerr << "InetAddress set_address error : " << errno << " " << strerror(errno) << std::endl;
		std::terminate();
	}
}

std::string Kiwi::InetAddress::get_address() const
{
	char buf[16];
	const char *retval = inet_ntop(AF_INET, &_inet_addr_.sin_addr, buf, 16);
	if (retval == nullptr)
	{
		std::cerr << "InetAddress get_address error : " << errno << " " << strerror(errno) << std::endl;
		std::terminate();
	}
	std::string res(buf);
	return res;
}

void Kiwi::InetAddress::set_port(uint16_t port)
{
	_inet_addr_.sin_port = htons(port);
}

uint16_t Kiwi::InetAddress::get_port() const
{
	return ntohs(_inet_addr_.sin_port);
}

sockaddr_in Kiwi::InetAddress::get_sockaddr_in() const
{
	return _inet_addr_;
}