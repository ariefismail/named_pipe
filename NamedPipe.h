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
#include <thread>
#include <mutex>
#include <atomic>
#include <queue>
#include <condition_variable>

class CNamedPipe
{
public:
    // formulatrix Driver CommunicationPort interface
    void Write(char *data, int32_t index, int32_t count);
    void Write(const char *data);

    int32_t Read(char *data, int32_t index, int32_t count);
    char *Read(int32_t count);

    bool HasData();

    void Connect();
    void Disconnect();

    int32_t BytesInReadQueue();
    // -------------------------------

    CNamedPipe(const std::string &txFifoFileName, const std::string &rxFifoFileName);
    ~CNamedPipe();

private:
    void executeRx(); // threading!
    void executeTx(); // threading!
    bool createFile(const std::string &fileName);

private:
    std::string m_txFifoFileName;
    std::string m_rxFifoFileName;
    std::thread m_txThread;
    std::thread m_rxThread;
    int m_txFd;
    int m_rxFd;
    // queue<char>m_txQueue;
    std::queue<char> m_rxQueue;
    std::condition_variable m_txGo;
    std::atomic<bool> m_isOpen;
};

#endif