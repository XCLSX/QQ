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
        connect(item->GetChatDlg(),SIGNAL(SIG_ADDITEM(char*,int)),SLOT(slot_AddMsg(char*,int)));
        item->SetInfo(&rs->m_FriInfo[i],m_userInfo->m_user_id);
        m_Friendls.push_back(item);
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

void QQMainDlg::UpdateMsg(char *szbuf)
{
    STRU_SENDMSG_RQ *rq = (STRU_SENDMSG_RQ*)szbuf;
    auto mite = m_Msgls.begin();
    while(mite!=m_Msgls.end())
    {
        if((*mite)->m_UserInfo.m_user_id == rq->m_userid)
        {
            //添加信息
            (*mite)->m_chat->AddMsg(rq->msg);
            (*mite)->SetCurrentMsg(rq->msg);

            if((*mite)->m_chat->isHidden())
                (*mite)->UpdateMsgNum();

            (*mite)->setVisible(false);
            m_Msglayout->removeWidget(*mite);
            (*mite)->setVisible(true);
            m_Msglayout->insertWidget(0,*mite);
            return;
        }
        ++mite;
    }
    auto fite = m_Friendls.begin();
    while(fite != m_Friendls.end())
    {
        if((*fite)->m_UserInfo.m_user_id == rq->m_userid)
        {
            (*fite)->m_chat->AddMsg(rq->msg);

            UserItem *item = new UserItem;
            item->SetInfo(&(*fite)->m_UserInfo,rq->m_userid);
            item->SetChatDlg((*fite)->GetChatDlg());
            item->num = (*fite)->num;
            item->SetCurrentMsg(rq->msg);
            if(item->m_chat->isHidden())
                item->UpdateMsgNum();
            m_Msgls.push_back(item);
            m_Msglayout->insertWidget(0,item);
            break;
        }
        ++fite;
    }
}

void QQMainDlg::closeEvent(QCloseEvent *)
{
    STRU_OFFLINE_RQ rq;
    rq.m_userid = m_userInfo->m_user_id;
    m_tcp->SendData((char *)&rq,sizeof(rq));
    exit(0);
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

void QQMainDlg::slot_AddMsg(char *szbuf, int mode)
{
    //聊天
    if(mode == 0)
    {
        bool bflag = false;
        UserItem *pitem = (UserItem*)szbuf;
        auto ite = m_Msgls.begin();
        while(ite!=m_Msgls.end())
        {
            if((*ite)->m_UserInfo.m_user_id == pitem->m_UserInfo.m_user_id)
            {
                bflag = true;
                break;
            }
            ++ite;
        }

        //曾经存在消息列表中
        if(bflag)
        {
            (*ite)->setVisible(false);
            m_Msglayout->removeWidget(*ite);
            (*ite)->setVisible(true);
            m_Msglayout->insertWidget(0,*ite);
        }
        else
        {
            UserItem *item = new UserItem;
            item->SetInfo(&pitem->m_UserInfo,pitem->m_userid);
            item->SetChatDlg(pitem->GetChatDlg());
            item->num = pitem->num;
            m_Msgls.push_back(item);
            m_Msglayout->insertWidget(0,item);
        }

    }//添加好友
    else if(mode == 1)
    {
        STRU_ADDFRIEND_RQ *rq = (STRU_ADDFRIEND_RQ*)szbuf;
        AddFriendItem *item = new AddFriendItem;
        item->SetInfo(&rq->m_UserInfo,rq->m_frid);
        auto ite = m_Addfrils.begin();
        while(ite!=m_Addfrils.end())
        {
            if((*ite)->m_userid == item->m_userid)
                return ;
            ++ite;
        }
        m_Addfrils.push_back(item);
        m_Msglayout->addWidget(item);
        connect(item,&AddFriendItem::SIG_mCloseWidget,[=](AddFriendItem*delItem)
        {
           auto ite = m_Addfrils.begin();
           while(ite!=m_Addfrils.end())
           {
               if((*ite)->m_userid == delItem->m_userid)
               {
                   m_Addfrils.erase(ite);
                   break;
               }
               ++ite;
           }
           delItem->setVisible(false);
           m_Msglayout->removeWidget(delItem);
           delete delItem;
           delItem = NULL;
        });
//        m_Addfrils.push_back(item);
//        m_Msglayout->addWidget(item);
//        connect(item,&AddFriendItem::SIG_mCloseWidget,[=](AddFriendItem*delItem)
//        {
//            auto ite = m_Addfrils.begin();
//            while(ite!=m_Addfrils.end())
//            {
//                if((*ite)->m_userid == delItem->m_userid)
//                {
//                    m_Addfrils.erase(ite);
//                    break;
//                }
//            }
//            delItem->setVisible(false);
//            m_Msglayout->removeWidget(delItem);
//            delete delItem;
//            delItem = NULL;
//        });
    }
}

void QQMainDlg::UpdateFriendStatus(char *szbuf)
{
    bool bFlag = false;
    STRU_UPDATE_STATUS *sus = (STRU_UPDATE_STATUS*)szbuf;
    auto ite = m_Friendls.begin();
    while(ite!=m_Friendls.end())
    {
        //好友更新信息
        if((*ite)->m_UserInfo.m_user_id == sus->m_UserInfo.m_user_id)
        {
            bFlag = true;
            (*ite)->setVisible(false);
            m_Frilayout->removeWidget(*ite);
            (*ite)->SetInfo(&sus->m_UserInfo,m_userInfo->m_user_id);
            (*ite)->setVisible(true);
            if(sus->m_UserInfo.m_status)
            {
                m_Frilayout->insertWidget(0,*ite);
            }
            else
                m_Frilayout->addWidget(*ite);
            break ;
        }

        ++ite;
    }
    if(bFlag)
    {
        ite = m_Msgls.begin();
        while(ite!=m_Msgls.end())
        {
            if((*ite)->m_UserInfo.m_user_id == sus->m_UserInfo.m_user_id)
            {
                (*ite)->setVisible(false);
                m_Msglayout->removeWidget(*ite);
                (*ite)->SetInfo(&sus->m_UserInfo,m_userInfo->m_user_id);
                (*ite)->setVisible(true);
                m_Msglayout->addWidget(*ite);

            }
            ++ite;
        }
    }
    else
    {
            //新加好友
            UserItem *item = new UserItem;
            item->SetInfo(&sus->m_UserInfo,m_userInfo->m_user_id);
            m_Friendls.push_back(item);
            if(sus->m_UserInfo.m_status)
            {
                m_Frilayout->insertWidget(0,item);
            }
            else
                m_Frilayout->addWidget(item);
    }
}
