#include "SimObserver.h"

#include "../utility/LogManager.h"
#include "../utility/ToString.h"
#include "SimSubject.h"

namespace annatar {
namespace sim
{


CSimObserver::CSimObserver()
{
}

CSimObserver::~CSimObserver()
{
}

void CSimObserver::update(CSimSubject* sub, CSimEvent* e)
{
	std::cout << "CSimObserver::update(CSimSubject* sub, CSimEvent* e)";
}

}
}
