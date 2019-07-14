#include "PipeIO.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>

#include <fcntl.h>
#include <unistd.h>
#include <memory>

#include <iostream>


namespace sync_io
{

    int PipeIO::INVALIAD_FD = -1;


    PipeIO::PipeIO( std::string const& name, Mode mode )
        :file_fd_(INVALIAD_FD)
        ,mode_(mode)
    {
        this->open(name, mode);
    }

    PipeIO::~PipeIO()
    {
        if(INVALIAD_FD != file_fd_)
            ::close(file_fd_);

        file_fd_ = INVALIAD_FD;
    }

    bool PipeIO::open( std::string const& name, Mode mode)
    {
        auto real_name = name.c_str();
        if( -1 == ::access(real_name, F_OK))
        {
            if(0 != ::mkfifo(real_name, 0777))
            {
                return false;
            }
        }

        auto real_mode = this->ioMode(mode);
        file_fd_  = ::open(real_name, real_mode);

        return INVALIAD_FD != file_fd_;
    }



    int PipeIO::ioMode(Mode mode) const
    {
        if(PipeIO_READ == mode)
            return O_RDONLY;

        if(PipeIO_WRITE == mode)
            return O_WRONLY;

        return -1;
    }


    bool PipeIO::write(std::string const& content )
    {
        return this->write(content.c_str(), content.size());
    }


    bool PipeIO::write( char const* const data, size_t len )
    {
        return len == ::write(file_fd_, data, len);
    }


    void PipeIO::read( std::string& buffer )
    {
        std::array<char, 1024> buf;
        size_t buf_size = ::read(file_fd_, buf.data(), buf.size());

        buffer = std::string(buf.data(), buf_size);
    }

    std::unique_ptr<std::string> PipeIO::read()
    {

        std::array<char, 1024> buf;
        int buf_size = ::read(file_fd_, buf.data(), buf.size());

        std::unique_ptr<std::string> read_buf;
        if(-1 != buf_size)
        {
            read_buf.reset(new std::string(buf.data(), buf_size));
        }

        return read_buf;
    }


}
