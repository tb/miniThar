#ifndef __ANNATAR_NETWORKINGNODE_H__
#define __ANNATAR_NETWORKINGNODE_H__

#include "../simulation/SimObserver.h"
#include "../simulation/SimSubject.h"

#include "../net/IncomingADUFilter.h"
#include "../net/OutputPayloadBuffer.h"
#include "../net/NetworkRecorder.h"

#include "../utility/ToString.h"

#include <pinet.h>
#include <pasync.h>

namespace annatar {
namespace net
{

class CNetworkingNode : public annatar::sim::CSimSubject, public annatar::sim::CSimObserver
{
protected:
	pt::jobqueue *mJobQueue;
	CIncomingADUFilter *mIncomingADUFilter;
	COutputPayloadBuffer *mOutputPayloadBuffer;
	CNetworkRecorder *mNetworkRecorder;

	int id;
	pt::ipaddress ip;
	pt::ipmessage *mNodeAddress;
	int port;

	int mLastSequenceNumber;

protected:
	pt::jobqueue* getJobQueue() { return mJobQueue; }

public:
	CNetworkingNode( pt::ipmessage *ipMsg, pt::jobqueue* jq  )
	{
		id = 0;
		mLastSequenceNumber = 0;
		mNodeAddress = ipMsg;
		ip = ipMsg->get_ip();
		port = ipMsg->get_port();
		mJobQueue = jq;
		mIncomingADUFilter = new CIncomingADUFilter();
		mOutputPayloadBuffer = new COutputPayloadBuffer();
		mNetworkRecorder = new CNetworkRecorder();
	}

	virtual ~CNetworkingNode()
	{
		delete mIncomingADUFilter;
		delete mOutputPayloadBuffer;
		delete mNetworkRecorder;
	}

	inline bool operator == ( const CNetworkingNode& rkClient ) const
	{
		return ( (id == rkClient.id) &&
			(ip == rkClient.ip) && 
			(port == rkClient.port) );
	}

	inline bool operator != ( const CNetworkingNode& rkClient ) const
	{
		return ( (id != rkClient.id) ||
			(ip != rkClient.ip) ||
			(port != rkClient.port) );
	}

	inline bool operator < ( const CNetworkingNode& rhs ) const
	{
		if( (id < rhs.id) && (ip < rhs.ip) && (port < rhs.port) )
			return true;
		return false;
	}

	int acquireSequenceNumber();
	int getSequenceNumber();
	CNetworkRecorder* getNetworkRecorder();

	void broadcast( CPayload* payload );
	void rebroadcast( std::vector<int> missingSeq );

	virtual void process( CPayload *payload ) = 0;
	
	virtual void update(annatar::sim::CSimSubject* sub, annatar::sim::CSimEvent* e) = 0;

	std::string toString();
};

}
}

#endif