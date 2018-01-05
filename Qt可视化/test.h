#ifndef TEST_H
#define TEST_H

#include <QWidget>

namespace Ui {
class test;
}

class test : public QWidget
{
    Q_OBJECT

public:
    explicit test(QWidget *parent = 0,Qt::WindowFlags f = 0);
    ~test();

    int count;
    int currentNumber;
    int a[100][100];
    int loacation[100];

    void resizeEvent(QResizeEvent *event);

    void paintEvent(QPaintEvent *event);

    QPainter* getPainter();
    QPixmap* getPixMap();
    void initBackground(int n);
    void setBackgroundWhite();
    void runResult();

    void transeAnotherColor(int x,int y);

//    反转第x行，第y列的元素
    void transeColor(int x,int y);

    //重新根据矩阵画出方块矩阵
    void accordingTomatrix();

//    把米字型方块转置
    void toRice(int x,int y);

//    数组米字型转换
    void toRiceMatrix(int x,int y);

//    数组返回上一步
    void backToRice(int x,int y);

    bool canIncheckerboard();
private slots:
    void on_lineEdit_cursorPositionChanged(int arg1, int arg2);

    void on_pushButton_2_clicked();
    void on_lineEdit_editingFinished();

    void on_lineEdit_returnPressed();

    void on_lineEdit_destroyed();

private:
    Ui::test *ui;
    int testN;
    QPixmap* mPixmap;
    QPainter* mPainter;
};

#endif // TEST_H
