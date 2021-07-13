#include "addfrienditem.h"
#include "ui_addfrienditem.h"

AddFriendItem::AddFriendItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddFriendItem)
{
    ui->setupUi(this);
}

AddFriendItem::~AddFriendItem()
{
    delete ui;
}

void AddFriendItem::SetInfo(STRU_USER_INFO *info,int userid)
{
    ui->pb_icon->setIcon(QIcon(QString(":/tx/%1.png").arg(info->m_icon_id)));
    ui->lb_name->setText(QString(info->m_userName));
    m_userid = info->m_user_id;
    m_fri_id = userid;

}

