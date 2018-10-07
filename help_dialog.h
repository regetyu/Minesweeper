#ifndef HELP_DIALOG_H
#define HELP_DIALOG_H

#include <QDialog>

//这是帮助窗口

namespace Ui
{
    class help_Dialog;
}

class help_Dialog : public QDialog
{
    Q_OBJECT

public:
    //构造函数
    explicit help_Dialog(QWidget *parent = nullptr);

    //析构函数
    ~help_Dialog();

private:
    Ui::help_Dialog *ui;
};

#endif // HELP_DIALOG_H
