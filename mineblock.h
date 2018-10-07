#ifndef MINEBLOCK_H
#define MINEBLOCK_H

#include "statement.h"

//这个类包含一个雷块的信息

class Mineblock
{
public:
    //雷块的状态, 包括DEFAULT, DIGED, MARKED, QUESTIONED
    block_state state;

    //雷块的数字，-1代表有雷
    int num;

    //构造函数
    Mineblock();

    //构造函数
    Mineblock(const block_state &_state, const int &_num);


    //转换为block_state类变量运算
    bool operator ==(const block_state &_state);
    bool operator !=(const block_state &_state);
    void operator =(const block_state &_state);

    //转换为int型运算
    bool operator ==(const int &_num);
    bool operator !=(const int &_num);
    bool operator <(const int &_num);
    bool operator >(const int &_num);
    bool operator <=(const int &_num);
    bool operator >=(const int &_num);
    void operator +=(const int &_num);
    void operator =(const int &_num);

    //析构函数
    ~Mineblock();
};

#endif // MINEBLOCK_H
