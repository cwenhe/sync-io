#pragma once

#include <string>
#include <memory>

namespace sync_io
{
    class SyncIO 
    {
        public:
            virtual bool write(std::string const& content ) = 0;

            virtual bool write( char const* const data, size_t len ) = 0;

            virtual void read( std::string& buffer ) = 0;

            virtual std::unique_ptr<std::string> read() = 0;


            SyncIO()
            {
            }

            virtual ~SyncIO()
            {
            }

            SyncIO( SyncIO const& ) = delete;


            SyncIO& operator=(SyncIO const&) = delete;


    };
}

