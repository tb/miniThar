#ifndef __ANNATAR_INTERACTIVESHELL_H__
#define __ANNATAR_INTERACTIVESHELL_H__

#include <string>

class CInteractiveShell
{
private:
	std::string mLine, mCmd, mPrompt, quitCmd;

public:
	CInteractiveShell();
	~CInteractiveShell();

	bool readCommand();
	void printPrompt();
	bool hasCommand();
	std::string consume();
};

#endif
