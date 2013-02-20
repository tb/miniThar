#include "ServerServant.h"

#include "../net/Services.h"
#include "../net/Payload.h"
#include "../utility/ToString.h"

#include "../simulation/SimEvent.h"

#include "Client.h"

void CServerServant::execute()
{
	using namespace pt;
	using namespace annatar;
	using namespace annatar::net;

	bool quit = false;
	while (!quit)
	{
		// get the next message from the queue
		message* msg = jq->getmessage();

		try
		{
			switch (msg->id)
			{
			case MSG_RECVJOB:
				{
					cout << "<<--- MSG_RECVJOB <<---\n";
					ipmessage *nodeAddress = ((CRecvJob*)msg)->mClient;
					COctetBuffer *buffer = ((CRecvJob*)msg)->mBuf;

					//std::string str =
					//	utility::dumpBinary( buffer->buf, buffer->size, 10 );

					CClient *client = (CClient *)clientMgr->acquire(
						new CClient( nodeAddress, clientMgr->getJobQueue() ) );
					
					//cout << client->toString() << ""
					//<< " job from Service.cpp:\n" << str << "\n";

					CPayload *payload = new CPayload( buffer );
					
					client->getNetworkRecorder()->recordRecv( payload );
					client->process( payload );

					cout << endl << clientMgr->toString() << endl;
				}
				break;

			case MSG_SENDJOB:
				{
					cout << "--->> MSG_SENDJOB --->>\n";
					ipmessage *client = ((CSendJob*)msg)->mClient;
					COctetBuffer *buffer = ((CSendJob*)msg)->mBuf;

					try
					{
						client->send( buffer->buf, buffer->size );
					}
					catch(pt::estream* e)
					{
						pt::perr.putf("Error: %s\n", pt::pconst(e->get_message()));
						delete e;
					}
				}
				break;

			case MSG_QUIT:
				// MSG_QUIT is not used in our example
				quit = true;
				break;
			}
		}
		catch(pt::exception*)
		{
			// the message object must be freed!
			delete msg;
			throw;
		}

		delete msg;
	}
}
/*
void CServerServant::deleteMessage( pt::message* msg )
{
switch (msg->id)
{
case MSG_RECVJOB:
delete (CRecvJob*)msg;
break;

case MSG_SENDJOB:
delete (CSendJob*)msg;
break;
}
}
*/