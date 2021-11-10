#include <iostream>
#include <string>
#include <tchar.h>
#include <Windows.h>
using namespace std;

typedef unsigned (*f_rsa_genkey)(unsigned *e, unsigned *d);
typedef unsigned (*f_rsa_encrypt)(unsigned m, unsigned e, unsigned n, unsigned *crypt);
typedef unsigned (*f_rsa_decrypt)(unsigned crypt, unsigned d, unsigned n, unsigned *decrypt);

HINSTANCE ChooseLanguage() 
{
	_tsetlocale(LC_ALL, _T("Ukrainian"));

	bool correct = false;
	string input;
	HINSTANCE lang_lib = 0;
	do
	{
		cout << "Choose language (type in a number):\n"
			<< "1 - English\n"
			<< "2 - Українська\n\n";

		cin >> input;

		if (input == "1")
		{
			cout << "English language is chosen.\n\n";
			lang_lib = LoadLibrary(TEXT("Lang_EN_DLL.dll"));
			correct = true;
		}
		else if (input == "2")
		{
			cout << "Вибрано українську мову.\n\n";
			lang_lib = LoadLibrary(TEXT("Lang_UA_DLL.dll"));
			correct = true;
		}
		else
		{
			cout << "Wrong input.\n\n";
			correct = false;
		}
	} while (!correct);

	return lang_lib;
}

int TestRSA() 
{
	unsigned e1, d1, n1;
	unsigned e2, d2, n2;

	HINSTANCE lib = LoadLibrary(TEXT("RSA_DLL.dll"));

	if (!lib)
	{
		cout << "Error: could not load RSA library.\n";
		return 1;
	}
	else
		cout << "RSA library is loaded.\n";


	f_rsa_genkey rsa_genkey = (f_rsa_genkey)GetProcAddress(lib, "rsa_genkey");
	f_rsa_encrypt rsa_encrypt = (f_rsa_encrypt)GetProcAddress(lib, "rsa_encrypt");
	f_rsa_decrypt rsa_decrypt = (f_rsa_decrypt)GetProcAddress(lib, "rsa_decrypt");

	if (!rsa_genkey ||
		!rsa_encrypt ||
		!rsa_decrypt)
	{
		cout << "Error: could not load at least one of RSA functions.\n";
		return 1;
	}
	else
		cout << "RSA functions are loaded.\n";

	n1 = rsa_genkey(&e1, &d1);
	n2 = rsa_genkey(&e2, &d2);

	unsigned temp;
	int i;
	for (i = 2; i < 100; ++i)
	{
		unsigned crypt = rsa_encrypt(i, e2, n2, &temp);
		if (crypt) break;

		rsa_decrypt(temp, d2, n2, &temp);
		if (temp != i)
			break;

		crypt = rsa_encrypt(i, e1, n1, &temp);
		if (crypt) break;

		rsa_decrypt(temp, d1, n1, &temp);
		if (temp != i)
			break;
	}

	FreeLibrary(lib);

	if (i == 100)
		cout << "Test is completed.\n";
	else
		cout << "Test is failed.\n";
}

int main()
{	
	HINSTANCE lang_lib = ChooseLanguage();

	if (!lang_lib)
	{
		cout << "Error: could not load the language library.";
		return 1;
	}

	int str_loaded;
	TCHAR *str = new TCHAR[50];

	for (int i = 101; i <= 104; i++)
	{
		str_loaded = LoadString(lang_lib, i, str, sizeof(TCHAR) * 25);

		if (!str_loaded)
			cout << "Could not load the string.\n";
		else
		{
			_tprintf(str);
			cout << endl;
		}
	}
	cout << endl;

	FreeLibrary(lang_lib);

	return TestRSA();
}