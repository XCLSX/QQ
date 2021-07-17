#include "worker.h"
extern QMyTcpClient *m_tcp;
Worker::Worker(QObject *parent) : QObject(parent)
{

}

void Worker::dowork(char *szbuf,int m_userid,int m_frid)
{
    STRU_FILE_INFO *info = (STRU_FILE_INFO *)szbuf;

    while(1)
    {
        qDebug()<<"STRU_FILEBLOCK_RQ";
        STRU_FILEBLOCK_RQ rq;
        rq.m_nUserId = m_userid;
        rq.m_friendId = m_frid;

        int res  = info->pFile->read( rq.m_szFileContent ,MAX_CONTENT_LEN );
        strcpy_s( rq.m_szFileMD5 , MAX_PATH , info->fileMd5.toStdString().c_str() );

        info->filePos += res ;
        rq.m_nBlockLen = res;

        m_tcp->SendData( (char*)&rq , sizeof(rq) );

        if( info->filePos >= info->fileSize )
            {
                 Q_EMIT SIG_TASK_OVER();
                return ;
            }

    }

}
