#ifndef __OCTETBUFFER_H__
#define __OCTETBUFFER_H__

class COctetBuffer
{
public:
	char* buf;
	int size;

	COctetBuffer()
	{
		// ##FIXME## wielkosc bufora jest na sztywno
		// i nigdzie nie jest sprawdzana!
		buf = new char[2024];
		size = 0;
	}

	COctetBuffer( const COctetBuffer& theOther )
	{
		if (!size)
		{
			free( buf );
		}
		//buf = (char*)calloc(2048, sizeof(char));
		buf = new char[2048];
		size = theOther.size;
		memcpy(buf, theOther.buf, size-1);
	}

	virtual ~COctetBuffer()
	{
		delete buf;
	}
};

#endif
