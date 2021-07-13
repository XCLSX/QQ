#include "searchfrienditem.h"
#include "ui_searchfrienditem.h"

extern QMyTcpClient *m_tcp;

SearchFriendItem::SearchFriendItem(STRU_USER_INFO * info,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchFriendItem)
{
    ui->setupUi(this);
    m_UserInfo = info;
}

SearchFriendItem::~SearchFriendItem()
{
    delete ui;
}

void SearchFriendItem::InitInfo(STRU_USER_INFO *info)
{
    m_iconid = info->m_icon_id;
    m_frid = info->m_user_id;
    status = info->m_status;
    m_name = QString(info->m_userName);
    m_feeling = QString(info->sz_feeling);
    ui->lb_name->setText(m_name);
    ui->lb_feeling->setText(m_feeling);
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

void SearchFriendItem::on_pb_add_clicked()
{
   ui->pb_add->hide();
   STRU_ADDFRIEND_RQ rq;
   rq.m_frid = m_frid;
   rq.m_UserInfo = *m_UserInfo;
   m_tcp->SendData((char *)&rq,sizeof(rq));

}
