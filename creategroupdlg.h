#ifndef CREATEGROUPDLG_H
#define CREATEGROUPDLG_H

#include <QWidget>
#include <Packdef.h>
namespace Ui {
class CreateGroupDlg;
}

class CreateGroupDlg : public QWidget
{
    Q_OBJECT

public:
    explicit CreateGroupDlg(int,QWidget *parent = nullptr);
    ~CreateGroupDlg();

private slots:
    void on_pb_commit_clicked();

private:
    Ui::CreateGroupDlg *ui;
    int m_userid;
};

#endif // CREATEGROUPDLG_H
