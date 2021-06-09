#include "qqmaindlg.h"
#include "ui_qqmaindlg.h"

QQMainDlg::QQMainDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QQMainDlg)
{
    ui->setupUi(this);
}

QQMainDlg::~QQMainDlg()
{
    delete ui;
}

void QQMainDlg::SetInfo(STRU_USER_INFO &info)
{

    ui->lb_name->setText(QString(info.sz_userName));
    ui->lb_felling->setText(info.sz_felling);
}
