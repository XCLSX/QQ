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
    m_chatdlg->setInfo(m_group_id,ls);

}


void GroupItem::mouseDoubleClickEvent(QMouseEvent *event)
{
    m_chatdlg->show();
}

GroupChatDlg *GroupItem::GetChatDlg()
{
    return m_chatdlg;
}

void GroupItem::mousePressEvent(QMouseEvent *event)
{

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
    return item;
}

void GroupItem::GetMsg(int userid, QString msg)
{
    num++;
    ui->lb_felling->setText(msg);
    m_chatdlg->AddMsg(userid,msg);
}


