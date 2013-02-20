#include <pinet.h>
#include <pasync.h>

#include "../utility/LogManager.h"
#include "../utility/ToString.h"
#include "../net/ConnectionGuard.h"
#include "../asn1/ASN1Serializer.h"

#include "../net/Payload.h"
//#include "APConnect.h"

#include <algorithm>

//#define USING_PTYPES = 0;

#include "ClientNetworking.h"
#include "ClientSimulation.h"

#include "InteractiveShell.h" // shell
#include "CommandInterpreter.h" // shell

class CSingletonDestroyer
{
public:
	CSingletonDestroyer()
	{
		utility::LogManager::getSingletonPtr()->createLog( "thar-client.log" );
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
	pt::ipmessage *msg = new pt::ipmessage( pt::ipaddress(127, 0, 0, 1), serverport);

	for( int x = 0; x<3000; ++x)
	{

	annatar::net::CPayload *payload;
	payload = new annatar::net::CPayload();

	annatar::net::CPConnect *pconnect =
		new annatar::net::CPConnect( 1, "Tom");
	payload->addConnect( pconnect );
	delete pconnect;

	COctetBuffer *buf = payload->serialize();
	payload->clear();

	msg->send( buf->buf, buf->size );

	cout << buf->size << endl;
	cout << utility::dumpBinary(buf->buf,buf->size);
	cout << endl;

	pt::psleep( 500 );
	msg->waitfor(-1);

	COctetBuffer *buffer = new COctetBuffer();
	buffer->size = msg->receive( buffer->buf, maxtoken );
//	pt::ipmessage *client = new pt::ipmessage(srv->get_ip(),srv->get_port() );
	cout <<	utility::dumpBinary( buffer->buf, buffer->size );

//	pt::ipaddress src;
//	std::string rsp = msg->receive(maxtoken, src);
//	cout <<	utility::dumpBinary( (char *)rsp.c_str(), (int)rsp.size() );
//	pt::pout.putf("Received from %a:\n", long(src));

	system("PAUSE");

}

	delete msg;
*/


	//pt::ipmessage *server = new pt::ipmessage(pt::ipbcast, serverport);
	pt::ipmessage *server =
		new pt::ipmessage( pt::ipaddress(127, 0, 0, 1), 8045 );
	
	annatar::sim::CClientSimulation *simulation =
		new annatar::sim::CClientSimulation();
	
	annatar::net::CClientNetworking *clientNetworking =
		new annatar::net::CClientNetworking( server, simulation );
	clientNetworking->start();

	//simulation->start();
/*	while (1)
	{
		pt::psleep( 500 );
		
		if ( !clientNetworking->isRunning() )
		{
			//delete clientNetworking;
			//delete simulation;
			break;
		}
	}
*/

	pt::psleep( 2500 );

	CInteractiveShell *shell = new CInteractiveShell();
	CCommandInterpreter *interpreter =
		new CCommandInterpreter( clientNetworking->serversMgr, clientNetworking->server );

	while ( clientNetworking->isRunning() )
	{
		shell->printPrompt();
		
		if ( shell->readCommand() )
		{
			if ( shell->hasCommand() )
			{
				std::cout << "PROCESS: ";
				interpreter->process( shell->consume() );
				std::cout << endl;
			}
		}
		else
		{
			break;
		}
	}


//	clientNetworking->execute();

/*	while (connected)
	{
		try
		{
			pt::pout.put("Broadcasting a request...\n");
			//msg->send("Hello");

			pt::psleep( 1000 );

			// wait for a response the specified amount of time
			if (!msg->waitfor(timeout))
				break;
				//return false;

			pt::ipaddress src;
			pt::string rsp = msg->receive(maxtoken, src);
			pt::pout.putf("Received: '%s' (from %a)\n", pt::pconst(rsp), long(src));
		}
		catch(pt::estream* e)
		{
			pt::perr.putf("Error: %s\n", pt::pconst(e->get_message()));
			delete e;
		}
	}
*/

	return 0;
}