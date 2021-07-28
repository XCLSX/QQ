#ifndef USERITEM_H
#define USERITEM_H

#include <QWidget>
#include<chatdlg.h>
#include <Packdef.h>
#include <QMouseEvent>
#include <QMenu>
namespace Ui {
class UserItem;
}

class UserItem : public QWidget
{
    Q_OBJECT

public:
    explicit UserItem(QWidget *parent = nullptr);
    ~UserItem();
    void SetInfo(STRU_USER_INFO*,int );
    void mouseDoubleClickEvent(QMouseEvent *event);
    ChatDlg *GetChatDlg();
    void SetChatDlg(ChatDlg*);
    void UpdateMsgNum();
    void SetCurrentMsg(QString);
    void ChangeIconColor(int status,int);
    void mousePressEvent(QMouseEvent*event);
    UserItem *m_Copy();
    int *num;
signals:
    void SIG_DelMsg(int);
private slots:
    void slot_DealMenu(QAction*);
public:
    Ui::UserItem *ui;
    STRU_USER_INFO m_UserInfo;
    int m_userid;   //自己id
    ChatDlg *m_chat;
    QMenu *m_UserMenu;


};

#endif // USERITEM_H
