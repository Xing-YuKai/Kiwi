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
    return res;
}

std::string Buffer::retrieve_by_flag(const std::string &flag)
{
    auto itr = std::search(_buffer_.cbegin() + _read_index_, _buffer_.cbegin() + _read_index_ + _write_index_,
                           flag.cbegin(), flag.cend());
    if (itr == _buffer_.cend())
        return std::string();
    return retrieve(itr - _buffer_.cbegin() + _read_index_);
}

ssize_t Buffer::append_from(int fd)
{
    flag:
    std::string extra_buffer(65536, 0);
    struct iovec io_vec[2];
    size_t writable_bytes = get_writable_bytes();

    io_vec[0].iov_base = _buffer_.begin().base() + _write_index_;
    io_vec[0].iov_len = writable_bytes;
    io_vec[1].iov_base = extra_buffer.begin().base();
    io_vec[1].iov_len = extra_buffer.size();

    int io_counter = (writable_bytes < extra_buffer.size()) ? 2 : 1;
    ssize_t retval = readv(fd, io_vec, io_counter);
    if (retval < 0)
    {
        switch (errno)
        {
            case EWOULDBLOCK:
                return retval;
            case EINTR:
                goto flag;
            default:
                std::cerr << "Buffer append_from error : " << errno << " " << strerror(errno) << std::endl;
        }
    } else if (static_cast<size_t>(retval) <= writable_bytes)
    {
        _write_index_ += retval;
    } else
    {
        _write_index_ = _buffer_.size();
        append(extra_buffer);
    }
    return retval;
}

ssize_t Buffer::retrieve_to(int fd)
{
    flag:
    ssize_t retval = write(fd, peek(), get_readable_bytes());
    if (retval >= 0)
    {
        _read_index_ += retval;
    } else
    {
        switch (errno)
        {
            case EWOULDBLOCK:
                return retval;
            case EINTR:
                goto flag;
            default:
                std::cerr << "Buffer retrieve_to error : " << errno << " " << strerror(errno) << std::endl;
        }
    }
    return retval;
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