#include "ServerSimulation.h"

#include "Client.h"

namespace annatar {
	namespace sim
	{

		CServerSimulation::CServerSimulation()
		{
		}

		CServerSimulation::~CServerSimulation()
		{
		}

		void CServerSimulation::update(CSimSubject* sub, CSimEvent* e)
		{
			using namespace annatar::net;

			std::stringstream desc;
			desc << e->getEventType() << ", seq " << e-> getADU()->mSeq;

			utility::LogManager::getSingletonPtr()->logMessage(
				"CSimulation::update - event " + desc.str() );

			// wyslij eventa tylko do nadawcy eventa
			((CClient*)sub)->update( this, e );

			// wyslij eventa do wszystkich
			notify( e );
		}

	}
}
