#include "ConnectionGuard.h"
#include "../net/NodesManager.h"

namespace annatar {
namespace net
{

void CConnectionGuard::execute()
{
	using namespace pt;
	bool quit = false;

	while (!quit)
	{
		pt::psleep( 2000 );

		CPayload *payload = new annatar::net::CPayload();
		annatar::net::CPTick *ptick =
			new annatar::net::CPTick( mNetworkingNode->getSequenceNumber(), 1000, 9999 );
		payload->addTick( ptick );

		// dla kazdego polaczenia, sprawdz ostatni czas
		// odebrania pakietu, jesli przekracza jas wartosc
		// wyslij prosbe o odzew, jesli brak reakcji,
		// rozlacz
		//std::list<CServer*>::iterator itr;
		//mAddressSetLock.rdlock();
		
		/*
		for (itr = mServersMgr->mAddressSet.begin(); itr != mServersMgr->mAddressSet.end(); ++itr)
		{
			CServer* server = (CServer*)(*itr);
			server->broadcast( payload );
		}
		*/
		mNetworkingNode->broadcast( payload );
		
		delete ptick;
	}
}

}
}
