#include "plant.h"
#include <conio.h> 
//#include <dislin/discpp.h>

#include <cmath>
#include <vector>
#include <iostream>
using namespace std;
using std::vector;

size_t k = 0;
vector <int> Out_Channel;
vector <float> U;
vector <double> X;
size_t N = 0;
int In_Channel = 0;
void Vvod() {
    setlocale(LC_ALL, "Russian");
    bool fl = true;
    //Ввод количество каналов управления
    while (fl)
    {
        cout << "Vvedite kolinchestvo kanalov ypravlenia(1-4)" << "\n";
        cin >> k;
        if (k < 5 && k > 0)
        {
            fl = false;
        }
        else
        {
            cout << "ERROR nepravilniy diapazon" << "\n";
        }
    }
    Out_Channel.resize(k);
    U.resize(k);
    //Ввод использующихся каналов
    for (size_t i = 0; i < k; i++)
    {
        fl = true;
        while (fl)
        {
            cout << "Vvedite nomer kanala L[" << i << "] dlya ispolzovania(7-10)";
            cin >> Out_Channel[i];
            if (Out_Channel[i] < 11 && Out_Channel[i] > 6)
            {
                fl = false;
            }
            else
            {
                cout << "ERROR nepravilniy diapazon" << "\n";
            }
        }
    }
    fl = true;
    //Ввод числа повторений измерений
    cout << "Vvedite kol-vo povtoreniy";
    while (fl)
    {
        cin >> N;
        if (N > 0)
        {
            fl = false;
        }
        else
        {
            cout << "ERROR vvedite naturalnoe chislo" << "\n";
        }
    }
    fl = true;
    X.resize(N);
    //Ввод номера датчика
    while (fl)
    {
        cout << "Vvedite kanal oprosa (11-90)";
        cin >> In_Channel;
        if (In_Channel < 91 && In_Channel >10)
        {
            fl = false;
        }
        else
        {
            cout << "ERROR nepravilniy diapazon" << "\n";
        }
    }
    fl = true;

}
//Рассчёт среднего значения
double MiddleSize()
{
    double s = 0;
    for (size_t i = 0; i < N; i++)
    {
        s += X[i];
    }
    return(s / N);
}


int main() {
    setlocale(LC_ALL, "Russian");
    // Инициализация ОУ.
    Plant plant;
    plant_init(plant);
    /*// Получение экспериментальных данных.
    const int channel = 64;
    const size_t steps = 100;

    vector<double> xs(steps);
    vector<double> ys(steps);

    for (size_t i = 0; i < steps; i++) {
        xs[i] = i;
        ys[i] = plant_measure(channel, plant);
        cout << ys[i] << '\t'; //Вывод результатов измерений в консоль
    }*/
    Vvod();
    bool check = true;
    vector <double> shag;
    shag.resize(k);
    while (check)
    {
        //Подача значений на каналы управлений
        for (size_t i = 0; i < k; i++)
        {
            bool fl = true;
            while (fl)
            {
                switch (Out_Channel[i])
                {
                case 7:
                    cout << "Vvedite shag(0;70), diapozon ypravleniya(-70;70)";
                    cin >> shag[i];
                    if (shag[i] >= 1 && shag[i] <= 70)
                    {
                        fl = false;
                    }
                    else
                    {
                        cout << "ERROR nepravilniy diapozon";
                    }
                    break;
                case 8:
                    cout << "Vvedite shag(0;3), diapozon, ypravlenie(-3;3)";
                    cin >> shag[i];
                    if (shag[i] >= 1 && shag[i] <= 3)
                    {
                        fl = false;
                    }
                    else
                    {
                        cout << "ERROR nepravilniy diapozon";
                    }
                    break;
                case 9:
                    cout << "Vvedite shag(0;5), diapozon ypravlenie(-5;5)";
                    cin >> shag[i];
                    if (shag[i] >= 1 && shag[i] <= 5)
                    {
                        fl = false;
                    }
                    else
                    {
                        cout << "ERROR nepravilniy diapozon";
                    }
                    break;
                case 10:
                    cout << "Vvedite shag(0;2.5), diapozon ypravlenia (-2.5;2.5)";
                    cin >> shag[i];
                    if (shag[i] >= 1 && shag[i] <= 2.5)
                    {
                        fl = false;
                    }
                    else
                    {
                        cout << "ERROR nepravilniy diapozon";
                    }
                    break;
                }
            }
        }
        vector <double> max(2);
        for (size_t i = 0; i < k; i++)
        {
                switch (Out_Channel[i])
                {
                case 7:
                    cout << "Vibran 7 kanal ypravleniya"<<'\n';
                    plant_control(Out_Channel[i], -70, plant);
                    for (size_t ism = 0; ism < N; ism++)
                    {
                        X[ism] = plant_measure(In_Channel, plant);
                    }
                    max[1] = MiddleSize();
                    cout << "X[" << -70 << "]=" << max[1] << "\n";
                    max[0]=-70;
                    for (int ypravlenie = -70+shag[i]; ypravlenie <=70; ypravlenie+=shag[i])
                    {
                        plant_control(Out_Channel[i], ypravlenie, plant);
                      for (size_t ism = 0; ism < N; ism++)
                        {
                            plant_control(Out_Channel[i], ypravlenie, plant);
                            X[ism] = plant_measure(In_Channel, plant);
                        }
                        double x = MiddleSize();
                        cout << "X["<<ypravlenie<<"]=" << x << "\n";
                        if (abs(100-max[1]) > abs(100-x))
                        {
                            max[1] = x;
                            max[0] = ypravlenie;
                        }
                    }
                    cout <<"kanal ypravleinya 7 | kanal oprosa "<<In_Channel<<" | ypravlenie "<<max[0]<<" | znachenie "<<max[1]<<"\n" ;
                    break;
                case 8:
                    cout << "Vibran 8 kanal ypravleniya" << '\n';
                    plant_control(Out_Channel[i], -3, plant);
                    for (size_t ism = 0; ism < N; ism++)
                    {
                        X[ism] = plant_measure(In_Channel, plant);
                    }
                    max[1] = MiddleSize();
                    cout << "X[" << -3 << "]=" << max[1] << "\n";
                    max[0] = -3;
                    for (int num = -3 + shag[i]; num <= 3; num += shag[i])
                    {
                        plant_control(Out_Channel[i], num, plant);
                        for (size_t ism = 0; ism < N; ism++)
                        {
                            X[ism] = plant_measure(In_Channel, plant);
                        }
                        double x = MiddleSize();
                        cout << "X[" << num << "]=" << x << "\n";
                        if (abs(100 - max[1]) > abs(100 - x))
                        {
                            max[1] = x;
                            max[0] = num;
                        }
                    }
                    cout << "kanal ypravleinya 8 | kanal oprosa " << In_Channel << " | ypravlenie " << max[0] << " | znachenie " << max[1] << "\n";
                    break;
                case 9:
                    cout << "Vibran 9 kanal ypravleniya" << '\n';
                    plant_control(Out_Channel[i], -5, plant);
                    for (size_t ism = 0; ism < N; ism++)
                    {
                        X[ism] = plant_measure(In_Channel, plant);
                    }
                    max[1] = MiddleSize();
                    cout << "X[" << -5 << "]=" << max[1] << "\n";
                    max[0] = -5;
                    for (int num = -5 + shag[i]; num <= 5; num += shag[i])
                    {
                        plant_control(Out_Channel[i], num, plant);
                        for (size_t ism = 0; ism < N; ism++)
                        {
                            X[ism] = plant_measure(In_Channel, plant);
                        }
                        double x = MiddleSize();
                        cout << "X[" << num << "]=" << x << "\n";
                        if (abs(100 - max[1]) > abs(100 - x))
                        {
                            max[1] = x;
                            max[0] = num;
                        }
                    }
                    cout << "kanal ypravleinya 9 | kanal oprosa " << In_Channel << " | ypravlenie " << max[0] << " | znachenie " << max[1] << "\n";                    break;
                case 10:
                    cout << "Vibran 10 kanal ypravleniya" << '\n';
                    plant_control(Out_Channel[i], -2.5, plant);
                    for (size_t ism = 0; ism < N; ism++)
                    {
                        X[ism] = plant_measure(In_Channel, plant);
                    }
                    max[1] = MiddleSize();
                    cout << "X[" << -2.5 << "]=" << max[1] << "\n";
                    max[0] = -2.5;
                    for (int num = -2.5 + shag[i]; num <= 2.5; num += shag[i])
                    {
                        plant_control(Out_Channel[i], num, plant);
                        for (size_t ism = 0; ism < N; ism++)
                        {
                            X[ism] = plant_measure(In_Channel, plant);
                        }
                        double x = MiddleSize();
                        cout << "X[" << num << "]=" << x << "\n";
                        if (abs(100 - max[1]) > abs(100 - x))
                        {
                            max[1] = x;
                            max[0] = num;
                        }
                    }
                    cout << "kanal ypravleinya 10 | kanal oprosa " << In_Channel << " | ypravlenie " << max[0] << " | znachenie " << max[1] << "\n";                    break;
                }
        }    
        cout << "Push '1' if you want to continue or any different key to quit" << "\n";
        int C = 0;
        cin >> C;
        if (!(C == 1))
        {
            check = false;
        }
    }
}