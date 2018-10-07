#include "mineblock.h"

Mineblock::Mineblock()
{

}

Mineblock::Mineblock(const block_state &_state, const int &_num):state(_state), num(_num)
{

}


Mineblock::~Mineblock()
{

}

bool Mineblock::operator==(const block_state &_state)
{
    return(state==_state);
}

bool Mineblock::operator!=(const block_state &_state)
{
    return(state!=_state);
}

void Mineblock::operator=(const block_state &_state)
{
    state=_state;
}

bool Mineblock::operator==(const int &_num)
{
    return(num==_num);
}

bool Mineblock::operator!=(const int &_num)
{
    return(num!=_num);
}

bool Mineblock::operator<(const int &_num)
{
    return(num<_num);
}

bool Mineblock::operator>(const int &_num)
{
    return(num>_num);
}

bool Mineblock::operator<=(const int &_num)
{
    return(num<=_num);
}

bool Mineblock::operator>=(const int &_num)
{
    return(num>=_num);
}

void Mineblock::operator+=(const int &_num)
{
    num+=_num;
}

void Mineblock::operator=(const int &_num)
{
    num=_num;
}
