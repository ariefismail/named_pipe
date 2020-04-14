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
    // formulatrix Driver CommunicationPort interface
    void Write(char *data, int32_t index, int32_t count);
    void Write(const char *data);

    int32_t Read(char *data, int32_t index, int32_t count);
    char *Read(int32_t count);

    bool HasData();
    // -------------------------------

    CNamedPipe(const std::string &txFifoFileName, const std::string &rxFifoFileName);
    ~CNamedPipe();

private:
    bool createFile(const std::string &fileName);

private:
    std::string m_txFifoFileName;
    std::string m_rxFifoFileName;
    int m_fd;
    int m_mode;
};

#endif