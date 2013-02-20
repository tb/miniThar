#include "ToString.h"

namespace utility {
    
	    template <typename T> std::string toString(const T& _value) {
    	    std::ostringstream ost;
	        ost << _value;
	        return ost.str();
	    }

		std::string dumpBinary( char* buf, int size, int width )
		{
			using namespace std;

			stringstream desc;

			int i=0,k=0,l=0;
			bool br=false;
			
			for( ; i < size; ++i)
			{
				if( ++k > width )
				{
					l=i+1;
					l=l-k;
					k=0;
					br = true;
				}

				if( br )
				{
					desc << "  ";
					for(; l<i;l++)
					{
						if( ((unsigned char)buf[l] > 32) && 
							((unsigned char)buf[l] < 255 ))
							desc << buf[l];
						else
							desc << ".";
					} 
					i--;
					desc << "\n";
				} else {
					desc << "0x";
					desc.fill('0');
					desc.width(2);
					desc << hex << (int)(unsigned char)buf[i] << " ";
					desc << dec;
				}

				if(i > ((size)-2))
				{
					for(int j=0; j<width-k; ++j)
						desc << "     ";

					desc <<"  ";
				}

				br=false;
			}

			for(; l<i; ++l)
			{
				if( ((unsigned char)buf[l] > 32) && 
					((unsigned char)buf[l] < 255 ))
					desc << buf[l];
				else
					desc << ".";
			}

			return desc.str();
		}

}  
