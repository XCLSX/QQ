#include "fileitem.h"
#include "ui_fileitem.h"

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
    fileName = str;
    ui->lb_fileName->setText(fileName);
    ui->progressBar->setValue(0);
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

void FileItem::slot_ChangeProcessBar(int val)
{
    ui->progressBar->setValue(val);

}


void FileItem::on_pb_pause_clicked()
{
    if(bFlag)
    {
        //m_thread->
    }
}
