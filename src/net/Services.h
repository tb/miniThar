#ifndef __ANNATAR_SERVICES_H__
#define __ANNATAR_SERVICES_H__

#include <ptime.h>
#include <pasync.h>
#include <pinet.h>

#include "../utility/OctetBuffer.h"
//#include "../server/ClientManager.h"





const int clientport = 4005;
const int serverport = 8045;

const int tries = 30;
const int firsttimeout = 2000;



//const int maxthreads = 30;
const int maxtoken = 4096;


const int MSG_RECVJOB = pt::MSG_USER + 1;
const int MSG_SENDJOB = pt::MSG_USER + 2;

class CRecvJob: public pt::message
{
public:
	COctetBuffer *mBuf;
	pt::ipmessage *mClient;

	CRecvJob(pt::ipmessage *client, COctetBuffer *buf)
		: pt::message(MSG_RECVJOB), mClient(client), mBuf(buf)
	{
	}

	virtual ~CRecvJob(){
		delete mBuf;
		//delete mClient;
	}
};

class CSendJob: public pt::message
{
public:
	COctetBuffer *mBuf;
	pt::ipmessage *mClient;

	CSendJob(pt::ipmessage *client, COctetBuffer *buf)
		: pt::message(MSG_SENDJOB), mClient(client), mBuf(buf)
	{
	}

	virtual ~CSendJob(){
		//delete mClient;
		delete mBuf;
	}
};

#endif
