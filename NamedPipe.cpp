#include "NamedPipe.h"

CNamedPipe::CNamedPipe(const std::string &txFifoFileName, const std::string &rxFifoFileName)
{
    m_txFifoFileName = "/tmp/"; // store our fifo in RAM pls
    m_rxFifoFileName = "/tmp/"; // store our fifo in RAM pls
    m_txFifoFileName.append(txFifoFileName);
    m_rxFifoFileName.append(rxFifoFileName);
    createFile(m_txFifoFileName);
    createFile(m_rxFifoFileName);
}

CNamedPipe::~CNamedPipe()
{
}

void CNamedPipe::Write(char *data, int32_t index, int32_t count)
{

}
    
void CNamedPipe::Write(const char *data)
{

}

int32_t CNamedPipe::Read(char *data, int32_t index, int32_t count)
{

}
    
char *CNamedPipe::Read(int32_t count)
{

}

bool CNamedPipe::HasData()
{

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