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
}

QQMainDlg::~QQMainDlg()
{
    delete ui;
}

void QQMainDlg::SetInfo(STRU_USER_INFO &info)
{
    m_userid = info.m_user_id;
    icon_id = info.m_icon_id;
    strcpy(szName,info.sz_userName);
    strcpy(szFelling,info.sz_felling);
    ui->lb_name->setText(QString(szName));
    ui->lb_felling->setText(szFelling);
    ui->pb_icon->setIcon(QIcon(QString(":/")));

}

void QQMainDlg::on_pb_addfriend_clicked()
{
    m_SearchDlg->show();
}
