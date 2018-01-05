# Qt


## paintEvent - 画布

![](https://www.cnblogs.com/findumars/p/5176323.html)

运行前画出，运行完毕后就不能直接在屏幕上进行改变



## 在 paintEvent 之外进行绘制

![鼎威推荐教程](https://www.cnblogs.com/wiki3d/p/4227307.html)

## 本次Qt用与猴子称大王的运用

### 新建项目Qt/设计师界面类
+ 呈现三个文件
	+ text.h
	+ text.cpp
	+ text.ui

### text.h 所用函数进行声明

需要的函数、按钮的点击事件、外部输入传进来的数值.....都需要在这里进行声明

```
#ifndef TEXT_H#define TEXT_H#include <QWidget>namespace Ui {class text;}class text : public QWidget{    Q_OBJECTpublic:    explicit text(QWidget *parent = 0,Qt::WindowFlags f = 0);    ~text();//析构函数    void resizeEvent(QResizeEvent *event);    void paintEvent(QPaintEvent *event);    QPainter* getPainter();    QPixmap* getPixMap();     void initBackground(int sum);//初始化背景颜色的函数     void setBackgroundWhite();//将背景设置为白色的函数     void runResult(int m,int n);//运行整个程序内容private slots:   //槽    void on_lineEdit_cursorPositionChanged(int arg1, int arg2);    void on_lineEdit_editingFinished();    void on_lineEdit_2_cursorPositionChanged(int arg1, int arg2);    void on_lineEdit_2_editingFinished();    void on_pushButton_clicked();    void on_label_5_linkActivated(const QString &link);private:    Ui::text *ui;    QPixmap* mPixmap;    QPainter* mPainter;    int sum;//猴子总数    int number;//每次排序的数目};#endif // TEXT_H
``` 

### text.cpp

+ 所有涉及到的函数，都需要在这里进行定义

```
#include <QPainter>#include <stdio.h>#include <QResizeEvent>#include<QColor>#include<iostream>#include <stdio.h>#include <QTime>#include<cstring>using namespace std;text::text(QWidget *parent, Qt::WindowFlags f) :    QWidget(parent,f),    ui(new Ui::text){    ui->setupUi(this);//这个this很重要 很重要。后面涉及到 画刷、画笔、正方形.....的绘制    mPixmap = new QPixmap(1000,1000);    mPainter = new QPainter(mPixmap);    resize(1000,1000);    mPixmap->fill(QColor(100,255,255));//设置填充颜色}void text::setBackgroundWhite(){    this->getPainter()->setBrush(QColor(255,255,255));//设置画刷    this->getPainter()->setPen(QPen(QColor(255,255,255),5));//设置画笔    this->getPainter()->drawRect(0,0,3000,3000);//画正方形}//初始化原始矩阵方块void text::initBackground(int n){//    count=0;    this->getPainter()->setRenderHint(QPainter::Antialiasing, true);    this->getPainter()->setPen(QPen(QColor(255,255,255),5));    this->getPainter()->setBrush(QColor(100,255,0));    int x=0,y=0;    for(int i=0;i<sum;i++){        y=0;//        for(int j=0;j<sum;j++){            this->getPainter()->drawRect(x,y,100,100);            this->update();            y+=100;//        }        x+=100;        this->update();    }}void sleep(unsigned int msec){    QTime dieTime = QTime::currentTime().addMSecs(msec);    while( QTime::currentTime() < dieTime )        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);}text::~text(){    delete ui;    delete mPainter;    delete mPixmap;}void text::resizeEvent(QResizeEvent *event){    if(event->size().width() > mPixmap->width() || event->size().height() > mPixmap->height())    {        mPixmap->fill(QColor(255,255,255));        QPixmap* pixmap = new QPixmap((std::max)(event->size().width(), mPixmap->width()), (std::max)(event->size().height(), mPixmap->height()));        delete mPainter;        mPainter = new QPainter(pixmap);        mPainter->drawPixmap(0, 0, *mPixmap);        delete mPixmap;        mPixmap = pixmap;    }}void text::runResult(int m,int n){    int mon[m];        int i=0,j=0,t=-1;        while(i<m) {            mon[i]=1;            i++;        }        i=0;        while(i<m) {            while(j<n) {                t=(t+1)%m;  //防止n>m情况                if(mon[t]==1)  //等于0时代表此处猴子已经出去                    j++;            }            mon[t]=0;  //代表已经出去的猴子             ui->announce->setText("");               sleep(500);            this->getPainter()->setBrush(QColor(100,100,100));            this->getPainter()->setPen(QPen(QColor(255,255,255),5));            this->getPainter()->drawRect(t*100,0,100,100);//如果是横线画图，则在 x 处进行改变，四个参数分别代表： x ，y,width,height            this->update();//每次画完都必须进行更新                 ui->king->setText(QString::number(t+1));//在UI对应的label上进行动态数字的显示变化                 ui->king->repaint();//一旦有变化就必须进行更新
                             if(i+1==sum)//指示条件，当进行到最后一只猴子，就是大王的时候，在另外一个label上显示“King”            {                sleep(500);                ui->announce->setText("King");            }//            printf("%d ",t+1);       在画布上不能直接print内容，必须通过label进行 setText的显示            i++;            j=0;        }}void text::paintEvent(QPaintEvent *event){    QPainter painter(this);    painter.drawPixmap(50, 50,500,500,*mPixmap);    //设置初始化画布的位置}QPainter *text::getPainter(){    return mPainter;}//输入框的信号槽   在ui框中输入数字，就是通过这的获得的void text::on_lineEdit_cursorPositionChanged(int arg1, int arg2){    sum=ui->lineEdit->text().toInt();        }//输入框的 number  从这里获得，然后就可以将number运行到上面的函数中使用void text::on_lineEdit_2_cursorPositionChanged(int arg1, int arg2){    number=ui->lineEdit_2->text().toInt();}void text::on_lineEdit_editingFinished(){}void text::on_lineEdit_2_editingFinished(){}//设置按钮的点击事件，  点击ui界面的 Start ，就会运行里面所包含的程序，展现所需界面void text::on_pushButton_clicked(){    setBackgroundWhite();    initBackground(sum);    runResult(sum,number);}void text::on_label_5_linkActivated(const QString &link){}

```

### main.cpp 主要负责实例化对象，show出来

```
#include "mainwindow.h"#include"text.h"#include <QApplication>#include<QPainter>#include<iostream>int n;using namespace std;int main(int argc, char *argv[]){    QApplication a(argc, argv);    text w;//text就是我的大文件    w.show();    return a.exec();}
```

### text.ui

![](http://oz3rf0wt0.bkt.clouddn.com/18-1-5/65305665.jpg)

+ 每一个需要现实的空间都在右上方汇总
+ 有文字输出的控件（setText），需要特别注意对象名，因为在cpp文件中，就是⬇️进行设置的
	+  ui->announce->setText("King");
	+  ui->king->setText(QString::number(t+1));

### 流程测试界面

+ 登陆界面

![](http://oz3rf0wt0.bkt.clouddn.com/18-1-5/41471104.jpg)

+ 第一次测试

![](http://oz3rf0wt0.bkt.clouddn.com/18-1-5/86947998.jpg)

![](http://oz3rf0wt0.bkt.clouddn.com/18-1-5/24455495.jpg)

![](http://oz3rf0wt0.bkt.clouddn.com/18-1-5/80893079.jpg)

+ 第二次测试

![](http://oz3rf0wt0.bkt.clouddn.com/18-1-5/88194881.jpg)

![](http://oz3rf0wt0.bkt.clouddn.com/18-1-5/43005735.jpg)
