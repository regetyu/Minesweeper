#ifndef ABOUT_DIALOG_H
#define ABOUT_DIALOG_H

#include <QDialog>

//这是"关于"界面窗口

namespace Ui
{
    class about_Dialog;
}

class about_Dialog : public QDialog
{
    Q_OBJECT

public:
    //构造函数
    explicit about_Dialog(QWidget *parent = nullptr);

    //析构函数
    ~about_Dialog();

private:
    Ui::about_Dialog *ui;
};

#endif // ABOUT_DIALOG_H
