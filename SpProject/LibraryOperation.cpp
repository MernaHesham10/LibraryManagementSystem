#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <time.h>
#include <cstring>
#include<conio.h>
#include "LibraryOperation.h"
using namespace std;

//Enter Book Data Function 
void LibraryOperation::EnterBookData()
{
	char bookTitle[60], bookAuthorName[60];
	int bookSerialNum;
	fstream fstream_Obj("library_books_data.dat", ios::out | ios::app);

	cout << "\nEnter Book ID: ";
	cin >> bookSerialNum;

	cout << "\nEnter Book Title: ";
	cin.ignore();
	cin.getline(bookTitle, 60);

	cout << "\nEnter Book Author Name: ";
	cin.getline(bookAuthorName, 60);


	fstream_Obj << " " << bookSerialNum << "      " << bookTitle << "      " << bookAuthorName << endl;
	fstream_Obj.close();

	cout << "\n*******Successfully Saved Data of Book In Database of Library******";
}

//Search Specific Book Function
void LibraryOperation::SearchSpecificBook()
	{
		fstream fstream_Obj1("library_books_data.dat", ios::in);
	label_search:
		cout << "\n\nSelect What Do You Want to Do: ";
		cout << "\n1. Display all Books Data";
		cout << "\n2. Search About Specific Book";
		cout << "\n3. Back To Main Menu";
		int chooseNumber;
		cin >> chooseNumber;
		switch (chooseNumber)
		{
			case 1:
				char DB_LineNumber[500], DB_Line1Number[500];

				if (fstream_Obj1.getline(DB_Line1Number, 500))
				{
					cout << "\n\n********************************************************************************";

					cout << "\n\n" << DB_Line1Number;

					while (fstream_Obj1.getline(DB_LineNumber, 500))
					{
						cout << "\n\n" << DB_LineNumber;
					}
					cout << "\n\n********************************************************************************\n\n";
				}
				else
					cout << "\nThere're No Books.";
				break;


			case 2:
				char DB_Line2Number[500], DB_Line5Number[500];
				cout << "\nEnter Book Title : ";
				char bookTitle[10];
				cin.ignore();
				cin.getline(bookTitle, 50);
				if (fstream_Obj1.getline(DB_Line2Number, 500))
				{
					fstream_Obj1.seekg(0, ios::beg);
					int CheckBookAvailability = 1;
					cout << "\n\n********************************************************************************=";
					while (fstream_Obj1.getline(DB_Line2Number, 500))
					{
						if (strstr(DB_Line2Number, bookTitle) != NULL)
						{
							cout << "\n\n" << DB_Line2Number;
							CheckBookAvailability = 0;
						}
					}
					if (CheckBookAvailability == 1)
					{
						cout << "\nThis Book isn't found";
					}
					cout << "\n\n********************************************************************************\n\n";
				}
				else
					cout << "\nThis Book isn't found";
				break;


			case 3:
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
				cout << "\n....Please Select From list....";
				goto label_search;
				break;
			}
			fstream_Obj1.close();
	}

//delete Book Function
void LibraryOperation::deleteBook()
	{
		char tempBookTitle[500];
		fstream fin("library_books_data.dat", ios::in);

		cout << "\nEnter The Full Book Title to delete its data : ";
		char bookTitleToSearch[500], bookTitleToSearch1[500];
		cin.ignore();
		cin.getline(bookTitleToSearch, 500);

		if (fin.getline(bookTitleToSearch1, 500))
		{
			fin.seekg(0, ios::beg);
			char q;
			cout << "\nAre you sure you want to delete this Data (Y/N)? ";
			cin >> q;
			if (q == 'Y' | q == 'y')
			{
				fstream fout("temporary_library.dat", ios::out | ios::app);
				fout.seekg(0, ios::beg);

				while (fin.getline(bookTitleToSearch, 500))
				{
					if (strstr(tempBookTitle, bookTitleToSearch) == NULL)
					{
						fout << tempBookTitle << endl;
					}
				}
				fin.close();
				fout.close();
				remove("library_books_data.dat");
				rename("temporary_library.dat", "library_books_data.dat");
				cout << "\n....Successfully Deleted....";
			}
		}
		else
			cout << "\nNo books are found to be deleted";
	}

//librarian Menu Function
void LibraryOperation::librarianMenu()
{
	label_admin:
		char EnteredPass = ' ';
		string passwordForAdmin = "";
		cout << "\nEnter Librarian Password: ";
		while (EnteredPass != 13)
		{
			EnteredPass = _getch();
			if (EnteredPass != 13)
			{
				passwordForAdmin += EnteredPass;
				cout << "*";
			}
		}


		if (passwordForAdmin == "admin")
		{
			cout << "\a";
			cout << "\n\nLibrarian MENU";
			cout << "\n1. Delete Book Data";
			cout << "\n2. Reset Program";
			cout << "\n3. Exit Program";

			int adminSelect;
			cin >> adminSelect;
			LibraryOperation bookop;
			switch (adminSelect)
			{
			case 1:
				bookop.deleteBook();
				break;

			case 2:
			{
				char resetProgram;
				cout << "\nAll Saved Data will be deleted and The Program will be restored to defaults. Continue anyway? (Y/N) : ";
				cin >> resetProgram;
				if (resetProgram == 'Y' | resetProgram == 'y')
				{
					cout << "\nResetting";
					for (int i = 0; i < 5; i++)
					{
						Sleep(500);
						cout << ".";
					}
					remove("library_books_data.dat");
					remove("library_issue_return.dat");
					remove("temp_id.dat");
					remove("issue_return.dat");
					remove("temp_return.dat");
					cout << "\n....Restored to defaults....";
				}
				break;
			}
			case 3:
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
				cout << "\n....please Select From Menu....";
				break;
			}
		}
		else
		{
			cout << "\n....Invalid Password that you enter....";
			goto label_admin;
		}
	}



