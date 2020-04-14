#include "NamedPipe.h"

CNamedPipe::CNamedPipe(const std::string &txFifoFileName, const std::string &rxFifoFileName)
{
    m_txFifoFileName = "/tmp/"; // store our fifo in RAM pls
    m_rxFifoFileName = "/tmp/"; // store our fifo in RAM pls
    m_txFifoFileName.append(txFifoFileName);
    m_rxFifoFileName.append(rxFifoFileName);
    createFile(m_txFifoFileName);
    createFile(m_rxFifoFileName);

    // initial value
    m_txFd = 0;
    m_rxFd = 0;
    m_isOpen = false;
}

CNamedPipe::~CNamedPipe()
{
    Disconnect();
}

void CNamedPipe::Write(char *data, int32_t index, int32_t count)
{
    if (!m_isOpen)
        return;
}

void CNamedPipe::Write(const char *data)
{
    if (!m_isOpen)
        return;
    write(m_txFd, data, strlen(data));
}

int32_t CNamedPipe::Read(char *data, int32_t index, int32_t count)
{
    if (!m_isOpen)
        return 0;
}

char *CNamedPipe::Read(int32_t count)
{
    if (!m_isOpen)
        return NULL;
}

bool CNamedPipe::HasData()
{
    if (!m_isOpen)
        return false;
}

void CNamedPipe::Connect()
{
    if (m_isOpen)
        return;
    m_isOpen.store(true);
    std::cout<<"isopen: "<<m_isOpen<<'\n';
    m_txThread = std::thread(&CNamedPipe::executeTx, this);
    m_rxThread = std::thread(&CNamedPipe::executeRx, this);
}

void CNamedPipe::Disconnect()
{
    if (!m_isOpen)
        return;
    m_isOpen = false;
    m_txThread.join();
    m_rxThread.join();
    close(m_rxFd);
    close(m_txFd);
}

int32_t CNamedPipe::BytesInReadQueue()
{
    if (!m_isOpen)
        return 0;
}

void CNamedPipe::executeRx()
{
    m_rxFd = open(m_rxFifoFileName.data(), O_RDONLY);
    if (m_rxFd < 0)
    {
        std::perror("Open RX error");
        return;
    }
    std::cout << "RX Connected!\n";

    int count;
    char data[10];
    memset(data,0,sizeof(data));
    struct pollfd fds;
    fds.fd = m_rxFd;
    fds.events = POLLIN;
    std::cout<<m_isOpen<<'\n';
    std::cout<<"hehe\n";
    while (m_isOpen)
    {
        switch (poll(&fds, 1, 100))
        {
        case -1:
            std::perror("rx thread error");
            break;

        case 0:
            std::cout << "no data\n";
            break;

        default:
            count=read(m_rxFd,data,10);
            if(count<0)
                std::perror("read error");
            else
                printf("%s,",data);
            memset(data,0,sizeof(data));
            break;
        }
    }
}

void CNamedPipe::executeTx()
{
    m_txFd = open(m_txFifoFileName.data(), O_WRONLY);
    if (m_txFd < 0)
    {
        std::perror("Open TX error");
        return;
    }
    std::cout << "TX Connected!\n";

    // while(m_isOpen)
    // {
    //     m_txGo.wait();
    // }
}

bool CNamedPipe::createFile(const std::string &fileName)
{
    if (mkfifo(fileName.data(), 0666) < 0)
    {
        if (errno != EEXIST)
        {
            std::perror("make fifo error");
            return false;
        }
        std::cout << "file already created " << fileName << '\n';
    }
    else
    {
        std::cout << "file created " << fileName << '\n';
    }
    return true;
}