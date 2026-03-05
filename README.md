# Тетерина Юлия ИТ-16
## Лабораторная работа №1
## Вариант 4

### Исправления по кодстайлу EpicGames:
### Задание 1: Артефакты
1. Именование функций
 
Было: ```void insert_sort(...)``` - с маленькой буквы, snake_case

Стало: ```void InsertionSort(...)``` - с заглавной буквы, PascalCase

Было: ```int backpack(...)``` - с маленькой буквы, непонятное название

Стало: ```int SolveBackpack(...)``` - с заглавной буквы, понятное название

2. Именование параметров функций

Было: ```std::vector<int>& w, std::vector<int>& p``` - однобуквенные

Стало: ```std::vector<int>& Weights, std::vector<int>& Values``` - осмысленные, с заглавной

Было: ```int W, std::vector<int>& wt, std::vector<int>& val, int n```

Стало: ```int MaxWeight, const std::vector<int>& Weights, const std::vector<int>& Values, int NumItems, std::vector<int>& SelectedItems```

3. Именование локальных переменных

Было: ```int temp = i;```

Стало: ```int Temp = i;``` - с заглавной буквы

Было: ```std::vector<std::vector<int>> dp(...)```

Стало: ```std::vector<std::vector<int>> DP(...)``` - с заглавной буквы

Было: ```int n, W;```

Стало: ```int NumItems = 0, MaxWeight = 0;``` - инициализация и осмысленные имена

4. Типы индексов в циклах

Было: ```for (int i = 1; i < w.size(); i++)``` - сравнение int с size_t

Стало: ```for (size_t i = 1; i < Weights.size(); ++i)``` - правильный тип size_t

Было: ```while (temp - 1 >= 0 && w[temp] < w[temp - 1])``` - потенциальное переполнение

Стало: ```while (Temp - 1 >= 0 && Temp - 1 < static_cast<int>(Weights.size()) && Weights[Temp] < Weights[Temp - 1])``` - явная проверка границ

5. Форматирование кода

Было: ```if (i == 0 || w == 0) dp[i][w] = 0;``` - оператор на той же строке

Стало:

if (i == 0 || w == 0) {  
    DP[i][w] = 0;  
} - фигурные скобки и оператор на новой строке

Было: ```dp[i][w] = std::max(val[i - 1] + dp[i - 1][w - wt[i - 1]], dp[i - 1][w]);``` - длинная строка

Стало: ```DP[i][w] = std::max(Values[i - 1] + DP[i - 1][w - Weights[i - 1]], DP[i - 1][w]);``` - форматирование с переносом

6. Добавление const для неизменяемых параметров

Было: ```int SolveBackpack(int MaxWeight, std::vector<int>& Weights, std::vector<int>& Values, ...)```

Стало: ```int SolveBackpack(int MaxWeight, const std::vector<int>& Weights, const std::vector<int>& Values, ...)``` - добавлен const

7. Инициализация переменных

Было: ```int n, W;``` - неинициализированные переменные

Стало: ```int NumItems = 0, MaxWeight = 0;``` - инициализация при объявлении

8. Удаление ненужной сортировки

Было: Сортировка нарушала соответствие индексов оригинальным номерам артефактов

Стало: Убрали вызов InsertionSort перед решением задачи

9. Добавление восстановления ответа

Было: Функция возвращала только максимальную стоимость

Стало: Функция через параметр SelectedItems возвращает индексы выбранных предметов  

Добавлен код:  

int CurrentWeight = MaxWeight;  
for (int i = NumItems; i > 0; --i) {  
    if (DP[i][CurrentWeight] > DP[i - 1][CurrentWeight]) {  
        SelectedItems.push_back(i - 1);  
        CurrentWeight -= Weights[i - 1];  
    }  
}  

10. Исправление условия проверки выбранного предмета  

Было: ```if (DP[i][CurrentWeight] != DP[i - 1][CurrentWeight])``` - некорректно  

Стало: ```if (DP[i][CurrentWeight] > DP[i - 1][CurrentWeight])``` - правильно определяет, взяли ли предмет  

11. Подсчет суммарного веса

Было: не считался

Стало: добавлен подсчет TotalWeight по выбранным индексам

12. Сортировка индексов при выводе

Было: ```for (int Index : SelectedIndices)``` - вывод в порядке восстановления (обратном)

Стало: ```std::sort(SelectedIndices.begin(), SelectedIndices.end())``` - вывод в порядке возрастания для удобства чтения результатов

13. Вывод номеров артефактов (1-based)
 
Было: ```<< SelectedIndices[i]``` - вывод 0-based индексов

Стало: ```<< SelectedIndices[i] + 1``` - вывод 1-based номеров для пользователя

14. Форматирование вывода

Было: вывод без разделителей

Стало: добавлены запятые между номерами артефактов

### Задача 2: Хромой король
1. Именование функций

Было: ```void Solve(...)``` - непонятное название  

Стало: ```void SolveLameKing(...)``` - конкретное название, отражающее суть задачи  

Было: ```void p(...)``` - абсолютно непонятное название  

Стало: ```void BuildPathString(...)``` - понятное название, описывающее действие  

2. Удаление глобальных переменных

Было: ```int n;``` - глобальная переменная  

Стало: локальная переменная ```int BoardSize```, передаваемая через параметры  

3. Именование локальных переменных

Было: ```int n;``` - однобуквенная переменная  

Стало: ```int BoardSize;``` - осмысленное имя  

Было: ```vector<vector<int>> pole1, pole2``` - непонятные названия 

Стало: ```std::vector<std::vector<int>> Board, SumBoard``` - понятные имена: доска и таблица сумм  

Было: ```int i, j``` - индексы в циклах 

Стало: ```int RowIndex, ColIndex``` - понятные имена счетчиков  

4. Добавление const для неизменяемых параметров
 
Было: ```void Solve(std::vector<std::vector<int>>& Board, ...)```  

Стало: ```void SolveLameKing(const std::vector<std::vector<int>>& Board, ...)``` - добавлен const, так как Board не изменяется  

5. Инициализация переменных

Было: ```int max;``` - неинициализированная переменная

Стало: ```int MaxValue;``` - инициализируется перед использованием  

6. Проверка открытия файлов

Было: отсутствовала проверка  

Стало:  
if (!InputFile.is_open())  
{  
    std::cout << "Ошибка открытия файла a.txt" << std::endl;  
    return;  
}

7. Закрытие файлов

Было: отсутствовало явное закрытие  

Стало: ```InputFile.close(); OutputFile.close(); ``` 

8. Исправление направления пути

Было: ```reverse(put1.begin(), put1.end());``` - неправильно, путь разворачивался  

Стало: путь не разворачивается, так как строится в правильном направлении  

9. Добавление проверки границ при восстановлении пути
  
Было: ```while (RowIndex < n - 1 || ColIndex < n - 1)```  

Стало: ```while (RowIndex < BoardSize - 1 || ColIndex < BoardSize - 1)```    
более читаемое условие с явным использованием размера  

10. Форматирование кода

Было: ```for (int i=n-2; i>=0; i--)```  

Стало: ```for (int RowIndex = BoardSize - 2; RowIndex >= 0; --RowIndex)```   

### Задание 3: K-ичные числа
1. Инициализация переменных

Было: ```int K, N;```  
неинициализированные переменные

Стало:  
```int K = 0;```  
```int N = 0;```  
явная инициализация

2. Именование переменных
 
Было: ```nz, oz, tz, _nz, _oz, _tz``` - непонятные сокращения  

Стало:  
```int NonZeroLast = 0;```  // числа, оканчивающиеся не на ноль  
```int ZeroLast = 0;```     // числа, оканчивающиеся на один ноль  
```int TwoZeroLast = 0;```  // числа, оканчивающиеся на два и более нулей  
```int TempNonZero = 0;```  
```int TempZero = 0;```  
```int TempTwoZero = 0;```  
осмысленные имена с комментариями

3. Исправление логики вычислений

Было: неправильная логика для начальных значений  
```nz = K - 1; oz = 1; tz = 0;```

Стало: правильные начальные значения  
```NonZeroLast = K - 1;```  // первая цифра не может быть нулем  
```ZeroLast = 0;```         // с одной цифрой не может быть окончания на ноль  
```TwoZeroLast = 0;```      // с одной цифрой не может быть двух нулей подряд  

Было: неправильные формулы пересчета  
```nz = _nz * (K - 1) + _oz * (K - 1);```  
```oz = _nz;```  
```tz = _tz * K + _oz;```  

Стало: правильные формулы  

```NonZeroLast = (TempNonZero + TempZero) * (K - 1);```  
```ZeroLast = TempNonZero;```  
```TwoZeroLast = TempTwoZero * K + TempZero;```  

4. Добавление проверок входных данных

Было: отсутствовали проверки  

Стало:  
if (K < 2 || K > 10)  
{  
    std::cout << "Некорректные входные данные." << std::endl;  
    return;  
}  
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

5. Форматирование циклов

Было: ```for (int i = 2; i <= N; i++)``` 

Стало: ```for (int i = 2; i <= N; ++i)``` - префиксный инкремент  

6. Явное приведение типов

Было: ```double s = nz + oz;``` - неявное преобразование  

Стало: ```double Result = static_cast<double>(NonZeroLast + ZeroLast);``` - явное static_cast  

7. Именование результата

Было: ```double s;``` - непонятное имя

Стало: ```double Result;``` - понятное имя

### Задача 4: Логические выражения
1. Удаление неиспользуемых заголовочных файлов

Было:  
#include fstream  
#include cstdlib  
#include ctime  
#include random  
#include sstream

Стало: только необходимые заголовки  
#include iostream  
#include string  
#include vector  
#include limits  

2. Удаление using namespace std  

Было: ```using namespace std;``` - плохая практика

Стало: явное использование ```std::``` префикса

3. Именование функций  

Было: ```bool evaluate(const string& expr)``` - с маленькой буквы  

Стало: ```bool EvaluateExpression(const std::string& Expression)``` - понятное имя  

Было: ```bool evaluateAnd(...)``` - с маленькой буквы

Стало: ```bool EvaluateAnd(...)``` - понятное имя

Было: ```bool evaluateOr(...)``` - с маленькой буквы

Стало: ```bool EvaluateOr(...)``` - понятное имя

Было: ```vector<string> splitRecursive(...)``` - с маленькой буквы

Стало: ```std::vector<std::string> SplitRecursive(...)``` - понятное имя

4. Именование параметров функций

Было: ```const string& s, char delimiter, size_t start```

Стало: ```const std::string& String, char Delimiter, size_t StartPos``` - с заглавной буквы

Было: ```const vector<string>& expressions, size_t index```

Стало: ```const std::vector<std::string>& Expressions, size_t Index``` - с заглавной буквы

Было: ```const string& expr```

Стало: ```const std::string& Expression``` - с заглавной буквы

5. Именование локальных переменных

Было: ```size_t pos = s.find(delimiter, start);```

Стало: ```size_t Pos = String.find(Delimiter, StartPos);``` - с заглавной буквы

Было: ```vector<string> result;```

Стало: ```std::vector<std::string> Result;v``` - с заглавной буквы

6. Добавление пользовательского интерфейса

Было: функция ```void Recur23()``` без интерфейса

Стало: ```void Task4_LogicalExpressions()``` с меню и циклом ввода

Добавлены функции:  
```void PrintLogicalExpressionsMenu()```  
```void ClearInputBuffer()```  

7. Добавление обработки пустого ввода  

Было: отсутствовала проверка

Стало:  
if (!Expression.empty())  
{  
    // обработка  
}  
else  
{  
    std::cout << "Ошибка: выражение не может быть пустым!" << std::endl;  
}  

8. Исправление извлечения параметров

Было: неправильное извлечение подстрок  
```std::string Params = Expression.substr(4, Expression.size() - 5);``` // для And  
```std::string Params = Expression.substr(3, Expression.size() - 4);``` // для Or  

9. Добавление функции очистки буфера ввода

Было: отсутствовала

Стало:  
void ClearInputBuffer()  
{  
    std::cin.clear();  
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  
}  

10. Добавление const для неизменяемых параметров

Было: ```std::vector<std::string>& Expressions```

Стало: ```const std::vector<std::string>& Expressions``` - добавлен const

11. Использование правильных типов индексов

Было: ```int index``` - смешивание типов

Стало: ```size_t Index``` - правильный тип для индексации вектора

12. Рекурсивный подход без циклов

Сохранена рекурсивная реализация в соответствии с требованием "не использовать оператор цикла" для обработки выражений:  

```SplitRecursive``` - рекурсивное разбиение строки  

```EvaluateAnd``` - рекурсивное вычисление AND  

```EvaluateOr``` - рекурсивное вычисление OR  

13. Форматирование вывода

Было: только результат  

Стало:  
```std::cout << "Результат: " << Expression << " -> " << (Result ? "T" : "F") << std::endl;  ```
выводится и исходное выражение, и результат
