#include <iostream>
#include <Windows.h>
#include <cmath>

double f(double x) {
    return std::log(x) - std::cos(x);
}

double df(double x) {
    return (1.0 / x) + std::sin(x);
}

int main()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    srand(time(NULL));

    std::cout << "локализация корня\n";
    double start = 0.5;
    double end = 3.0;
    double h = 0.1;

    double a = 0.0, b = 0.0;
    bool sss = false;

    for (double x = start; x <= end - h; x += h)
    {
        double xarbyz = x + h;
        if (f(x) * f(xarbyz) < 0) {
            a = x;
            b = xarbyz;
            sss = true;
            break;
        }
    }

    if (!sss)
    {
        std::cout << "не найдено\n";
        return 1;
    }

    std::cout << "найден подотрезок: [" << a << ", " << b << "]\n";

    std::cout << "сужение интервала\n";
    double c = 0.0;
    for (int i = 1; i <= 3; ++i)
    {
        c = (a + b) / 2.0;
        std::cout << "итерация " << i << ": c = " << c << "\n";

        if (f(a) * f(c) < 0) {
            b = c;
        }
        else {
            a = c;
        }
    }

    double x0 = (a + b) / 2.0;
    std::cout << "начальное приближение x0 = " << x0 << "\n\n";

    std::cout << "уточнение корня\n";
    double epp = 0.00001;
    double xcur = x0;
    double xarbyz = 0.0;
    int iter = 0;
    bool gotovo = false;

    while (true)
    {
        iter++;
        double d = df(xcur);

        if (std::abs(d) < 1e-10)
        {
            std::cout << "производная близка к нулю (df(x) = " << d << "). деление на ноль ч стоп\n";
            break;
        }

        xarbyz = xcur - f(xcur) / d;

        std::cout << "итерация " << iter
            << ": x = " << xarbyz
            << ", f(x) = " << f(xarbyz) << "\n";

        if (std::abs(xarbyz - xcur) < epp)
        {
            gotovo = true;
            break;
        }

        xcur = xarbyz;
    }

    std::cout << "\nрезультат\n";
    if (gotovo) {
        std::cout << "корень найден x = " << xarbyz << ", f(x) = " << f(xarbyz) << "\n";
    }
    else {
        std::cout << "не удалось найти корень\n";
    }

    return 0;
}

/*
* 
1
25 вызовов 
16 в сканировании 6 в делении 3 в Ньютоне

2
Равна ~2.48. нечего все будет нормально

3 
При делении на ноль горизонтальный график или если начать слишком далеко от корня.




локализация корня
найден подотрезок: [1.3, 1.4]
сужение интервала
итерация 1: c = 1.35
итерация 2: c = 1.325
итерация 3: c = 1.3125
начальное приближение x0 = 1.30625

уточнение корня
итерация 1: x = 1.30296, f(x) = -1.75315e-06
итерация 2: x = 1.30296, f(x) = -1.66367e-13

результат
корень найден x = 1.30296, f(x) = -1.66367e-13

*/
