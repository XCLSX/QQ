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
