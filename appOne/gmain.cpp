#include<functional>
#include"libOne.h"

//�֐�(function)
double func0(double x) { return -0.2 * x - 1; }
double func1(double x) { return 0.2 * x * x - 2; }
double func2(double x) { return -0.03 * x * x * x - 1; }
double func3(double x) { return cos(x) * 0.8 - 1; }

//�n�`
void ground(std::function<double(double)> f)
{
    double h = 0.1f;
    double maxX = maxScaleX() + 0.1;
    //�n��
    strokeWeight(16);
    stroke(60);
    for (double x = -maxX; x <= maxX; x += h)
    {
        mathLine(x, f(x), x, -maxX);
    }
    //�n�\
    strokeWeight(50);
    stroke(128);
    for (double x = -maxX; x <= maxX; x += h)
    {
        mathLine(x, f(x), x + h, f(x + h));
    }
}

//�֐��O���t
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

    //�\������Ă��邘���W�̍ő�l
    double maxX = 4;

    //�L�����N�^�f�[�^
    int img = loadImage("assets\\sukebo.png");
    double x = -maxX - 0.2;
    double y = 0;
    double angle = 0;

    //�֐��̃|�C���^
    std::function<double(double)> f = &func0;
    int sw = 0;

    while (notQuit)
    {
        //�֐��؂�ւ�
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
        //�L���������W
        x += 0.06;
        if (x > maxX + 0.2)x = -maxX - 0.2;
        //�L���������W
        y = f(x);
        //�L�����p�x
        double dx = 0.0000001;//x�̕ω���
        double dy = f(x + dx) - f(x);//y�̕ω���
        double tangent = dy / dx;//�X��
        angle = atan(tangent);

        //�`��
        clear(80, 128, 255);
        mathAxis(maxX);
        ground(f);
        graph(f);
        mathImage(img, x, y, angle);
    }
}
