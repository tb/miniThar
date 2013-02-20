#ifndef __UTILITY_TOSTRING_H__
#define __UTILITY_TOSTRING_H__

#include <string>
#include <sstream>

namespace utility {
    
        /**
        * Funkcja zamieniajaca dowolny typ posiadajacy operator<< na std::string.
        * Przekazywanie duzych obiektow moze byc kosztowne.
        *
        * @param _value obiekt, ktory ma zostac zamieniony na string
        * @return reprezentacja argumentu w postaci napisu
        */
	    template <typename T> std::string toString(const T& _value);

		std::string dumpBinary( char* buf, int size, int width = 10 );
}  

#endif

