#ifndef __ANNATAR_SERVER_H__
#define __ANNATAR_SERVER_H__

#include "../net/NetworkingNode.h"

#include <pinet.h>
#include <pasync.h>

namespace annatar {
namespace net
{

class CServer : public annatar::net::CNetworkingNode
{
public:
	CServer( pt::ipmessage *ipMsg, pt::jobqueue* jq  )
		: annatar::net::CNetworkingNode( ipMsg, jq )
	{
	}

	virtual ~CServer()
	{
	}

	virtual void update( annatar::sim::CSimSubject* sub, annatar::sim::CSimEvent* e );
	void process( CPayload *payload );
};

}
}

#endif