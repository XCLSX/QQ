#ifndef USERITEM_H
#define USERITEM_H

#include <QWidget>
#include<chatdlg.h>
#include <Packdef.h>
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
    void SetCurrentMsg(char *);
    void ChangeIconColor(int status,int);
    int *num;
private slots:
public:
    Ui::UserItem *ui;
    STRU_USER_INFO m_UserInfo;
    int m_userid;   //自己id
    ChatDlg *m_chat;


};

#endif // USERITEM_H
