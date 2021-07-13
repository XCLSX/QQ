#ifndef ADDFRIENDITEM_H
#define ADDFRIENDITEM_H

#include <QWidget>
#include <Packdef.h>
namespace Ui {
class AddFriendItem;
}

class AddFriendItem : public QWidget
{
    Q_OBJECT

public:
    explicit AddFriendItem(QWidget *parent = nullptr);
    ~AddFriendItem();
    void SetInfo(STRU_USER_INFO *info,int);
private:
    Ui::AddFriendItem *ui;
    int m_fri_id; //被添加好友 此为自己id
    int m_userid;
};

#endif // ADDFRIENDITEM_H
