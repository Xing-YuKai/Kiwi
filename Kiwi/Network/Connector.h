//
// Created by kiwi on 19-1-19.
//

#ifndef KIWI_CONNECTOR_H
#define KIWI_CONNECTOR_H

#include "../Base/Types.h"

namespace Kiwi
{
	class Connector
	{
	public:
		Connector();

		~Connector();

		Connector(const Connector &) = delete;

		Connector &operator=(const Connector &) = delete;
	};
}


#endif //KIWI_CONNECTOR_H
