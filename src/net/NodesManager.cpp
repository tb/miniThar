#include "NodesManager.h"

//#include "../utility/LogManager.h"

#include <sstream>
#include <algorithm>

namespace annatar {
namespace net
{
	CNodesManager::CNodesManager( annatar::sim::CSimulation *simulation, pt::jobqueue* jq )
	{
		mJobQueue = jq;
		mSimulation = simulation;
	}

	CNodesManager::~CNodesManager()
	{
		delete mSimulation;
	}

	void CNodesManager::add( CNetworkingNode *client )
	{
		client->attach( mSimulation );
		mSimulation->attach( client );

		mAddressSetLock.wrlock();
		mAddressSet.push_back( client );
		mAddressSetLock.unlock();
	}

	void CNodesManager::remove( CNetworkingNode *client )
	{
		std::list<CNetworkingNode*>::iterator itr;

		//mAddressSetLock.rdlock();
		for (itr = mAddressSet.begin(); itr != mAddressSet.end(); ++itr)
		{
			if ( *(*itr) == *client )
			{
				mAddressSetLock.wrlock();
				delete (CNetworkingNode *)(*itr);
				mAddressSet.erase( itr );
				mAddressSetLock.unlock();
				break;
			}
		}
	}

/*	bool CNodesManager::has( CServer *adr )
	{
		mAddressSetLock.rdlock();
		bool ret =
			(find(mAddressSet.begin(), mAddressSet.end(), *adr) != mAddressSet.end());
		mAddressSetLock.unlock();

		return ret;
	}
*/
	CNetworkingNode* CNodesManager::acquire( CNetworkingNode *node )
	{
		std::list<CNetworkingNode*>::iterator itr;
		mAddressSetLock.rdlock();
		for (itr = mAddressSet.begin(); itr != mAddressSet.end(); ++itr)
		{
			if ( *(*itr) == *node )
			{
				break;
			}
		}
		mAddressSetLock.unlock();

		if ( itr == mAddressSet.end() )
		{
			add( node );
			return node;
		}
		else
		{
			delete node;
			return (CNetworkingNode*)(*itr);
		}
	}

	std::string CNodesManager::toString()
	{
		using namespace pt;

		std::list<CNetworkingNode*>::iterator itr;
		std::stringstream desc;

		for (itr = mAddressSet.begin(); itr != mAddressSet.end(); ++itr)
		{
			desc << (*itr)->toString();
			desc << "\n";
		}

		return desc.str();
	}
}
}
