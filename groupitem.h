#ifndef GROUPITEM_H
#define GROUPITEM_H

#include <QWidget>
#include <Packdef.h>
#include <groupchatdlg.h>
#include <QMouseEvent>
#include <QMenu>
namespace Ui {
class GroupItem;
}

class GroupItem : public QWidget
{
    Q_OBJECT

public:
    explicit GroupItem(int userid,QWidget *parent = nullptr);
    ~GroupItem();



public:
    void SetInfo(QString group_name,int group_id, int iconid ,list<STRU_USER_INFO*>ls);
    void mouseDoubleClickEvent(QMouseEvent *event);
    GroupChatDlg *GetChatDlg();
    void UpdateMsgNum();
    void SetCurrentMsg(char *);
    void ChangeIconColor(int status,int);
    void mousePressEvent(QMouseEvent*event);
    GroupItem *m_Copy();
    void GetMsg(int userid,QString msg);
    int *num;   //未读消息数
signals:
    //void SIG_DelMsg(int);
private slots:
    //void slot_DealMenu(QAction*);
public:
    Ui::GroupItem *ui;
    QString m_group_name;
    int m_group_id;   //群id
    int m_userid;
    int m_iconid;
    GroupChatDlg *m_chatdlg;
    //ChatDlg *m_chat;
    //QMenu *m_UserMenu;
};

#endif // GROUPITEM_H
