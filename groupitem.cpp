#include "groupitem.h"
#include "ui_groupitem.h"

GroupItem::GroupItem(int userid,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GroupItem)
{
    ui->setupUi(this);
    m_userid = userid;
    m_chatdlg = new GroupChatDlg((char*)this,m_userid);
    this->num =new int(0);
    m_GroupMenu = new QMenu;
    m_GroupMenu->addAction("查看群资料");
    m_GroupMenu->addAction("退出群聊");
    connect(m_GroupMenu,SIGNAL(triggered(QAction*)),this,SLOT(slot_DealMenu(QAction*)));

}

GroupItem::~GroupItem()
{
    delete ui;
}

void GroupItem::SetInfo(QString group_name, int group_id,int iconid, list<STRU_USER_INFO *> ls)
{
    m_group_name = group_name;
    m_group_id = group_id;
    m_iconid = iconid;
    ui->lb_name->setText(m_group_name);
    ui->pb_icon->setIcon(QIcon(QString(":/tx/%1.png").arg(iconid)));
    m_chatdlg->setInfo(group_name,m_group_id,ls);

}


void GroupItem::mouseDoubleClickEvent(QMouseEvent *event)
{
    m_chatdlg->show();
    *num = 0;
    ui->lb_num->setText("");
}

GroupChatDlg *GroupItem::GetChatDlg()
{
    return m_chatdlg;
}

void GroupItem::UpdateMsgNum()
{
    (*num)++;
    char str[4] = {0};
    itoa(*num,str,10);
    ui->lb_num->setText(QString(str));
}

void GroupItem::SetCurrentMsg(QString msg)
{
    ui->lb_currentMsg->setText(msg);
}

void GroupItem::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::RightButton&&m_GroupMenu)
    {
        QPoint p;
        p.setX(QCursor::pos().x());
        p.setY(QCursor::pos().y()-m_GroupMenu->sizeHint().height());
        m_GroupMenu->exec(p);
        qDebug()<<"right";
    }
}

GroupItem *GroupItem::m_Copy()
{
    GroupItem *item = new GroupItem(m_userid);
    delete item->m_chatdlg;
    item->m_group_name = m_group_name;
    item->m_group_id = m_group_id;
    item->m_iconid = m_iconid;
    item->ui->lb_name->setText(m_group_name);
    item->ui->pb_icon->setIcon(QIcon(QString(":/tx/%1.png").arg(m_iconid)));
    item->m_chatdlg = this->GetChatDlg();
    delete item->num;
    item->num = this->num;
    this->num++;
    item->m_GroupMenu->addAction("从会话列表清除");
    return item;
}

void GroupItem::GetMsg(int userid, QString msg)
{
    num++;
    ui->lb_currentMsg->setText(msg);
    m_chatdlg->AddMsg(userid,msg);
}

void GroupItem::slot_DealMenu(QAction *action)
{
    if(action->text()=="查看群资料")
    {

    }
    else if(action->text() == "退出群聊")
    {
//        STRU_DELFRIEND_RQ rq;
//        rq.m_userid = m_userid;
//        rq.m_frid = m_UserInfo.m_user_id;
//        m_tcp->SendData((char *)&rq,sizeof(rq));
    }
    else if(action->text() == "从会话列表清除")
    {
        SIG_DelMsg(this->m_group_id);
    }
}


