#include "creategroupdlg.h"
#include "ui_creategroupdlg.h"
extern QMyTcpClient *m_tcp;
CreateGroupDlg::CreateGroupDlg(int userid,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateGroupDlg)
{
    ui->setupUi(this);
    m_userid = userid;
}

CreateGroupDlg::~CreateGroupDlg()
{
    delete ui;
}

void CreateGroupDlg::on_pb_commit_clicked()
{
    QString str = ui->le_groupName->text();
    QString temp = str;
    if(temp.remove(' ').isEmpty())
    {
        QMessageBox::about(this,"错误","不能为空");
        return;
    }
    else if(str.size()>=10)
    {
        QMessageBox::about(this,"错误","名称过长(＜10)");
        return;
    }
    STRU_CREATE_GROUP_RQ rq;
    strcpy(rq.m_szGroupName,ui->le_groupName->text().toStdString().c_str());
    rq.m_userid = m_userid;
    m_tcp->SendData((char *)&rq,sizeof(rq));
    this->hide();

}
