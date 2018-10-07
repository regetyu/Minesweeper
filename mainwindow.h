#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>
#include <QMessageBox>
#include "record_dialog.h"
#include "object.h"
#include "customlize_dialog.h"
#include "about_dialog.h"
#include "help_dialog.h"



//这是主窗口


namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //构造函数
    explicit MainWindow(QWidget *parent = nullptr);

    //析构函数
    ~MainWindow();

    //一秒的timer
    QTimer *timer;

    //总游戏时间
    int time;


    //检查记录是否被打破，如果是就刷新纪录
    void check_record(const int &a, const game_mode &mode);

protected:
    virtual void paintEvent(QPaintEvent *event);

    virtual void mousePressEvent(QMouseEvent *event);

private slots:
    //初级游戏
    void on_primary_triggered();

    //中级游戏
    void on_intermediate_triggered();

    //高级游戏
    void on_advance_triggered();

    //自定义游戏
    void on_customize_triggered();

    //输了
    void lose();

    //赢了
    void win();

    //每过一秒总游戏时间+1
    void updatetimer();

    //纪录窗口
    void on_record_triggered();

    //帮助窗口
    void on_help_triggered();

    //关于窗口
    void on_about_triggered();

signals:
    //开始游戏
    void game_start(int, int, int);

    //左键点击
    void left_click(int, int);

    //右键点击
    void right_click(int ,int);

    //中建点击
    void mid_click(int, int);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
