#ifndef RECORD_DIALOG_H
#define RECORD_DIALOG_H

#include <QDialog>
#include <QFile>
#include <QTextStream>
#include "statement.h"

//这是纪录窗口

namespace Ui
{
    class record_Dialog;
}

class record_Dialog : public QDialog
{
    Q_OBJECT

public:
    //构造函数
    explicit record_Dialog(QWidget *parent = nullptr);

    //析构函数
    ~record_Dialog();

private slots:

    //重置纪录
    void on_reset_clicked();


private:
    Ui::record_Dialog *ui;
};

#endif // RECORD_DIALOG_H
