#include "LibraryReport.h"
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <time.h>
#include <cstring>
#include<conio.h>
using namespace std;

// Display Report Function
void LibraryReport::DisplayReport()
{
	char EnteredPassword = ' ';
	string libraryPassword = "";
	cout << "\nEnter library password : ";
	while (EnteredPassword != 13)
	{
		EnteredPassword = _getch();
		if (EnteredPassword != 13)
		{
			libraryPassword += EnteredPassword;
			cout << "*";
		}
	}
	if (libraryPassword == "library")
	{
		cout << "\a";
		LibraryReport libraryReport;
		cout << "\nSelect What Do You Want to Do";
		cout << "\n1. Issue Book";
		cout << "\n2. Return Book";
		cout << "\n3. Issue and Return status";
		cout << "\n4. Exit Program";

		int choiceNumber;
		cin >> choiceNumber;
		switch (choiceNumber)
		{
		case 1:
			libraryReport.BookReport();
			break;
		case 2:
			libraryReport.BookReport();
			break;
		case 3:
		{
			fstream libraryReport("library_issue_return.dat", ios::in);
			fstream libraryReport2("library_issue_return.dat", ios::in);
			char tempData[500], tempData1[500];
			if (libraryReport.getline(tempData1, 500))
			{
				cout << "\n\n****************************************************************************************\n\n";
				while (libraryReport2.getline(tempData, 500))
				{
					cout << tempData << endl;
				}
				cout << "\n****************************************************************************************";
				libraryReport.close();
				libraryReport2.close();
			}
			else
				cout << "\nNo Books have been issued or returned.";
			break;
		}
		case 4:
		{
			Sleep(500);
			cout << "\n\nExiting ";
			for (int i = 0; i <= 4; i++)
			{
				Sleep(500);
				cout << ".";
			}
			exit(0);
			break;
		}
		default:
			cout << "\n....Invalid Choice, please Select from Menu....";
			break;
		}
	}
	else
	{
		cout << "\n....Invalid Entered Password....";
	}

}

// Book Report Function
void LibraryReport::BookReport()
{
	ifstream File;
	string filepath = "temp_id.dat";
	File.open(filepath.c_str(), std::ifstream::out | std::ifstream::trunc);
	File.close();

	int Counter = 0, i, j, UserIdNumber, bookSerialNumber;
	char bookTitleCopy[50], StringCopy[50];

	fstream bi_in("library_issue_return.dat", ios::out | ios::in | ios::app);
	fstream temp_id("temp_id.dat", ios::out | ios::app);
	fstream bd_out("library_books_data.dat", ios::in);
	fstream ir("issue_return.dat", ios::in);
	fstream ir2("issue_return.dat", ios::out | ios::app);

	char tempCopy[500], stuName[50], book_SerialNumber[10];
	cout << "\nEnter Your Id Number: ";
	cin >> UserIdNumber;

	cout << "\nEnter the name of the User you Want o issue book to : ";
	cin.ignore();
	cin.getline(stuName, 50);

	cout << "\nEnter the ID of the book you want to issue to the user : ";
	cin >> bookSerialNumber;
	temp_id << " " << bookSerialNumber << "  " << endl;

	fstream tempIdNumber2("temp_id.dat", ios::in);
	tempIdNumber2.seekg(0, ios::beg);
	tempIdNumber2.getline(book_SerialNumber, 10);
	cout << book_SerialNumber << endl;
	tempIdNumber2.close();
	remove("temp_id.dat");

	Counter = strlen(book_SerialNumber);
	int checkFound = 0;
	while (bd_out.getline(tempCopy, 500))
	{

		char number[10];
		int Counter2 = 0;
		for (int NumOfOperation = 0; NumOfOperation < Counter; NumOfOperation++) {
			number[NumOfOperation] = tempCopy[NumOfOperation];
		}for (int NumOfOperation = Counter; NumOfOperation < 10; NumOfOperation++) {
			number[NumOfOperation] = '\0';
		}

		if (strstr(number, book_SerialNumber) != NULL)
		{
			checkFound = 1;
			for (i = Counter; tempCopy[i] != '\0'; i++)
				Counter2++;
			for (i = Counter + 4, j = 0; tempCopy[i] != '\0', j < Counter2; i++, j++)
				bookTitleCopy[j] = tempCopy[i];

		}
	}

	int flag = 0;
	char temp[500];
	while (ir.getline(temp, 500))
	{
		if (strstr(temp, bookTitleCopy) == NULL)
			continue;
		else
		{
			flag = 1;
			break;
		}
	}
	if (flag == 0 && checkFound == 1)
	{
		cin.ignore();
		bi_in << " " << UserIdNumber << "    " << stuName << "    " << bookTitleCopy << "    " << _strdate(date1) << endl;
		ir2 << bookTitleCopy << endl;
		bi_in.close();
		bd_out.close();
		ir.close();
		ir2.close();
		remove("temp_id.dat");
		remove("temp_id2.dat");
		cout << "\n....Book Issued....";
	}
	else
	{
		bi_in.close();
		bd_out.close();
		ir.close();
		ir2.close();
		remove("temp_id.dat");
		remove("temp_id2.dat");
		cout << "\nBook not available for issue.";
	}

}

// Display Book Report Function
void LibraryReport::DisplayBookReport()
{
	char tempString[500];
	char date2[10];
	cout << "\nRETURN MENU";
	cout << "\n1. Return by serial Number.";
	cout << "\n2. Return by Full Book Title";
	int choose_return;
	cin >> choose_return;
	switch (choose_return)
	{
		case 1:
		{
			ifstream File;
			string filepath = "temp_id.dat";
			File.open(filepath.c_str(), std::ifstream::out | std::ifstream::trunc);
			File.close();
			
			int issueSerialNumber;
			cout << "\nEnter issue Serial Number Return List : ";
			cin >> issueSerialNumber;
			
			fstream ser("temp.dat", ios::out | ios::app);
			ser.seekg(0, ios::beg);
			cin.ignore();
			ser << " " << issueSerialNumber << "    ";
			ser.close();

			char serialNumberCopy[50];
			fstream ser1("temp.dat", ios::in);
			ser1.seekg(0, ios::beg);
			ser1.getline(serialNumberCopy, 50);
			ser1.close();
			remove("temp.dat");
			int Counter = 0;
			Counter = strlen(serialNumberCopy);

			fstream out_book_return("library_issue_return.dat", ios::in);
			char bookReturnNumber[500], tempCopyNumber[500];
			while (out_book_return.getline(bookReturnNumber, 500))
			{
				char numberOfOperation[10];
				int Counter2 = 0;
				for (int op = 0; op < Counter; op++) {
					numberOfOperation[op] = bookReturnNumber[op];
				}for (int op = Counter; op < 10; op++) {
					numberOfOperation[op] = '\0';
				}

				if (strstr(numberOfOperation, serialNumberCopy) != NULL)
				{

					int i;
					for (i = Counter; bookReturnNumber[i] != '\0'; i++)
						Counter2++;
					int j;
					for (i = Counter + 4, j = 0; bookReturnNumber[i] != '\0', j < Counter2; i++, j++)
						tempCopyNumber[j] = bookReturnNumber[i];
				}
			}
			out_book_return.close();

			fstream check("issue_return.dat", ios::in);
			char strCopy[500];
			int CheckFound = 0;
			while (check.getline(strCopy, 500))
			{
				if (strstr(tempCopyNumber, strCopy) == NULL)
					continue;
				else
				{
					cout << "Book Returned Successfully\n";
					CheckFound = 1;
					break;
				}
			}
			check.close();
			if (CheckFound == 1)
			{
				fstream book_rn("library_issue_return.dat", ios::in);
				fstream bo_return("temp_ir.dat", ios::out | ios::app);
				while (book_rn.getline(bookReturnNumber, 500))
				{
					if (strstr(bookReturnNumber, serialNumberCopy) == NULL)
						bo_return << bookReturnNumber << endl;
					else
						bo_return << bookReturnNumber << "    " << _strdate(date2) << endl;
				}
				book_rn.close();
				bo_return.close();
				remove("library_issue_return.dat");
				rename("temp_ir.dat", "library_issue_return.dat");
			}
			else
			{
				cout << "\nNo such book have been issued.";
			}
			break;
		}

		case 2:
		{
			fstream br_out("library_issue_return.dat", ios::in);
			fstream temp_return("temp_return.dat", ios::out | ios::app);
			int flag = 0;
			char tempBn[50], temp[500], temp1[500];
			fstream ir("issue_return.dat", ios::in);
			fstream teir("issue_return.dat", ios::in);
			cout << "\nEnter Full Book Title : ";
			cin.ignore();
			cin.getline(tempBn, 50);
			ir.seekg(0, ios::beg);
			if (!teir.getline(temp1, 500))
			{

			}
			else
			{
				ir.seekg(0, ios::beg);
				while (ir.getline(temp1, 500))
				{
					if (strstr(temp1, tempBn) != NULL)
					{
						flag = 1;
						break;
					}
				}
			}
			teir.close();
			ir.close();
			if (flag == 0)
				cout << "\nNo Books Are Found To Be Returned";
			else
			{
				fstream ir2("issue_return_temp.dat", ios::out | ios::app);
				cin.ignore();
				while (br_out.getline(temp, 500))
				{
					if (strstr(temp, tempBn) != NULL)
					{
						temp_return << temp;
						temp_return << "    " << _strdate(date2) << endl;
					}
					else
						temp_return << temp << endl;
				}

				while (ir2.getline(temp1, 500))
				{
					if (strstr(temp1, tempBn) == NULL)
						ir2 << tempBn << endl;
				}
				br_out.close();
				remove("library_issue_return.dat");
				temp_return.close();
				rename("temp_return.dat", "library_issue_return.dat");
				ir2.close();
				remove("issue_return.dat");
				rename("issue_return_temp.dat", "issue_return.dat");
				cout << "\n....Book Returned....";
			}
			break;
		}

		default:
			cout << "\n....Invalid Choice....";
			break;
	}
}

