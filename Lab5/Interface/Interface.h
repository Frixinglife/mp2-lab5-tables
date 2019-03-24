#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include "Polynomials.h"
#include "LogTables.h"

void Start(LogTables<NamedPolynom> &t); // Запуск интерфейса
void EntryRules(); // Правила ввода полиномов
void OperationСhoice(LogTables<NamedPolynom> &t); // Операции с таблицей (положить, найти или удалить полином с заданным именем)
void SelectPolynoms(LogTables<NamedPolynom> &t); // Выбор двух полиномов из таблицы для операции с ними
void OperationsWithPolynoms(LogTables<NamedPolynom> &t, NamedPolynom a, NamedPolynom b); // Выбор операции для выбранных полиномов
void SetNameResult(LogTables<NamedPolynom> &t, NamedPolynom res); // Установить название полученному полиному
void OperationWithResult(LogTables<NamedPolynom> &t, NamedPolynom res); // Положить результат операции в таблицу или нет
void OperationsWithTableOrPolynoms(LogTables<NamedPolynom> &t); // Перейти к выбору операций с таблицей или к выбору операций с полиномами
void AddPolynomToTable(LogTables<NamedPolynom> &t); // Добавить полином в таблицу
void FindPolynomInTable(LogTables<NamedPolynom> &t); // Найти полином в таблице
void DeletePolynomFromTable(LogTables<NamedPolynom> &t); // Удалить полином из таблицы

#endif