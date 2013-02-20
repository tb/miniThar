#ifndef __ANNATAR_NODESMANAGER_H__
#define __ANNATAR_NODESMANAGER_H__

#include <pinet.h>
#include <pasync.h>

#include <list>

#include "../simulation/Simulation.h"
#include "NetworkingNode.h"

namespace annatar {
namespace net
{

class CNodesManager
{
private:
	pt::rwlock mAddressSetLock;
//	pt::rwlock mEtherLock;

	std::list<CNetworkingNode*> mAddressSet; //std::set<CServer> mAddressSet; 
	annatar::sim::CSimulation *mSimulation;
	pt::jobqueue* mJobQueue;

public:
	CNodesManager( annatar::sim::CSimulation *simulation, pt::jobqueue* jq );
	virtual ~CNodesManager();

	void add( CNetworkingNode *adr );
	void remove( CNetworkingNode *adr );
	//bool has( CServer *adr );

	CNetworkingNode* acquire( CNetworkingNode *node );

	annatar::sim::CSimulation* getSimulation()
	{
		return mSimulation;
	}
	
	pt::jobqueue* getJobQueue()
	{
		return mJobQueue;
	}

	std::string toString();
};

}
}

#endif