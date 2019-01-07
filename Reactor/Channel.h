//
// Created by kiwi on 19-1-7.
//

#ifndef KIWI_CHANNEL_H
#define KIWI_CHANNEL_H

#include <functional>

namespace Kiwi
{
	class Channel
	{
	public:
		using EventHandler = std::function<void()>;

		Channel();

		~Channel();

		Channel(const Channel &) = delete;

		Channel &operator=(const Channel &) = delete;

	private:

	};
}

#endif //KIWI_CHANNEL_H
