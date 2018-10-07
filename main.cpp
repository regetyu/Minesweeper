#include "mainwindow.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QFile file("primary_record.txt");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {   //如果文件不存在就创建文件
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream s(&file);
        s<<"N/A";
    }
    file.close();
    QFile file1("intermediate_record.txt");
    if(!file1.open(QIODevice::ReadOnly | QIODevice::Text))
    {   //如果文件不存在就创建文件
        file1.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream s(&file1);
        s<<"N/A";
    }
    file1.close();
    QFile file2("advance_record.txt");
    if(!file2.open(QIODevice::ReadOnly | QIODevice::Text))
    {   //如果文件不存在就创建文件
        file2.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream s(&file2);
        s<<"N/A";
    }
    file2.close();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
