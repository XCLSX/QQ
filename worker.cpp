#include "worker.h"
extern QMyTcpClient *m_tcp;
Worker::Worker(QObject *parent) : QObject(parent)
{

}

void Worker::slot_dowork(STRU_FILE_INFO *szbuf,int m_userid,int m_frid)
{
    STRU_FILE_INFO *info = (STRU_FILE_INFO *)szbuf;
    double percent = 0;
    double m = info->fileSize;
    qDebug()<<"STRU_FILEBLOCK_RQ";
    STRU_FILEBLOCK_RQ rq;
    rq.m_nUserId = m_userid;
    rq.m_friendId = m_frid;
    while(1)
    {
s
        //mx.lock();
        int res  = info->pFile->read( rq.m_szFileContent ,MAX_CONTENT_LEN );
        strcpy_s( rq.m_szFileMD5 , MAX_PATH , info->fileMd5.toStdString().c_str() );

        info->filePos += res ;
        rq.m_nBlockLen = res;
        m_tcp->SendData( (char*)&rq , sizeof(rq) );
        double z = info->filePos;
        percent = (z/m)*100;
        Q_EMIT SIG_VALUE_CHANGE((int)percent);
       // mx.unlock();

        if( info->filePos >= info->fileSize )
            {
                 Q_EMIT SIG_TASK_OVER(info);
               // mx.unlock();
                this->~QObject();
                return ;
            }


    }

}
