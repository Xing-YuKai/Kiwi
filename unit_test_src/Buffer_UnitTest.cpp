//
// Created by kiwi on 19-1-27.
//

#include "../Kiwi/Base/Buffer.h"
#include <string>
#include <iostream>

int main()
{
	Kiwi::Buffer buffer;
	std::string data(1500,'a');

	std::cout<<"Initial"<<std::endl;
	std::cout<<"writable bytes : "<<buffer.get_writable_bytes()<<std::endl;
	std::cout<<"readable bytes : "<<buffer.get_readable_bytes()<<std::endl<<std::endl;

	buffer.append(data);

	std::cout<<"After appended 1500 bytes"<<std::endl;
	std::cout<<"writable bytes : "<<buffer.get_writable_bytes()<<std::endl;
	std::cout<<"readable bytes : "<<buffer.get_readable_bytes()<<std::endl<<std::endl;

	std::string val(buffer.peek());
	if(val==data)
		std::cout<<"peek data equals"<<std::endl<<std::endl;

	std::string ret = buffer.retrieve(1500);
	if(ret==data)
		std::cout<<"retrieve data equals"<<std::endl<<std::endl;

	std::cout<<"After retrieved 1500 bytes"<<std::endl;
	std::cout<<"writable bytes : "<<buffer.get_writable_bytes()<<std::endl;
	std::cout<<"readable bytes : "<<buffer.get_readable_bytes()<<std::endl<<std::endl;

	return 0;
}