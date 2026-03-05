#pragma once

#include <vector>
#include <string>

// Задача 1: Задача о рюкзаке (артефакты)
void Task1_Artifacts();

// Задача 2: Хромой король
void Task2_LameKing();

// Задача 3: K-ичные числа
void Task3_KaryNumbers();

// Задача 4: Логические выражения
void Task4_LogicalExpressions();

// Функции для задачи 1
void InsertionSort(std::vector<int>& Weights, std::vector<int>& Values);
int SolveBackpack(int MaxWeight, const std::vector<int>& Weights, const std::vector<int>& Values, int NumItems, std::vector<int>& SelectedItems);

// Функции для задачи 2
void SolveLameKing(const std::vector<std::vector<int>>& Board, std::vector<std::vector<int>>& SumBoard, std::vector<std::vector<char>>& PathBoard);
void BuildPathString(const std::vector<std::vector<char>>& PathBoard, std::string& OutPath);

// Функции для задачи 4
bool EvaluateExpression(const std::string& Expression);
bool EvaluateAnd(const std::vector<std::string>& Expressions, size_t Index);
bool EvaluateOr(const std::vector<std::string>& Expressions, size_t Index);
std::vector<std::string> SplitRecursive(const std::string& String, char Delimiter, size_t StartPos);
void ClearInputBuffer();
void PrintLogicalExpressionsMenu();