#include <iostream>
#include <time.h>
#include <iomanip>
#include <stdio.h>
#include <conio.h>

#include "Functions.hpp"

using namespace std;
//
//#define NAME_SIZE 15 //size student's name and surname 
//#define MARK_COUNT 5 //count of mark 
//
//struct Student
//{
//	char Name[NAME_SIZE];
//	char Surname[NAME_SIZE];
//	unsigned int Age;
//	unsigned int Mark[MARK_COUNT];
//	double Averadge;
//};

void InitStudent(int nSize, Student *pStud);
void ShowStudent(int nSize, Student *pStud);
void sortStudentByName(int nSize, Student *pStud);
void sortStudentBySurname(int nSize, Student *pStud);
void sortStudentByAge(int nSize, Student *pStud);
void sortStudentByMarks(int nSize, Student *pStud);
void newStudent(int nSize, Student *pAr);
int searchByName(int nSize, Student *pStud, Student *pBuff, int *nIndex, char *cBuff);
void deleteStudent(int Index, int *nIndex, Student *pStud2, int nSize2);
void Mem();

//TODO: add delete function - now doesn't work


int main()
{
	srand((unsigned int)time(0));

	int nSize;
	int nSize2;
	int choise = 5;
	while (choise != 27)
	{
		cout << "Press '1' to create new grup with students" << endl;
		cout << "Press '2' to show list of students" << endl;
		cout << "Press '3' to sort list of students" << endl; 
		cout << "Press '4' to editing list of students\n" << endl; //add or delete student from list

		switch (_getch())
	    {
		case 49: // 1 - create new grup
		{
			FILE * f;
			errno_t err = fopen_s(&f, "Students.txt", "wb");
			if (f == NULL)
			{
				cout << "Error!! Can't open file!" << endl;
				break;
			}
			system("cls");
			cout << "Enter count of students:";
			cin >> nSize;
			cout << endl;

			Student *pStud2 = new Student[nSize];
			InitStudent(nSize, pStud2);

			ShowStudent(nSize, pStud2);

			//writing to file
			if (fwrite(pStud2, sizeof(Student), nSize, f) < 0)
				cout << "Error with writing ro file" << endl;
			
			fclose(f);
			delete[] pStud2;
			
			break;
		}
		case 50://2 - show student
		{
			FILE * f;
			errno_t err = fopen_s(&f, "Students.txt", "rb");
			if (f == NULL || f < 0)
			{
				cout << "Error!!Can't open file!" << endl;
				break;
			}

			fseek(f, 0, SEEK_END);
			int nBytes = ftell(f);
			nSize2 = nBytes / sizeof(Student);
			
			fseek(f, 0, SEEK_SET);
			Student *pStud2 = new Student[nSize2];
			if (fread(pStud2, sizeof(Student), nSize2, f) < 0)
				cout << "Error!! Cant read file!" << endl;;

			ShowStudent(nSize2, pStud2);

			delete[]pStud2;
			fclose(f);

			break;
		}
		case 51: //3 - sort  
		{
			FILE * f;
			errno_t err = fopen_s(&f, "Students.txt", "r+b");
			if (f == NULL || f < 0)
			{
				cout << "Error!!Can't open file!" << endl;
				break;
			}

			fseek(f, 0, SEEK_END);
			int nBytes = ftell(f);
			int nSize2 = nBytes / sizeof(Student);

			fseek(f, 0, SEEK_SET);
			Student *pStud2 = new Student[nSize2];
			if (fread(pStud2, sizeof(Student), nSize2, f) < 0)
				cout << "Error!! Cant read file!" << endl;

			cout << "Select an option to sort: " << endl;
			cout << "N - sort by student's name " << endl;
			cout << "S - sort by student's surname " << endl;
			cout << "A - sort by student's age " << endl;
			cout << "M - sort by student's average makr " << endl;
			cout << "Esc to exit in priviosly menu " << endl;
			switch (_getch())
			{
			case 110://n - sort by name
			{
				sortStudentByName(nSize2, pStud2);
				ShowStudent(nSize2, pStud2);
				break;
			}
			case 78: //N - sort by name
			{
				sortStudentByName(nSize2, pStud2);
				ShowStudent(nSize2, pStud2);
				break;
			}
			case 115://S - sort by surname
			{
				sortStudentBySurname(nSize2, pStud2);
				ShowStudent(nSize2, pStud2);
				break;
			}
			case 83://s - sort by surname
			{
				sortStudentBySurname(nSize2, pStud2);
				ShowStudent(nSize2, pStud2);
				break;
			}
			case 65: //A - sort by age
			{
				sortStudentByAge(nSize, pStud2);
				ShowStudent(nSize2, pStud2);
				break;
			}
			case 97: //a - sort by age
			{
				sortStudentByAge(nSize, pStud2);
				ShowStudent(nSize2, pStud2);
				break;
			}
			case 77: //M - sort by average mark
			{
				sortStudentByMarks(nSize, pStud2);
				ShowStudent(nSize2, pStud2);
				break;
			}
			case 109: //m - sort by average mark
			{
				sortStudentByMarks(nSize, pStud2);
				ShowStudent(nSize2, pStud2);
				break;
			}
			default:
				break;
			}
		
			delete[] pStud2;
			fclose(f);
			break;
		}
		case 52: //4 - editing list of students
		{
			cout << "Press '+' to addition new students or '-' to delete student" << endl;
			switch (_getch())
			{
			case 43: //+ addition new students
			{
				FILE *f;
				errno_t eerr = fopen_s(&f, "Students.txt", "a+b");
				if (f == NULL || f < 0)
				{
					cout << "Error!!Can't open file!" << endl;
					break;
				}

				//opening the file and create new array with students
				fseek(f, 0, SEEK_END);
				int nBytes = ftell(f);
				int nSize2 = nBytes / sizeof(Student); // check current file size and +1 student in total

				fseek(f, 0, SEEK_END);
				Student *pStud2 = new Student[nSize2+1];
				fseek(f, 0, SEEK_SET);
				if (fread(pStud2, sizeof(Student), nSize2, f) < 0)
					cout << "Error!! Cant read file!" << endl;

				fseek(f, 0, SEEK_END);
				newStudent(nSize2+1, pStud2); //addition new student
				ShowStudent(nSize2+1, pStud2); //show array with new student

				fclose(f);
				
				//writing new array in the file 
				eerr = fopen_s(&f, "Students.txt", "wb");
				if (f == NULL || f < 0)
				{
					cout << "Error!!Can't open file!" << endl;
					break;
				}

				fseek(f, 0, SEEK_SET);
				if (fwrite(pStud2, sizeof(Student), nSize2+1, f) < 0)
					cout << "Error!! Cant read file!" << endl;

				fclose(f);
				delete[] pStud2;
			}
			case 45: // - delete student // TODO!!!!
			{
			
				FILE *f;
				errno_t eerr = fopen_s(&f, "Students.txt", "a+b");
				if (f == NULL || f < 0)
				{
					cout << "Error!!Can't open file!" << endl;
					break;
				}

				//opening the file and create new array with students
				fseek(f, 0, SEEK_END);
				int nBytes = ftell(f);
				int nSize2 = nBytes / sizeof(Student); 
				if (nSize2 = 0)
				{
					cout << "There aren't any students in your file. Create new students  and try again" << endl;
					break;
				}

				Student *pStud2 = new Student[nSize2 -1];

				//create new array for founded objects
				Student *pStud3 = new Student[nSize2 - 1];

				fseek(f, 0, SEEK_SET);
				if (fread(pStud2, sizeof(Student), nSize2-1, f) < 0)
					cout << "Error!! Can't read file!" << endl;
				
				system("cls");
				cout << "Choise option to delete student" << endl;
				cout << "Press 'N' to delete by name" << endl;
				cout << "Press 'S' to delete by surname" << endl;
				cout << "Press 'A' to delete by age" << endl;
				cout << "Press 'M' to delete by makr" << endl;

				switch (_getch())
				{
				case 110://n - search by name
				{
					char *cBuff = new char[300];
					cout << "Enter name to search: " << endl;
					cin.sync();
					cin.getline(cBuff, NAME_SIZE);

					int *pIndex = new int[nSize2];

					int nSizeSearch = searchByName(nSize2, pStud2, pStud3, pIndex, cBuff);//need to check functions - something not good
					cout << "There are students with name " << cBuff << ':'<< endl;
					ShowStudent(nSizeSearch, pStud3);
					int Index;
					cout << "Enter number student, wich do you want to delete:" << endl;
					while (!(cin >> Index) || cin.get() != '\n' || Index >= nSizeSearch  || Index <=0)   //
					{
						cin.clear(); 
						cin.ignore(); 
						cout << "Invalid Input!" << endl;
						cout << "enter the number of student: ";
					};

					Index-=1;
					deleteStudent(Index, pIndex, pStud2, nSize2);
					ShowStudent(nSize2, pStud2);

					//тут допиши запись в файл итогового списка после удаления
					delete[] cBuff;
					delete[] pIndex;
					delete[] pStud3;
					delete[] pStud2;
					break;
				}
				case 78: //N - search by name
				{
					sortStudentByName(nSize2, pStud2);
					ShowStudent(nSize2, pStud2);
					break;
				}
				case 115://S - search by surname
				{
					sortStudentBySurname(nSize2, pStud2);
					ShowStudent(nSize2, pStud2);
					break;
				}
				case 83://s - search by surname
				{
					sortStudentBySurname(nSize2, pStud2);
					ShowStudent(nSize2, pStud2);
					break;
				}
				case 65: //A - search by age
				{
					sortStudentByAge(nSize, pStud2);
					ShowStudent(nSize2, pStud2);
					break;
				}
				case 97: //a - search by age
				{
					sortStudentByAge(nSize, pStud2);
					ShowStudent(nSize2, pStud2);
					break;
				}
				case 77: //M - search by average mark
				{
					sortStudentByMarks(nSize, pStud2);
					ShowStudent(nSize2, pStud2);
					break;
				}
				case 109: //m - search by average mark
				{
					sortStudentByMarks(nSize, pStud2);
					ShowStudent(nSize2, pStud2);
					break;
				}
				default:
					break;
				}
			}
			default:
				break;
			}
		}
		
		default:
			break;
		}

		if (choise == 27) break;
		cout << "Press enter to continue or esc to exit " << endl;
		while (choise !=27)
		{
			choise = _getch();
			if (choise == 13) break;
		}

		
	}

	Mem();
	system("pause");
	return 0;
}

