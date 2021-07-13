#include "useritem.h"
#include "ui_useritem.h"

UserItem::UserItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserItem),m_iconid(0),m_userid(0)
{
    ui->setupUi(this);
}

UserItem::~UserItem()
{
    delete ui;
}

void UserItem::SetInfo(STRU_USER_INFO * info)
{
   m_iconid = info->m_icon_id;
   m_userid = info->m_user_id;
   status = info->m_status;
   m_name = QString(info->m_userName);
   m_feeling = QString(info->sz_feeling);
   ui->lb_name->setText(m_name);
   ui->lb_felling->setText(m_feeling);
   if(status)
   {
       ui->pb_icon->setIcon(QIcon(QString(":/tx/%1.png").arg(m_iconid)));
   }
   else
   {
       QBitmap bp;
       bp.load(QString(":/tx/%1.png").arg(m_iconid));
       ui->pb_icon->setIcon(bp);
   }
   this->repaint();
}
