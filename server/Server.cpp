#include "PipeIO.h"



int main(int argc, char **argv)
{
    using namespace sync_io;

    std::unique_ptr<SyncIO> io(new PipeIO("./pips", PipeIO::PipeIO_WRITE));
    io->write(std::string("hello client"));

    return 0;
}

