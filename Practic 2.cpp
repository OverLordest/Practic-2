#include "plant.h"
#include <conio.h> 
//#include <discpp.h>
#include <cmath>
#include <vector>
#include <iostream>
using namespace std;
using std::vector;
size_t k = 0;//Количество каналов управления
vector <int> L;//Номера используемых каналов управления
double U;//Управляющие воздействия 
vector <double> X;//Измеряемые значения
vector <double> Shag;//Шаг для канала управления
vector <double> Max(2);//Вектор определяющий максимальное воздействие управления
size_t N = 0;//Число повторений измерений
size_t M = 0;//Номер датчика, канал опроса
double x;//Управление средние значение

//Ввод изначальных данных
void Vvod() {
    setlocale(LC_ALL, "Russian");
    bool fl = true;
    //Ввод количество каналов управления
    while (fl)
    {
        cout << "Введите количество канлов управления(1-4)" << "\n";
        cin >> k;
        if (k < 5 && k > 0)
        {
            fl = false;
        }
        else
        {
            cout << "ERROR" << "\n";
        }
    }
    L.resize(k);
    Shag.resize(k);
    //Ввод использующихся каналов
    for (size_t i = 0; i < k; i++)
    {
        fl = true;
        while (fl)
        {
            cout << "Введите номер канала L[" << i << "] для использования(7-10)" << "\n";
            cin >> L[i];
            if (L[i] < 11 && L[i] > 6)
            {
                fl = false;
            }
            else
            {
                cout << "ERROR" << "\n";
            }
        }
    }
    fl = true;
    //Ввод числа повторений измерений
    cout << "Введите количество повторений измерений" << "\n";
    while (fl)
    {
        cin >> N;
        if (N > 0)
        {
            fl = false;
        }
        else
        {
            cout << "ERROR Введите натуральное число" << "\n";
        }
    }
    fl = true;
    X.resize(N);
    //Ввод номера датчика
    while (fl)
    {
        cout << "Введитк канал опроса (11-99)" << "\n";
        cin >> M;
        if (M < 100 && M >10)
        {
            fl = false;
        }
        else
        {
            cout << "ERROR" << "\n";
        }
    }
    fl = true;

}
//Рассчёт среднего значения для X по N
double MiddleSize()
{
    double s = 0;
    for (size_t i = 0; i < N; i++)
    {
        s += X[i];
    }
    return(s / N);
}
//Запись значений шага на каналы управлений
void Write_shag(size_t i)
{
    setlocale(LC_ALL, "Russian");
    bool fl = true;
    while (fl)
    {
        switch (L[i])
        {
        case 7:
            cout << "Введите шаг управления (0;70)" << "\n";
            cin >> Shag[i];
            if (Shag[i] > 0 && Shag[i] <= 70)
            {
                fl = false;
            }
            else
            {
                cout << "ERROR";
            }
            break;
        case 8:
            cout << "Введите шаг управления (0;3)" << "\n";
            cin >> Shag[i];
            if (Shag[i] > 0 && Shag[i] <= 3)
            {
                fl = false;
            }
            else
            {
                cout << "ERROR";
            }
            break;
        case 9:
            cout << "Введите шаг управления (0;5)" << "\n";
            cin >> Shag[i];
            if (Shag[i] > 0 && Shag[i] <= 5)
            {
                fl = false;
            }
            else
            {
                cout << "ERROR";
            }
            break;
        case 10:
            cout << "Введите шаг управления (0;2.5)" << "\n";
            cin >> Shag[i];
            if (Shag[i] > 0 && Shag[i] <= 2.5)
            {
                fl = false;
            }
            else
            {
                cout << "ERROR";
            }
            break;
        }
    }

}

void Vivod(size_t i)
{
    setlocale(LC_ALL, "Russian");
    cout << "Канал управления L[" << L[i] << "] | Канал опроса " << M << " | наиболее близкое к 100, управление " << Max[0] << " | значение " << Max[1] << "\n";
}


int main() {
    setlocale(LC_ALL, "Russian");
    Plant plant;
    plant_init(plant);
    Vvod();
    bool check = true;
    while (check)
    {
        //Запись значений шагов на каналы управлений
        for (size_t i = 0; i < k; i++)
        {
            Write_shag(i);
        }

        //Подача на объект управляющего воздействия
        for (size_t i = 0; i < k; i++)
        {
            cout << "Выбран " << L[i]<<" канал управления"<<"\n";
            switch (L[i])
            {
            case 7:
                Max[0] = -70;
                plant_control(L[i], -70, plant);
                for (size_t ism = 0; ism < N; ism++)
                {
                    X[ism] = plant_measure(M, plant);
                    
                }
                x = MiddleSize();
                cout << "x[-70]=" << x << "\n";
                Max[1] = x;
                for (double U = -70 + Shag[i]; U <= 70; U += Shag[i])
                {
                    plant_control(L[i], U, plant);
                    for (size_t ism = 0; ism < N; ism++)
                    {
                        X[ism] = plant_measure(M, plant);
                        
                    }
                    x = MiddleSize();
                    cout << "x[" << U << "]=" << x << "\n";
                    if (abs(100 - Max[1]) > abs(100 - x))
                    {
                        Max[1] = x;
                        Max[0] = U;
                    }
                }
                Vivod(i);
                break;
            case 8:
                Max[0] = -3;
                plant_control(L[i], -3, plant);
                for (size_t ism = 0; ism < N; ism++)
                {
                    X[ism] = plant_measure(M, plant);
                }
                x = MiddleSize();
                cout << "x[-3]=" << x << "\n";
                Max[1] = x;
                for (double U = -3 + Shag[i]; U <= 3; U += Shag[i])
                {
                    plant_control(L[i], U, plant);
                    for (size_t ism = 0; ism < N; ism++)
                    {
                        X[ism] = plant_measure(M, plant);                       
                    }
                    x = MiddleSize();
                    cout << "x[" << U << "]=" << x << "\n";
                    if (abs(100 - Max[1]) > abs(100 - x))
                    {
                        Max[1] = x;
                        Max[0] = U;
                    }
                }
                Vivod(i);
                break;
            case 9:
                Max[0] = -5;
                plant_control(L[i], -5, plant);
                for (size_t ism = 0; ism < N; ism++)
                {
                    X[ism] = plant_measure(M, plant);
                    
                }
                x = MiddleSize();
                cout << "x[-5]=" << x << "\n";
                Max[1] = x;
                for (double U = -5 + Shag[i]; U <= 5; U += Shag[i])
                {
                    plant_control(L[i], U, plant);
                    for (size_t ism = 0; ism < N; ism++)
                    {
                        X[ism] = plant_measure(M, plant);
                        
                    }
                    x = MiddleSize();
                    cout << "x[" << U << "]=" << x << "\n";
                    if (abs(100 - Max[1]) > abs(100 - x))
                    {
                        Max[1] = x;
                        Max[0] = U;
                    }
                }
                Vivod(i);
                break;
            case 10:
                Max[0] = -2.5;
                plant_control(L[i], -2.5, plant);
                for (size_t ism = 0; ism < N; ism++)
                {
                    X[ism] = plant_measure(M, plant);
                }
                x = MiddleSize();
                cout << "x[-2.5]=" << x << "\n";
                Max[1] = x;
                for (double U = -2.5 + Shag[i]; U <= 2.5; U += Shag[i])
                {
                    plant_control(L[i], U, plant);
                    for (size_t ism = 0; ism < N; ism++)
                    {
                        X[ism] = plant_measure(M, plant);     
                    }
                    x = MiddleSize();
                    cout << "x[" << U << "]=" << x << "\n";
                    if (abs(100 - Max[1]) > abs(100 - x))
                    {
                        Max[1] = x;
                        Max[0] = U;
                    }
                }
                Vivod(i);
                break;
            }

            
        }

        cout << "Нажмите '1' если хотите повторить или что-нибудь другое чтобы выйти" << "\n";
        int C = 0;
        cin >> C;
        if (!(C == 1))
        {
            check = false;
        }
    }
}