#include "qqmaindlg.h"
#include "ui_qqmaindlg.h"

QQMainDlg::QQMainDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QQMainDlg)
{
    ui->setupUi(this);
    m_SearchDlg = new SearchFriendDlg;
    m_userid = 0;
    icon_id = 0;
    memset(szName,0,sizeof(szName));
    memset(szFelling,0,sizeof(szFelling));
    m_layout = new QVBoxLayout;
    ui->wid_friendList->setLayout(m_layout);

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
    m_userid = info->m_user_id;
    icon_id = info->m_icon_id;
    QPixmap icon;
    QString str = QString(":/tx/%1.png").
            arg(icon_id);
    icon.load(str.toStdString().c_str());
    ui->pb_icon->setIcon(icon);
    strcpy(szName,info->m_userName);
    strcpy(szFelling,info->sz_feeling);
    ui->lb_name->setText(QString(szName));
    ui->lb_felling->setText(szFelling);

    UserItem *item = new UserItem;
    item->SetInfo(info);
    this->AddUserItem(item);
}



void QQMainDlg::on_pb_Search_clicked()
{
    m_SearchDlg = new SearchFriendDlg;
    m_SearchDlg->show();
}

void QQMainDlg::on_pb_icon_clicked()
{

}

void QQMainDlg::AddUserItem(QWidget *item)
{
    m_layout->addWidget(item);
}

