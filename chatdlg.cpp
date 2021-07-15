#include "chatdlg.h"
#include "ui_chatdlg.h"

ChatDlg::ChatDlg(int user_id,STRU_USER_INFO*info,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatDlg)
{
    ui->setupUi(this);
    m_userid = user_id;
    m_charUserInfo = info;
    ui->lb_name->setText(QString(m_charUserInfo->m_userName));
    //connect(this,SIGNAL(SIG_ADDITEM(void*)),this->parent()->parent(),));
}

ChatDlg::~ChatDlg()
{
    delete ui;

}

void ChatDlg::SetUserItem(char *p)
{
    m_UserItem = p;
}

void ChatDlg::on_pb_send_clicked()
{
    QString str = ui->te_msg->toPlainText();
    if(str.isEmpty())
        return;
    ui->tb_chat->append("我:"+str);
    ui->te_msg->clear();
    Q_EMIT SIG_ADDITEM(m_UserItem,0);
}
