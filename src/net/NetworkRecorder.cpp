#include "NetworkRecorder.h"

#include "../utility/ToString.h"

namespace annatar {
namespace net
{

CNetworkRecorder::CNetworkRecorder()
{
	
}

CNetworkRecorder::~CNetworkRecorder()
{

}

//	"00:00	Client asdfsadf sdaf"
//  "<<---	seq: xx		type: Connect"
//  "		0x99 0x99 0x99 ..."
//	"00:00	Client asdfsadf sdaf"
//  "--->>	seq: xx		type: Connect"
//  "		0x99 0x99 0x99 ..."

void CNetworkRecorder::recordBroadcast( CPayload* payload )
{
	std::stringstream desc;

	COctetBuffer *buffer = payload->serialize();
	desc << "--->>\t" << "Payload size: " << buffer->size;
	desc << " contains:" << payload->toString() << "\n";
	desc << utility::dumpBinary( buffer->buf, buffer->size, 10 ) << "\n\n";
	cout << desc.str();
}

void CNetworkRecorder::recordRebroadcast( CPayload* payload )
{
	std::stringstream desc;

	COctetBuffer *buffer = payload->serialize();
	desc << "->>>>\t" << "Payload size: " << buffer->size;
	desc << " contains:" << payload->toString() << "\n";
	desc << utility::dumpBinary( buffer->buf, buffer->size, 10 ) << "\n\n";
	cout << desc.str();
}

void CNetworkRecorder::recordRecv( CPayload* payload )
{
	std::stringstream desc;

	COctetBuffer *buffer = payload->serialize();
	desc << "<<---\t" << "Payload size: " << buffer->size;
	desc << " contains:" << payload->toString() << "\n";
	desc << utility::dumpBinary( buffer->buf, buffer->size, 10 ) << "\n\n";
	cout << desc.str();
}

}
}
