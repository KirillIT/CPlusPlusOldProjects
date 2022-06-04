﻿#include <iostream> //библиотека для ввода и вывода данных в консоль

#include <Windows.h> //библиотека для подлючения русского языка (В данном случае)

#include <fstream> //для подключения файлов

#include <string> //для использования строк

#include <sstream> //эта нужна только для 73-ей строки (переводит строку в число)

using namespace std;//эта строка позволяет писать так - "cout « ..." вместо "std::cout « ..."

int main() {//программа начинает работать именно отсюда, с этой главной функции

	SetConsoleCP(1251); //для подлючения русского языка

	SetConsoleOutputCP(1251); //для подлючения русского языка

	cout << "Введите путь к файлу: ";

	fstream file; //переменная файла(для работы с файлами)

	string path; //строка, хранящая путь к файлу

	cin >> path; //вводим путь к файлу

	file.open(path, fstream::in); //окрываем файл, path - путь, fstream::in означает, что файл открыт только для чтения

	int M = 0, N = 1; //это размер нашего будущего массива, пока что присвоим M(кол-во строк) - ноль и N (кол-во столбцов) - 1. Почему тут 1, внизу поясню

	string helper; //строка-помощник

	while (!file.eof()) {//для начала, чтобы создать массив, мы должны узнать его размеры. Тут кзнаем кол-во строк. Пока файл не закончен, выполняем это цикл. eof = end of file

		getline(file, helper);//считываем строку из файла в строку-помощник

		M++;//и увеличиваем наш счётчик строк
		
	}

	for (int i = 0; i < helper.size(); i++) {//теперь узнаем кол-во столбцов. У нас в переменной helper сейчас строка из файла. Например "-2 -3 -4 -5 -6 -7"
		//соответственно, сколько у нас элеменетов в одной строке, столько у нас и столбцов, т.к. по условию матрица прямоугольная
		if (helper[i] == ' ') {//проходим по нашей строке "-2 -3 -4 -5 -6 -7" посимвольно, и если встречаем пробел,
		
			N++;//то увеличиваем счётчик столбцов. Замечу, что пробелов в строке - 5, а чисел 6. Именно поэтому появилась единица(см. строку 29)

		}

	}

	file.close();//закроем файл, т.к. он у нас уже закончился (условно говоря мы сейчас находимся в конце файла) и нужно будет открыть его заново, чтобы начать просмотр с первой строки

	int** mainArr = new int* [M];//создаём нашу матрицу

	for (int i = 0; i < M; i++){
	
		mainArr[i] = new int[N];//это тоже её создание

	}

	cout << "Исходная матрица из файла" << endl;

	file.open(path, fstream::in);//опять окрываем файл, path - путь, fstream::in означает, что файл открыт только для чтения

	for (int i = 0; i < M; i++) {//тут алгоритм записи данных из файла в нашу матрицу

		for (int j = 0; j < N; j++) {

			helper = "";//обнуляем строку-помощник

			file >> helper;//записываем из файла в строку-помощник 

			istringstream(helper) >> mainArr[i][j];//а эта строка конвертирует строку в число и записывает это число в массив

			cout << mainArr[i][j] << " ";//тут выводим массив в консоль

		}

		cout << endl;//когда строка закончилась, мы должны перейти на следующую. Для вывода в консоль

	}

	int counter;//счётчик чётных отрицательных элементов

	for (int i = 0; i < M; i++) {

		counter = 0;//для каждой строки он свой, поэтому вначале мы всегда должны обнулить его

		bool stringMatchTheCondition = false; //логическая перемененая - строка подходит условию - пока что нет (по умолчанию)

		for (int j = 0; j < N; j++) {
		
			if (mainArr[i][j] % 2 == 0 && mainArr[i][j] < 0) {//если на элемент при делении на 2 даёт остаток 0(то есть он чётный) и  он меньше нуля, то...

				stringMatchTheCondition = true; //логическая перемененая - строка подходит условию - становится верной

				counter++;// и счётчик увеличивется

			}
		
		}

		if (stringMatchTheCondition) {//если логическая перемененая - строка подходит условию - верная, то...

			cout << "В строке " << i + 1 << " - " << "чётных отрицательных элементов - "  << counter << endl; //выводим кол-во чётных отрицательных элементов в ней и её номер

		}

	}

	for (int i = 0; i < M; i++){
	
		delete[] mainArr[i];//в конце программы обязательно удаляем матрицу
			
	}

	delete[] mainArr;//это тоже удаление матрицы
}