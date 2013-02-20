#include "NetworkingNode.h"

#include "Services.h"  // CSendJob

namespace annatar {
namespace net
{

int CNetworkingNode::acquireSequenceNumber()
{		
	return ++mLastSequenceNumber;
}

int CNetworkingNode::getSequenceNumber()
{
	return mLastSequenceNumber;
}

CNetworkRecorder* CNetworkingNode::getNetworkRecorder()
{
	return mNetworkRecorder;
}

void CNetworkingNode::broadcast( CPayload* payload )
{
	mNetworkRecorder->recordBroadcast( payload );

	COctetBuffer *buf = payload->serialize();

	mOutputPayloadBuffer->append( payload );

	mNodeAddress = mNodeAddress;

	getJobQueue()->post( new CSendJob(
		mNodeAddress, buf ) );
}

void CNetworkingNode::rebroadcast( std::vector<int> missingSeq )
{
	std::vector<CPayload*> payloadVec;
	std::vector<CPayload*>::iterator itr;
	payloadVec = mOutputPayloadBuffer->getPayloadSequence( missingSeq );

	for (itr = payloadVec.begin(); itr != payloadVec.end(); ++itr)
	{
		mNetworkRecorder->recordRebroadcast( *itr );

		COctetBuffer *buf = ((CPayload*)(*itr))->serialize();

		getJobQueue()->post( new CSendJob(
			new pt::ipmessage( ip, port ), buf ) );
	}
}

std::string CNetworkingNode::toString()
{
	using namespace pt;
	std::stringstream desc;
	char buf[16];

	snprintf(buf, sizeof(buf), "%d.%d.%d.%d",
		uint(ip.data[0]), uint(ip.data[1]),
		uint(ip.data[2]), uint(ip.data[3]));

	desc << "Id: " << id;
	desc << ", Ip: " << buf;
	desc << ", Port: " << port;

	return desc.str();
}

}
}
