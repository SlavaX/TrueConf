/*
	Необходимо:
	1.заполнить случайными числами от 1 до 9 значения контейнеров
	vector[i] и map[i];

	2.удалить случайное число элементов(не более 15) в каждом
	контейнере;

	3.после этого провести синхронизацию, чтобы в vector и map
	остались только имеющиеся в обоих контейнерах элементы
	(дубликаты не удалять).
*/
#include <vector>
#include <map>
#include <iostream>
#include <time.h>
#include "ContFunctions.h"

//! Количество чисел
const size_t Quantity = 40;

//! Начало диапазона возможных значений
const unsigned BeginOfTheRange = 1;

//! Количество возможных значений
const unsigned Range = 9;

//! Допустимое количество удаляемых чисел
const unsigned QuantityToRemove = 15;


int main()
{
	setlocale(LC_ALL, "Russian");

	//! Vector для синхронизации
	std::vector<unsigned> VectorSample(Quantity);
	//! Map для синхронизации
	std::map<size_t, unsigned> MapSample;

	//1. Заполнить контейнеры случайными числами
	srand(time(NULL));
	for (size_t Index = 0, ContSize = VectorSample.size();
		Index < ContSize; ++Index)
	{
		VectorSample[Index] = rand() % Range + BeginOfTheRange;
		MapSample[Index] = VectorSample[Index];
	}

	//Вывод содержимого контейнеров в консоль
	std::cout << "После инициализации" << std::endl;
	PrintContainer(VectorSample);
	PrintContainer(MapSample);

	//2. Удалить элементы из контейнеров
	RemoveItems(VectorSample, rand() % QuantityToRemove);
	RemoveItems(MapSample, rand() % QuantityToRemove);

	//Вывод содержимого контейнеров в консоль
	std::cout << std::endl << "После удаления элементов" << std::endl;
	PrintContainer(VectorSample);
	PrintContainer(MapSample);

	//3. Синхронизировать контейнеры
	Synchronize(MapSample, VectorSample);

	//Вывод содержимого контейнеров в консоль
	std::cout << std::endl << "После синхронизации" << std::endl;
	PrintContainer(VectorSample);
	PrintContainer(MapSample);

	system("pause");
	return 0;
}