# Kiwi
Kiwi is a multi-thread network library implemented in Reactor design pattern  
[**中文文档**](./README_CH.md)  
## Build
---
* Change your directory to floder *Kiwi* and use **cmake** to build the library  
* The output path is located at *lib_release*  
* Change your directory to floder *example_src* and use **cmake** to build examples for this library  
* Change your directory to floder *unit_test_src* and use **cmake** to build unit tests for this library  
## Design Pattern
---
![Design Pattern](./model.png "Design Pattern")
## Usage
---
**This library is under namespace Kiwi::**  
### For server :
* `EventLoop()`  
  inital an eventloop  
  this class is included in file *Ractor/EventLoop.h*
* `InetAddress()`  
  inital an internet address  
  this class is included in file *Base/InetAddress.h*
* `void set_address(std::string address)`  
  set ipv4 address in dot-decimal format **eg : "127.0.0.1"**
* `void set_address_any()`  
  set ipv4 address to **INADDR_ANY**
* `void set_port(uint16_t port)`  
  set port number
* `TcpServer(EventLoop *base_loop, unsigned int io_thread_num, const InetAddress &acceptor_address)`  
  