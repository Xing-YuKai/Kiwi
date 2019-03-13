//
// Created by kiwi on 19-1-11.
//

#include "../Kiwi/Base/InetAddress.h"

using namespace std;

int main()
{
	string addr;
	cin >> addr;
	uint16_t port;
	cin >> port;

	Kiwi::InetAddress address;
	address.set_address(addr);
	address.set_port(port);

	cout << address.get_address() << endl;
	cout << address.get_port() << endl;

	if (address.get_address() == addr)
		cout << "address equal" << endl;
	if (address.get_port() == port)
		cout << "port equal" << endl;

	return 0;
}