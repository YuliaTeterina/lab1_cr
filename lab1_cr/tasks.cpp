#include "tasks.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <limits>

// Задача 1: 
/*Археолог нашел N артефактов. Известны веса(сi) и ценности(di) артефактов. Нужно
выбрать такое подмножество найденных вещей, чтобы суммарный их вес не превысил Z кг, а их
общая ценность оказалась максимальной. Известно, что решение единственно. Укажите поряд-
ковые номера вещей, которые нужно взять. Исходные данные находятся в текстовом файле, в
первой строке указаны N и Z, а во второй строке значения весов(в кг), в третьей - ценность
находок. Вывести так же суммарный вес и общую ценность результата.*/

// FIX_ME: Неправильное имя функции - должно быть с заглавной буквы согласно кодстайлу
// void insert_sort(std::vector<int>& w, std::vector<int>& p) {
void InsertionSort(std::vector<int>& Weights, std::vector<int>& Values) 
{
    // FIX_ME: Использование int для индекса - должен быть size_t
    // for (int i = 1; i < w.size(); i++) {
    for (size_t i = 1; i < Weights.size(); ++i) 
    {
        int Temp = static_cast<int>(i);
        // FIX_ME: Сравнение int и size_t
        // while (temp - 1 >= 0 && w[temp] < w[temp - 1]) {
        while (Temp - 1 >= 0 && Temp - 1 < static_cast<int>(Weights.size()) && Weights[Temp] < Weights[Temp - 1]) 
        {
            std::swap(Weights[Temp], Weights[Temp - 1]);
            std::swap(Values[Temp], Values[Temp - 1]);
            --Temp;
        }
    }
}

// FIX_ME: Неправильное имя функции
// int backpack(int W, std::vector<int>& wt, std::vector<int>& val, int n) {
int SolveBackpack(int MaxWeight, const std::vector<int>& Weights, const std::vector<int>& Values, int NumItems, std::vector<int>& SelectedItems) {
    // FIX_ME: Создание двумерного вектора каждый раз - неэффективно
    // std::vector<std::vector<int>> dp(n + 1, std::vector<int>(W + 1));
    std::vector<std::vector<int>> DP(NumItems + 1, std::vector<int>(MaxWeight + 1, 0));

    // Заполнение таблицы динамического программирования
    for (int i = 1; i <= NumItems; ++i) 
    {
        for (int w = 1; w <= MaxWeight; ++w) 
        {
            if (Weights[i - 1] <= w) 
            {
                // Выбор между включением и исключением текущего предмета
                DP[i][w] = std::max(Values[i - 1] + DP[i - 1][w - Weights[i - 1]], DP[i - 1][w]);
            }
            else 
            {
                // Текущий предмет не вмещается в рюкзак
                DP[i][w] = DP[i - 1][w];
            }
        }
    }

    // Восстановление ответа (какие предметы были взяты)
    int CurrentWeight = MaxWeight;
    for (int i = NumItems; i > 0; --i) 
    {
        // FIX_ME: Неправильное условие для проверки, был ли взят предмет
        // if (DP[i][CurrentWeight] != DP[i - 1][CurrentWeight]) {
        if (DP[i][CurrentWeight] > DP[i - 1][CurrentWeight]) 
        {
            SelectedItems.push_back(i - 1); // Добавляем индекс предмета (0-based)
            CurrentWeight -= Weights[i - 1];
        }
    }

    return DP[NumItems][MaxWeight];
}

void Task1_Artifacts() 
{
    setlocale(LC_ALL, "Russian");
    std::cout << "=== ЗАДАЧА 1: АРТЕФАКТЫ (РЮКЗАК) ===\n\n";

    int NumItems = 0;
    int MaxWeight = 0;

    do 
    {
        std::cout << "Введите объем рюкзака (кг) > 0: ";
        std::cin >> MaxWeight;
    } while (MaxWeight <= 0);

    do 
    {
        std::cout << "Введите количество артефактов > 0: ";
        std::cin >> NumItems;
    } while (NumItems <= 0);

    std::cout << "Введите параметры артефактов:\n";

    std::vector<int> Values(NumItems);
    std::vector<int> Weights(NumItems);

    for (int i = 0; i < NumItems; ++i) 
    {
        std::cout << "Артефакт #" << i + 1 << ":\n";
        std::cout << "  Вес (кг): ";
        std::cin >> Weights[i];
        std::cout << "  Стоимость: ";
        std::cin >> Values[i];
    }

    // FIX_ME: Сортировка изменяет соответствие индексов оригинальным номерам
    // InsertionSort(Weights, Values);

    std::vector<int> SelectedIndices;
    int MaxValue = SolveBackpack(MaxWeight, Weights, Values, NumItems, SelectedIndices);

    std::cout << "\nРезультат:\n";
    std::cout << "Максимальная стоимость: " << MaxValue << "\n";

    // Подсчет суммарного веса выбранных предметов
    int TotalWeight = 0;
    for (int Index : SelectedIndices) 
    {
        TotalWeight += Weights[Index];
    }

    std::cout << "Суммарный вес: " << TotalWeight << " кг\n";
    std::cout << "Выбраны артефакты с номерами: ";

    // FIX_ME: Вывод индексов должен быть в порядке возрастания
    // for (int Index : SelectedIndices) {
    std::sort(SelectedIndices.begin(), SelectedIndices.end());
    for (size_t i = 0; i < SelectedIndices.size(); ++i) 
    {
        if (i > 0) std::cout << ", ";
        std::cout << SelectedIndices[i] + 1; // +1 для вывода порядкового номера (1-based)
    }
    std::cout << "\n";
}

// Задача 2: 
/*Хромой король.На квадратной доске расставлены монеты, достоинством от 1 до 100.
Хромой король, находящийся в правом нижнем углу, мечтает попасть в левый верхний.
При этом он может передвигаться только в клетку слева или сверху и хочет, чтобы сумма всех
монет, оказавшихся у него на пути, была бы максимальной.Определить эту сумму и путь, каким
образом должен двигаться король, чтобы ее собрать.Ввод и вывод организовать при помощи
текстовых файлов.Формат входных данных : в первой строке входного файла записано число
N - размер доски(1 < N < 80).Далее следует N строк, каждая из которых содержит N целых чисел,
представляющих доску.В первую строку выходного файл нужно вывести единственное число :
максимальную сумму, а во второй строке вывести путь в виде строки символов, обозначив сим
волом L движение влево, а символом U - движение вверх.*/

void SolveLameKing(const std::vector<std::vector<int>>& Board, std::vector<std::vector<int>>& SumBoard, std::vector<std::vector<char>>& PathBoard)
{
    //FIX_ME: использование глобальной переменной
    //int n;
    int BoardSize = static_cast<int>(Board.size());

    SumBoard[BoardSize - 1][BoardSize - 1] = Board[BoardSize - 1][BoardSize - 1];

    // Заполняем последний столбец
    for (int RowIndex = BoardSize - 2; RowIndex >= 0; --RowIndex)
    {
        SumBoard[RowIndex][BoardSize - 1] = SumBoard[RowIndex + 1][BoardSize - 1] + Board[RowIndex][BoardSize - 1];
        PathBoard[RowIndex][BoardSize - 1] = 'U';
    }

    // Заполняем последнюю строку
    for (int ColIndex = BoardSize - 2; ColIndex >= 0; --ColIndex)
    {
        SumBoard[BoardSize - 1][ColIndex] = SumBoard[BoardSize - 1][ColIndex + 1] + Board[BoardSize - 1][ColIndex];
        PathBoard[BoardSize - 1][ColIndex] = 'L';
    }

    //FIX_ME: переменная max объявлена не там и не инициализирована
    //int max;

    // Заполняем остальные клетки
    for (int RowIndex = BoardSize - 2; RowIndex >= 0; --RowIndex)
    {
        for (int ColIndex = BoardSize - 2; ColIndex >= 0; --ColIndex)
        {
            int MaxValue;
            if (SumBoard[RowIndex + 1][ColIndex] > SumBoard[RowIndex][ColIndex + 1])
            {
                MaxValue = SumBoard[RowIndex + 1][ColIndex];
                PathBoard[RowIndex][ColIndex] = 'U';
            }
            else
            {
                MaxValue = SumBoard[RowIndex][ColIndex + 1];
                PathBoard[RowIndex][ColIndex] = 'L';
            }
            SumBoard[RowIndex][ColIndex] = MaxValue + Board[RowIndex][ColIndex];
        }
    }
}

//FIX_ME: непонятное название функции
//void p
void BuildPathString(const std::vector<std::vector<char>>& PathBoard, std::string& OutPath)
{
    int BoardSize = static_cast<int>(PathBoard.size());
    int RowIndex = 0;
    int ColIndex = 0;

    while (RowIndex < BoardSize - 1 || ColIndex < BoardSize - 1)
    {
        if (PathBoard[RowIndex][ColIndex] == 'U')
        {
            OutPath += 'U';
            ++RowIndex;
        }
        else if (PathBoard[RowIndex][ColIndex] == 'L')
        {
            OutPath += 'L';
            ++ColIndex;
        }
    }

    //FIX_ME: неправильное направление пути
    //reverse(put1.begin(), put1.end());
    // Путь не нужно разворачивать, так как мы идем от начала к концу
}

void Task2_LameKing()
{
    setlocale(LC_ALL, "Russian");
    std::cout << "=== ЗАДАЧА 2: ХРОМОЙ КОРОЛЬ ===\n\n";

    std::ifstream InputFile("a.txt");
    //FIX_ME: проверка открытия файла
    if (!InputFile.is_open())
    {
        std::cout << "Ошибка открытия файла a.txt" << std::endl;
        return;
    }

    std::ofstream OutputFile("b.txt");
    if (!OutputFile.is_open())
    {
        std::cout << "Ошибка открытия файла b.txt" << std::endl;
        InputFile.close();
        return;
    }

    int BoardSize;
    InputFile >> BoardSize;

    //FIX_ME: непонятные названия переменных
    //vector<vector<int>> pole1(n, vector<int>(n));
    //vector<vector<int>> pole2(n, vector<int>(n));
    std::vector<std::vector<int>> Board(BoardSize, std::vector<int>(BoardSize));
    std::vector<std::vector<int>> SumBoard(BoardSize, std::vector<int>(BoardSize));
    std::vector<std::vector<char>> PathBoard(BoardSize, std::vector<char>(BoardSize));

    for (int RowIndex = 0; RowIndex < BoardSize; ++RowIndex)
    {
        for (int ColIndex = 0; ColIndex < BoardSize; ++ColIndex)
        {
            InputFile >> Board[RowIndex][ColIndex];
        }
    }

    SolveLameKing(Board, SumBoard, PathBoard);

    std::string ResultPath;
    BuildPathString(PathBoard, ResultPath);

    //FIX_ME: вывод лишнего текста, нужна только сумма
    //f2 << "Максимальная сумма монет, которую может собрать король: " << pole2[0][0] << '\n';
    OutputFile << SumBoard[0][0] << std::endl;

    //FIX_ME: вывод лишнего текста и пробелов в пути
    //f2 << "Путь: " << put1;
    OutputFile << ResultPath;

    InputFile.close();
    OutputFile.close();

    std::cout << "Программа завершена. Ответ записан в файл b.txt" << std::endl;
}

// Задача 3: 
/*К-ичные числа. Среди чисел в системе счисления с основанием K (2≤K≤10) определить сколько
имеется чисел из N (1<N<20, K+N<26) разрядов таких, что в их записи не содержится два и
более подряд идущих нулей. Для того, чтобы избежать переполнения, ответ
представьте в виде вещественного числа.*/

void Task3_KaryNumbers()
{
    setlocale(LC_ALL, "Russian");
    std::cout << "=== ЗАДАЧА 3: K-ИЧНЫЕ ЧИСЛА ===\n\n";

    //FIX_ME: Добавлена инициализация переменных
    int K = 0;
    int N = 0;

    std::cout << "Введите основание K (2 <= K <= 10): ";
    std::cin >> K;
    std::cout << "Введите количество разрядов N (1 < N < 20): ";
    std::cin >> N;

    // Проверка корректности входных данных
    if (K < 2 || K > 10)
    {
        std::cout << "Некорректные входные данные." << std::endl;
        return;
    }

    //FIX_ME: Исправлено некорректное условие (K+N < 26, а не K+N >= 26)
    //if (K + N >= 26)
    if (K + N >= 26)
    {
        std::cout << "Некорректные входные данные." << std::endl;
        return;
    }

    if (N <= 1 || N >= 20)
    {
        std::cout << "Некорректные входные данные." << std::endl;
        return;
    }

    //FIX_ME: Изменены названия переменных в соответствии со стилем EpicGames
    int NonZeroLast = 0;  // числа, оканчивающиеся не на ноль
    int ZeroLast = 0;     // числа, оканчивающиеся на один ноль
    int TwoZeroLast = 0;  // числа, оканчивающиеся на два и более нулей

    int TempNonZero = 0;
    int TempZero = 0;
    int TempTwoZero = 0;

    //FIX_ME: Исправлены начальные значения для случая с одной цифрой
    //nz = K - 1; oz = 1; tz = 0;
    NonZeroLast = K - 1;  // первая цифра не может быть нулем
    ZeroLast = 0;         // с одной цифрой не может быть окончания на ноль
    TwoZeroLast = 0;      // с одной цифрой не может быть двух нулей подряд

    // Цикл для добавления разрядов
    for (int i = 2; i <= N; i++)
    {
        // Сохраняем текущие значения
        TempNonZero = NonZeroLast;
        TempZero = ZeroLast;
        TempTwoZero = TwoZeroLast;

        //FIX_ME: Исправлена логика вычислений
        //nz = _nz * (K - 1) + _oz * (K - 1);
        NonZeroLast = (TempNonZero + TempZero) * (K - 1);

        //oz = _nz;
        ZeroLast = TempNonZero;

        //tz = _tz * K + _oz;
        TwoZeroLast = TempTwoZero * K + TempZero;
    }

    // Общее количество подходящих чисел (без двух и более нулей подряд)
    //FIX_ME: Исправлено вычисление результата
    //double s = nz + oz;
    double Result = static_cast<double>(NonZeroLast + ZeroLast);

    std::cout << "Количество подходящих K-ичных чисел: " << Result << std::endl;
}

// Задача 4: 
/*Во всех заданиях данной подгруппы предполагается, что исходные строки, определяющие выражения,
не содержат пробелов.При выполнении заданий не следует использовать оператор цикла.
Вывести значение логического выражения, заданного в виде строки S.Выражение определяется следующим
образом(«T» — True, «F» — False) :
 <выражение> :: = T | F | And(<параметры>) | Or(<параметры>)
 <параметры> :: = <выражение> | <выражение>, <параметры>*/

void ClearInputBuffer()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void PrintLogicalExpressionsMenu()
{
    std::cout << "========== КАЛЬКУЛЯТОР ЛОГИЧЕСКИХ ВЫРАЖЕНИЙ ==========\n";
    std::cout << "T - истина (True)\n";
    std::cout << "F - ложь (False)\n";
    std::cout << "And(expr1, expr2, ...) - логическое И\n";
    std::cout << "Or(expr1, expr2, ...) - логическое ИЛИ\n";
    std::cout << "================================================\n";
}

// FIX_ME: переименована функция splitRecursive в SplitRecursive
// vector<string> splitRecursive(const string& s, char delimiter, size_t start = 0)
std::vector<std::string> SplitRecursive(const std::string& String, char Delimiter, size_t StartPos)
{
    std::vector<std::string> Result;
    size_t Pos = String.find(Delimiter, StartPos);

    // FIX_ME: изменены имена переменных
    if (Pos != std::string::npos)
    {
        Result.push_back(String.substr(StartPos, Pos - StartPos));
        std::vector<std::string> Remaining = SplitRecursive(String, Delimiter, Pos + 1);
        Result.insert(Result.end(), Remaining.begin(), Remaining.end());
    }
    else if (StartPos < String.length())
    {
        Result.push_back(String.substr(StartPos));
    }

    return Result;
}

// FIX_ME: переименована функция evaluateAnd в EvaluateAnd
// bool evaluateAnd(const vector<string>& expressions, size_t index = 0)
bool EvaluateAnd(const std::vector<std::string>& Expressions, size_t Index)
{
    if (Index >= Expressions.size())
    {
        return true;
    }

    if (!EvaluateExpression(Expressions[Index]))
    {
        return false;
    }

    return EvaluateAnd(Expressions, Index + 1);
}

// FIX_ME: переименована функция evaluateOr в EvaluateOr
// bool evaluateOr(const vector<string>& expressions, size_t index = 0)
bool EvaluateOr(const std::vector<std::string>& Expressions, size_t Index)
{
    if (Index >= Expressions.size())
    {
        return false;
    }

    if (EvaluateExpression(Expressions[Index]))
    {
        return true;
    }

    return EvaluateOr(Expressions, Index + 1);
}

// FIX_ME: переименована функция evaluate в EvaluateExpression
// bool evaluate(const string& expr)
bool EvaluateExpression(const std::string& Expression)
{
    // FIX_ME: изменены имена переменных
    if (Expression == "T")
    {
        return true;
    }
    else if (Expression == "F")
    {
        return false;
    }
    else if (Expression.substr(0, 3) == "And")
    {
        // Убираем "And(" и ")"
        // FIX_ME: исправлено извлечение параметров
        std::string Params = Expression.substr(4, Expression.size() - 5);
        std::vector<std::string> SubExprs = SplitRecursive(Params, ',', 0);
        return EvaluateAnd(SubExprs, 0);
    }
    else if (Expression.substr(0, 2) == "Or")
    {
        // Убираем "Or(" и ")"
        // FIX_ME: исправлено извлечение параметров
        std::string Params = Expression.substr(3, Expression.size() - 4);
        std::vector<std::string> SubExprs = SplitRecursive(Params, ',', 0);
        return EvaluateOr(SubExprs, 0);
    }

    return false;
}

void Task4_LogicalExpressions()
{
    setlocale(LC_ALL, "Russian");
    std::cout << "=== ЗАДАЧА 4: ЛОГИЧЕСКИЕ ВЫРАЖЕНИЯ ===\n\n";

    PrintLogicalExpressionsMenu();

    std::string Expression;
    char Choice;

    do
    {
        std::cout << "\nВведите логическое выражение: ";
        std::getline(std::cin, Expression);

        if (!Expression.empty())
        {
            bool Result = EvaluateExpression(Expression);
            std::cout << "Результат: " << Expression << " -> " << (Result ? "T" : "F") << std::endl;
        }
        else
        {
            std::cout << "Ошибка: выражение не может быть пустым!" << std::endl;
        }

        std::cout << "\nПродолжить? (y/n): ";
        std::cin >> Choice;
        ClearInputBuffer();

    } while (Choice == 'y' || Choice == 'Y');

    std::cout << "Программа завершена." << std::endl;
}