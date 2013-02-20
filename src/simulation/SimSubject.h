#ifndef __ANNATAR_PROTOCOLSUBJECT_H__
#define __ANNATAR_PROTOCOLSUBJECT_H__

#include "SimEvent.h"
#include "SimObserver.h"

#include <map>
#include <set>

namespace annatar {
namespace sim
{

class CSimSubject
{
private:
	std::set< CSimObserver* > mObservers;

public:
	CSimSubject();
	virtual ~CSimSubject();
	
	void attach( CSimObserver* ob );
	void detach( CSimObserver* ob );
	void notify( CSimEvent* e );
};

}
}

#endif
