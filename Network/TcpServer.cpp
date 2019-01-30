//
// Created by kiwi on 19-1-19.
//

#include "TcpServer.h"
#include "Acceptor.h"
#include "../Reactor/EventLoopPool.h"
#include "../Reactor/EventLoop.h"

using namespace Kiwi;
using namespace Kiwi::Type;

TcpServer::TcpServer(const unsigned int &io_thread_num, const InetAddress &acceptor_address, unsigned int thread_num)
{

}

void TcpServer::run()
{
	if(!_running_.load())
	{
		_acceptor_loop_ptr_->run_in_loop(std::bind(&Acceptor::listen, _acceptor_.get()));
		_acceptor_loop_ptr_->loop();
	}
}

TcpServer::~TcpServer()
{

}

void TcpServer::new_connection()
{

}

void TcpServer::remove_connection()
{

}

