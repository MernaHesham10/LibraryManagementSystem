#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <time.h>
#include <cstring>
#include<conio.h>
#include "LibraryOperation.h"
#include "LibraryReport.h"
using namespace std;

//about Function
void about()
{
	fstream about_out("library_about.dat", ios::in);
	char aboutString[500];
	cout << "\n\n-----------------------------------------------------------------------------------------------\n\n";
	about_out.seekg(0, ios::beg);
	while (about_out.getline(aboutString, 500))
	{
		cout << aboutString << endl;
	}
	cout << "\n-----------------------------------------------------------------------------------------------\n";
	about_out.close();
}

int main()
{
	system("COLOR 3F");
	char date[10];
	cout << "\n                              ***** Library Management System *****                                 " << _strdate(date);
	LibraryOperation libraryOperation;
	LibraryReport libraryReport;
	string ValidPassword = "";
label_main:
	char EnteredPassword = ' ';
	cout << "\nEnter Program Password : ";
	while (EnteredPassword != 13)
	{
		EnteredPassword = _getch();
		if (EnteredPassword != 13)
		{
			ValidPassword += EnteredPassword;
			cout << "*";
		}
	}
	if (ValidPassword == "project")
	{
		cout << "\a";
		int EnteredChoice;
		while (1)
		{
			cout << "\n\nMAIN MENU";
			cout << "\n1. Enter Book Data";
			cout << "\n2. Search Specific Book Data";
			cout << "\n3. Librarian Menu";
			cout << "\n4. Reports";
			cout << "\n5. About";
			cout << "\n6. Exit Program";

			cin >> EnteredChoice;

			switch (EnteredChoice)
			{
				case 1:
					libraryOperation.EnterBookData();
					break;
				case 2:
					libraryOperation.SearchSpecificBook();
					break;
				case 3:
					libraryOperation.librarianMenu();
					break;
				case 4:
					libraryReport.DisplayReport();
					break;
				case 5:
					about();
					break;
				case 6:
					Sleep(500);
					cout << "\n\nExiting ";
					for (int i = 0; i <= 4; i++)
					{
						Sleep(500);
						cout << ".";
					}
					exit(0);
					break;
				default:
					cout << "\n....Invalid Choice, Please select from Menu....";
			}
		}
	}
	else
	{
		cout << "\n....Invalid Entered Password....";
		goto label_main;
	}
}