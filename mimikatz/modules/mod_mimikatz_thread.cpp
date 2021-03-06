/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : http://creativecommons.org/licenses/by-nc-sa/3.0/
*/
#include "mod_mimikatz_thread.h"

vector<KIWI_MIMIKATZ_LOCAL_MODULE_COMMAND> mod_mimikatz_thread::getMimiKatzCommands()
{
	vector<KIWI_MIMIKATZ_LOCAL_MODULE_COMMAND> monVector;
	monVector.push_back(KIWI_MIMIKATZ_LOCAL_MODULE_COMMAND(list,	L"list",	L"Lists the threads"));
	monVector.push_back(KIWI_MIMIKATZ_LOCAL_MODULE_COMMAND(suspend,	L"suspend",	L"Suspends a running thread"));
	monVector.push_back(KIWI_MIMIKATZ_LOCAL_MODULE_COMMAND(resume,	L"resume",	L"Resumes a suspended thread"));
	monVector.push_back(KIWI_MIMIKATZ_LOCAL_MODULE_COMMAND(stop,	L"stop",	L"Stops a thread"));
	monVector.push_back(KIWI_MIMIKATZ_LOCAL_MODULE_COMMAND(quit,	L"quit",	L"Sending a close message to a thread"));
	return monVector;
}

bool mod_mimikatz_thread::list(vector<wstring> * arguments)
{
	vector<THREADENTRY32> * vectorThreads = new vector<THREADENTRY32>();

	DWORD processId = arguments->empty() ? 0 : _wtoi(arguments->front().c_str());

	if(mod_thread::getList(vectorThreads, arguments->empty() ? NULL : &processId))
	{
		wcout << L"PID\tTID\tprTh" << endl;
		for(vector<THREADENTRY32>::iterator monThread = vectorThreads->begin(); monThread != vectorThreads->end(); monThread++)
			wcout << 
				setw(5) << setfill(wchar_t(' ')) << monThread->th32OwnerProcessID << L'\t' <<
				setw(5) << setfill(wchar_t(' ')) << monThread->th32ThreadID << L'\t' <<
				setw(5) << setfill(wchar_t(' ')) << monThread->tpBasePri <<
			endl;
	}
	else
		wcout << L"mod_thread::getList ; " << mod_system::getWinError() << endl;

	delete vectorThreads;
	return true;
}

bool mod_mimikatz_thread::resume(vector<wstring> * arguments)
{
	for(vector<wstring>::iterator monArgThread = arguments->begin(); monArgThread != arguments->end(); monArgThread++)
	{
		DWORD threadId = _wtoi(monArgThread->c_str());
		
		if(threadId != 0)
		{
			wcout << L"thread " << setw(5) << setfill(wchar_t(' ')) << threadId << L"\treprise ";
			
			if(mod_thread::resume(threadId))
				wcout << L"OK";
			else
				wcout << L"KO - mod_thread::resume ; " << mod_system::getWinError();
		}
		else
			wcout << L"argument \'" << *monArgThread << L"\' invalide";

		wcout << endl;
	}

	return true;
}

bool mod_mimikatz_thread::suspend(vector<wstring> * arguments)
{
	for(vector<wstring>::iterator monArgThread = arguments->begin(); monArgThread != arguments->end(); monArgThread++)
	{
		DWORD threadId = _wtoi(monArgThread->c_str());
		
		if(threadId != 0)
		{
			wcout << L"thread " << setw(5) << setfill(wchar_t(' ')) << threadId << L"\tsuspension ";
			
			if(mod_thread::suspend(threadId))
				wcout << L"OK";
			else
				wcout << L"KO - mod_thread::suspend ; " << mod_system::getWinError();
		}
		else
			wcout << L"argument \'" << *monArgThread << L"\' invalid";

		wcout << endl;
	}

	return true;
}

bool mod_mimikatz_thread::stop(vector<wstring> * arguments)
{
	for(vector<wstring>::iterator monArgThread = arguments->begin(); monArgThread != arguments->end(); monArgThread++)
	{
		DWORD threadId = _wtoi(monArgThread->c_str());
		
		if(threadId != 0)
		{
			wcout << L"thread " << setw(5) << setfill(wchar_t(' ')) << threadId << L"\toff ";
			
			if(mod_thread::stop(threadId))
				wcout << L"OK";
			else
				wcout << L"KO - mod_thread::stop ; " << mod_system::getWinError();
		}
		else
			wcout << L"argument \'" << *monArgThread << L"\' invalid";

		wcout << endl;
	}

	return true;
}


bool mod_mimikatz_thread::quit(vector<wstring> * arguments)
{
	for(vector<wstring>::iterator monArgThread = arguments->begin(); monArgThread != arguments->end(); monArgThread++)
	{
		DWORD threadId = _wtoi(monArgThread->c_str());
		
		if(threadId != 0)
		{
			wcout << L"thread " << setw(5) << setfill(wchar_t(' ')) << threadId << L"\tpost closing ";
			
			if(mod_thread::quit(threadId))
				wcout << L"OK";
			else
				wcout << L"KO - mod_thread::quit ; " << mod_system::getWinError();
		}
		else
			wcout << L"argument \'" << *monArgThread << L"\' invalid";

		wcout << endl;
	}

	return true;
}
