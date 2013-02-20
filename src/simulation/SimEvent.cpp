#include "SimEvent.h"

namespace annatar {
namespace sim
{

CSimEvent::CSimEvent()
	: mProtocolEvent( EEtherEvent::Null ), mADU( 0 )
{
}

CSimEvent::~CSimEvent()
{
	delete mADU;
}

CSimEvent::CSimEvent( const CSimEvent& theOther )
{
	mProtocolEvent = theOther.mProtocolEvent;
	mADU = theOther.mADU;
}

CSimEvent::EEtherEvent CSimEvent::getEventType()
{
	return mProtocolEvent;
}

void CSimEvent::setEvent( EEtherEvent e,  annatar::net::CPADU* o )
{
	mProtocolEvent = e;
	mADU = o;
}

}
}
