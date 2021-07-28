#include "groupchatdlg.h"
#include "ui_groupchatdlg.h"

extern QMyTcpClient *m_tcp;
GroupChatDlg::GroupChatDlg(char *item,int userid,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GroupChatDlg)
{
    ui->setupUi(this);
    m_UserLayout = new QVBoxLayout;
    ui->wid_userList->setLayout(m_UserLayout);
    m_userid = userid;
    m_item = item;
}

GroupChatDlg::~GroupChatDlg()
{
    delete ui;
}

void GroupChatDlg::setInfo(QString name,int groupid,list<STRU_USER_INFO *> ls)
{
    ui->lb_name->setText(name+"("+groupid+")");
    m_groupid = groupid;
    auto ite = ls.begin();
    while(ite!=ls.end())
    {
        this->m_userls.push_back(*ite);
        UserItem *item = new UserItem;
        item->SetInfo(*ite,m_userid);
        m_UserLayout->addWidget(item);
        ++ite;
    }

}

void GroupChatDlg::AddMsg(int userid, QString msg)
{
    auto ite = m_userls.begin();
    while(ite!=m_userls.end())
    {
        if((*ite)->m_user_id == userid)
             break;
        ++ite;
    }
    if((*ite)->m_user_id == userid)
    {
        ui->tb_chat->append(QString((*ite)->m_userName)+":"+msg);
    }
}

list<STRU_USER_INFO *> *GroupChatDlg::GetLs()
{
    return &m_userls;
}

void GroupChatDlg::on_pb_send_clicked()
{
    QString str = ui->te_msg->toPlainText();
    if(str.isEmpty())
        return;
    ui->tb_chat->append("我:"+str);
    ui->te_msg->clear();

    Q_EMIT SIG_SENDMSG(m_item,str,m_groupid);
}
