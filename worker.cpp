#include "worker.h"
extern QMyTcpClient *m_tcp;
Worker::Worker(QObject *parent) : QObject(parent)
{
    isWork = true;
}

void Worker::slot_SendFile(STRU_FILE_INFO *szbuf,int m_userid,int m_frid)
{
    qDebug()<<GetCurrentThreadId();

    STRU_FILE_INFO *info = (STRU_FILE_INFO *)szbuf;
    double percent = 0;
    double m = info->fileSize;
    qDebug()<<"STRU_FILEBLOCK_RQ";
    STRU_FILEBLOCK_RQ rq;
    rq.m_nUserId = m_userid;
    rq.m_friendId = m_frid;
    int pos = 0;
    while(1)
    {
        pos++;
        if(pos%500==0)
        {
            Sleep(10);
        }
        while(!isWork)
        {
            Sleep(300);
        }
        int res  = info->pFile->read( rq.m_szFileContent ,MAX_CONTENT_LEN );
        strcpy_s( rq.m_szFileMD5 , MAX_PATH , info->fileMd5.toStdString().c_str() );

        info->filePos += res ;
        rq.m_nBlockLen = res;
       while( m_tcp->SendData( (char*)&rq , sizeof(rq) )==-1)
           {
                Sleep(1000);
                //判断时间
           }

        double z = info->filePos;
        percent = (z/m)*100;
        Q_EMIT SIG_VALUE_CHANGE((int)percent);

        if( info->filePos >= info->fileSize )
            {
                 Q_EMIT SIG_TASK_OVER(info);
                this->~QObject();
                return ;
            }


    }

}

void Worker::slot_pause()
{
    isWork = !isWork;
}

void Worker::slot_GetFIle(STRU_FILE_INFO*info,char *szbuf)
{
    STRU_FILEBLOCK_RQ*rq = (STRU_FILEBLOCK_RQ*)szbuf;

           int res = info->pFile->write(rq->m_szFileContent,rq->m_nBlockLen);
                   //fwrite(rq->m_szFileContent,1,rq->m_nBlockLen,info->pFile);
           info->filePos += res;
           double percent;
           double z = info->filePos;
           double m = info->fileSize;
           percent = z/m;
           Q_EMIT SIG_VALUE_CHANGE((int)percent*100);
           if(info->filePos>=info->fileSize)
           {
               info->pFile->close();
               Q_EMIT SIG_TASK_OVER(info);
               this->~QObject();
           }
}
