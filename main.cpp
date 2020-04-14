#include <iostream>
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
    CNamedPipe("TxFifo",O_WRONLY);
    return 0;

}
