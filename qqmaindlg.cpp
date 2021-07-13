#include "qqmaindlg.h"
#include "ui_qqmaindlg.h"

QQMainDlg::QQMainDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QQMainDlg)
{
    ui->setupUi(this);


    m_Frilayout = new QVBoxLayout;
    ui->wid_friendList->setLayout(m_Frilayout);
    m_Msglayout = new QVBoxLayout;
    ui->wid_MessageList->setLayout(m_Msglayout);
}

QQMainDlg::~QQMainDlg()
{
    delete ui;
}

SearchFriendDlg *QQMainDlg::GetSearchDLg()
{
    return m_SearchDlg;
}

void QQMainDlg::SetInfo(STRU_USER_INFO *info)
{
    m_userInfo = info;
    QPixmap icon;
    QString str = QString(":/tx/%1.png").
            arg(m_userInfo->m_icon_id);
    icon.load(str.toStdString().c_str());
    ui->pb_icon->setIcon(icon);

    ui->lb_name->setText(QString(m_userInfo->m_userName));
    ui->lb_felling->setText(QString(m_userInfo->sz_feeling));




}



void QQMainDlg::on_pb_Search_clicked()
{
    m_SearchDlg = new SearchFriendDlg(m_userInfo->m_user_id);
    m_SearchDlg->show();
}

void QQMainDlg::on_pb_icon_clicked()
{

}

void QQMainDlg::AddUserItem(QWidget *item)
{
    m_Frilayout->addWidget(item);
}

void QQMainDlg::AddMsg(char *szbuf, int mode)
{
    //聊天
    if(mode == 0)
    {

    }//添加好友
    else if(mode == 1)
    {
        STRU_ADDFRIEND_RQ *rq = (STRU_ADDFRIEND_RQ*)szbuf;
        AddFriendItem *item = new AddFriendItem;
        item->SetInfo(&rq->m_UserInfo,rq->m_frid);
        m_Msglayout->addWidget(item);
    }
}

