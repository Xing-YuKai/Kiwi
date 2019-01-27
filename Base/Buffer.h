//
// Created by kiwi on 19-1-27.
//

#ifndef KIWI_BUFFER_H
#define KIWI_BUFFER_H

#include <vector>
#include "Types.h"
namespace Kiwi
{
	class Buffer
	{
	public:
		Buffer(size_t initial_size = 1024);

		size_t get_readable_bytes()const;
		size_t get_writable_bytes()const;
		size_t get_prependable_bytes()const;


		~Buffer();

	private:
		std::vector<char> _buffer_;
		size_t _read_index_;
		size_t _write_index_;
	};
}

#endif //KIWI_BUFFER_H
