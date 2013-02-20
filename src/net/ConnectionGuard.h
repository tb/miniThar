#ifndef __ANNATAR_CONNECTIONGUARD_H__
#define __ANNATAR_CONNECTIONGUARD_H__

#include "NetworkingNode.h"

#include <pinet.h>
#include <pasync.h>

namespace annatar {
namespace net
{
	class CConnectionGuard : public pt::thread
	{
	protected:
		annatar::net::CNetworkingNode *mNetworkingNode;

		virtual void execute();

	public:
		CConnectionGuard( annatar::net::CNetworkingNode *node )
			: pt::thread(false), mNetworkingNode(node)
		{
		}
		
		~CConnectionGuard()
		{
			waitfor();
		}
	};
}
}

#endif
