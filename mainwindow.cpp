#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //计时器初始化
    timer=new QTimer(this);

    connect(this, SIGNAL(game_start(int,int,int)), &obj, SLOT(initialize(int,int,int)));
    connect(this, SIGNAL(left_click(int,int)), &obj, SLOT(dig(int, int)));
    connect(this, SIGNAL(right_click(int, int)), &obj, SLOT(mark(int,int)));
    connect(this, SIGNAL(mid_click(int, int)), &obj, SLOT(quick_dig(int, int)));
    connect(&obj, SIGNAL(lose()), this, SLOT(lose()));
    connect(&obj, SIGNAL(win()), this, SLOT(win()));
    connect(timer, SIGNAL(timeout()), this, SLOT(updatetimer()));

    //默认是初级游戏
    emit game_start(9,9,10);
    setFixedSize(block_size*obj.column+offset_x*2, block_size*obj.row+offset_y*2);
    obj.mode=PRIMARY;
    time=0;
    obj.first_dig=true;
    update();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_primary_triggered()
{
    emit game_start(9,9,10);
    setFixedSize(block_size*obj.column+offset_x*2, block_size*obj.row+offset_y*2);
    obj.mode=PRIMARY;
    time=0;
    obj.first_dig=true;
    update();
}

void MainWindow::on_intermediate_triggered()
{
    emit game_start(16,16,40);
    setFixedSize(block_size*obj.column+offset_x*2, block_size*obj.row+offset_y*2);
    obj.mode=INTERMEDIATE;
    time=0;
    obj.first_dig=true;
    update();
}

void MainWindow::on_advance_triggered()
{
    emit game_start(16,30,99);
    setFixedSize(block_size*obj.column+offset_x*2, block_size*obj.row+offset_y*2);
    obj.mode=ADVANCE;
    time=0;
    obj.first_dig=true;
    update();
}

void MainWindow::on_customize_triggered()
{
    customlize_Dialog dialog(this);
    if(dialog.exec()==QDialog::Accepted)
    {
        emit game_start(dialog.row_num(), dialog.column_num(), dialog.mine_num());
        setFixedSize(block_size*obj.column+offset_x*2, block_size*obj.row+offset_y*2);
        obj.mode=CUSTOMIZE;
        time=0;
        obj.first_dig=true;
        update();
    }
}


void MainWindow::paintEvent(QPaintEvent *event)
{
    //加载图片
    QPainter painter(this);
    QPixmap png_blank(":/images/blank.png");
    QPixmap png_gray(":/images/gray.png");
    QPixmap png_1(":/images/1.png");
    QPixmap png_2(":/images/2.png");
    QPixmap png_3(":/images/3.png");
    QPixmap png_4(":/images/4.png");
    QPixmap png_5(":/images/5.png");
    QPixmap png_6(":/images/6.png");
    QPixmap png_7(":/images/7.png");
    QPixmap png_8(":/images/8.png");
    QPixmap png_mine(":/images/mine.png");
    QPixmap png_mark(":/images/mark.png");
    QPixmap png_wrong_mark(":/images/wrong_mark.png");
    QPixmap png_question(":/images/question.png");
    QPixmap png_00(":/images/00.png");
    QPixmap png_01(":/images/01.png");
    QPixmap png_02(":/images/02.png");
    QPixmap png_03(":/images/03.png");
    QPixmap png_04(":/images/04.png");
    QPixmap png_05(":/images/05.png");
    QPixmap png_06(":/images/06.png");
    QPixmap png_07(":/images/07.png");
    QPixmap png_08(":/images/08.png");
    QPixmap png_09(":/images/09.png");
    QPixmap png_smile(":/images/smile.png");
    QPixmap png_lose(":/images/lose.png");
    QPixmap png_win(":/images/win.png");

    //绘制图片
    for(int i=0; i<obj.row; i++)
        for(int k=0; k<obj.column; k++)
            {
                painter.drawPixmap(offset_x+k*block_size, offset_y+i*block_size, png_blank);
            }
    if(obj.state==PLAYING)
    {
        for(int i=0; i<obj.row; i++)
            for(int k=0; k<obj.column; k++)
            {
                switch(obj.map[i][k].state)
                {
                case DIGED:
                    painter.drawPixmap(offset_x+k*block_size, offset_y+i*block_size, png_gray);
                    switch(obj.map[i][k].num)
                    {
                    case -1:
                        painter.drawPixmap(offset_x+k*block_size, offset_y+i*block_size, png_mine);
                        break;
                    case 1:
                        painter.drawPixmap(offset_x+k*block_size, offset_y+i*block_size, png_1);
                        break;
                    case 2:
                        painter.drawPixmap(offset_x+k*block_size, offset_y+i*block_size, png_2);
                        break;
                    case 3:
                        painter.drawPixmap(offset_x+k*block_size, offset_y+i*block_size, png_3);
                        break;
                    case 4:
                        painter.drawPixmap(offset_x+k*block_size, offset_y+i*block_size, png_4);
                        break;
                    case 5:
                        painter.drawPixmap(offset_x+k*block_size, offset_y+i*block_size, png_5);
                        break;
                    case 6:
                        painter.drawPixmap(offset_x+k*block_size, offset_y+i*block_size, png_6);
                        break;
                    case 7:
                        painter.drawPixmap(offset_x+k*block_size, offset_y+i*block_size, png_7);
                        break;
                    case 8:
                        painter.drawPixmap(offset_x+k*block_size, offset_y+i*block_size, png_8);
                        break;
                     default:
                        break;
                    }
                    break;
                case MARKED:
                    painter.drawPixmap(offset_x+k*block_size, offset_y+i*block_size, png_mark);
                    break;
                case QUESTIONED:
                    painter.drawPixmap(offset_x+k*block_size, offset_y+i*block_size, png_question);
                    break;
                default:
                    break;
                }
            }
    }
    if(obj.state==LOSE||obj.state==WIN)
    {
        for(int i=0; i<obj.row; i++)
            for(int k=0; k<obj.column; k++)
            {
                switch(obj.map[i][k].state)
                {
                case DIGED:
                    painter.drawPixmap(offset_x+k*block_size, offset_y+i*block_size, png_gray);
                    switch(obj.map[i][k].num)
                    {
                    case -1:
                        painter.drawPixmap(offset_x+k*block_size, offset_y+i*block_size, png_mine);
                        break;
                    case 1:
                        painter.drawPixmap(offset_x+k*block_size, offset_y+i*block_size, png_1);
                        break;
                    case 2:
                        painter.drawPixmap(offset_x+k*block_size, offset_y+i*block_size, png_2);
                        break;
                    case 3:
                        painter.drawPixmap(offset_x+k*block_size, offset_y+i*block_size, png_3);
                        break;
                    case 4:
                        painter.drawPixmap(offset_x+k*block_size, offset_y+i*block_size, png_4);
                        break;
                    case 5:
                        painter.drawPixmap(offset_x+k*block_size, offset_y+i*block_size, png_5);
                        break;
                    case 6:
                        painter.drawPixmap(offset_x+k*block_size, offset_y+i*block_size, png_6);
                        break;
                    case 7:
                        painter.drawPixmap(offset_x+k*block_size, offset_y+i*block_size, png_7);
                        break;
                    case 8:
                        painter.drawPixmap(offset_x+k*block_size, offset_y+i*block_size, png_8);
                        break;
                     default:
                        break;
                    }
                    break;
                case MARKED:
                {
                    if(obj.map[i][k].num>=0)
                    {
                        painter.drawPixmap(offset_x+k*block_size, offset_y+i*block_size, png_blank);
                        painter.drawPixmap(offset_x+k*block_size, offset_y+i*block_size, png_wrong_mark);
                    }
                    else
                    {
                        painter.drawPixmap(offset_x+k*block_size, offset_y+i*block_size, png_blank);
                        painter.drawPixmap(offset_x+k*block_size, offset_y+i*block_size, png_mine);
                    }
                    break;
                }
                case QUESTIONED:
                    if(obj.map[i][k].num>=0)
                    {
                        painter.drawPixmap(offset_x+k*block_size, offset_y+i*block_size, png_blank);
                    }
                    else
                    {
                        painter.drawPixmap(offset_x+k*block_size, offset_y+i*block_size, png_blank);
                        painter.drawPixmap(offset_x+k*block_size, offset_y+i*block_size, png_mine);
                    }
                    break;
                case DEFAULT:
                    if(obj.map[i][k].num==-1)
                        painter.drawPixmap(offset_x+k*block_size, offset_y+i*block_size, png_mine);
            }
        }
    }

      //     painter.drawPixmap(0,0,png_time_1);
  //  qDebug()<<time/100<<time%100/10<<time%10;
    switch(time%10)
    {
    case 0:
        painter.drawPixmap(width()-264, 50, png_00);
        break;
    case 1:
        painter.drawPixmap(width()-264,50,png_01);
        break;
    case 2:
        painter.drawPixmap(width()-264,50,png_02);
        break;
    case 3:
        painter.drawPixmap(width()-264,50,png_03);
        break;
    case 4:
        painter.drawPixmap(width()-264,50,png_04);
        break;
    case 5:
        painter.drawPixmap(width()-264,50,png_05);
        break;
    case 6:
        painter.drawPixmap(width()-264,50,png_06);
        break;
    case 7:
        painter.drawPixmap(width()-264,50,png_07);
        break;
    case 8:
        painter.drawPixmap(width()-264,50,png_08);
        break;
    case 9:
        painter.drawPixmap(width()-264,50,png_09);
        break;
    default:
        break;
    }
    switch(time%100/10)
    {
    case 0:
        painter.drawPixmap(width()-328,50,png_00);
        break;
    case 1:
        painter.drawPixmap(width()-328,50,png_01);
        break;
    case 2:
        painter.drawPixmap(width()-328,50,png_02);
        break;
    case 3:
        painter.drawPixmap(width()-328,50,png_03);
        break;
    case 4:
        painter.drawPixmap(width()-328,50,png_04);
        break;
    case 5:
        painter.drawPixmap(width()-328,50,png_05);
        break;
    case 6:
        painter.drawPixmap(width()-328,50,png_06);
        break;
    case 7:
        painter.drawPixmap(width()-328,50,png_07);
        break;
    case 8:
        painter.drawPixmap(width()-328,50,png_08);
        break;
    case 9:
        painter.drawPixmap(width()-328,50,png_09);
        break;
    default:
        break;
    }
    switch(time/100)
    {
    case 0:
        painter.drawPixmap(width()-392,50, png_00);
        break;
    case 1:
        painter.drawPixmap(width()-392,50,png_01);
        break;
    case 2:
        painter.drawPixmap(width()-392,50,png_02);
        break;
    case 3:
        painter.drawPixmap(width()-392,50,png_03);
        break;
    case 4:
        painter.drawPixmap(width()-392,50,png_04);
        break;
    case 5:
        painter.drawPixmap(width()-392,50,png_05);
        break;
    case 6:
        painter.drawPixmap(width()-392,50,png_06);
        break;
    case 7:
        painter.drawPixmap(width()-392,50,png_07);
        break;
    case 8:
        painter.drawPixmap(width()-392,50,png_08);
        break;
    case 9:
        painter.drawPixmap(width()-392,50,png_09);
        break;
    default:
        break;
    }
    switch(obj.mine_remain/100)
    {
    case 0:
        painter.drawPixmap(200,50,png_00);
        break;
    case 1:
        painter.drawPixmap(200,50,png_01);
        break;
    case 2:
        painter.drawPixmap(200,50,png_02);
        break;
    case 3:
        painter.drawPixmap(200,50,png_03);
        break;
    case 4:
        painter.drawPixmap(200,50,png_04);
        break;
    case 5:
        painter.drawPixmap(200,50,png_05);
        break;
    case 6:
        painter.drawPixmap(200,50,png_06);
        break;
    case 7:
        painter.drawPixmap(200,50,png_07);
        break;
    case 8:
        painter.drawPixmap(200,50,png_08);
        break;
    case 9:
        painter.drawPixmap(200,50,png_09);
        break;
    default:
        break;
    }
    switch(obj.mine_remain%100/10)
    {
    case 0:
        painter.drawPixmap(264,50,png_00);
        break;
    case 1:
        painter.drawPixmap(264,50,png_01);
        break;
    case 2:
        painter.drawPixmap(264,50,png_02);
        break;
    case 3:
        painter.drawPixmap(264,50,png_03);
        break;
    case 4:
        painter.drawPixmap(264,50,png_04);
        break;
    case 5:
        painter.drawPixmap(264,50,png_05);
        break;
    case 6:
        painter.drawPixmap(264,50,png_06);
        break;
    case 7:
        painter.drawPixmap(264,50,png_07);
        break;
    case 8:
        painter.drawPixmap(264,50,png_08);
        break;
    case 9:
        painter.drawPixmap(264,50,png_09);
        break;
    default:
        break;
    }
    switch(obj.mine_remain%10)
    {
    case 0:
        painter.drawPixmap(328,50,png_00);
        break;
    case 1:
        painter.drawPixmap(328,50,png_01);
        break;
    case 2:
        painter.drawPixmap(328,50,png_02);
        break;
    case 3:
        painter.drawPixmap(328,50,png_03);
        break;
    case 4:
        painter.drawPixmap(328,50,png_04);
        break;
    case 5:
        painter.drawPixmap(328,50,png_05);
        break;
    case 6:
        painter.drawPixmap(328,50,png_06);
        break;
    case 7:
        painter.drawPixmap(328,50,png_07);
        break;
    case 8:
        painter.drawPixmap(328,50,png_08);
        break;
    case 9:
        painter.drawPixmap(328,50,png_09);
        break;
    default:
        break;
    }

    switch(obj.state)
    {
    case WIN:
        painter.drawPixmap(width()/2-32, 68, png_win);
        break;
    case LOSE:
        painter.drawPixmap(width()/2-32, 68, png_lose);
        break;
    default:
        painter.drawPixmap(width()/2-32, 68, png_smile);
    }



    for(int i=0;i<=obj.row;i++)
    {
        painter.drawLine(offset_x, offset_y+i*block_size, offset_x+obj.column*block_size, offset_y+i*block_size);
    }
    for(int k=0; k<=obj.column; k++)
    {
        painter.drawLine(offset_x+k*block_size, offset_y, offset_x+k*block_size, offset_y+obj.row*block_size);
    }

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(obj.state==NOTPLAY||obj.state==PLAYING)
    {
        int k=(event->x()-offset_x)/block_size, i=(event->y()-offset_y)/block_size;
        if(event->x()>=offset_x&&i<obj.row&&event->y()>=offset_y&&k<obj.column)
        {
            if(obj.state==NOTPLAY)
                timer->start(1000);
            obj.state=PLAYING;
            if(event->button()==Qt::LeftButton)
            {
                emit left_click(i, k);
                update();
            }
            if(event->button()==Qt::RightButton)
            {
                emit right_click(i, k);
                update();
            }
            if(event->button()==Qt::MidButton)
            {
                emit mid_click(i, k);
                update();
            }
        }
    }
    if(event->y()>=68&&event->y()<132&&event->x()>=width()/2-32&&event->y()<width()/2+32&&event->button()==Qt::LeftButton)
    {
        emit game_start(obj.row, obj.column, obj.mine_totalnum);
        time=0;
        obj.first_dig=true;
        timer->stop();
        update();
    }
}


void MainWindow::lose()
{
    timer->stop();
    QMessageBox box(QMessageBox::Information, "You lose", "You lose!", QMessageBox::Ok, this);
    box.exec();
}

void MainWindow::win()
{
    timer->stop();
    check_record(time, obj.mode);
    QMessageBox box(QMessageBox::Information, "You win", "You win!", QMessageBox::Ok, this);
    box.exec();
}



void MainWindow::updatetimer()
{
    if(time<=999)
    {   //最大时间数为999
        time++;
        update();
    }
}

void MainWindow::on_record_triggered()
{
    record_Dialog dialog(this);
    dialog.exec();
}

void MainWindow::check_record(const int &a, const game_mode &mode)
{
    if(mode==PRIMARY)
    {
        QFile file("primary_record.txt");
        QString primary;
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream in(&file);
        in>>primary;
        if(primary=="N/A"||(primary!="N/A"&&primary.toInt()>a))
        {
            file.close();
            QFile _file("primary_record.txt");
            _file.open(QIODevice::WriteOnly | QIODevice::Text);
            QTextStream out(&_file);
            out<<a;
        }
    }
    if(mode==INTERMEDIATE)
    {
        QFile file("intermediate_record.txt");
        QString intermediate;
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream in(&file);
        in>>intermediate;
        if(intermediate=="N/A"||(intermediate!="N/A"&&intermediate.toInt()>a))
        {
            file.close();
            QFile _file("intermediate.txt");
            _file.open(QIODevice::WriteOnly | QIODevice::Text);
            QTextStream out(&_file);
            out<<a;
        }
    }
    if(mode==ADVANCE)
    {
        QFile file("advance.txt");
        QString advance;
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream in(&file);
        in>>advance;
        if(advance=="N/A"||(advance!="N/A"&&advance.toInt()>a))
        {
            file.close();
            QFile _file("advance.txt");
            _file.open(QIODevice::WriteOnly | QIODevice::Text);
            QTextStream out(&_file);
            out<<a;
        }
    }
}

void MainWindow::on_help_triggered()
{
    help_Dialog dialog(this);
    dialog.exec();
}

void MainWindow::on_about_triggered()
{
    about_Dialog dialog(this);
    dialog.exec();
}
