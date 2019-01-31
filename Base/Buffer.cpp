//
// Created by kiwi on 19-1-27.
//

#include "Buffer.h"

using namespace Kiwi;
using namespace Kiwi::Type;

Buffer::Buffer(size_t initial_size) :
		_buffer_(initial_size + PREPEND_SIZE),
		_read_index_(PREPEND_SIZE),
		_write_index_(PREPEND_SIZE) {}

void Buffer::swap(Buffer &rhs)
{
	_buffer_.swap(rhs._buffer_);
	std::swap(_read_index_, rhs._read_index_);
	std::swap(_write_index_, rhs._write_index_);
}

void Buffer::append(const std::string &data)
{
	if (get_writable_bytes() < data.size())
		make_space(data.size());

	std::copy(data.begin(), data.end(), _buffer_.begin() + _write_index_);

	_write_index_ += data.size();
}

std::string Buffer::retrieve(size_t len)
{
	size_t readable_bytes = get_readable_bytes();
	if (len > readable_bytes)
		len = readable_bytes;
	std::string res(peek(), len);
	_read_index_ += len;
}

ssize_t Buffer::append_from(int fd)
{
	return 0;
}

void Buffer::make_space(size_t data_len)
{
	size_t writable_bytes = get_writable_bytes();
	size_t readable_bytes = get_readable_bytes();
	size_t prependable_bytes = get_prependable_bytes();
	if (writable_bytes + readable_bytes - PREPEND_SIZE < data_len)
	{
		_buffer_.resize(_write_index_ + data_len);
	} else
	{
		auto begin_itr = _buffer_.begin();
		std::copy(begin_itr + _read_index_, begin_itr + _write_index_, begin_itr + PREPEND_SIZE);
		_read_index_ = PREPEND_SIZE;
		_write_index_ = _read_index_ + readable_bytes;
	}
}
