#ifndef __ANNATAR_SERVERSERVANT_H__
#define __ANNATAR_SERVERSERVANT_H__

#include <ptime.h>
#include <pasync.h>
#include <pinet.h>

#include "../utility/OctetBuffer.h"
#include "../net/NodesManager.h"

//const int maxthreads = 30;
//const int maxtoken = 4096;

//const int MSG_RECVJOB = pt::MSG_USER + 1;
//const int MSG_SENDJOB = pt::MSG_USER + 2;


class CServerServant: public pt::thread
{
protected:
	int id;
	pt::jobqueue* jq;
	annatar::net::CNodesManager *clientMgr;

	virtual void execute();
	//void deleteMessage( pt::message* msg );

public:
	CServerServant(int iid, pt::jobqueue* ijq, annatar::net::CNodesManager *clMgr )
		: pt::thread(false), id(iid), jq(ijq), clientMgr(clMgr)
	{
	}
	virtual ~CServerServant()
	{
		waitfor();
	}
};

#endif