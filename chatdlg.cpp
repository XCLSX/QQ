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
    m_layout = new QVBoxLayout;
    ui->sa_File->setLayout(m_layout);
    fileTask_num  = 0;
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

            //mtx.lock();
            fileTask_num++;
           // mtx.unlock();

            //布局界面
            ui->sa_File->setMaximumWidth(250);
            FileItem* m_fileItem = new FileItem(info->fileName,0);
            m_layout->addWidget(m_fileItem);
            m_filels.push_back(m_fileItem);

            info->pFile = new QFile(info->filePath);
            if(info->pFile->open(QIODevice::ReadOnly ))
            {
                QThread *m_thread = new QThread;
                Worker *work = new Worker;
                work->moveToThread(m_thread);
                map_Md5Tothread[md5str] = m_thread;
                m_fileItem->SetThread(m_thread);
                connect(this,SIGNAL(SIG_THREAD_WORK(STRU_FILE_INFO*,int,int)),work,SLOT(slot_dowork(STRU_FILE_INFO*,int,int)));
                connect(work,SIGNAL(SIG_VALUE_CHANGE(int)),m_fileItem,SLOT(slot_ChangeProcessBar(int)));
                connect(work,SIGNAL(SIG_TASK_OVER(STRU_FILE_INFO*)),this,SLOT(slot_FileSendSuss(STRU_FILE_INFO*)));

                m_thread->start();
                Q_EMIT SIG_THREAD_WORK(info,m_userid,m_charUserInfo->m_user_id);
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
        strcpy(rq.m_szFileName , fileName.c_str());

        //发送文件头
        //mtx.lock();
        m_tcp->SendData((char *)&rq,sizeof(rq));
       // mtx.unlock();
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


    //QString filePath = "C:/Users/44420/Desktop/4..暗红色中英文(1).docx";
    QString filePath = "C:/Users/44420/Desktop/210430_1806故障转移.mp4.baiduyun.p.downloading";
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
        //mtx.lock();
        m_tcp->SendData((char *)&rq,sizeof(rq));
       // mtx.unlock();
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

void ChatDlg::slot_FileSendSuss(STRU_FILE_INFO*info)
{
    if(info == NULL)
        return ;
    info->pFile->close();
    mtx.lock();
    //去除该节点

    auto ite = m_filels.begin();
    while(ite!=m_filels.end())
    {
        if((*ite)->GetFileName() == info->fileName)
        {

            FileItem *fItem = *ite;
            fItem->setVisible(false);
            m_layout->removeWidget(fItem);
            delete fItem;
            fItem = NULL;
            m_filels.erase(ite);
            break;
        }
        ++ite;
    }
    if(map_Md5Tothread.find(info->fileMd5)!=map_Md5Tothread.end())
    {
       QThread *tid = map_Md5Tothread[info->fileMd5];
       auto ite = map_Md5Tothread.find(info->fileMd5);
       map_Md5Tothread.erase(ite);
       tid->terminate();
       tid->~QObject();
       tid = NULL;


    }
    if(map_Md5ToFile.find(info->fileMd5)!=map_Md5ToFile.end())
    {
        map_Md5ToFile.erase( info->fileMd5 );
        delete info;
    }
    fileTask_num--;
    if(fileTask_num == 0)
        this->ui->sa_File->setMaximumWidth(0);
    mtx.unlock();
}

void ChatDlg::on_pushButton_2_clicked()
{
    //QString filePath = "C:/Users/44420/Desktop/4..暗红色中英文(1).docx";
    QString filePath = "C:/Users/44420/Desktop/210430_1934redis内存.mp4.baiduyun.p.downloading";
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
