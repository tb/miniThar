#ifndef __ANNATAR_COMMANDINTERPRETER_H__
#define __ANNATAR_COMMANDINTERPRETER_H__

#include <iostream>
#include <string>

#include "../net/Payload.h"
#include "../net/NodesManager.h"

class CCommandInterpreter
{
private:
	annatar::net::CPayload *mPayload;
	annatar::net::CNodesManager *mMgr;
	annatar::net::CNetworkingNode *mNode;

public:
	CCommandInterpreter( annatar::net::CNodesManager *mgr, annatar::net::CNetworkingNode *node );
	virtual ~CCommandInterpreter(void);
	
	void process( std::string line );
	void flush();
};

#endif
