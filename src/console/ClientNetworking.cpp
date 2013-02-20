#include "ClientNetworking.h"

#include "../net/Services.h"
#include "ClientServant.h"

#include "../net/ConnectionGuard.h"

namespace annatar {
namespace net
{

void CClientNetworking::execute()
{
	using namespace pt;

	running = true;
	std::cout << "\n -= CClientNetworking->execute() =-\n" << std::endl;

	jobqueue jq;
	tobjlist<CClientServant> threads(true);

	//annatar::net::CNodesManager *serversMgr =
	serversMgr =
		new annatar::net::CNodesManager( new annatar::sim::CClientSimulation(), &jq );

	for(int i = 0; i < 2; ++i)
	{
		CClientServant* j = new CClientServant(i + 1, &jq, serversMgr);
		j->start();
		threads.add(j);
	}

	// DODAJEMY SERVER do listy serwerow
	//cli = new pt::ipmessage( pt::ipaddress(127, 0, 0, 1), 8045 );

	//CServer *server = new CServer( srv, &jq );
	server = new CServer( srv, &jq );
	serversMgr->add( server );

	CPayload *payload = new annatar::net::CPayload();
	annatar::net::CPConnect *pconnect =
		new annatar::net::CPConnect( server->acquireSequenceNumber(), "Tom");
	payload->addConnect( pconnect );
	delete pconnect;

	COctetBuffer *buffer = payload->serialize();
	srv->send( buffer->buf, buffer->size );
	pt::psleep( 800 ); // czas na ustanowienie polaczenia
	server->broadcast( payload );
	delete buffer;
	// DODAJEMY SERVER do listy serwerow

	// sprawiamy ze 
	annatar::net::CConnectionGuard *connectionGuard =
		new annatar::net::CConnectionGuard( server );
	//connectionGuard->start();

	pout.putf("Ready to answer queries on port %d\n", srv->get_myport() );
	bool quit = false;
	do
	{
		try
		{		
			COctetBuffer *buffer = new COctetBuffer();
			pt::psleep( 1000 );
			//srv->waitfor( 1000 );
			buffer->size = srv->receive( buffer->buf, maxtoken );

			//pt::ipmessage *client = new pt::ipmessage(srv->get_ip(),srv->get_port() );

			jq.post( new CRecvJob(srv, buffer ) );
		}
		catch(pt::estream* e)
		{
			pt::perr.putf("Client error: %s\n", pconst(e->get_message()));
			delete e;
			quit = true;
			mRunning = false;
		}

	} while (!quit);

	delete connectionGuard;

	delete serversMgr;
}

}
}
