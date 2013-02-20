#ifndef __ANNATAR_CLIENT_H__
#define __ANNATAR_CLIENT_H__

#include "../net/NetworkingNode.h"

#include <pinet.h>
#include <pasync.h>

namespace annatar {
namespace net
{

class CClient : public annatar::net::CNetworkingNode
{
public:
	CClient( pt::ipmessage *ipMsg, pt::jobqueue *jq  )
		: annatar::net::CNetworkingNode( ipMsg, jq )
	{
	}

	virtual ~CClient()
	{
	}

	void update( annatar::sim::CSimSubject* sub, annatar::sim::CSimEvent* e );
	void process( CPayload *payload );
};

}
}

#endif