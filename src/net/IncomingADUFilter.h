#ifndef __ANNATAR_INCOMINGADUFILTER_H__
#define __ANNATAR_INCOMINGADUFILTER_H__

#include "Payload.h"

namespace annatar {
namespace net
{

	class CIncomingADUFilter
	{
	public:
		std::list<CPADU*>* mADUList;
		int curSeq;
		std::vector<int> mMissingSeq;

	public:
		CIncomingADUFilter();
		virtual ~CIncomingADUFilter();

		void append( CPayload *payload );
		std::list<CPADU*>* getADUSequence();
		std::vector<int> getMissingSequence();
		bool hasMissingSequence();
	};

}
}

#endif
