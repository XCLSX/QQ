#include "userinfodlg.h"
#include "ui_userinfodlg.h"

extern QMyTcpClient *m_tcp;
UserInfoDlg::UserInfoDlg(STRU_USER_INFO*m_info,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserInfoDlg)
{

    ui->setupUi(this);
    for(int i=0;i<=35;i++)
        ui->cbx_icon->addItem(QIcon(QString(":/tx/%1.png").arg(i)),"");
    info = m_info;
    ui->lb_account->setText(QString(info->m_userAccount));
    ui->le_name->setText(QString(info->m_userName));
    ui->le_felling->setText(QString(info->sz_feeling));

}

UserInfoDlg::~UserInfoDlg()
{
    delete ui;
}

void UserInfoDlg::on_pb_commi_clicked()
{

    STRU_ALTER_USERINFO_RQ rq;
    rq.m_iconid = ui->cbx_icon->currentIndex();
    rq.m_userid = info->m_user_id;
    strcpy(rq.m_szName,ui->le_name->text().toStdString().c_str());
    strcpy(rq.m_szFeeling,ui->le_felling->text().toStdString().c_str());
    if(rq.m_iconid == info->m_icon_id&&rq.m_userid == info->m_user_id
            &&(strcmp(rq.m_szFeeling,info->sz_feeling) == 0)
            &&(strcmp(rq.m_szName,info->m_userName) == 0))
    {
        return ;
    }
    else if(ui->le_name->text().remove(" ").isEmpty())
    {
        return ;
    }
    else
    {
        m_tcp->SendData((char *)&rq,sizeof(rq));
        this->hide();
        this->~QObject();
    }

}

void UserInfoDlg::on_pb_cancel_clicked()
{
    this->hide();
    this->~QObject();
}

void UserInfoDlg::on_pb_yingyong_clicked()
{
    STRU_ALTER_USERINFO_RQ rq;
    rq.m_iconid = ui->cbx_icon->currentIndex();
    rq.m_userid = info->m_user_id;
    strcpy(rq.m_szName,ui->le_name->text().toStdString().c_str());
    strcpy(rq.m_szFeeling,ui->le_felling->text().toStdString().c_str());
    if(rq.m_iconid == info->m_icon_id&&rq.m_userid == info->m_user_id
            &&(strcmp(rq.m_szFeeling,info->sz_feeling) == 0)
            &&(strcmp(rq.m_szName,info->m_userName) == 0))
    {
        return ;
    }
    else if(ui->le_name->text().remove(" ").isEmpty())
    {
        return ;
    }
    else
    {
        m_tcp->SendData((char *)&rq,sizeof(rq));
    }
}
