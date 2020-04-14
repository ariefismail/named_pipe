#ifndef __NAMED_PIPE_H__
#define __NAMED_PIPE_H__

#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <cerrno>
#include <poll.h>
#include <signal.h>

class CNamedPipe
{
public:
    CNamedPipe(const std::string& fifoFileName,int mode);
    ~CNamedPipe();

private:
    std::string m_fifoFileName;
    int m_fd;
    int m_mode;
};

#endif