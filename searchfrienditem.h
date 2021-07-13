#ifndef SEARCHFRIENDITEM_H
#define SEARCHFRIENDITEM_H

#include <QWidget>
#include <Packdef.h>

namespace Ui {
class SearchFriendItem;
}

class SearchFriendItem : public QWidget
{
    Q_OBJECT

public:
    explicit SearchFriendItem(STRU_USER_INFO*,QWidget *parent = nullptr);
    ~SearchFriendItem();
    void InitInfo(STRU_USER_INFO *);

private slots:
    void on_pb_add_clicked();

private:
    Ui::SearchFriendItem *ui;
    int m_frid;
    QString m_name;
    QString m_feeling;
    int status;
    int m_iconid;
    STRU_USER_INFO *m_UserInfo;//自己的信息
};

#endif // SEARCHFRIENDITEM_H
