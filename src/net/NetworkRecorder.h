#ifndef __ANNATAR_NETWORKRECORDER_H__
#define __ANNATAR_NETWORKRECORDER_H__

#include "Payload.h"

//#include "../utility/Log.h"

//#include <pinet.h>
//#include <pasync.h>

namespace annatar {
namespace net
{

class CNetworkRecorder
{
private:
	//utility::Log *mLog;

public:
	CNetworkRecorder();
	virtual ~CNetworkRecorder();

	void recordBroadcast( CPayload* payload );
	void recordRebroadcast( CPayload* payload );
	void recordRecv( CPayload* payload );
};

}
}

#endif