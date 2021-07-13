#include "searchfrienditem.h"
#include "ui_searchfrienditem.h"

SearchFriendItem::SearchFriendItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchFriendItem)
{
    ui->setupUi(this);
}

SearchFriendItem::~SearchFriendItem()
{
    delete ui;
}

void SearchFriendItem::InitInfo(STRU_USER_INFO *info)
{
    m_iconid = info->m_icon_id;
    m_userid = info->m_user_id;
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
