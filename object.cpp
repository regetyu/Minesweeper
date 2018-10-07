#include "object.h"

object obj;


object::object(QObject *parent) : QObject(parent)
{

}

void object::initialize(const int &_row, const int &_column , const int &_mine_totalnum)
{
    row=_row;
    column=_column;
    mine_totalnum=_mine_totalnum;
    mine_remain=mine_totalnum;
    state=NOTPLAY;
    map.clear();

    for(int i=0; i<row; i++)
    {
        Row a;
        map.push_back(a);
        for(int k=0; k<column; k++)
            map[i].push_back(Mineblock(DEFAULT,0));
    }

    //生成随机数
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    for(int i=0; i<mine_totalnum; )
    {
        int a=qrand()%row;
        int b=qrand()%column;
        if(map[a][b]>=0)
        {
            map[a][b]=-1;
            i++;
        }
    }
    for(int i=0; i<row; i++)
        for(int k=0; k<column; k++)
            if(map[i][k]!=-1)
            {
               if(i!=row-1&&k!=column-1)
                   if(map[i+1][k+1]<0)
                       map[i][k]+=1;
               if(i!=row-1)
                   if(map[i+1][k]<0)
                       map[i][k]+=1;
               if(i!=row-1&&k!=0)
                   if(map[i+1][k-1]<0)
                       map[i][k]+=1;
               if(k!=column-1)
                   if(map[i][k+1]<0)
                       map[i][k]+=1;
               if(k!=0)
                   if(map[i][k-1]<0)
                       map[i][k]+=1;
               if(i!=0&&k!=column-1)
                   if(map[i-1][k+1]<0)
                       map[i][k]+=1;
               if(i!=0)
                   if(map[i-1][k]<0)
                       map[i][k]+=1;
               if(i!=0&&k!=0)
                   if(map[i-1][k-1]<0)
                       map[i][k]+=1;
            }
}

void object::dig(const int &i, const int &k)
{
    if(first_dig==true)
    {
        first_dig=false;
        if(map[i][k]==-1)
        {
            int a=0,b=0;
            bool flag=false;
            for(; a<row&&flag==false; a++)
                for(b=0; b<column&&flag==false; b++)
                    if(map[a][b]!=-1)
                        flag=true;
            map[i][k]=0;
            map[a][b]=-1;
            for(int i=0; i<row; i++)
                for(int k=0; k<column; k++)
                    if(map[i][k]!=-1)
                    {
                        map[i][k]=0;
                       if(i!=row-1&&k!=column-1)
                           if(map[i+1][k+1]<0)
                               map[i][k]+=1;
                       if(i!=row-1)
                           if(map[i+1][k]<0)
                               map[i][k]+=1;
                       if(i!=row-1&&k!=0)
                           if(map[i+1][k-1]<0)
                               map[i][k]+=1;
                       if(k!=column-1)
                           if(map[i][k+1]<0)
                               map[i][k]+=1;
                       if(k!=0)
                           if(map[i][k-1]<0)
                               map[i][k]+=1;
                       if(i!=0&&k!=column-1)
                           if(map[i-1][k+1]<0)
                               map[i][k]+=1;
                       if(i!=0)
                           if(map[i-1][k]<0)
                               map[i][k]+=1;
                       if(i!=0&&k!=0)
                           if(map[i-1][k-1]<0)
                               map[i][k]+=1;
                    }
        }

    }
    if(map[i][k]==DEFAULT)
    {
        map[i][k]=DIGED;
        autodig(i,k);
        change_game_state();
    }
}


void object::mark(const int &i, const int &k)
{
    switch(map[i][k].state)
    {
    case DEFAULT:
        map[i][k]=MARKED;
        mine_remain--;
        break;
    case MARKED:
        map[i][k]=QUESTIONED;
        mine_remain++;
        break;
    case QUESTIONED:
        map[i][k]=DEFAULT;
        break;
    default:
        break;
    }
}

void object::change_game_state()
{
    if(state==PLAYING)
    {
        for(int i=0;i<row; i++)
            for(int k=0; k<column; k++)
            {
                if(map[i][k]==DIGED&&map[i][k]==-1)
                {
                    state=LOSE;
                    emit lose();
                }
            }
        bool flag=true;
        for(int i=0; i<row; i++)
            for(int k=0; k<column; k++)
            {
                if(map[i][k]!=DIGED&&map[i][k]>=0)
                    flag=false;
            }
        if(flag==true)
        {
            state=WIN;
            emit win();
        }
    }
}

void object::autodig(const int &i, const int &k)
{
    if(map[i][k]==DIGED&&map[i][k]==0)
    {
       if(i!=row-1&&k!=column-1)
           dig(i+1,k+1);
       if(i!=row-1)
           dig(i+1,k);
       if(i!=row-1&&k!=0)
           dig(i+1,k-1);
       if(k!=column-1)
           dig(i, k+1);
       if(k!=0)
           dig(i, k-1);
       if(i!=0&&k!=column-1)
           dig(i-1,k+1);
       if(i!=0)
           dig(i-1,k);
       if(i!=0&&k!=0)
           dig(i-1,k-1);
    }
}


void object::quick_dig(const int &i, const int &k)
{
    if(map[i][k]==DIGED)
    {
        int temp=0;
        if(i!=row-1&&k!=column-1)
            if(map[i+1][k+1]==MARKED)
                temp++;
        if(i!=row-1)
            if(map[i+1][k]==MARKED)
                temp++;
        if(i!=row-1&&k!=0)
            if(map[i+1][k-1]==MARKED)
                temp++;
        if(k!=column-1)
            if(map[i][k+1]==MARKED)
                temp++;
        if(k!=0)
            if(map[i][k-1]==MARKED)
                temp++;
        if(i!=0&&k!=column-1)
            if(map[i-1][k+1]==MARKED)
                temp++;
        if(i!=0)
            if(map[i-1][k]==MARKED)
                temp++;
        if(i!=0&&k!=0)
            if(map[i-1][k-1]==MARKED)
                temp++;
        if(map[i][k]<=temp)
        {
            if(i!=row-1&&k!=column-1)
                if(map[i+1][k+1]==DEFAULT)
                    dig(i+1,k+1);
            if(i!=row-1)
                if(map[i+1][k]==DEFAULT)
                    dig(i+1,k);
            if(i!=row-1&&k!=0)
                if(map[i+1][k-1]==DEFAULT)
                    dig(i+1,k-1);
            if(k!=column-1)
                if(map[i][k+1]==DEFAULT)
                    dig(i,k+1);
            if(k!=0)
                if(map[i][k-1]==DEFAULT)
                    dig(i,k-1);
            if(i!=0&&k!=column-1)
                if(map[i-1][k+1]==DEFAULT)
                    dig(i-1,k+1);
            if(i!=0)
                if(map[i-1][k]==DEFAULT)
                    dig(i-1,k);
            if(i!=0&&k!=0)
                if(map[i-1][k-1]==DEFAULT)
                    dig(i-1,k-1);
        }

    }
}

