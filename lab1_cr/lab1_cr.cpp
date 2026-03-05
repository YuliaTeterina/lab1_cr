#include <iostream>
#include <limits>
#include <windows.h>
#include "tasks.h"

void PrintMainMenu()
{
    std::cout << "\n========================================\n";
    std::cout << "           ВЫБОР ЗАДАЧИ\n";
    std::cout << "========================================\n";
    std::cout << "1. Задача о рюкзаке (артефакты)\n";
    std::cout << "2. Хромой король\n";
    std::cout << "3. K-ичные числа\n";
    std::cout << "4. Логические выражения\n";
    std::cout << "0. Выход\n";
    std::cout << "========================================\n";
    std::cout << "Выберите задачу: ";
}

int main()
{
    system("chcp 1251 > nul");

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    setlocale(LC_ALL, "ru");

    int Choice = -1;

    do
    {
        PrintMainMenu();
        std::cin >> Choice;
        ClearInputBuffer();

        std::cout << "\n";

        switch (Choice)
        {
        case 1:
            Task1_Artifacts();
            break;
        case 2:
            Task2_LameKing();
            break;
        case 3:
            Task3_KaryNumbers();
            break;
        case 4:
            Task4_LogicalExpressions();
            break;
        case 0:
            std::cout << "Программа завершена.\n";
            break;
        default:
            std::cout << "Неверный выбор. Пожалуйста, выберите 0-4.\n";
            break;
        }

        if (Choice != 0)
        {
            std::cin.get();
        }

    } while (Choice != 0);

    return 0;
}