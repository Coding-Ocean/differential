#include<functional>
#include"libOne.h"

//関数(function)
double func0(double x) { return -0.2 * x - 1; }
double func1(double x) { return 0.2 * x * x - 2; }
double func2(double x) { return -0.03 * x * x * x - 1; }
double func3(double x) { return cos(x) * 0.8 - 1; }

//地形
void ground(std::function<double(double)> f)
{
    double h = 0.1f;
    double maxX = maxScaleX() + 0.1;
    //地中
    strokeWeight(16);
    stroke(60);
    for (double x = -maxX; x <= maxX; x += h)
    {
        mathLine(x, f(x), x, -maxX);
    }
    //地表
    strokeWeight(50);
    stroke(128);
    for (double x = -maxX; x <= maxX; x += h)
    {
        mathLine(x, f(x), x + h, f(x + h));
    }
}

//関数グラフ
void graph(std::function<double(double)> f)
{
    double h = 0.1f;
    double maxX = maxScaleX();
    strokeWeight(6);
    stroke(200);
    for (double x = -maxX; x <= maxX; x += h)
    {
        mathLine(x, f(x), x + h, f(x + h));
    }
}

void gmain()
{
    window(1000, 1000);
    axisMode(NODRAW);
    rectMode(CENTER);

    //表示されているｘ座標の最大値
    double maxX = 4;

    //キャラクタデータ
    int img = loadImage("assets\\sukebo.png");
    double x = -maxX - 0.2;
    double y = 0;
    double angle = 0;

    //関数のポインタ
    std::function<double(double)> f = &func0;
    int sw = 0;

    while (notQuit)
    {
        //関数切り替え
        if (isTrigger(KEY_SPACE))
        {
            ++sw %= 4;
            switch (sw)
            {
            case 0: f = &func0; break;
            case 1: f = &func1; break;
            case 2: f = &func2; break;
            case 3: f = &func3; break;
            }
            x = -maxX - 0.2;
        }
        //キャラｘ座標
        x += 0.06;
        if (x > maxX + 0.2)x = -maxX - 0.2;
        //キャラｙ座標
        y = f(x);
        //キャラ角度
        double dx = 0.0000001;//xの変化量
        double dy = f(x + dx) - f(x);//yの変化量
        double tangent = dy / dx;//傾き
        angle = atan(tangent);

        //描画
        clear(80, 128, 255);
        mathAxis(maxX);
        ground(f);
        graph(f);
        mathImage(img, x, y, angle);
    }
}
