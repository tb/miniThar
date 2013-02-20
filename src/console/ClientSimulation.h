#ifndef __ANNATAR_CLIENTSIMULATION_H__
#define __ANNATAR_CLIENTSIMULATION_H__

#include "../simulation/Simulation.h"
//#include "../utility/Singleton.h"
//#include <pasync.h>

namespace annatar {
	namespace sim
	{

		class CClientSimulation : public CSimulation
		{
		protected:
			bool connected;
		public:
			CClientSimulation();
			virtual ~CClientSimulation();

			virtual void update(CSimSubject* sub, CSimEvent* e);
		};

	}
}

#endif