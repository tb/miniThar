#include "ServerNetworking.h"

#include "../net/Services.h"
#include "ServerServant.h"

namespace annatar {
namespace net
{

void CServerNetworking::execute()
{
	using namespace pt;

	std::cout << "\n -= CServerNetworking->execute() =-\n" << std::endl;

	try
	{
		srv.bindall(serverport);
		srv.poll();
	}
	catch(pt::estream* e)
	{
		pt::perr.putf("FATAL: %s\n", pt::pconst(e->get_message()));
		delete e;
	}

	jobqueue jq;
	tobjlist<CServerServant> threads(true);

	annatar::net::CNodesManager *clientMgr =
		new annatar::net::CNodesManager( new annatar::sim::CServerSimulation(), &jq );

	for(int i = 0; i < 3; ++i)
	{
		CServerServant* j = new CServerServant(i + 1, &jq, clientMgr);
		j->start();
		threads.add(j);
	}

	std::cout << "Ready to answer queries on port " << serverport << std::endl;;
	
	bool quit = false;
	do
	{
		try
		{		
			COctetBuffer *buffer = new COctetBuffer();
			buffer->size = srv.receive( buffer->buf, maxtoken );

			pt::ipmessage *client = new pt::ipmessage(srv.get_ip(),srv.get_port() );

			jq.post( new CRecvJob(client, buffer ) );
		}
		catch(pt::estream* e)
		{
			pt::perr.putf("Client error: %s\n", pconst(e->get_message()));
			delete e;
		}

	} while (!quit);

	delete clientMgr;
}

}
}
