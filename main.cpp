#include <iostream>
#include <iomanip>
#include <cstdint>
#include <fcntl.h>
#include <chrono>
#include <thread>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <cerrno>
#include <sys/select.h>
#include <poll.h>
#include <signal.h>

#include "NamedPipe.h"

int main(int argc, char *argv[])
{
    
    CNamedPipe np("txFifo","rxFifo");
    
    char keyData[10];
    // std::cin>>std::setw(sizeof(keyData))>>keyData;
    // std::cout<<keyData;
    np.Connect();
    while(1)
    {
        std::this_thread::sleep_for(std::chrono::microseconds(100));
    }
    return 0;

}
