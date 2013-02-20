#include "ClientSimulation.h"

#include "Server.h"

namespace annatar {
	namespace sim
	{

		CClientSimulation::CClientSimulation()
		{
			connected = false;
		}

		CClientSimulation::~CClientSimulation()
		{
		}

		void CClientSimulation::update(CSimSubject* sub, CSimEvent* e)
		{
			using namespace annatar::net;

			std::stringstream desc;
			desc << e->getEventType() << ", seq " << e-> getADU()->mSeq;

			utility::LogManager::getSingletonPtr()->logMessage(
				"CSimulation::update - event " + desc.str() );

			// wyslij eventa tylko do nadawcy eventa
			((CServer*)sub)->update( this, e );

			// wyslij eventa do wszystkich
			notify( e );
		}

	}
}
