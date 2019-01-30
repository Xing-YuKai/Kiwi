//
// Created by kiwi on 19-1-19.
//

#include "TcpConnection.h"


using namespace Kiwi;
using namespace Kiwi::Type;

TcpConnection::TcpConnection(Type::EventLoopPtr io_loop_ptr,
							 Type::TcpConnectionID id,
							 Socket socket,
							 const InetAddress &local_address,
							 const InetAddress &peer_address):

{

}

void TcpConnection::connection_established()
{

}

void TcpConnection::connection_destroyed()
{

}
