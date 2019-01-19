cmake_minimum_required(VERSION 3.10)
project(Kiwi)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(ThreadPool_UnitTest UnitTest/ThreadPool_UnitTest.cpp ThreadPool/ThreadPool.h Base/Semaphore.cpp Base/Semaphore.h )
add_executable(EventLoop_UnitTest UnitTest/EventLoop_UnitTest.cpp Base/Socket.cpp Base/Socket.h Reactor/EventLoop.cpp Reactor/EventLoop.h Reactor/Channel.cpp Reactor/Channel.h Reactor/Epoll.cpp Reactor/Epoll.h Base/InetAddress.cpp Base/InetAddress.h)
add_executable(InetAddress_UnitTest UnitTest/InetAddress_UnitTest.cpp Base/InetAddress.cpp Base/InetAddress.h)
add_executable(EventLoopPool_UnitTest UnitTest/EventLoopPool_UnitTest.cpp Reactor/EventLoopPool.cpp Reactor/EventLoopPool.h)
add_executable(EchoClient example/EchoClient.cpp network/TcpClient.cpp network/TcpClient.h network/Connector.cpp network/Connector.h)
add_executable(EchoServer example/EchoServer.cpp network/TcpServer.cpp network/TcpServer.h network/Acceptor.cpp network/Acceptor.h network/TcpConnection.cpp network/TcpConnection.h)