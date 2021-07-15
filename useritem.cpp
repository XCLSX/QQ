#include "useritem.h"
#include "ui_useritem.h"

UserItem::UserItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserItem)
{
    ui->setupUi(this);
    m_chat = new ChatDlg;


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
