#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <iomanip>
#include <Windows.h>
#include <time.h>
#include <stdio.h>
#include <string>
#pragma warning (disable : 4996)
using namespace std;

struct Student {
	char name[64];
	char inizials[6];
	int Note[5];
};


void Create(const char* fname);
void Print(const char* fname);
void fWrite(fstream& f, const int i, Student s);
Student fRead(fstream& f, const int i);
void Add(const char* fname);

void SearchTXTStudentWith(const char* fname, int cheker, const int count);
int SearchAndRemoteTXTStudentWithTwo(const char* fname, int cheker, const int count);
void CreateFileToUnit();


using namespace std;


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	char fname[100];

	int menuItem;
	do {
		cout << "Оберіть дію: " << endl;
		cout << "[1]  Cтворити файл." << endl;
		cout << "[2]  Додати елементи до списку." << endl;
		cout << "[3]  Переглянути список." << endl;
		cout << "[4]  Вивести список з хочаб одною трійкою." << endl;
		cout << "[5]  Вивести список з хочаб одною двійкою." << endl;
		cout << "[6]  Вивести список відміників." << endl;
		cout << "[7]  Вивести список з 2-ма або більше двійок." << endl;
		cout << "[8]  Видалити із списка студента з 2-ма або більше двійок." << endl;
		cout << "[9]  Відкрити файл." << endl;
		cout << "[0]  вихід та завершення роботи програми" << endl << endl;
		cout << "Введіть значення: "; cin >> menuItem;
		switch (menuItem) {
		case 1:
			cout << "Введіть ім'я файлу: "; cin >> fname;
			Create(fname);
			break;
		case 2:
			Add(fname);
			break;
		case 3:
			Print(fname);
			break;
		case 4:
			SearchTXTStudentWith(fname, 3, 1);
			break;
		case 5:
			SearchTXTStudentWith(fname, 2, 1);
			break;
		case 6:
			SearchTXTStudentWith(fname, 5, 5);
			break;
		case 7:
			SearchTXTStudentWith(fname, 2, 2);
			break;
		case 8:
			SearchAndRemoteTXTStudentWithTwo(fname, 2, 2);
			break;
		case 9:
			cout << "Введіть ім'я файлу: "; cin >> fname;
			break;
		case 0:
			break;
		default:
			cout << "Ви ввели помилкове значення! Слід ввести число - номер вибраного пункту меню" << endl;
		}
	} while (menuItem != 0);

	system("pause");
	cin.get();
	return 0;
}

void Create(const char* fname)
{
	ofstream f(fname, ios::binary);
	Student s;
	char ch;
	int i = 1;
	do {
		cout << "Студент №: " << i++ << ": " << endl;
		cin.ignore();
		cout << "Ім'я: ";
		cin >> s.name;
		cout << "Ініціали: ";
		cin >> s.inizials;
		for (int i = 0; i < 5; i++)
		{
			cout << "Оцінка з " << i + 1 << "предмету : ";
			cin >> s.Note[i];
		}
		cout << endl;
		cout << endl;
		if (!f.write((char*)&s, sizeof(Student))) {
			cerr << "Error writing file." << endl;
		}
		cout << "Continue?(Y/N)"; cin >> ch;
	} while (ch == 'y' || ch == 'Y');
}

void Print(const char* fname)
{
	cout << "=================================================" << endl;
	cout << "|  №  |    Ім'я     | iніціали |  1  |  2  |  3  |  4  |  5  |" << endl;
	cout << "-------------------------------------------------" << endl;

	ifstream f(fname, ios::binary);
	Student s;
	int i = 1;
	while (f.read((char*)&s, sizeof(Student))) {
		cout << "| " << setw(3) << right << i++
			<< " | " << setw(11) << left << s.name
			<< " | " << setw(8) << right << s.inizials << " |";
		for (int i = 0; i < 5; i++)
		{
			cout << " " << setw(3) << right << s.Note[i] << " |";
		}
		cout << endl;

	}
	cout << "=================================================" << endl;
	cout << endl;
}

void fPrint(fstream& f, int i)
{
	Student s;
	f.seekg(i * (long)sizeof(Student));
	f.read((char*)&s, sizeof(Student));
	cout << " --> " << s.name << " " << s.inizials;
	for (int i = 0; i < 5; i++)
	{
		cout << " " << s.Note[i];
	}
	cout << endl;

}

void fWrite(fstream& f, const int i, Student s) {
	f.seekp(i * (long)sizeof(Student));
	f.write((char*)&s, sizeof(Student));
}

Student fRead(fstream& f, const int i) {
	Student s;
	f.seekg(i * (long)sizeof(Student));
	f.read((char*)&s, sizeof(Student));
	return s;
}

void Add(const char* fname) {
	fstream f(fname, ios::in | ios::out);
	f.seekg(0, ios::end);
	Student s;
	char ch;
	int i = 1;
	do {
		cout << "Студент №: " << i++ << ": " << endl;
		cin.ignore();
		cout << "Ім'я: ";
		cin >> s.name;
		cout << "Ініціали: ";
		cin >> s.inizials;
		for (int i = 0; i < 5; i++)
		{
			cout << "Оцінка з " << i + 1 << "предмету : ";
			cin >> s.Note[i];
		}
		cout << endl;
		cout << endl;
		if (!f.write((char*)&s, sizeof(Student))) {
			cerr << "Error writing file." << endl;
		}
		cout << "Continue?(Y/N)"; cin >> ch;
	} while (ch == 'y' || ch == 'Y');
}

void  SearchTXTStudentWith(const char* fname, int cheker, const int count) {

	fstream fin(fname, ios::binary | ios::out | ios::in);
	cin.ignore();
	fin.seekg(0, ios::end);
	int size = fin.tellg() / sizeof(Student);
	fin.seekg(0, ios::beg);

	int counter;
	bool isUsed = false;

	for (int i = 0; i < size; i++) {
		Student tmp;

		isUsed = false;
		counter = 0;

		tmp = fRead(fin, i);
		for (int j = 0; j < 5; j++)
		{
			if (tmp.Note[j] == cheker)
			{
				counter++;
				if (counter >= count)
					if (!isUsed)
					{
						cout << "Дані про людину з " << cheker << " : "; fPrint(fin, i); cout << endl;
						isUsed = true;
					}
			}
		}
	}
}

int  SearchAndRemoteTXTStudentWithTwo(const char* fname, int cheker, const int count)
{

	fstream fin(fname, ios::binary | ios::out | ios::in);
	fstream t("tmp", ios::binary | ios::in | ios::out);
	t.seekg(0, ios::end);
	cin.ignore();
	fin.seekg(0, ios::end);
	int size = fin.tellg() / sizeof(Student);
	fin.seekg(0, ios::beg);

	int counter;
	bool isUsed;
	int rem = 0;
	for (int i = 0; i < size; i++) {
		Student tmp;

		isUsed = false;

		counter = 0;


		tmp = fRead(fin, i);



		for (int j = 0; j < 5; j++)
		{
			if (tmp.Note[j] == cheker)
			{
				counter++;
				if (counter >= count)
					if (!isUsed)
					{
						cout << "Видаленно " << cheker << " : "; fPrint(fin, i); cout << endl;
						isUsed = true;
						rem++;
					}
			}
		}
		if (!isUsed == true)
		{
			if (!t.write((char*)&tmp, sizeof(Student))) {
				cerr << "Error writing file." << endl;
			}

		}
		fin.close(); // для вилучення і перейменування
		t.close(); // файли мають бути закриті

		remove(fname); // знищуємо заданий файл
		rename("tmp", fname); // перейменовуємо тимчасовий файл
		return rem;
	}
}

void CreateFileToUnit()
{
	char fname[100]{ 'U','n','i','t','T','e','s','t' };
	ofstream fout;
	fout.open(fname, ios::app);
	fout << ' ' << "Pavel";
	fout << ' ' << "G.G.";
	fout << ' ' << "2";
	fout << ' ' << "2";
	fout << ' ' << "2";
	fout << ' ' << "2";
	fout << ' ' << "2";
	fout.close();
}
