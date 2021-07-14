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

public:

    int m_fri_id; //被添加好友 此为自己id
    int m_userid;
signals:
    void SIG_mCloseWidget(AddFriendItem*);
    void SIG_Accept(AddFriendItem*,char *);
private slots:
    void on_pb_refuse_clicked();

    void on_pb_accept_clicked();

private:
    //friend class
    Ui::AddFriendItem *ui;

};

#endif // ADDFRIENDITEM_H
