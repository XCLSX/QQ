#include "fileitem.h"
#include "ui_fileitem.h"
#include <QFileDialog>
FileItem::FileItem(QString str,int mode,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileItem)
{
    ui->setupUi(this);
    bFlag = true;
    if(mode == 0)
    {
        ui->pb_accept->hide();
        ui->pb_refuse->hide();
    }
    else
    {
        ui->pb_pause->hide();
        ui->pb_stop->hide();
        ui->progressBar->hide();
    }
    fileName = str;
    ui->lb_fileName->setText(fileName);
    ui->progressBar->setValue(0);
    m_thread = NULL;

}

FileItem::~FileItem()
{
    delete ui;
}

QString FileItem::GetFileName()
{
    return fileName;
}

void FileItem::SetThread(QThread *t)
{
    m_thread = t;
}

void FileItem::Pause()
{
    Q_EMIT SIG_PAUSE();
}

QString FileItem::GetFilePath()
{
    return FilePath;
}

void FileItem::slot_ChangeProcessBar(int val)
{
    ui->progressBar->setValue(val);

}


void FileItem::on_pb_pause_clicked()
{
    if(!m_thread)
        return ;
   Q_EMIT SIG_PAUSE();
}

void FileItem::on_pb_accept_clicked()
{
    ui->pb_accept->hide();
    ui->pb_refuse->hide();
    ui->pb_stop->show();
    ui->pb_pause->show();
    ui->progressBar->show();
    //FilePath = "D:\\迅雷下载\\";
    FilePath = QFileDialog::getExistingDirectory(this,QString("选择文件保存路径"),"C/");
    Q_EMIT SIG_ACCEPT();
}
