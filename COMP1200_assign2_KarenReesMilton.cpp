/*********************************************
Karen Rees-Milton. March 29, 2018
COMP1200. Assignment2
A program to manage records for an employment
agency for individuals seeking work
*********************************************/

#include<fstream>
#include<iostream>
#include<string>
#include<iomanip>

using namespace std;

//prototypes and global constants
const int SIZE = 1000;
int loadArrays(string[], int[]);
int removeEmployee(string[], int[], int);
void printEmployees(const string[], const int[], int);
int addEmployee(string[], int[], int);
bool isFull(int);
double computeAvg(const int[], int);
int computeMostYears(const int[], int);
int validateYear(int);

int main()
{
	string names[SIZE];
	int experience[SIZE];
	int noRecords;


	cout << "Initial array load:\n\n" << endl;
	noRecords = loadArrays(names, experience);
	printEmployees(names, experience, noRecords);

	cout << "An employee added:\n\n" << endl;
	noRecords = addEmployee(names, experience, noRecords);
	printEmployees(names, experience, noRecords);

	cout << "Attempted to add same employee:\n\n" << endl;
	noRecords = addEmployee(names, experience, noRecords);
	printEmployees(names, experience, noRecords);

	cout << "Employee deleted:\n\n" << endl;
	noRecords = removeEmployee(names, experience, noRecords);
	printEmployees(names, experience, noRecords);

	cout << "Attempted to delete same employee load\n\n" << endl;
	noRecords = removeEmployee(names, experience, noRecords);
	printEmployees(names, experience, noRecords);

	cout << "Program ended successfully" << endl;
	system("type employees.dat");
	system("pause");

}

//function to load arrays from file
int loadArrays(string empName[], int noYearsExperience[])
{
	int length;
	ifstream fin("employees.dat");
	if (!fin.is_open())
	{
		cout << "Error opening file";
		system("pause");
		exit(-1);
	}
	for (length = 0; length < SIZE; length++)
	{
		getline(fin, empName[length]);
		if (fin.eof())
			break;
		if (isFull(length))
			break;
		else
		{
			fin >> noYearsExperience[length];
			fin.ignore(80, '\n');
		}
	}
	return length;
}
//function to remove an employee from arrays
int removeEmployee(string names[], int years[], int noEmps)
{
	int position;
	string empName;
	cout << "Enter name of employee to delete ";
	getline(cin, empName);
	for (position = 0; position < noEmps; position++)
	{
		if (names[position] == empName)
			break;
	}
	if (position == noEmps)
		cout << empName << " not found" << endl << endl;
	else
	{
		if (position == 0)
			cout << "No elements in array" << endl << endl;
		else
		{
			noEmps--;
			for (int index = position; index < noEmps; index++)
			{
				names[index] = names[index + 1];
				years[index] = years[index + 1];
			}
		}
	}
	return noEmps;
}

//function to print to screen array employee information
void printEmployees(const string empName[], const int yearsExp[], int length)
{
	cout << left << setw(15) << "Employee Name"
		<< right << setw(15) << "Experience"
		<< endl << endl;
	int indexMostYears = computeMostYears(yearsExp, length);
	for (int ctr = 0; ctr < length; ctr++)
	{
		cout << left << setw(15) << empName[ctr]
			<< right << setw(15) << yearsExp[ctr];
		if (ctr == indexMostYears)
			cout << " * most experience *";
		cout << endl;
	}
	cout << endl << "Average number of years worked is "
		<< fixed << setprecision(1)
		<< computeAvg(yearsExp, length)
		<< endl << endl;
}

//function to add an employee
int addEmployee(string names[], int years[], int length)
{
	if (isFull(length))
		cout << "No room to add any more employees" << endl;
	else
	{
		int position;
		string name;
		cout << "Enter a new employee name ";
		getline(cin, name);
		for (position = 0; position < length; position++)
		{
			if (name <= names[position])
				break;
		}
		if (position < length && name == names[position])
		{
			cout << "Name already exists. Cannot add again" << endl;
		}
		else
		{
			for (int index = length; index > position; index--)
			{
				names[index] = names[index - 1];
				years[index] = years[index - 1];
			}
			names[position] = name;
			cout << "Enter years of experience for "
				<< name << " ";
			cin >> years[position];
			years[position] = validateYear(years[position]);
			length++;
		}
	}
	return length;
}

//function to check if arrays full
bool isFull(int length)
{
	return(length == SIZE);
}

// function to compute average years for an employee
double computeAvg(const int years[], int length)
{
	int totalYears = 0;
	double  avgYears = 0.;
	
	for(int ctr = 0; ctr < length; ctr++)
	{
		totalYears += years[ctr];
	}
	if (length > 0)
		avgYears = static_cast<double>(totalYears) / length;
	return avgYears;
}

//function to determine employee with most experience
int computeMostYears(const int years[], int length)
{
	int indexMostYears = 0;
	for (int ctr = 1; ctr < length; ctr++)
	{
		if (years[ctr] > years[indexMostYears])
		{
			indexMostYears = ctr;
		}
	}
	return indexMostYears;
}

//function to validate year 
int validateYear(int year)
{
	while (cin.fail() || year < 0 || year > 60)
	{
		cin.clear();
		cin.ignore(80, '\n');
		cout << "Error. Year must be 0 - 60. Re-enter ";
		cin >> year;
	}
	cin.ignore(80, '\n');
	return year;
}

/**********************************************
I/O dialog
***********************************************

Initial array load:


Employee Name       Experience

B.Lee                       5
J.Doe                      10
J.Wayne                     2
P.Smith                    24
S.Moir                     25 * most experience *
T.Jones                     1
T.Woods                    12
W.Gretzky                   4

Average number of years worked is 10.4

An employee added :


Enter a new employee name K.Rees - Milton
Enter years of experience for K.Rees - Milton two
Error.Year must be 0 - 60. Re - enter 222
Error.Year must be 0 - 60. Re - enter - 22
Error.Year must be 0 - 60. Re - enter 22
Employee Name       Experience

B.Lee                       5
J.Doe                      10
J.Wayne                     2
K.Rees - Milton            22
P.Smith                    24
S.Moir                     25 * most experience *
T.Jones                     1
T.Woods                    12
W.Gretzky                   4

Average number of years worked is 11.7

Attempted to add same employee :


Enter a new employee name K.Rees - Milton
Name already exists.Cannot add again
Employee Name       Experience

B.Lee                       5
J.Doe                      10
J.Wayne                     2
K.Rees - Milton            22
P.Smith                    24
S.Moir                     25 * most experience *
T.Jones                     1
T.Woods                    12
W.Gretzky                   4

Average number of years worked is 11.7

Employee deleted :


Enter name of employee to delete K.Rees - Milton
Employee Name       Experience

B.Lee                       5
J.Doe                      10
J.Wayne                     2
P.Smith                    24
S.Moir                     25 * most experience *
T.Jones                     1
T.Woods                    12
W.Gretzky                   4

Average number of years worked is 10.4

Attempted to delete same employee load


Enter name of employee to delete K.Rees - Milton
K.Rees - Milton not found

Employee Name       Experience

B.Lee                       5
J.Doe                      10
J.Wayne                     2
P.Smith                    24
S.Moir                     25 * most experience *
T.Jones                     1
T.Woods                    12
W.Gretzky                   4

Average number of years worked is 10.4

Program ended successfully
B.Lee
5
J.Doe
10
J.Wayne
2
P.Smith
24
S.Moir
25
T.Jones
1
T.Woods
12
W.Gretzky
4Press any key to continue . . .

**************************************************/