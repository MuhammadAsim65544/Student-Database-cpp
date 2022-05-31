 //Name Muhammad Asim 
//RegNo 3956-FBAS-BSCS-F18(B)
//sir Nadeem
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
//pre processor director
#define SIZE 70
#define RMAX 3
#define TM 100
#define SUB 3
ofstream outfile;
fstream infile;
//structure defination
struct student
{
	int reg;
	string name;
	int sub[SUB];
	int tm;
	float perc;
	char grd;
};
//function defination
void appendfile();
void readData(student ss[],int& nn);
void savedata(student ss[],int nn);
void checkreg1(student sss[], int nnn, int ii);
void checkreg2(student sss[], int nnn, int ii);
void checkm(student ss[], int nn, int i, int j);
void myinput(student ss[], int& nn, int& checkk);
void process(student ss[], int& nn);
void display(student ss[], int nn);
void dlete(student ss[], int& nn);
void append(student ss[], int& nn);
int search(student ss[], int nn, int rgg);
void sorting(student ss[], int nn);
void update(student ss[], int nn);
void checkst(int& nnn);
void proc();
int main()
{

	proc();


	return 0;
}
void proc()
{

	student s[RMAX];
	int n, ch, p, found;
	bool con = true;
	int check = 0;

	do
	{
		cout << "\n              ....Main Menu...." << endl;
		cout<<"      0. readData\n";
		cout << "      1. Create database" << endl;
		cout << "      2. Append new results" << endl;
		cout << "      3. Prepare results" << endl;;
		cout << "      4. SEARCH" << endl;
		cout << "      5. Sorting" << endl;
		cout << "      6. Updation" << endl;
		cout << "      7. Delation" << endl;
		cout << "      8. Display result" << endl;
		cout<<"      9. Savedata\n";
		cout << "      10. Exit" << endl;
		cout << "      11. Append in file" << endl;
		cout << "Please enter the choice: ";
		cin >> ch;
		switch (ch)
		{
		case 0:
			infile.open("database.dat",ios::in);
			readData(s,n);
			infile.close();
			break;
		case 1:
			myinput(s, n, check);
			break;
		case 2:
			if (check > 0)
				append(s, n);
			else
			{
				cout << "Please create database first.";
			}	
			break;
		case 3:
			if (check > 0)
			{
				process(s, n);
			}
			else
				cout << "Please create database first.";
			break;
		case 4:
			if (check > 0)
			{
				int pos;
				int rg;
				cout <<"Please create database first.";
				cin >> rg;
				pos = search(s, n, rg);

				if (pos == -1)
					cout << "Result Not Found, Sorry";
				else
				{
					cout << "\nResult Found\nHere it is:\n";
					cout << "Name\t";
					/*fixnamespaces(ss, pos);*/
					cout << "Regg" << "\t" << "Subj1" << "\t" << "Subj2" << "\t" << "Subj3" << "\t" << "TMO" << "\t" << "Perc" << "\t" << "Grade" << "\n";
					cout << s[pos].name << "\t";
					cout << s[pos].reg << "\t";
					for (int j = 0; j < SUB; j++)
					{
						cout << s[pos].sub[j] << "\t";
					}
					cout << s[pos].tm << "\t";
					cout << s[pos].perc << "%" << "\t";
					cout << s[pos].grd << "\t\n";
				}

			}
			else
				cout << "Please create database first.";
			break;
		case 5:
			if (check > 0)
				sorting(s, n);
			else
				cout << "Please create database first.";
			break;
		case 6:
			if (check > 0)
				update(s, n);

			else
				cout << "Please create database first.";
			break;
		case 7:
			if (check > 0)
			{
				dlete(s, n);
			}
			else
				cout << "Please create database first.";
			break;
		case 8:
				display(s, n);
			break;
		case 9:
			outfile.open("database.dat", ios::app|ios::in);
			savedata(s,n);
			outfile.close();
			break;
		case 10:
			con = false;
			break;
		case 11:
			appendfile();
			break;
		}
	} while (con);
}
void appendfile()
{
	int record_no,n;
	cout<<"Enter record n0#: ";
	cin>>record_no;
	fstream file;
	file.open("database.txt", ios::in|ios::app);
	file.seekg(0,ios::beg);
	file.read(reinterpret_cast<char*>(&n),sizeof(int));
	if(!(record_no>=1 && record_no<=n))
	{
		cout<<"Record not in file\n";
		exit(-1);
		
	}
	student obj;
	int jump=(record_no-1)*sizeof(student);
	file.seekg(jump,ios::cur);
	file.read(reinterpret_cast<char*>(&obj),sizeof(student));
	//obj.setter();
	file.seekp(0,ios::beg);
	int jumpp=jump+sizeof(int);
	file.seekp(jumpp,ios::beg);
	file.write(reinterpret_cast<char*>(&obj),sizeof(student));
	file.close();	
}
void savedata(student ss[],int nn)
{
	ofstream outfile;
	outfile.open("database.dat", ios::app|ios::binary );
	if(!outfile)
	{
		cout<<"Errors";
		exit(-1);
	}
	outfile.write(reinterpret_cast<char*>(&nn),nn*sizeof(int));
	outfile.write(reinterpret_cast<char*>(ss),nn*sizeof(student));
	//cout<<"SIZE OF FILE: "<<sizeof(file);
	cout<<"DATA HAS BEEN WROTE IN THE FILE\n";
}

void readData(student ss[],int& nn)
{
	fstream infile;
	infile.open("database.dat",ios::in|ios::binary);
	if(!infile)
	{
		cout<<"Errors";
		exit(-1);
	}
	infile.read(reinterpret_cast<char*>(&nn),sizeof(int));
	infile.read(reinterpret_cast<char*>(ss),nn*sizeof(student));
	cout<<"SIZE IS "<<nn<<endl;
	infile.close();
	cout<<"DATA HAS BEEN READ IN THE FILE\n";
	
}
void myinput(student ss[], int& nn, int& checkk)
{
	cout << "Please enter the number of students:  ";
	cin >> nn;
	checkst(nn);

	for (int i = 0; i < nn; i++)
	{
		ss[i].tm = 0;
		cout << "Enter the Reg.No of student " << i + 1 << ": ";
		cin >> ss[i].reg;
		
		checkreg1(ss, nn, i);
		if(i != 0)
			checkreg2(ss, nn, i);
	

		cin.ignore(10, '\n');
		cout << "Enter the name of student " << i + 1 << ": ";
		getline(cin, ss[i].name);
		for (int j = 0; j < SUB; j++)
		{

			cout << "Enter marks of subject: " << j + 1 << ": ";
			cin >> ss[i].sub[j];
			checkm(ss, nn, i, j);
			ss[i].tm += ss[i].sub[j];
		}
	}
	checkk++;
	process(ss, nn);
}
void process(student ss[], int& nn)
{
	for (int i = 0; i < nn; i++)
	{
		ss[i].perc = ss[i].tm * 100 / (SUB * 100);

		switch (static_cast<int>(ss[i].perc) / 10)
		{
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			ss[i].grd = 'D';
			break;
		case 7:
			ss[i].grd = 'C';
			break;
		case 8:
			ss[i].grd = 'B';
			break;
		case 9:
		case 10:
			ss[i].grd = 'A';
			break;
		}
	}
}
void display(student ss[], int nn)
{
	char chh;
	cout << " a. Full result" << endl;
		cout << " b. Particular result" << endl;
		cout << " c. Back" << endl;
	cout << "Enter your choice: ";
	cin >> chh;
	int i, found, pos;
	switch (chh)
	{
	case 'a':
		cout << "Name\t";
		cout << "Regg" << "\t" << "Subj1" << "\t" << "Subj2" << "\t" << "Subj3" << "\t" << "TMO" << "\t" << "Perc" << "\t" << "Grade" << "\n";
		for (int i = 0; i < nn; i++)
		{
			cout << ss[i].name << "\t";

			cout << ss[i].reg << "\t";

			for (int j = 0; j < SUB; j++)
				cout << ss[i].sub[j] << "\t";

			cout << ss[i].tm << "\t";
			cout << ss[i].perc << "%" << "\t";
			cout << ss[i].grd << "\t\n";
		}


		break;

	case 'b':

		int pos;
		int rg;
		cout << "Please enter the registration number  to be Printed:";
		cin >> rg;
		pos = search(ss, nn, rg);

		if (pos == -1)
			cout << "Result Not Found, Sorry.";

		else
		{
			cout << "Name\t";
			cout << "Regg" << "\t" << "Subj1" << "\t" << "Subj2" << "\t" << "Subj3" << "\t" << "TMO" << "\t" << "Perc" << "\t" << "Grade" << "\n";
			cout << ss[pos].name << "\t";
			cout << ss[pos].reg << "\t";

			for (int j = 0; j < SUB; j++)
				cout << ss[pos].sub[j] << "\t";

			cout << ss[pos].tm << "\t";
			cout << ss[pos].perc << "%" << "\t";
			cout << ss[pos].grd << "\t\n";
		}
		break;

	case 'c':
	case 'C':
		break;
	}
}
void append(student ss[], int& nn)
{
	nn = nn++;

	cout << "ENTER the Reg.No of NEW student: ";
	cin >> ss[nn].reg;

	cin.ignore(10, '\n');
	cout << "ENTER the NAME of NEW student : ";
	getline(cin, ss[nn].name);
	ss[nn].tm = 0;
	for (int j = 0; j < SUB; j++)
	{

		cout << "Enter marks of subject " << j + 1;
		cin >> ss[nn].sub[j];
		ss[nn].tm += ss[nn].sub[j];
	}
	process(ss, nn);
}
int search(student ss[], int nn, int rgg)
{
	int i;
	for (i = 0; i < nn; i++)
	{
		if (rgg == ss[i].reg)
			return i;
		else
			return -1;
	}
	
}
void dlete(student ss[], int& nn)
{
	int pos;
	int rg;
	cout << "Please enter the registration number to be Deleted: ";
	cin >> rg;
	pos = search(ss, nn, rg);

	if (pos == -1)
		cout << "nRecord do not Exist.";

	else
	{

		cout << "Name\t";
		cout << "Regg" << "\t" << "Subj1" << "\t" << "Subj2" << "\t" << "Subj3" << "\t" << "TMO" << "\t" << "Perc" << "\t" << "Grade" << "\n";
		cout << ss[pos].name << "\t";
		cout << ss[pos].reg << "\t";

		for (int j = 0; j < SUB; j++)
			cout << ss[pos].sub[j] << "\t";

		cout << ss[pos].tm << "\t";
		cout << ss[pos].perc << "%" << "\t";
		cout << ss[pos].grd << "\t\n";

		for (int i = pos; i < nn; i++)
		{
			ss[i].reg = ss[i + 1].reg;
			for (int j = 0; i < SUB; i++)
			{
				ss[i].sub[j] = ss[i + 1].sub[j];
			}

			ss[i].perc = ss[i + 1].perc;
			ss[i].grd = ss[i + 1].grd;
		}
		nn--;
	}

}
void sorting(student ss[], int nn)
{
	string namme;
	for (int i = 0; i < nn; i++)
	{
		for (int j = i + 1; j < nn; j++)
		{
			if (ss[i].reg > ss[j].reg)
			{
				int temp[SIZE];
				temp[i] = ss[i].reg;
				ss[i].reg = ss[j].reg;
				ss[j].reg = temp[i];
				for (int k = 0; k < SUB; k++)
				{
					temp[i] = ss[i].sub[k];
					ss[i].sub[k] = ss[j].sub[k];
					ss[j].sub[k] = temp[i];
				}

				temp[i] = ss[i].perc;
				ss[i].perc = ss[j].perc;
				ss[j].perc = temp[i];

				temp[i] = ss[i].grd;
				ss[i].grd = ss[j].grd;
				ss[j].grd = temp[i];

				namme = ss[i].name;
				ss[i].name = ss[j].name;
				ss[j].name = namme;
			}
		}
	}
}


void update(student ss[], int nn)
{
	int pos;
	int rg;
	cout << "Please enter the registration number to be searched: ";
	cin >> rg;
	pos = search(ss, nn, rg);

	if (pos == -1)
		cout << "nResult Not Found, Sorry";

	else
	{
		cout << "Name\t";
		cout << "Regg" << "\t" << "Subj1" << "\t" << "Subj2" << "\t" << "Subj3" << "\t" << "TMO" << "\t" << "Perc" << "\t" << "Grade" << "\n";
		cout << ss[pos].name << "\t";
		cout << ss[pos].reg << "\t";

		for (int j = 0; j < SUB; j++)
			cout << ss[pos].sub[j] << "\t";

		cout << ss[pos].tm << "\t";
		cout << ss[pos].perc << "%" << "\t";
		cout << ss[pos].grd << "\t\n";
	}
	cout << "\nENTER the Reg.No of This student in (XXXX) Format to Update: ";
	cin >> ss[pos].reg;

	cin.ignore(10, '\n');
	cout << "\nENTER the NAME of NEW student to Update : ";
	getline(cin, ss[pos].name);

	for (int j = 0; j < SUB; j++)
	{
		ss[pos].tm = 0;
		cout << "Enter marks of subject " << j + 1 << " out of (100): ";
		cin >> ss[pos].sub[j];
		ss[pos].tm += ss[pos].sub[j];
	}
	process(ss, nn);
}
void checkreg1(student sss[], int nnn, int ii)
{
	do
	{
		if ((sss[ii].reg >= 1000) && (sss[ii].reg < 10000))
			return;	
		else
		{
			cout << "Enter the Reg.No of student again: ";
			cin >> sss[ii].reg;
		}
	}while(1);

}
void checkreg2(student sss[], int nnn, int ii)
{
	do
	{
		for (int i = 0; i < nnn - 1; i++)
		{
			if (sss[ii].reg != sss[i].reg)
				return;
		}
		
		cout << "Enter the Reg.No of student again: ";
		cin >> sss[ii].reg;
		
	}while(1);
	
}
void checkm(student ss[], int nn, int i, int j)
{
	do
	{
		
		if ((ss[i].sub[j]) <= 100 && (ss[i].sub[j]>=0))
			return;
		else
		{
			cout << "Please enter again: ";
			cin >> ss[i].sub[j];
		}
	}
	while(1);
}
void checkst(int& nnn)
{
	do
	{	
		if ((nnn) <= 70 && (nnn > 0))
			return;
		else
		{
			cout << "Please enter No of Students again: ";
			cin >> nnn;
		}
	}
	while(1);
}
