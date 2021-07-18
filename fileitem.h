#ifndef FILEITEM_H
#define FILEITEM_H

#include <QWidget>
namespace Ui {
class FileItem;
}

class FileItem : public QWidget
{
    Q_OBJECT

public:
    explicit FileItem(QString,int,QWidget *parent = nullptr);
    ~FileItem();
    QString GetFileName();
    void SetThread(QThread*);
private slots:
    void slot_ChangeProcessBar(int);
    void on_pb_pause_clicked();

private:
    Ui::FileItem *ui;
    QString fileName;
    QThread *m_thread;
    bool bFlag;
};

#endif // FILEITEM_H
