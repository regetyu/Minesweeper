#ifndef STATEMENT_H
#define STATEMENT_H


//雷块的状态
enum block_state
{
    DEFAULT, DIGED, MARKED, QUESTIONED
};

//游戏状态
enum game_state
{
    NOTPLAY, PLAYING, WIN, LOSE
};

//游戏模式
enum game_mode
{
    PRIMARY, INTERMEDIATE, ADVANCE, CUSTOMIZE
};

//雷块大小
const static int block_size=64;

//主窗口左右空白大小
const static int offset_x=200;

//主窗口上下空白大小
const static int offset_y=200;

#endif // STATEMENT_H
