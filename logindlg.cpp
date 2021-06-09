#include "logindlg.h"
#include "ui_logindlg.h"

LoginDlg::LoginDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDlg)
{
    ui->setupUi(this);
}

LoginDlg::~LoginDlg()
{
    delete ui;
}

Ui::LoginDlg *LoginDlg::GetUi() const
{
    return ui;
}



void LoginDlg::on_pb_register_clicked()
{
    QString account = ui->le_register_account->text();
    QString name = ui->le_register_name->text();
    QString pwd = ui->le_register_pwd->text();
    QString repwd = ui->le_register_repwd->text();
    if(account.isEmpty()||name.isEmpty()||pwd.isEmpty()||repwd.isEmpty())
    {
        QMessageBox::about(this,"提示","输入不能为空");
        return ;
    }
    else if(pwd!=repwd)
    {
        QMessageBox::about(this,"提示","两次密码不一致");
        return ;
    }
    STRU_REGISTER_RQ rq;
    strcpy(rq.m_szAccount,account.toStdString().c_str());
    strcpy(rq.m_szUserName,name.toStdString().c_str());
    strcpy(rq.m_szPassword,pwd.toStdString().c_str());

    Q_EMIT SIG_RegisterRq((char *)&rq,sizeof(rq));
}

void LoginDlg::on_pb_login_clicked()
{
    QString account = ui->le_account->text();
    QString pwd = ui->le_pwd->text();
    if(account.isEmpty()||pwd.isEmpty())
    {
        QMessageBox::about(this,"提示","输入不能为空");
        return ;
    }

    STRU_LOGIN_RQ rq;
    strcpy(rq.m_szAccount,account.toStdString().c_str());
    strcpy(rq.m_szPassword,pwd.toStdString().c_str());

    Q_EMIT SIG_LoginRq((char *)&rq,sizeof(rq));
}
