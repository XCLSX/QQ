#ifndef SEARCHFRIENDDLG_H
#define SEARCHFRIENDDLG_H

#include <QDialog>
#include <Packdef.h>
#include <searchfrienditem.h>
#include <QVBoxLayout>
namespace Ui {
class SearchFriendDlg;
}

class SearchFriendDlg : public QDialog
{
    Q_OBJECT

public:
    explicit SearchFriendDlg(int,QWidget *parent = nullptr);
    ~SearchFriendDlg();
    void AddFriWidget(QWidget*item);
    void ClearLayout();
    vector<SearchFriendItem*> vec_friend;

signals:
    void SIG_Search(char *,int);
private slots:
    //void slot_UpdateFriList(char *);

    void on_pb_people_search_clicked();

    void on_pb_group_search_clicked();

private:
    Ui::SearchFriendDlg *ui;
    int m_userid;
    QVBoxLayout *m_friLayout;
    QVBoxLayout *m_groupLayout;
};

#endif // SEARCHFRIENDDLG_H
