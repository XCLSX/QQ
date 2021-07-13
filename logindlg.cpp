#include "logindlg.h"
#include "ui_logindlg.h"

extern QMyTcpClient *m_tcp;


LoginDlg::LoginDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDlg)
{
    ui->setupUi(this);
//    ui->tb_loginDlg->setStyleSheet("QTabWidget:pane {border-top:0px solid #e8f3f9;background:  transparent; }");
//    ui->le_account->setStyleSheet("QLineEdit{background-color: rgba(96, 96, 96, 0.4)}"
//                             "QLineEdit{border-width:2;border-style:outset;border : 1px solid white;}");
//    ui->le_pwd->setStyleSheet("QLineEdit{background-color:rgba(96,96,96,0.4)}");
}

LoginDlg::~LoginDlg()
{
    delete ui;
}

Ui::LoginDlg *LoginDlg::GetUi() const
{
    return ui;
}

void LoginDlg::paintEvent(QPaintEvent *event)
{
//    QPainter painter(this);
//    QPixmap  pix;
//    pix.load(":/images/back.jpg");
    //    painter.drawPixmap(0,0,this->width(),this->height(),pix);
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
    strcpy(rq.m_szName,name.toStdString().c_str());
    strcpy(rq.m_szPwd,pwd.toStdString().c_str());

    m_tcp->SendData((char *)&rq,sizeof(rq));
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
    strcpy(rq.m_szPwd,pwd.toStdString().c_str());
    m_tcp->SendData((char *)&rq,sizeof(rq));
}
