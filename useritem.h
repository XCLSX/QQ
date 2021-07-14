#ifndef USERITEM_H
#define USERITEM_H

#include <QWidget>
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
    void SetInfo(STRU_USER_INFO*);
private slots:
public:
    int m_mode;
    Ui::UserItem *ui;
    int m_userid;
    QString m_name;
    QString m_feeling;
    int status;
    int m_iconid;

};

#endif // USERITEM_H
