#ifndef CUSTOMLIZE_DIALOG_H
#define CUSTOMLIZE_DIALOG_H

#include <QDialog>

//这是自定义游戏窗口

namespace Ui
{
    class customlize_Dialog;
}

class customlize_Dialog : public QDialog
{
    Q_OBJECT

public:
    //构造函数
    explicit customlize_Dialog(QWidget *parent = nullptr);

    //析构函数
    ~customlize_Dialog();

    //返回列数
    int row_num();

    //返回行数
    int column_num();

    //返回雷数
    int mine_num();

private slots:
    //根据列数和行数设定雷数的范围
    void set_mine_range(int);

private:
    Ui::customlize_Dialog *ui;
};

#endif // CUSTOMLIZE_DIALOG_H
