#include "InteractiveShell.h"

#include <iostream>

CInteractiveShell::CInteractiveShell()
{
	mPrompt = "# ";
	quitCmd = "quit;";
}

CInteractiveShell::~CInteractiveShell()
{
}

bool CInteractiveShell::readCommand()
{
	using namespace std;

	string temp;

//	cout << mPrompt;

//	while (true)
//	{
		getline( cin, temp, '\n');
		mLine += temp;

		if ( mLine.size() > 0 )
		{
			string::iterator itr = mLine.end();
			--itr;

			if ( *itr == '-' )
			{
				int del = 0;

				while ( *itr == '-' )
				{
					++del;
					--itr;
				}

				if ( 2*del < (int)mLine.size() )
				{
					mLine = mLine.substr( 0, mLine.size()-(2*del) );
				}
				else
				{
					mLine.clear();
				}
			}
			else if ( mLine.find(quitCmd, 0) != string::npos )
			{
				mCmd = quitCmd;
				mLine.clear();

				return false;
			}
/*			else if ( *mLine.rbegin() == ';' )
			{
				mCmd = mLine;
				mLine.clear();

				return true;
			}
*/ //		}
//		cout << mPrompt << mLine;// << endl;
	}

	return true; // nigdy tego nie dojedziemy
}

void CInteractiveShell::printPrompt()
{
	std::cout << mPrompt << mLine;// << endl;
}

bool CInteractiveShell::hasCommand()
{
	if ( *mLine.rbegin() == ';' )
	{
		std::string::iterator itr = mLine.end();
		--itr;
		mLine.erase( itr );

		mCmd = mLine;
		mLine.clear();

		return true;
	}
	else
	{
		return false;
	}
}

std::string CInteractiveShell::consume()
{
	std::string tmp;
	tmp = mCmd;
	mCmd.clear();

	return tmp;
}
