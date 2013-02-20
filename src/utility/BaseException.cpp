#include "BaseException.h"

#include <string>

namespace utility {

BaseException::BaseException(int line, const char *file, const std::string &msg) :
	std::exception(),
	mMessage(msg),
	mSrcLine(line),
	mSrcFile(file)
{
}

std::string BaseException::getMessage() const
{
	return mMessage;
}


int BaseException::getSrcLine() const
{
	return mSrcLine;
}


std::string BaseException::getSrcFile() const
{
	return mSrcFile;
}


}