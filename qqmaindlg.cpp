#include "qqmaindlg.h"
#include "ui_qqmaindlg.h"
extern QMyTcpClient *m_tcp;

QQMainDlg::QQMainDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QQMainDlg)
{
    ui->setupUi(this);


    m_Frilayout = new QVBoxLayout;
    ui->wid_friendList->setLayout(m_Frilayout);
    m_Msglayout = new QVBoxLayout;
    ui->wid_MessageList->setLayout(m_Msglayout);

}

QQMainDlg::~QQMainDlg()
{
    delete ui;
}

SearchFriendDlg *QQMainDlg::GetSearchDLg()
{
    return m_SearchDlg;
}

void QQMainDlg::FreshFriendList(char *szbuf)
{
    STRU_GetFriList_Rs *rs = (STRU_GetFriList_Rs*)szbuf;
    UserItem *item = NULL;
    int i=0;
    while(rs->m_FriInfo[i].m_user_id!=0)
    {
        item = new UserItem;
        item->SetInfo(&rs->m_FriInfo[i]);
        m_FriendVec.push_back(item);
        m_Frilayout->addWidget(item);
        i++;
    }
}

void QQMainDlg::SetInfo(STRU_USER_INFO *info)
{
    m_userInfo = info;
    QPixmap icon;
    QString str = QString(":/tx/%1.png").
            arg(m_userInfo->m_icon_id);
    icon.load(str.toStdString().c_str());
    ui->pb_icon->setIcon(icon);

    ui->lb_name->setText(QString(m_userInfo->m_userName));
    ui->lb_felling->setText(QString(m_userInfo->sz_feeling));




}



void QQMainDlg::on_pb_Search_clicked()
{
    m_SearchDlg = new SearchFriendDlg(m_userInfo->m_user_id);
    m_SearchDlg->show();
}

void QQMainDlg::on_pb_icon_clicked()
{

}

void QQMainDlg::AddUserItem(QWidget *item)
{
    m_Frilayout->addWidget(item);
}

void QQMainDlg::AddMsg(char *szbuf, int mode)
{
    //聊天
    if(mode == 0)
    {

    }//添加好友
    else if(mode == 1)
    {
        STRU_ADDFRIEND_RQ *rq = (STRU_ADDFRIEND_RQ*)szbuf;
        AddFriendItem *item = new AddFriendItem;
        item->SetInfo(&rq->m_UserInfo,rq->m_frid);
        for(int i=0;i<m_AddfriVec.size();i++)
        {
            if(m_AddfriVec[i]->m_userid == item->m_userid)
                return;
        }
        m_AddfriVec.push_back(item);
        m_Msglayout->addWidget(item);
        connect(item,&AddFriendItem::SIG_mCloseWidget,[=](AddFriendItem*delItem)
        {
            auto ite = m_AddfriVec.begin();
            while(ite!=m_AddfriVec.end())
            {
                if((*ite)->m_userid == delItem->m_userid)
                {
                    m_AddfriVec.erase(ite);
                    break;
                }
            }
            delItem->setVisible(false);
            m_Msglayout->removeWidget(delItem);
            delete delItem;
            delItem = NULL;
        });
        connect(item,&AddFriendItem::SIG_Accept,[=](AddFriendItem*delItem,char *szbuf)
        {
           m_tcp->SendData(szbuf,sizeof(szbuf));
           auto ite = m_AddfriVec.begin();
           while(ite!=m_AddfriVec.end())
           {
               if((*ite)->m_userid == delItem->m_userid)
               {
                   m_AddfriVec.erase(ite);
                   break;
               }
           }
           delItem->setVisible(false);
           m_Msglayout->removeWidget(delItem);
           delete delItem;
           delItem = NULL;
        });
    }
}

void QQMainDlg::UpdateFriendStatus(char *szbuf)
{
    STRU_UPDATE_STATUS *sus = (STRU_UPDATE_STATUS*)szbuf;
    auto ite = m_FriendVec.begin();
    while(ite!=m_FriendVec.end())
    {
        if((*ite)->m_userid == sus->m_UserInfo.m_user_id)
        {
            (*ite)->status = sus->m_UserInfo.m_status;
            if((*ite)->status == 0)
            {

            }
        }
        else
        {
            UserItem *item;
            item->SetInfo(&sus->m_UserInfo);
            m_Frilayout->addWidget(item);
        }
        ++ite;
    }
}

