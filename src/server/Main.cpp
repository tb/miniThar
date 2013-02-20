#include <ptime.h>
#include <pinet.h>
#include <pasync.h>

#include "../net/Services.h"
//#include "../net/ClientsManager.h"

#include "../asn1/NetSerializer.h"
#include "../asn1/DBaseSerializer.h"

#include "ServerServant.h"

#include "ServerNetworking.h"

//#include "Simulation.h"

//USING_PTYPES

#include "../net/IncomingADUFilter.h"
#include "../net/OutputPayloadBuffer.h"
#include "../utility/ToString.h"
#include <vector>


//const int testport = 8085;

/*
void servermain(pt::ipmsgserver& svr)
{
	using namespace pt;

	jobqueue jq;
	tobjlist<CServerServant> threads(true);
	
	annatar::net::CClientsManager *clientMgr =
		new annatar::net::CClientsManager( &jq );

	// create the thread pool
	int i;
	for(i = 0; i < 16; i++)
	{
		CServerServant* j = new CServerServant(i + 1, &jq, clientMgr);
		j->start();
		threads.add(j);
	}

	pout.putf("Ready to answer queries on port %d\n", serverport);
	bool quit = false;
	do
	{
		try
		{		
			COctetBuffer *buffer = new COctetBuffer();
			buffer->size = svr.receive( buffer->buf, maxtoken ); 

			pt::ipmessage *client = new pt::ipmessage(svr.get_ip(),svr.get_port() );

			jq.post( new CRecvJob(client, buffer ) );
		}
		catch(pt::estream* e)
		{
			pt::perr.putf("Server error: %s\n", pconst(e->get_message()));
			delete e;
		}

	} while (!quit);

	delete clientMgr;
}
*/

class CSingletonDestroyer
{
public:
	CSingletonDestroyer()
	{
		utility::LogManager::getSingletonPtr()->createLog( "thar-server.log" );
	}

	~CSingletonDestroyer()
	{
		utility::LogManager::removeSingleton();
#ifdef PLAYERUPDATER
		annatar::net::CPlayerUpdater::removeSingleton();
#endif
	}
};



int main()
{
	CSingletonDestroyer autoDestroyer;
/*
	// ---------========== POCZATEK TESTU ETHER ==========----------------
	{
		using namespace annatar::net;

		pt::ipmessage* xxx = new pt::ipmessage();

		CClient* c1 = new CClient( xxx );
		CClient* c2 = new CClient( xxx );
		CSimulation* eth = new CSimulation();

		CSimulationEvent* ev = new CSimulationEvent();
		ev->setEvent( CSimulationEvent::Connect, 0 );
		c1->attach( eth );
		c2->attach( eth );

		c2->notify( ev );
		ev->setEvent( CSimulationEvent::Close, 0 );
		c2->notify( ev );

	}
	// ---------========== KONEC TESTU ETHER ==========----------------
*/
	
/*
	// ---------========== POCZATEK TESTU LOGOW ==========----------------
	try
	{
		std::stringstream desc;
		desc << "Jakas informacja o bledzie";
		throw utility::BaseException( ERROR_MSG( desc.str() ) );
	}
	catch ( utility::BaseException e )
	{
		std::cout << e.getMessage() << std::endl;
		utility::LogManager::getSingletonPtr()->logMessage( e.getMessage() );
	}
	// ---------========== KONEC TESTU LOGOW ==========----------------

	// ---------========== POCZATEK TESTU ASN1C ==========----------------
	std::stringstream desc;
	desc << "Test serializacji gracza:";

	annatar::CPlayer *player = new annatar::CPlayer(
		Ogre::Vector3(100,100,100),Ogre::Radian(10), "Player1" );

	COctetBuffer *buffer = annatar::NetSerializer::serialize( player );

	annatar::CPlayer *newPlayer = new annatar::CPlayer(
		Ogre::Vector3(0,0,0),Ogre::Radian(0), "noname" );
	desc << "\nnewPlayer->getName() przed deserializacja: " << newPlayer->getName();

	annatar::NetSerializer::deserialize( buffer, newPlayer);
	desc << "\nnewPlayer->getName() po deserializacji: " << newPlayer->getName();

	utility::LogManager::getSingletonPtr()->logMessage( desc.str() );
	// ---------========== KONEC TESTU ASN1C ==========----------------
*/

	//pt::ipmessage *server = new pt::ipmessage(pt::ipbcast, 8085);
	annatar::sim::CServerSimulation *simulation = new annatar::sim::CServerSimulation();

	annatar::net::CServerNetworking *serverNetworking =
		new annatar::net::CServerNetworking( simulation );
	serverNetworking->start();

	//simulation->start();
	pt::psleep( -1 );

/*
	pt::ipmsgserver svr;

	try
	{
		svr.bindall(serverport);

		// try to listen on socket once to generate an error right away,
		// before entering the main server loop
		svr.poll();

		// enter an infinite loop of serving requests
		servermain(svr);
	}
	catch(pt::estream* e)
	{
		pt::perr.putf("FATAL: %s\n", pt::pconst(e->get_message()));
		delete e;
	}
*/

/*
	using namespace annatar::net;

	CPayload *payload = new CPayload();
	CPayload *payload2 = new CPayload();
	CPayload *payload3 = new CPayload();
	CPayload *payload4 = new CPayload();
	CPayload *payload199 = new CPayload();
	CIncomingADUFilter *adubuf = new CIncomingADUFilter();
	std::list<CPADU*> *lista;

	payload->addTick( new CPTick( 1, 122, 111) );
	payload->addConnect( new CPConnect(1, "Tom") );
	payload->addConnect( new CPConnect(2, "Tom") );
	adubuf->append( payload->getAll() );

	payload->addConnect( new CPConnect(3, "Tom") );
	adubuf->append( payload->getAll() );

	COutputPayloadBuffer *outbuf = new COutputPayloadBuffer();
	outbuf->append( payload, 3 );


	payload2->addTick( new CPTick( 3, 122, 111) );
	outbuf->append( payload2, 3 );
	adubuf->append( payload2->getAll() );

	payload3->addConnect( new CPConnect(5, "Tom") );
	payload3->addConnect( new CPConnect(10, "Tom") );
	outbuf->append( payload3, 10 );
	adubuf->append( payload3->getAll() );

	//outbuf->consume( 1 );
	//CPayload *pl = outbuf->getPayload( 4 );
	
	//if ( pl != NULL ) {
	//	std::cout << pl->toString();
	//	lista = adubuf->getADUSequence();
	//	std::cout << "lista ma dlugosc: " << lista->size() << std::endl;
	//}

//	adubuf->append( payload199->getAll() );

	lista = adubuf->getADUSequence();
	std::cout << "lista ma dlugosc: " << lista->size() << std::endl;


	std::vector<int> vec = adubuf->getMissingSequence();
	int size = vec.size();
	payload4->addMissingSeq( new CPMissingSeq( 9, vec ) );

	COctetBuffer *buf = payload4->serialize();
	std::string str =
		utility::dumpBinary( buf->buf, buf->size, 10 );
	std::cout << str << std::endl;
	payload199 = new CPayload( buf );

	outbuf->getPayloadSequence( vec );
*/
	std::cout << "Koniec dzialania servera!!!" << std::endl;
	system("PAUSE");

	return 0;
}