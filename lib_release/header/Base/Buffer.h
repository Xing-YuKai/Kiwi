//
// Created by kiwi on 19-1-27.
//

#ifndef KIWI_BUFFER_H
#define KIWI_BUFFER_H

#include <vector>
#include <string>
#include <sys/uio.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <algorithm>
#include "Types.h"

namespace Kiwi
{
    //class Buffer is non-thread-safe
    class Buffer
    {
    public:
        Buffer(size_t initial_size = INITIAL_SIZE);

        size_t get_readable_bytes() const { return _write_index_ - _read_index_; }

        size_t get_writable_bytes() const { return _buffer_.size() - _write_index_; }

        size_t get_prependable_bytes() const { return _read_index_; }

        const char *peek() const { return _buffer_.cbegin().base() + _read_index_; }

        void swap(Buffer &rhs);

        void append(const std::string &data);

        std::string retrieve(size_t len);

        std::string retrieve_by_flag(const std::string &flag);

        ssize_t append_from(int fd);

        ssize_t retrieve_to(int fd);

        ~Buffer() = default;

    private:
        void make_space(size_t data_len);

    private:
        static const size_t PREPEND_SIZE = 8;
        static const size_t INITIAL_SIZE = 1024;
        std::vector<char> _buffer_;
        size_t _read_index_;
        size_t _write_index_;
    };
}

#endif //KIWI_BUFFER_H
