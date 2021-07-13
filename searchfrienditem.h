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
    explicit SearchFriendItem(QWidget *parent = nullptr);
    ~SearchFriendItem();
    void InitInfo(STRU_USER_INFO *);

private:
    Ui::SearchFriendItem *ui;
    int m_userid;
    QString m_name;
    QString m_feeling;
    int status;
    int m_iconid;
};

#endif // SEARCHFRIENDITEM_H
