#ifndef __ANNATAR_SERVERNETWORKING_H__
#define __ANNATAR_SERVERNETWORKING_H__

#include <pinet.h>
#include <pasync.h>

#include "ServerSimulation.h"

namespace annatar {
namespace net
{

class CServerNetworking : public pt::thread
{
protected:
	pt::ipmsgserver srv;
	annatar::sim::CServerSimulation *mSimulation;

	virtual void execute();
public:
	CServerNetworking( annatar::sim::CServerSimulation *simulation )
		: pt::thread(false)
	{
		mSimulation = simulation;
	}
	
	~CServerNetworking()
	{
		waitfor();
	}
};
}
}

#endif
