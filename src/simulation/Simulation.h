#ifndef __ANNATAR_SIMULATION_H__
#define __ANNATAR_SIMULATION_H__

#include "../simulation/SimObserver.h"
#include "../simulation/SimSubject.h"
//#include "../utility/Singleton.h"
//#include <pasync.h>

namespace annatar {
	namespace sim
	{

		class CSimulation : public CSimSubject, public CSimObserver
		{
		protected:
		public:
			CSimulation();
			virtual ~CSimulation();

			virtual void update(CSimSubject* sub, CSimEvent* e) = 0;
		};

	}
}

#endif