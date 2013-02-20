#include "OutputPayloadBuffer.h"

namespace annatar {
namespace net
{

COutputPayloadBuffer::COutputPayloadBuffer()
{
}

COutputPayloadBuffer::~COutputPayloadBuffer()
{
}

void COutputPayloadBuffer::append( CPayload *payload )
{
	CSequencePayloadPair para;
	para.payload = payload;
	para.seq = payload->getMaxSeq();
	mPayloadDeque.push_back( para );
//	delete payload;
}

CPayload* COutputPayloadBuffer::getPayload( int seq )
{
	std::deque<CSequencePayloadPair>::iterator itr;
	for (itr = mPayloadDeque.begin(); itr != mPayloadDeque.end(); )
	{
		if ( (*itr).seq >= seq )
		{
			return (*itr).payload;
		}
		else
		{
			++itr;	
		}
	}

	return NULL;
}

std::vector<CPayload*> COutputPayloadBuffer::getPayloadSequence( std::vector<int> missingSeq )
{
	int n=0, last=0, lastAdded=0;
	std::vector<CPayload*> payloadSequence;

	std::deque<CSequencePayloadPair>::iterator itr;
	lastAdded = 0;
	itr = mPayloadDeque.begin();

	std::vector<int>::iterator seqItr;
	seqItr = missingSeq.begin();
	n = (int)(*seqItr);
	seqItr = missingSeq.end();
	--seqItr;
	last = (int)(*seqItr);

//	std::cout << mPayloadDeque.size();
	
	do {
		if (itr == mPayloadDeque.end())
		{
			break;
		}

		int seq = (*itr).seq;
		if ( (*itr).seq >= n )
		{
			//jesli ostatni na liscie do zworcenia nie jest n,
			// dodaj n
			if ( lastAdded != (*itr).seq )
			{
				payloadSequence.push_back( (*itr).payload );
				lastAdded = (*itr).seq;
				++itr;
			}
		}
		else
		{
			++itr;
		}
		++n;

	} while( n <= last );

//	std::cout << payloadSequence.size();

	return payloadSequence;
}

void COutputPayloadBuffer::consume( int seq )
{
	std::deque<CSequencePayloadPair>::iterator itr;
	for (itr = mPayloadDeque.begin(); itr != mPayloadDeque.end(); )
	{
		if ( (*itr).seq < seq )
		{
			delete (*itr).payload;
			mPayloadDeque.erase( itr );
			++itr;
		}
		else
		{
			break;
		}
	}
}

}
}
