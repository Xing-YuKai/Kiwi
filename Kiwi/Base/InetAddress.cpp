//
// Created by kiwi on 19-1-10.
//

#include "InetAddress.h"

using namespace Kiwi;

InetAddress::InetAddress()
{
	bzero(&_inet_addr_, sizeof(_inet_addr_));
	_inet_addr_.sin_family = AF_INET;
}

InetAddress::InetAddress(sockaddr_in sockaddr) :
		_inet_addr_(sockaddr) {}

InetAddress::InetAddress(uint16_t port, std::string address)
{
	bzero(&_inet_addr_, sizeof(_inet_addr_));
	_inet_addr_.sin_family = AF_INET;
}

void InetAddress::set_address(std::string address)
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

void InetAddress::set_address_any()
{
	_inet_addr_.sin_addr.s_addr = INADDR_ANY;
}

std::string InetAddress::get_address() const
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

void InetAddress::set_port(uint16_t port)
{
	_inet_addr_.sin_port = htons(port);
}

uint16_t InetAddress::get_port() const
{
	return ntohs(_inet_addr_.sin_port);
}