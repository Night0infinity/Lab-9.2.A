#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <Windows.h> // ������������ ����������� ��������
using namespace std;

enum Spec { ME, TN, FI, In, KN };
string specStr[] = { "���������� �� ��������", "������� ��������", "Գ���� �� �����������", "�����������" ,"����'������ �����" };

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
{ // ������������ ����������� ��������:
	SetConsoleCP(1251); // ������������ ������� win-cp1251 � ���� �����
	SetConsoleOutputCP(1251); // ������������ ������� win-cp1251 � ���� ������
	int N;
	cout << "������ N: "; cin >> N;

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
		cout << "������� ��:" << endl << endl;
		cout << " [1] - �������� ����� � ���������" << endl;
		cout << " [2] - ���� ����� �� �����" << endl;
		cout << " [3] - ������� �����" << endl;
		cout << " [4] - ������� ������������� �����" << endl;
		cout << " [5] - �������� �������������" << endl;
		cout << " [0] - ����� �� ���������� ������ ��������" << endl << endl;
		cout << "������ ��������: "; cin >> menuItem;
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
			cout << "������ ����� ������:" << endl;
			cout << "���� : ";
			cin >> ikurs;
			kurs = ikurs;
			cout << "������ � �����������: ";
			cin >> iinformatika;
			informatika = iinformatika;

			cin.get(); // ������� ����� ��������� � �� ����������� �������
			cin.sync(); // "����� �����", �� �� ����� ������ ��������� ������� �����
			cout << " �������: "; getline(cin, prizv);
			cout << endl;
			if ((found = BinSearch(p, N, prizv, kurs, informatika)) != -1)
				cout << "�������� ���������� � ������� " << found + 1 << endl;
			else
				cout << "�������� ���������� �� ��������" << endl;
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
			cout << "�� ����� ��������� ��������! "
				"��� ������ ����� - ����� ��������� ������ ����" << endl;
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
		cout << "������� � " << i + 1 << ":" << endl;
		cin.get(); // ������� ����� ��������� � �� ����������� �������
		cin.sync(); // "����� �����", �� �� ����� ������ ��������� ������� �����

		cout << " �������: "; getline(cin, p[i].prizv);
		cout << " ����: "; cin >> p[i].kurs;
		cout << " ������������� ( 0 - ���������� �� ��������, 1 - ������� ��������, 2 - Գ���� �� �����������, 3 - ����������� , 4 - ����'������ �����): ";
		cin >> spec;
		p[i].spec = (Spec)spec;
		cout << " ��� � ������: "; cin >> p[i].fizika;
		cout << " ��� � ����������: "; cin >> p[i].matematika;
		cout << " ��� � �����������: "; cin >> p[i].informatika;
		cout << endl;
	}
}
void Print(Student* p, const int N)
{
	cout << "============================================================================================="
		<< endl;
	cout << "________________________________________________________|              ����                 |"
		<< endl;
	cout << "| � |     �������     | ���� |       C������������     | Գ���� | ���������� | ����������� |"
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
	for (int i0 = 0; i0 < N - 1; i0++) // ����� "���������"
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
{ // ������� ������ ���������� �������� ��� -1, ���� ������� ������� ��������
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
	int* I = new int[N]; // �������� ��������� �����
	for (int i = 0; i < N; i++)
		I[i] = i; // ��������� ���� ����������� ������
	int i, j, value; // �������� ��������� ����� �������
	for (i = 1; i < N; i++)
	{
		value = I[i];
		for (j = i - 1;
			j >= 0 && ((p[I[j]].kurs < p[value].kurs)
				||
				(p[I[j]].kurs == p[value].kurs && //���� ������� �� ���
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
	cout << "________________________________________________________|              ����                 |"
		<< endl;
	cout << "| � |     �������     | ���� |       C������������     | Գ���� | ���������� | ����������� | "
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