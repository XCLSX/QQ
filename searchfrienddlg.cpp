#include "searchfrienddlg.h"
#include "ui_searchfrienddlg.h"
extern QMyTcpClient *m_tcp;

SearchFriendDlg::SearchFriendDlg(int id,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchFriendDlg)
{
    ui->setupUi(this);
    m_friLayout = new QVBoxLayout;
    m_friLayout->setContentsMargins(0,0,0,0);//设置外边距
    m_friLayout->setSpacing(2);
    ui->wid_friendList->setLayout(m_friLayout);
    m_userid = id;

}

SearchFriendDlg::~SearchFriendDlg()
{
    delete ui;
}

void SearchFriendDlg::AddFriWidget(QWidget *item)
{
    m_friLayout->addWidget(item);
}

void SearchFriendDlg::ClearLayout()
{
    auto ite = vec_friend.begin();
    while(ite!=vec_friend.end())
    {
        m_friLayout->removeWidget(*ite);
        delete *ite;
        *ite = NULL;
        ite++;
    }
    vec_friend.clear();

}



void SearchFriendDlg::on_pb_people_search_clicked()
{
   // m_friLayout->
    STRU_SEARCHFRIEND_RQ rq;
    strcpy(rq.m_szBuf,ui->le_perple_search->text().toStdString().c_str());
    m_tcp->SendData((char *)&rq,sizeof(rq));

}

void SearchFriendDlg::on_pb_group_search_clicked()
{
    STRU_SEARCHFRIEND_RQ rq;
    strcpy(rq.m_szBuf,ui->le_perple_search->text().toStdString().c_str());
    m_tcp->SendData((char *)&rq,sizeof(rq));

}

void SearchFriendDlg::slot_UpdateDlg(char *szbuf)
{

}
