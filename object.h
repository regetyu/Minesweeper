#ifndef OBJECT_H
#define OBJECT_H

#include <QObject>
#include <QVector>
#include "mineblock.h"
#include <QDebug>
#include <QtGlobal>
#include <QTimer>
#include <QTime>
#include <QMessageBox>

//这个类存储了游戏的大部分信息

typedef QVector <QVector <Mineblock>> Matrix;
typedef QVector <Mineblock> Row;

class object : public QObject
{
    Q_OBJECT
public:
    //地图是一个二维向量
    Matrix map;

    //地图行数
    int row;

    //地图列数
    int column;

    //总雷数
    int mine_totalnum;

    //剩余雷数
    int mine_remain;

    //是否是第一次挖雷
    bool first_dig;

    //游戏状态
    game_state state;

    //游戏模式
    game_mode mode;

    //构造函数
    explicit object(QObject *parent = nullptr);

    //改变游戏状态
    void change_game_state();

    //如果是空格自动挖周围的8个雷
    void autodig(const int &i, const int &k);
signals:

    //输
    void lose();

    //赢
    void win();


public slots:

    //初始化
    void initialize(const int & _row, const int &_column, const int &_mine_totalnum);

    //右键标记
    void mark(const int &i, const int &k);

    //中键挖雷
    void quick_dig(const int &i, const int &k);

    //左键挖雷
    void dig(const int &i, const int &k);
};


//全局变量
extern object obj;

#endif // OBJECT_H
