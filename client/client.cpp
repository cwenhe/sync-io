#include <iostream>

#include "PipeIO.h"

int main()
{

    using namespace sync_io;

    std::unique_ptr<SyncIO> io(new PipeIO("./pips", PipeIO::PipeIO_READ));

    auto read_files = io->read();
    std::cout<<"recieve msg:"<<*read_files<<std::endl;




    return 0;
}
