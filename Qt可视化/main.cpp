#include "mainwindow.h"
#include "paintwidget.h"
#include"test.h"
#include <QApplication>
#include<QPainter>
#include<iostream>
int n;
using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    test ttest;

    ttest.show();
//    ttest.tt();
    return a.exec();
}
