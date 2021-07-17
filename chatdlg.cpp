#include "chatdlg.h"
#include "ui_chatdlg.h"
#include <worker.h>
#define MD5_KEY 1234
extern QMyTcpClient *m_tcp;

static QByteArray GetMD5( QString val)
{
    QCryptographicHash hash(QCryptographicHash::Md5);
    QString key = QString("%1_%2").arg(val).arg( MD5_KEY );

    hash.addData(  key.toLocal8Bit() );
    QByteArray bt =  hash.result();

    return bt.toHex();  // AD1234F....   32位  MD5
}
ChatDlg::ChatDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatDlg)
{
    ui->setupUi(this);
}

ChatDlg::~ChatDlg()
{
    delete ui;

}

void ChatDlg::SetInfo(char *p,int user_id,STRU_USER_INFO*info)
{
    m_userid = user_id;
    m_charUserInfo = info;
    ui->lb_name->setText(QString(m_charUserInfo->m_userName));
    m_UserItem = p;
    setWindowTitle(QString("与%1的聊天").arg(info->m_userName));
}

void ChatDlg::AddMsg(char *msg)
{

    QString str = QString("%1:").arg(m_charUserInfo->m_userName);
            str+=QString(msg);
    ui->tb_chat->append(str);


}

void ChatDlg::SendFile(char *szbuf)
{
    STRU_UPLOAD_RS *rs = (STRU_UPLOAD_RS*)szbuf;
    if(rs->m_nResult == 0)
    {

    }
    else
    {
        QString md5str = QString(rs->m_szFileMD5);
        if(map_Md5ToFile.find(md5str)!=map_Md5ToFile.end())
        {
            STRU_FILE_INFO *info = map_Md5ToFile[md5str];
            info->pFile = new QFile(info->filePath);
            if(info->pFile->open(QIODevice::ReadOnly ))
            {
                Worker *work = new Worker;
                work->moveToThread(&myThread);
                connect(this,SIGNAL(SIG_THREAD_WORK(char*,int,int)),work,SLOT(dowork(char*,int,int)));
                connect(work,&Worker::SIG_TASK_OVER,[=]()
                {
                    info->pFile->close();
                    //去除该节点
                    map_Md5ToFile.erase( info->fileMd5 );
                    delete info;
                    //QMessageBox::about( NULL , "提示","发送完成" );

                });
                myThread.start();
                Q_EMIT SIG_THREAD_WORK((char*)info,m_userid,m_charUserInfo->m_user_id);
            }
        }
    }
}

void ChatDlg::on_pb_send_clicked()
{
    QString str = ui->te_msg->toPlainText();
    if(str.isEmpty())
        return;
    ui->tb_chat->append("我:"+str);
    ui->te_msg->clear();
    STRU_SENDMSG_RQ rq;
    strcpy(rq.msg,str.toStdString().c_str());
    rq.m_userid = this->m_userid;
    rq.m_Touserid = m_charUserInfo->m_user_id;
    m_tcp->SendData((char *)&rq,sizeof(rq));
    Q_EMIT SIG_ADDITEM(m_UserItem,0);
}

void ChatDlg::on_pb_sendFile_clicked()
{
    ui->sa_File->setMaximumWidth(100);
    QString filePath = QFileDialog::getOpenFileName(this,QString("选择发送文件"));
    if(!filePath.remove(" ").isEmpty())
    {
        qDebug()<<filePath;
        QFileInfo fileInfo(filePath);
        string fileName = fileInfo.fileName().toStdString();
        QByteArray resMd5 = GetMD5(fileInfo.fileName() + QTime::currentTime().toString("hhmmss"));
        STRU_UPLOAD_RQ rq;
        rq.m_friendId = this->m_charUserInfo->m_user_id;
        rq.m_nFileSize = fileInfo.size();
        memcpy(rq.m_szFileMD5,resMd5.data(),resMd5.size());
        rq.m_UserId = this->m_userid;
        //发送文件头
        m_tcp->SendData((char *)&rq,sizeof(rq));
        //录入映射
        string strMD5 = rq.m_szFileMD5;
        QString MD5 = QString::fromStdString( strMD5 );

        STRU_FILE_INFO * pInfo = new STRU_FILE_INFO;
        pInfo->fileMd5 = MD5 ;
        pInfo->fileName = fileInfo.fileName();
        pInfo->filePath = filePath;
        pInfo->filePos = 0;
        pInfo->fileSize = rq.m_nFileSize;
        pInfo->pFile = NULL;

        map_Md5ToFile[ MD5 ] = pInfo;

    }
}



void ChatDlg::on_pushButton_clicked()
{
    ui->sa_File->setMaximumWidth(100);
    QString filePath = "C:/Users/44420/Desktop/4..暗红色中英文(1).docx";
    if(!filePath.remove(" ").isEmpty())
    {
        qDebug()<<filePath;
        QFileInfo fileInfo(filePath);
        string fileName = fileInfo.fileName().toStdString();
        QByteArray resMd5 = GetMD5(fileInfo.fileName() + QTime::currentTime().toString("hhmmss"));
        STRU_UPLOAD_RQ rq;
        rq.m_friendId = this->m_charUserInfo->m_user_id;
        rq.m_nFileSize = fileInfo.size();
        memcpy(rq.m_szFileMD5,resMd5.data(),resMd5.size());
        rq.m_UserId = this->m_userid;
        strcpy(rq.m_szFileName , fileName.c_str());
        //发送文件头
        m_tcp->SendData((char *)&rq,sizeof(rq));
        //录入映射
        string strMD5 = rq.m_szFileMD5;
        QString MD5 = QString::fromStdString( strMD5 );

        STRU_FILE_INFO * pInfo = new STRU_FILE_INFO;
        pInfo->fileMd5 = MD5 ;
        pInfo->fileName = fileInfo.fileName();
        pInfo->filePath = filePath;
        pInfo->filePos = 0;
        pInfo->fileSize = rq.m_nFileSize;
        pInfo->pFile = NULL;

        map_Md5ToFile[ MD5 ] = pInfo;

    }
}
