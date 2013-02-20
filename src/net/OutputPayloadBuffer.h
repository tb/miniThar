#ifndef __ANNATAR_OUTPUTPAYLOADBUFFER_H__
#define __ANNATAR_OUTPUTPAYLOADBUFFER_H__

#include "Payload.h"

#include <deque>
//#include <list>

namespace annatar {
namespace net
{

	class CSequencePayloadPair
	{
	public:
		int seq;
		CPayload *payload;

		inline bool operator < ( const CSequencePayloadPair& rhs ) const
		{
			if( (seq < rhs.seq) )
				return true;
			return false;
		}
	};

	class COutputPayloadBuffer
	{
	public:
		std::deque<CSequencePayloadPair> mPayloadDeque;

	public:
		COutputPayloadBuffer();
		virtual ~COutputPayloadBuffer();

		void append( CPayload *payload );
		CPayload* getPayload( int seq );
		std::vector<CPayload*> getPayloadSequence( std::vector<int> missingSeq );
		void consume( int seq );
	};

}
}

#endif
