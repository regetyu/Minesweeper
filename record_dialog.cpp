#include "record_dialog.h"
#include "ui_record_dialog.h"

record_Dialog::record_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::record_Dialog)
{
    setFixedSize(400,300);
    setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);
    QString primary, intermediate, advance;
    ui->setupUi(this);
    setTabOrder(ui->reset, ui->ok);
    setTabOrder(ui->ok, ui->reset);
    QFile file("primary_record.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    in>>primary;
    file.close();
    QFile file1("intermediate_record.txt");
    file1.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in1(&file1);
    in1>>intermediate;
    file1.close();
    QFile file2("advance_record.txt");
    file2.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in2(&file2);
    in2>>advance;
    file2.close();
    ui->primary->setText(primary);
    ui->intermediate->setText(intermediate);
    ui->advance->setText(advance);
}

record_Dialog::~record_Dialog()
{
    delete ui;
}

void record_Dialog::on_reset_clicked()
{
    QFile file("primary_record.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out<<"N/A";
    file.close();
    QFile file1("intermediate_record.txt");
    file1.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out1(&file1);
    out1<<"N/A";
    file1.close();
    QFile file2("advance_record.txt");
    file2.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out2(&file2);
    out2<<"N/A";
    file2.close();
    ui->primary->setText("N/A");
    ui->intermediate->setText("N/A");
    ui->advance->setText("N/A");
}



