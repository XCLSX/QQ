#include "chatdlg.h"
#include "ui_chatdlg.h"
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
    QString filePath = QFileDialog::getOpenFileName(this,QString("选择发送文件"),"C:");
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
