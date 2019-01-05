#include <iostream>
#include <time.h>
#include <iomanip>
#include <stdio.h>
#include <conio.h>

#define NAME_SIZE 15 //size student's name and surname 
#define MARK_COUNT 5 //count of mark 

using namespace std;

struct Student
{
	char Name[NAME_SIZE];
	char Surname[NAME_SIZE];
	unsigned int Age;
	unsigned int Mark[MARK_COUNT];
	double Averadge;
};


void InitStudent(int nSize, Student *pStud)
{

	const char *sNames[] = { "Bill", "Jhon", "Julia", "Pavel", "Alisa", "Vladimir", "Sergey" };
	const int nNameSize = sizeof(sNames) / sizeof(char *);
	int randNameSize[nNameSize];
	for (int i = 0; i <nNameSize; ++i)
		randNameSize[i] = strlen(sNames[i]) + 1;

	const char *sSurNames[] = { "Clinton", "Linkoln", "Cherchel", "Ivanov", "Petrov", "Sidorov", "Tolkien" };
	const int nSurNameSize = sizeof(sSurNames) / sizeof(char *);
	int randSurNameSize[nSurNameSize];
	for (int i = 0; i <nSurNameSize; ++i)
		randSurNameSize[i] = strlen(sSurNames[i]) + 1;
	int numbName;
	double sumMarks = 0;

	for (int i = 0; i < nSize; ++i)
	{
		//create random name
		numbName = rand() % nNameSize;
		//randNameSize = strlen(sNames[numbName])+1;
		memcpy(pStud[i].Name, sNames[numbName], randNameSize[numbName]);

		//create random surname
		numbName = rand() % nSurNameSize;
		//randNameSize = strlen(sSurNames[numbName])+1;
		memcpy(pStud[i].Surname, sSurNames[numbName], randSurNameSize[numbName]);

		//create random age
		pStud[i].Age = (rand() % 10) + 16;

		//create random marks
		for (int j = 0; j < MARK_COUNT; ++j)
		{
			pStud[i].Mark[j] = rand() % 5 + 1;
			sumMarks += pStud[i].Mark[j];
		}

		//create average marks
		pStud[i].Averadge = sumMarks / MARK_COUNT;
		sumMarks = 0;

	}
}

void ShowStudent(int nSize, Student *pStud)
{
	cout << setw(3) << "#";
	cout << setw(NAME_SIZE + 1) << "Name";
	cout << setw(NAME_SIZE + 1) << "Sourname";
	cout << setw(7) << "Age";
	cout << setw(MARK_COUNT) << "Makr";
	cout << setw(20) << "Averadge  makr" << endl;

	for (int i = 0; i < nSize; ++i)
	{
		cout << setw(3) << i + 1;
		cout << setw(NAME_SIZE + 1) << pStud[i].Name;
		//cout.setf(ios::left);
		cout << setw(NAME_SIZE + 1) << pStud[i].Surname;
		cout << setw(7) << pStud[i].Age;
		//cout.setf(ios::right);
		for (int j = 0; j < MARK_COUNT; ++j)
			cout << setw(2) << pStud[i].Mark[j];

		//cout.setf(ios::right);
		cout << setw(5) << pStud[i].Averadge << endl;
	}
}

void sortStudentByName(int nSize, Student *pAr)
{
	char *nMin = new char[300];
	int iMinInd;
	Student pTemp;
	for (int i = 0; i < nSize; ++i)
	{
		memcpy(nMin, pAr[i].Name, sizeof(Student));
		iMinInd = i;
		for (int j = i + 1; j < nSize; ++j)
			if (_stricmp(pAr[j].Name, nMin) < 0)
			{
				memcpy(nMin, pAr[j].Name, sizeof(Student));
				iMinInd = j;
			}

		pTemp = pAr[i];
		pAr[i] = pAr[iMinInd];
		pAr[iMinInd] = pTemp;
	}
	delete[] nMin;
}

void sortStudentBySurname(int nSize, Student *pAr)
{
	char *nMin = new char[300];
	int iMinInd;
	Student pTemp;
	for (int i = 0; i < nSize; ++i)
	{
		memcpy(nMin, pAr[i].Surname, sizeof(Student));
		iMinInd = i;
		for (int j = i + 1; j < nSize; ++j)
			if (_stricmp(pAr[j].Surname, nMin) < 0)
			{
				memcpy(nMin, pAr[j].Surname, sizeof(Student));

				iMinInd = j;
			}

		pTemp = pAr[i];
		pAr[i] = pAr[iMinInd];
		pAr[iMinInd] = pTemp;
	}
	delete[] nMin;
}

void sortStudentByAge(int nSize, Student *pAr)
{
	int iMinInd;
	double nMin;
	Student pTemp;
	for (int i = 0; i < nSize; ++i)
	{
		nMin = pAr[i].Age;
		iMinInd = i;
		for (int j = i + 1; j < nSize; ++j)
			if (pAr[j].Age<nMin)
			{
				nMin = pAr[j].Age;
				iMinInd = j;
			}

		pTemp = pAr[i];
		pAr[i] = pAr[iMinInd];
		pAr[iMinInd] = pTemp;
	}

}

void sortStudentByMarks(int nSize, Student *pAr)
{
	double nMin;
	int iMinInd;
	Student pTemp;
	for (int i = 0; i < nSize; ++i)
	{
		nMin = pAr[i].Averadge;
		iMinInd = i;
		for (int j = i + 1; j < nSize; ++j)
			if (pAr[j].Averadge<nMin)
			{
				nMin = pAr[j].Averadge;
				iMinInd = j;
			}

		pTemp = pAr[i];
		pAr[i] = pAr[iMinInd];
		pAr[iMinInd] = pTemp;
	}
}

void newStudent(int nSize, Student *pAr)
{
	system("cls");
	cout << "Create new student" << endl;
	cin.getline(pAr[nSize - 1].Name, NAME_SIZE + 1);


	cin.sync();//clear threads from enter

			   //create new name
	cout << "Enter name of new student (max - 15 symbols)" << endl;
	cin.getline(pAr[nSize - 1].Name, NAME_SIZE + 1);

	cout << "Enter surname of new student (max - 15 symbols)" << endl;
	cin.getline(pAr[nSize - 1].Surname, NAME_SIZE + 1);

	unsigned int ageBuff;
	cout << "Enter age of new student (the integer number from 16 to 60)" << endl;
	while (!(cin >> ageBuff) || cin.get() != '\n' || ageBuff <= 16 || ageBuff >= 60)   //
	{
		cin.clear();
		cin.ignore();
		cout << "Invalid Input!" << endl;
		cout << "enter the integer number from 16 to 60: ";
	};

	pAr[nSize - 1].Age = ageBuff;

	int markBuff;
	double Sum = 0;
	for (int i = 0; i < MARK_COUNT; ++i)
	{
		cout << "Enter " << i + 1 << " makr of new student (the integer number from 1 to 5)" << endl;
		while (!(cin >> markBuff) || cin.get() != '\n' || markBuff < 1 || markBuff > 5)   //
		{
			cin.clear();
			cin.ignore();
			cout << "Invalid Input!" << endl;
			cout << "enter the integer number from 1 to 5: ";
		}
		pAr[nSize - 1].Mark[i] = markBuff;
		Sum += pAr[nSize - 1].Mark[i];
	}

	pAr[nSize - 1].Averadge = Sum / MARK_COUNT;

}

//void deleteStudent(int nSize, Student pStud2)
//{
//	system("cls");
//	//тут будет функция сравнения введенных данных с данными в структуре
//	cout << "Create new student" << endl;
//	cin.getline(pAr[nSize - 1].Name, NAME_SIZE + 1);
//
//
//	cin.sync();//очищаем поток от прошлого энтера
//
//			   //create new name
//	cout << "Enter name of new student (max - 15 symbols)" << endl;
//	cin.getline(pAr[nSize - 1].Name, NAME_SIZE + 1);
//
//	cout << "Enter surname of new student (max - 15 symbols)" << endl;
//	cin.getline(pAr[nSize - 1].Surname, NAME_SIZE + 1);
//
//	unsigned int ageBuff;
//	cout << "Enter age of new student (the integer number from 16 to 60)" << endl;
//	while (!(cin >> ageBuff) || cin.get() != '\n' || ageBuff <= 16 || ageBuff >= 60)   //
//	{
//		cin.clear(); // сбрасывает все биты потока (если предыдущий ввод завершился с ошибкой)
//		cin.ignore(); // пропускает во входном потоке всё до следующего \n (то есть, до конца строки)
//		cout << "Invalid Input!" << endl;
//		cout << "enter the integer number from 16 to 60: ";
//	};
//
//	pAr[nSize - 1].Age = ageBuff;
//
//	int markBuff;
//	double Sum = 0;
//	for (int i = 0; i < MARK_COUNT; ++i)
//	{
//		cout << "Enter " << i + 1 << " makr of new student (the integer number from 1 to 5)" << endl;
//		while (!(cin >> markBuff) || cin.get() != '\n' || markBuff < 1 || markBuff > 5)   //
//		{
//			cin.clear(); // сбрасывает все биты потока (если предыдущий ввод завершился с ошибкой)
//			cin.ignore(); // пропускает во входном потоке всё до следующего \n (то есть, до конца строки)
//			cout << "Invalid Input!" << endl;
//			cout << "enter the integer number from 1 to 5: ";
//		}
//		pAr[nSize - 1].Mark[i] = markBuff;
//		Sum += pAr[nSize - 1].Mark[i];
//	}
//
//	pAr[nSize - 1].Averadge = Sum / MARK_COUNT;
//}

int searchByName(int nSize, Student *pStud, Student *pBuff, int *nIndex, char *cBuff)
{

	int nSize_search = 0;

	for (int i = 0; i < nSize; ++i)
	{
		if (_stricmp(pStud[i].Name, cBuff) == 0)
		{
			memcpy(pBuff[nSize_search].Name, pStud[i].Name, sizeof(Student));
			memcpy(pBuff[nSize_search].Surname, pStud[i].Surname, sizeof(Student));
			pBuff[nSize_search].Age = pStud[i].Age;

			for (int j = 0; j < MARK_COUNT; ++j)
				pBuff[nSize_search].Mark[j] = pStud[i].Mark[j];
			pBuff[nSize_search].Averadge = pStud[i].Averadge;

			nIndex[nSize_search] = i;

			nSize_search += 1;
		}
	}

	return nSize_search;
}

void deleteStudent(int Index, int *nIndex, Student *pStud2, int nSize2)
{
	Index = nIndex[Index];
	for (int i = Index;i < nSize2; ++i)
	{
		memcpy(pStud2[i].Name, pStud2[i + 1].Name, sizeof(Student));
		memcpy(pStud2[i].Surname, pStud2[i + 1].Name, sizeof(Student));
		pStud2[i].Age = pStud2[i + 1].Age;
		for (int j = 0;j < MARK_COUNT;++j)
			pStud2[i].Mark[j] = pStud2[i + 1].Mark[j];
		pStud2[i].Averadge = pStud2[i + 1].Averadge;
	}
	nSize2--;
}

void Mem()
{
	if (_CrtDumpMemoryLeaks())
		cout << "Warning! Memory leaks!!" << endl;
	else
		cout << "Memory ok :-)" << endl;
}