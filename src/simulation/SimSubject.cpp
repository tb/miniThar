#include "SimSubject.h"

namespace annatar {
namespace sim
{


CSimSubject::CSimSubject()
{
}

CSimSubject::~CSimSubject()
{
}

//----------------------------------------------------------------------------
void CSimSubject::attach( CSimObserver* ob )
{
	mObservers.insert( ob );
}

//----------------------------------------------------------------------------
void CSimSubject::detach( CSimObserver* ob )
{
	mObservers.erase( ob );
}

//----------------------------------------------------------------------------
void CSimSubject::notify( CSimEvent* e )
{
	std::set<CSimObserver*>::iterator it;
	for( it = mObservers.begin(); it != mObservers.end(); it++ )
	{
		(*it)->update(this, e);
	}
}

}
}