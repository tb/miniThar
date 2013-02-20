#ifndef __ANNATAR_CLIENTNETWORKING_H__
#define __ANNATAR_CLIENTNETWORKING_H__

#include <pinet.h>
#include <pasync.h>

#include "ClientSimulation.h"
#include "../net/NodesManager.h"
#include "Server.h"

namespace annatar {
namespace net
{

class CClientNetworking : public pt::thread
{
protected:
	pt::ipmessage *srv;
	annatar::sim::CClientSimulation *mSimulation;
	bool mRunning;

	virtual void execute();
public:
	annatar::net::CNodesManager *serversMgr;
	CNetworkingNode* server;

	CClientNetworking( pt::ipmessage *server, annatar::sim::CClientSimulation *simulation )
		: pt::thread(false)
	{
		mSimulation = simulation;
		srv = server;
		running = false;
	}

	~CClientNetworking()
	{
		waitfor();
	}

	bool isRunning()
	{
		return mRunning;	
	}
};
}
}

#endif
