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
    void Pause();
    QString GetFilePath();
private slots:
    void slot_ChangeProcessBar(int);
    void on_pb_pause_clicked();
    void on_pb_accept_clicked();

signals:
    void SIG_PAUSE();
    void SIG_ACCEPT();

private:
    Ui::FileItem *ui;
    QString fileName;
    QThread *m_thread;
    QString FilePath;
    bool bFlag;
};

#endif // FILEITEM_H
