#include "QMyTcpClient.h"
#include<QThread>
#include<QDebug>

QMyTcpClient::QMyTcpClient(QObject *parent) : QObject(parent)
{
    m_pTcp = new TCPNet(this);
    strcpy( m_szBufIP , DEF_SERVER_IP);
    m_port = DEF_TCP_PORT;
}

QMyTcpClient::~QMyTcpClient()
{
    m_pTcp->UnInitNetWork();
}

bool QMyTcpClient::InitNetWork(char* szBufIP , unsigned short port)
{
    strcpy( m_szBufIP , szBufIP);
    m_port = port;
    return m_pTcp->InitNetWork(szBufIP,port);
}

void QMyTcpClient::setIpAndPort(char *szBufIP, unsigned short port)
{
    strcpy( m_szBufIP , szBufIP);
    m_port = port;
}


void QMyTcpClient::UnInitNetWork()
{
    m_pTcp->UnInitNetWork();
}

int QMyTcpClient::SendData(char* szbuf,int nLen)
{
    lock.lock();
    if( IsConnected() )
    {
        int res = m_pTcp->SendData(szbuf,nLen);
        lock.unlock();
        return res;
    }
    else
    {
        m_pTcp->UnInitNetWork( );
        delete m_pTcp;
        m_pTcp = new TCPNet(this);
        if( this->InitNetWork(m_szBufIP , m_port) )
        {
            int res = m_pTcp->SendData(szbuf,nLen);
            lock.unlock();
            return res;
        }
        else
        {
            lock.unlock();
            return -1;
        }
    }
}

int QMyTcpClient::ConnectToServer( char* szBufIP)
{
    return m_pTcp->ConnectToServer(szBufIP);
}


void QMyTcpClient::DealData(char* szbuf , int nLen)
{
    qDebug()<<"QMyTcpClient"<< QThread::currentThreadId();
    emit SIG_ReadyData(szbuf,nLen);
}

void QMyTcpClient::disConnect()
{
    emit SIG_disConnect();
}
int QMyTcpClient::IsConnected()
{
    return m_pTcp->IsConnected();
}


