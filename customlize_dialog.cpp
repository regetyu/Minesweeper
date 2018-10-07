#include "customlize_dialog.h"
#include "ui_customlize_dialog.h"

customlize_Dialog::customlize_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::customlize_Dialog)
{
    ui->setupUi(this);
    setFixedSize(500,400);  //设置固定窗口大小
    setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);  //去除"?"按钮
    ui->mine->setMaximum((ui->row->value()-1)*(ui->column->value()-1));  //设置最大雷数
    setTabOrder(ui->row, ui->column);
    setTabOrder(ui->column, ui->mine);
    setTabOrder(ui->mine, ui->ok);
    setTabOrder(ui->ok, ui->cancel);
    setTabOrder(ui->cancel, ui->row);
    connect(ui->row, SIGNAL(valueChanged(int)), this, SLOT(set_mine_range(int)));
    connect(ui->column, SIGNAL(valueChanged(int)), this, SLOT(set_mine_range(int)));
}

customlize_Dialog::~customlize_Dialog()
{
    delete ui;
}

int customlize_Dialog::row_num()
{
    return ui->row->value();
}

int customlize_Dialog::column_num()
{
    return ui->column->value();
}

int customlize_Dialog::mine_num()
{
    return ui->mine->value();
}

void customlize_Dialog::set_mine_range(int)
{
    ui->mine->setMaximum((ui->row->value()-1)*(ui->column->value()-1));
}

