#include "SyncIO.h"

namespace sync_io
{
    class PipeIO : public SyncIO
    {
        public:
            enum Mode
            {
                PipeIO_INVALID,
                PipeIO_READ,
                PipeIO_WRITE,
            };


            PipeIO( std::string const& name , Mode mode );

            ~PipeIO();

            virtual bool write(std::string const& content ) override;

            virtual bool write( char const* const data, size_t len ) override;

            virtual void read( std::string& buffer ) override;

            virtual std::unique_ptr<std::string> read() override;

        private:
             bool open(std::string const& name, Mode mode);

             int ioMode(Mode mode) const;


        private:
            int file_fd_;
            enum Mode mode_;
            

            static int INVALIAD_FD;
    };
}


