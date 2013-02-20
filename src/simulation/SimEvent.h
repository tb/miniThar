#ifndef __ANNATAR_SIMEVENT_H__
#define __ANNATAR_SIMEVENT_H__

#include "../net/Payload.h"

namespace annatar {
namespace sim
{

class CSimEvent
{
public:
	enum EEtherEvent
	{
		Null = 0, // nic sie nie stalo
		Connect,
		Phrase,
		Tick,
		Close // zakonczylem swoje istnienie
	};

private:
	EEtherEvent mProtocolEvent;

public:
	annatar::net::CPADU* mADU;
	CSimEvent();
	virtual ~CSimEvent();

	CSimEvent( const CSimEvent& theOther );

	EEtherEvent getEventType();
	void setEvent( EEtherEvent e,  annatar::net::CPADU* o );
	annatar::net::CPADU* getADU() {return mADU; }
//	CPADU* set() {return mADU; }
};

}
}

#endif
