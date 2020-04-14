#include "NamedPipe.h"

CNamedPipe::CNamedPipe(const std::string& fifoFileName,int mode)
{
    m_fifoFileName = fifoFileName;
    m_mode = mode;
    if (mkfifo(m_fifoFileName.data(), 0666) < 0)
    {
        if (errno != EEXIST)
        {
            std::perror("make fifo error");
            return;
        }
        std::cout << "file already created" << m_fifoFileName << '\n';
    }
    else
    {
        std::cout << "file created" << m_fifoFileName << '\n';
    }
}

CNamedPipe::~CNamedPipe()
{

}