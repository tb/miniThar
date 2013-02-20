#ifndef __ANNATAR_SERVERSIMULATION_H__
#define __ANNATAR_SERVERSIMULATION_H__

#include "../simulation/Simulation.h"
//#include "../utility/Singleton.h"
//#include <pasync.h>

namespace annatar {
	namespace sim
	{

		class CServerSimulation : public CSimulation
		{
		protected:
		public:
			CServerSimulation();
			virtual ~CServerSimulation();

			virtual void update(CSimSubject* sub, CSimEvent* e);
		};

	}
}

#endif