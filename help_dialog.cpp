#include "help_dialog.h"
#include "ui_help_dialog.h"

help_Dialog::help_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::help_Dialog)
{
    ui->setupUi(this);
    setFixedSize(800,600);  //设置固定窗口大小
    setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);  //去除"?"按钮
}

help_Dialog::~help_Dialog()
{
    delete ui;
}
