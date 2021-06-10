#include "searchfrienddlg.h"
#include "ui_searchfrienddlg.h"

SearchFriendDlg::SearchFriendDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchFriendDlg)
{
    ui->setupUi(this);
}

SearchFriendDlg::~SearchFriendDlg()
{
    delete ui;
}

void SearchFriendDlg::on_pb_search_clicked()
{
    string str = ui->le_search->text().toStdString();
    STRU_SEARCH_FRIEND_RQ rq;
    strcpy(rq.m_szbuf , str.c_str());
    Q_EMIT SIG_Search((char *)&rq,sizeof(rq));
}
