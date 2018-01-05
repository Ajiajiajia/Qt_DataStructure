#include "test.h"
#include "ui_test.h"

#include <QPainter>
#include <QResizeEvent>
#include<QColor>
#include<iostream>
#include <stdio.h>
#include <QTime>
#include <sys/select.h>
#include<cstring>
using namespace std;

int a[100][100];
test::test(QWidget *parent, Qt::WindowFlags f) :
    QWidget(parent,f),
    ui(new Ui::test)
{
    ui->setupUi(this);
    mPixmap = new QPixmap(1366,768);
    mPainter = new QPainter(mPixmap);
    resize(1366,768);
    mPixmap->fill(QColor(255,255,255));
    count=0;
    currentNumber=0;

}

void sleep(unsigned int msec)
{

    QTime dieTime = QTime::currentTime().addMSecs(msec);

    while( QTime::currentTime() < dieTime )

        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

}


test::~test()
{
    delete ui;
    delete mPainter;
    delete mPixmap;
}

void test::resizeEvent(QResizeEvent *event)
{
    if(event->size().width() > mPixmap->width() || event->size().height() > mPixmap->height())
    {
        mPixmap->fill(QColor(255,255,255));
        QPixmap* pixmap = new QPixmap((std::max)(event->size().width(), mPixmap->width()), (std::max)(event->size().height(), mPixmap->height()));
        delete mPainter;
        mPainter = new QPainter(pixmap);
        mPainter->drawPixmap(0, 0, *mPixmap);
        delete mPixmap;
        mPixmap = pixmap;
    }
}

void test::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.drawPixmap(100, 100,500,500,*mPixmap);
}

QPainter *test::getPainter()
{
    return mPainter;
}

QPixmap *test::getPixMap()
{
    return mPixmap;
}
//初始化原始矩阵方块
void test::initBackground(int n)
{
    count=0;
    this->getPainter()->setRenderHint(QPainter::Antialiasing, true);
    this->getPainter()->setPen(QPen(QColor(255,255,255),5));
    this->getPainter()->setBrush(QColor(100,255,0));
    int x=0,y=0;
    for(int i=0;i<n;i++){
        x=0;
        for(int j=0;j<n;j++){
            this->getPainter()->drawRect(x,y,100,50);
            sleep(1);
            this->update();

            x+=100;

        }
        y+=50;
        this->update();
    }
}

void test::setBackgroundWhite()
{
    this->getPainter()->setBrush(QColor(255,255,255));
    this->getPainter()->setPen(QPen(QColor(255,255,255),5));
    this->getPainter()->drawRect(0,0,3000,3000);
}

void test::runResult()
{
    if(currentNumber==testN+1){
        count++;
        initBackground(testN);
        for(int i=1;i<=testN;i++){
            transeAnotherColor(i,loacation[i]);
            this->update();
        }
        sleep(1000);
        return;
    }
        for(int i=1;i<testN;i++){
            loacation[currentNumber]=i;
            if(canIncheckerboard()){
                currentNumber++;
                runResult();
                currentNumber--;
            }
        }


    }
}

void test::transeAnotherColor(int y, int x)
{
    this->getPainter()->setBrush(QColor(255,64,64));
    this->getPainter()->setPen(QPen(QColor(255,255,255),5));
    this->getPainter()->drawRect(100*(x-1),50*(y-1),100,50);
    this->update();
}

//反转第i行，第j列的方块
void test::transeColor(int y, int x)
{
    this->getPainter()->setBrush(QColor(0,0,0));
    this->getPainter()->setPen(QPen(QColor(255,255,255),5));
    this->getPainter()->drawRect(100*(x-1),50*(y-1),100,50);
    this->update();
}
//根据数组画出方块
void test::accordingTomatrix()
{
    for(int i=1;i<=testN;i++){
        for(int j=1;j<=testN;j++){
            if(a[i][j]==1){
                transeColor(i,j);
                sleep(1);
            }
            else if(a[i][j]==-1){
                transeAnotherColor(i,j);
            }
            else{
                this->getPainter()->setBrush(QColor(100,255,0));
                this->getPainter()->setPen(QPen(QColor(255,255,255),5));
                this->getPainter()->drawRect(100*(j-1),50*(i-1),100,50);
                this->update();
                sleep(1);
            }
        }
    }
}
//画出米字型转换方块
void test::toRice(int x, int y)
{
    transeAnotherColor(x,y);
    for(int i=1;i<=testN;i++){
        if(x+i>testN||y+i>testN){
            break;
        }
        transeColor(x+i,y+i);
    }
    for(int i=1;i<=testN;i++){
        if(x-i==0||y-i==0){
            break;
        }
        transeColor(x-i,y-i);
    }
    for(int i=1;i<=testN;i++){
        if(x+i>testN||y-i==0){
            break;
        }
        transeColor(x+i,y-i);
    }
    for(int i=1;i<=testN;i++){
        if(x-i==0||y+i>testN){
            break;
        }
        transeColor(x-i,y+i);
    }
    for(int i=1;i<=testN;i++){
        if(i!=y)
        transeColor(x,i);
        if(i!=x)
        transeColor(i,y);
    }
}
//    数组米字型转换
void test::toRiceMatrix(int x, int y)
{
    for(int i=1;i<=testN;i++){
        if(x+i>testN||y+i>testN){
            break;
        }
        a[x+i][y+i]++;
    }
    for(int i=1;i<=testN;i++){
        if(x-i==0||y-i==0){
            break;
        }
        a[x-i][y-i]++;
    }
    for(int i=1;i<=testN;i++){
        if(x+i>testN||y-i==0){
            break;
        }
        a[x+i][y-i]++;
    }
    for(int i=1;i<=testN;i++){
        if(x-i==0||y+i>testN){
            break;
        }
        a[x-i][y+i]++;
    }
    for(int i=1;i<=testN;i++){

        if(i!=y){
            a[x][i]++;
        }
        if(i!=x){
            a[i][y]++;
        }
    }
}
//    数组返回上一步
void test::backToRice(int x, int y)
{
    for(int i=1;i<=testN;i++){
        if(x+i>testN||y+i>testN){
            break;
        }
        a[x+i][y+i]--;
    }
    for(int i=1;i<=testN;i++){
        if(x-i==0||y-i==0){
            break;
        }
        a[x-i][y-i]--;
    }
    for(int i=1;i<=testN;i++){
        if(x+i>testN||y-i==0){
            break;
        }
        a[x+i][y-i]--;
    }
    for(int i=1;i<=testN;i++){
        if(x-i==0||y+i>testN){
            break;
        }
        a[x-i][y+i]--;
    }
    for(int i=1;i<=testN;i++){

        if(i!=y){
            a[x][i]--;
        }
        if(i!=x){
            a[i][y]--;
        }
    }
}

bool test::canIncheckerboard()
{
    for(int i=1;i<currentNumber;i++){
        if(abs(loacation[currentNumber]-loacation[i]) ==abs(i-currentNumber)||loacation[i] == loacation[currentNumber])
            return false;
    }
    return true;
}



//求得输入框的信号槽
void test::on_lineEdit_cursorPositionChanged(int arg1, int arg2)
{
    testN=ui->lineEdit->text().toInt();
}

//test2Button的信号槽
void test::on_pushButton_2_clicked()
{

    memset(a,0,sizeof(a));
    memset(loacation,0,sizeof(loacation));
    currentNumber=1;
    count++;
    setBackgroundWhite();
    initBackground(testN);

    runResult();
    cout<<count<<endl;
}

