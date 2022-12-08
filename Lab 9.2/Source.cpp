#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <Windows.h> // забезпечення відображення кирилиці
using namespace std;

enum Spec { ME, TN, FI, In, KN };
string specStr[] = { "Математика та економіка", "Трудове навчання", "Фізика та інформатика", "Інформатика" ,"Комп'ютерні науки" };

struct Student
{
	string prizv;
	unsigned kurs;
	Spec spec;
	double fizika;
	double matematika;
	double informatika;
};

void Create(Student* p, const int N);
void Print(Student* p, const int N);
void Sort(Student* p, const int N);
int* IndexSort(Student* p, const int N);
void PrintIndexSorted(Student* p, int* I, const int N);
int BinSearch(Student* p, const int N, const string prizv, const unsigned kurs, const unsigned informatika);
int main()
{ // забезпечення відображення кирилиці:
	SetConsoleCP(1251); // встановлення сторінки win-cp1251 в потік вводу
	SetConsoleOutputCP(1251); // встановлення сторінки win-cp1251 в потік виводу
	int N;
	cout << "Введіть N: "; cin >> N;

	Student* p = new Student[N];

	int ikurs;
	unsigned kurs;
	string prizv;
	unsigned informatika;
	unsigned iinformatika;
	int found;

	int menuItem;
	do {
		cout << endl << endl << endl;
		cout << "Виберіть дію:" << endl << endl;
		cout << " [1] - введення даних з клавіатури" << endl;
		cout << " [2] - вивід даних на екран" << endl;
		cout << " [3] - бінарний пошук" << endl;
		cout << " [4] - фізичне впорядкування даних" << endl;
		cout << " [5] - індексне впорядкування" << endl;
		cout << " [0] - вихід та завершення роботи програми" << endl << endl;
		cout << "Введіть значення: "; cin >> menuItem;
		cout << endl << endl << endl;
		switch (menuItem)
		{
		case 1:
			Create(p, N);
			break;
		case 2:
			Print(p, N);
			break;
		case 3:
			cout << "Введіть ключі пошуку:" << endl;
			cout << "Курс : ";
			cin >> ikurs;
			kurs = ikurs;
			cout << "Оцінка з інформатики: ";
			cin >> iinformatika;
			informatika = iinformatika;

			cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
			cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок
			cout << " прізвище: "; getline(cin, prizv);
			cout << endl;
			if ((found = BinSearch(p, N, prizv, kurs, informatika)) != -1)
				cout << "Знайдено працівника в позиції " << found + 1 << endl;
			else
				cout << "Шуканого працівника не знайдено" << endl;
			break;

			break;
		case 4:
			Sort(p, N);
			break;
		case 5:
			PrintIndexSorted(p, IndexSort(p, N), N);
		case 0:
			break;
		default:
			cout << "Ви ввели помилкове значення! "
				"Слід ввести число - номер вибраного пункту меню" << endl;
		}
	} while (menuItem != 0);
	return 0;
}
void Create(Student* p, const int N)
{
	int spec;
	for (int i = 0; i < N; i++)
	{
		int n = 0;
		cout << "Студент № " << i + 1 << ":" << endl;
		cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
		cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок

		cout << " прізвище: "; getline(cin, p[i].prizv);
		cout << " курс: "; cin >> p[i].kurs;
		cout << " спеціальність ( 0 - Математика та економіка, 1 - Трудове навчання, 2 - Фізика та інформатика, 3 - Інформатика , 4 - Комп'ютерні науки): ";
		cin >> spec;
		p[i].spec = (Spec)spec;
		cout << " Бал з фізики: "; cin >> p[i].fizika;
		cout << " Бал з математики: "; cin >> p[i].matematika;
		cout << " Бал з інформатики: "; cin >> p[i].informatika;
		cout << endl;
	}
}
void Print(Student* p, const int N)
{
	cout << "============================================================================================="
		<< endl;
	cout << "________________________________________________________|              Бали                 |"
		<< endl;
	cout << "| № |     Прізвище     | Курс |       Cпеціальність     | Фізика | Математика | Інформатика |"
		<< endl;
	cout << "---------------------------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(1) << right << i + 1 << " ";
		cout << "| " << setw(17) << left << p[i].prizv
			<< "| " << setw(4) << right << p[i].kurs << " "
			<< "| " << setw(24) << left << specStr[p[i].spec] << "| " << setw(7) << right << p[i].fizika << "| " << setw(11) << right << p[i].matematika << "|" << setw(15) << right << setw(13) << right << p[i].informatika << "|" << endl;
			/*<< "| " << setw(11) << left << p[i].spec
			<< "| " << setw(4) << right << p[i].fizika << " "
			<< "| " << setw(4) << right << p[i].matematika << " "
			<< "| " << setw(4) << right << p[i].informatika << " |" << endl;*/
	}


	cout << "============================================================================================="
		<< endl;
	cout << endl;
}
void Sort(Student* p, const int N)
{
	Student tmp;
	for (int i0 = 0; i0 < N - 1; i0++) // метод "бульбашки"
		for (int i1 = 0; i1 < N - i0 - 1; i1++)
			if ((p[i1].kurs > p[i1 + 1].kurs)
				||
				(p[i1].kurs == p[i1 + 1].kurs &&
					p[i1].informatika < p[i1 + 1].informatika)
				||
				(p[i1].kurs == p[i1 + 1].kurs && p[i1].informatika == p[i1 + 1].informatika && p[i1].prizv < p[i1 + 1].prizv))
			{
				tmp = p[i1];
				p[i1] = p[i1 + 1];
				p[i1 + 1] = tmp;
			}
}
int BinSearch(Student* p, const int N, const string prizv, const unsigned kurs, const unsigned informatika)
{ // повертає індекс знайденого елемента або -1, якщо шуканий елемент відсутній
	int L = 0, R = N - 1, m;
	do {
		m = (L + R) / 2;
		if (p[m].prizv == prizv && p[m].kurs == kurs && p[m].informatika == informatika)
			return m;
		if ((p[m].kurs < kurs)
			||
			(p[m].kurs == kurs &&
				p[m].prizv < prizv)
			||
			(p[m].kurs == kurs &&
				p[m].prizv == prizv && p[m].informatika > informatika))
		{
			L = m + 1;
		}
		else
		{
			R = m - 1;
		}
	} while (L <= R);
	return -1;
}

int* IndexSort(Student* p, const int N)
{
	int* I = new int[N]; // створили індексний масив
	for (int i = 0; i < N; i++)
		I[i] = i; // заповнили його початковими даними
	int i, j, value; // починаємо сортувати масив індексів
	for (i = 1; i < N; i++)
	{
		value = I[i];
		for (j = i - 1;
			j >= 0 && ((p[I[j]].kurs < p[value].kurs)
				||
				(p[I[j]].kurs == p[value].kurs && //якщо помилка то тут
					p[I[j]].informatika > p[value].informatika)
				||
				(p[I[j]].prizv > p[value].prizv));
			j--)
		{
			I[j + 1] = I[j];
		}
		I[j + 1] = value;
	}
	return I;
}
void PrintIndexSorted(Student* p, int* I, const int N)
{
	cout << "============================================================================================="
		<< endl;
	cout << "________________________________________________________|              Бали                 |"
		<< endl;
	cout << "| № |     Прізвище     | Курс |       Cпеціальність     | Фізика | Математика | Інформатика | "
		<< endl;
	cout << "---------------------------------------------------------------------------------------------"
		<< endl;

	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(1) << right << i + 1 << " ";
		cout << "| " << setw(17) << left << p[I[i]].prizv
			<< "| " << setw(4) << right << p[I[i]].kurs << " "
			<< "| " << setw(24) << left << specStr[p[i].spec] << "| " << setw(7) << right << p[I[i]].fizika << "| " << setw(11) << right << p[I[i]].matematika << "|" << setw(15) << right << setw(13) << right << p[I[i]].informatika << "|" << endl;

	}
	cout << "---------------------------------------------------------------------------------------------" << endl;
}