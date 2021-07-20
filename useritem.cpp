#include "useritem.h"
#include "ui_useritem.h"
extern QMyTcpClient *m_tcp;
UserItem::UserItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserItem)
{
    ui->setupUi(this);
    m_chat = new ChatDlg;
    m_UserMenu = new QMenu;
    m_UserMenu->addAction("查看好友资料");
    m_UserMenu->addAction("删除好友");
    m_UserMenu->addAction("从会话列表清除");
    connect(m_UserMenu,SIGNAL(triggered(QAction*)),this,SLOT(slot_DealMenu(QAction*)));


}

UserItem::~UserItem()
{
    delete ui;
}

void UserItem::SetInfo(STRU_USER_INFO * info,int userid )
{
        m_userid = userid;
        m_UserInfo = *info;
        ui->lb_name->setText(QString(info->m_userName));
        ui->lb_felling->setText(QString(info->sz_feeling));
        if(info->m_status)
        {
            ui->pb_icon->setIcon(QIcon(QString(":/tx/%1.png").arg(info->m_icon_id)));
        }
        else
        {
            QBitmap bp;
            bp.load(QString(":/tx/%1.png").arg(info->m_icon_id));
            ui->pb_icon->setIcon(bp);
        }
        this->repaint();
        m_chat->SetInfo((char *)this,m_userid,info);
        num  = new int;
        *num = 0;
}

void UserItem::mouseDoubleClickEvent(QMouseEvent *event)
{
    m_chat->show();
    *num = 0;
    ui->lb_num->setText("");

}

ChatDlg *UserItem::GetChatDlg()
{
    return m_chat;
}

void UserItem::SetChatDlg(ChatDlg *pChat)
{
    m_chat = pChat;
}

void UserItem::UpdateMsgNum()
{
    (*num)++;
    char str[4] = {0};
    itoa(*num,str,10);
    ui->lb_num->setText(QString(str));
}

void UserItem::SetCurrentMsg(char *msg)
{
    ui->lb_felling->setText(QString(msg));
}

void UserItem::ChangeIconColor(int status,int icon_id)
{
    if(status)
    {
        ui->pb_icon->setIcon(QIcon(QString(":/tx/%1.png").arg(icon_id)));
    }
    else
    {
        QBitmap bp;
        bp.load(QString(":/tx/%1.png").arg(icon_id));
        ui->pb_icon->setIcon(bp);
    }
    this->repaint();
}

void UserItem::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::RightButton&&m_UserMenu)
    {
        QPoint p;
        p.setX(QCursor::pos().x());
        p.setY(QCursor::pos().y()-m_UserMenu->sizeHint().height());
        m_UserMenu->exec(p);
        qDebug()<<"right";
    }
}

UserItem *UserItem::m_Copy()
{
    UserItem *item = new UserItem;

    item->m_chat = this->m_chat;
    item->m_userid = this->m_userid;
    item->m_UserInfo = this->m_UserInfo;
    if(item->m_UserInfo.m_status)
    {
        item->ui->pb_icon->setIcon(QIcon(QString(":/tx/%1.png").arg(item->m_UserInfo.m_icon_id)));
    }
    else
    {
        QBitmap bp;
        bp.load(QString(":/tx/%1.png").arg(item->m_UserInfo.m_icon_id));
        item->ui->pb_icon->setIcon(bp);
    }
    item->repaint();
    item->ui->lb_name->setText(item->m_UserInfo.m_userName);
    item->num = this->num;
    return item;
}

void UserItem::slot_DealMenu(QAction * action)
{
    if(action->text()=="查看好友资料")
    {

    }
    else if(action->text() == "删除好友")
    {
        STRU_DELFRIEND_RQ rq;
        rq.m_userid = m_userid;
        rq.m_frid = m_UserInfo.m_user_id;
        m_tcp->SendData((char *)&rq,sizeof(rq));
    }
    else if(action->text() == "从会话列表清除")
    {

    }

}
