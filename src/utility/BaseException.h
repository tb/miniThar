#ifndef __ANN_BASEEXCEPTION_H__
#define __ANN_BASEEXCEPTION_H__

#include <string>
#include <exception>
#include <sstream>

using namespace std;

namespace utility {

/**
* Funkcja zamieniajaca dowolny typ posiadajacy operator<< na std::string.
* Przekazywanie duzych obiektow moze byc kosztowne.
*
* @param _value obiekt, ktory ma zostac zamieniony na string
* @return reprezentacja argumentu w postaci napisu
*/
/*
template <typename T> inline std::string toString(const T& _value) {
	std::ostringstream ost;
	ost << _value;
	return ost.str();
}   
*/
}

namespace utility {

class BaseException : public std::exception
{
protected:
	std::string		mMessage;
	int				mSrcLine;
	std::string		mSrcFile;

public:
	BaseException(int line, const char *file, const std::string &msg);
	std::string getMessage() const;
	int getSrcLine() const;
	std::string getSrcFile() const;
};
 
}

#define ERROR_MSG(message)	utility::BaseException( __LINE__, __FILE__, (message) )

#endif