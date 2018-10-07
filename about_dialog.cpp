#include "about_dialog.h"
#include "ui_about_dialog.h"

about_Dialog::about_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::about_Dialog)
{
    ui->setupUi(this);
    setFixedSize(600, 300);  //设定固定窗口大小
    setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);  //去除"?"按钮
}

about_Dialog::~about_Dialog()
{
    delete ui;
}
