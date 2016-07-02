#ifndef CONTFUNCTIONS_H
#define CONTFUNCTIONS_H
/**
Вывод в стандартный поток данных, находящихся в контейнере
\param[in] Cont Стандартный контейнерный класс
*/
template<class TypeCont>
void PrintContainer(TypeCont &Cont)
{
	for (size_t Index = 0, ContSize = Cont.size(); Index < ContSize; ++Index)
	{
		std::cout << Cont[Index] << " ";
	}
	std::cout << std::endl;
}//PrintContainer
 
//----------------------------------------------------------------------------- 
 /**
Синхронизация контейнеров
\param[in, out] &Cont1 Первый контейнер
\param[in, out] &Cont2 Второй контейнер
\param[in] SynchType Тип синхронизации
0 - если хоть один ноль, то в обоих должен быть ноль
1 - если хоть в одном есть число, то в обоих должно быть это число
*/
template<class TypeCont1, class TypeCont2>
void Synchronize(TypeCont1 &Cont1, TypeCont2 &Cont2, int SynchType = 0)
{
	for (size_t Index = 0, Cont1Size = Cont1.size(), Cont2Size = Cont2.size();
		Index < Cont1Size && Index < Cont2Size; ++Index)
	{
		if (Cont1[Index] != Cont2[Index])//Есть несоответствие
		{
			switch (SynchType)
			{
			case 0:
				Cont1[Index] = Cont2[Index] = 0;
				break;
			case 1:
				if (Cont1[Index] == 0)
				{
					Cont1[Index] = Cont2[Index];
				}
				else if (Cont2[Index] == 0)
				{
					Cont2[Index] = Cont1[Index];
				}
				break;
			}//switch
		}//if
	}//for
}//Synchronize

//----------------------------------------------------------------------------- 
//!Найти несколько разных случайных чисел в диапазоне
//!Если количество больше чем количество чисел в диапазоне, то будет заполнен только теми которые есть.
//! Пример
//! ctResult = {4, 6};
//! iRangeBegin = 5;
//! iRangeEnd = 10;
//! iResultQuantity = 10;
//! Результат ctResult = {4, 6, 8, 9, 5, 7};
/**
\param ctResult [out] Результирующий набор чисел вектор. Может быть уже заполнен
\param iRangeBegin [in] Начало диапазона
\param iRangeEnd [in] Конец диапазона
\param iResultQuantity [in] Количество результатов
*/
void GetSeveralDifferentRandomNumbers(
	std::vector<size_t> & Result,
	const size_t & RangeBegin,
	const size_t & RangeEnd,
	const size_t & ResultQuantity)
{
	if (RangeBegin < RangeEnd)
	{
		std::vector<size_t> Sequence;
		Sequence.reserve(RangeEnd - RangeBegin);

		//Заполнить вектор рядом из допустимых чисел
		for (size_t RangeItem = RangeBegin;
			RangeItem < RangeEnd;
			++RangeItem)
		{
			//Исключить из ряда те числа, которые уже есть
			if (std::find(Result.begin(), Result.end(), RangeItem) == Result.end())
			{
				Sequence.push_back(RangeItem);
			}
		}//for

		//Сделать последовательность случайной
		size_t Counter = 0;

		for (;
			Counter < ResultQuantity && //достаточно "перепутать" только первые элементы
			Counter < Sequence.size(); //защита от неправильных входных данных
			++Counter)
		{
			//найти случайный элемент из оставшихся
			size_t ItemToSwap = (rand() % (Sequence.size() - Counter)) + Counter;

			if (Counter != ItemToSwap)
			{
				//поменять местами текущий элемент со случайно выбранным в хвосте
				std::swap(Sequence[Counter], Sequence[ItemToSwap]);
			}
		}//for

		Result.insert(Result.end(), Sequence.begin(), Sequence.begin() + Counter);
	}//if
}//GetSeveralDifferentRandomNumbers

//----------------------------------------------------------------------------- 
/**
Очистить заданное количество элементов в контейнере
\param[in, out] Cont контейнер
\param[in] Quantity количество элементов, которые надо удалить
*/
template<class ContType>
void RemoveItems(ContType &Cont, size_t Quantity)
{
	std::vector<size_t> Result;
	Result.reserve(Cont.size());
	for (size_t Index = 0, ContSize = Cont.size(); Index < ContSize; ++Index)
	{
		if (Cont[Index] == 0)
		{
			Result.push_back(Index);
		}
	}
	size_t RemovedIndex = Result.size();
	//Дополнить индексами элементов, которые надо удалить
	GetSeveralDifferentRandomNumbers(Result, 0, Cont.size(), Quantity);
	for (auto ResultSize = Result.size() ;RemovedIndex < ResultSize; ++RemovedIndex)
	{
		Cont[Result[RemovedIndex]] = 0;
	}
}//RemoveItems

//----------------------------------------------------------------------------- 

#endif
