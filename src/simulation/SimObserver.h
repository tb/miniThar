#ifndef __ANNATAR_SIMOBSERVER_H__
#define __ANNATAR_SIMOBSERVER_H__

#include "SimEvent.h"

namespace annatar {
namespace sim
{

class CSimSubject;

class CSimObserver
{
public:
	virtual ~CSimObserver();
	virtual void update(CSimSubject* sub, CSimEvent* e);
protected:
	CSimObserver();
};

}
}

#endif
