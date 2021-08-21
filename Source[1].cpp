#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python function you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, double param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

void DailyReport()		// Takes the input file and prints out a list of items and their purchase amounts
{
	CallProcedure("printSomething");
	//try {
	//	int str_usr;
	//	cin >> str_usr;
	//	cout << "Generating Report...\n\n";
	//	cout << callIntFunc("daily_report", str_usr);			// Passes input and function name to PythonCode
	//} catch(...)
	//{
	//	cout << "an error occurred";
	//}
}

void doubl() {			// Takes user input and passes it to PythonCode function DoubleValue
	int userNum;
	cout << "Enter a number: ";
	cin >> userNum;
	int aDouble = callIntFunc("DoubleValue", userNum);			// Passes input and function name to PythonCode
	cout << "Double of value: " << aDouble << "\n";
}
void menu() {		// Menu to let user select which functions they'd like to perform
	int ch;

	do {
		cin.clear();		// Clears input on loop
		cout << "1: Generate Daily Report \n";
		cout << "2: Item Lookup \n";
		cout << "3: Display Histogram \n";
		cout << "4: Quit\n";
		cout << "Enter your choice:\n";
		cin >> ch;
		switch (ch) {		// Checks for user input and if value has no case, alert is printed
		case 1: {
			DailyReport();		// Shows multiplication table in PythonCode
			break;
		}
		case 2: {		// Shows doubled value in PythonCode
			doubl();
			break;
		}
		case 3: {		// Prints out a pretty lame but functional histogram
			// histogram();
			break;
		}
		case 4: {		// Exits the program with input of 4
			cout << "Have a good day\n" << ch;
			ch = 3;
			break;
		}
		default:
			printf("Invalid value. \n");		// Handles improper input
		}
	} while (ch != 3);
}


int main()
{
	menu();
}