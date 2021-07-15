#include "chatdlg.h"
#include "ui_chatdlg.h"
extern QMyTcpClient *m_tcp;


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
