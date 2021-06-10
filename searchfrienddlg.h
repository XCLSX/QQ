#ifndef SEARCHFRIENDDLG_H
#define SEARCHFRIENDDLG_H

#include <QDialog>
#include <Packdef.h>
namespace Ui {
class SearchFriendDlg;
}

class SearchFriendDlg : public QDialog
{
    Q_OBJECT

public:
    explicit SearchFriendDlg(QWidget *parent = nullptr);
    ~SearchFriendDlg();

signals:
    void SIG_Search(char *,int);
private slots:
    void on_pb_search_clicked();

private:
    Ui::SearchFriendDlg *ui;
};

#endif // SEARCHFRIENDDLG_H
