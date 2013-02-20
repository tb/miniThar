#include "ClientServant.h"

#include "../net/Services.h"
#include "../net/Payload.h"
#include "../utility/ToString.h"

#include "../simulation/SimEvent.h"

#include "Server.h"

void CClientServant::execute()
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

					CServer *server = (CServer *)serverMgr->acquire(
						new CServer( nodeAddress, serverMgr->getJobQueue() ) );

					CPayload *payload = new CPayload( buffer );

					server->getNetworkRecorder()->recordRecv( payload );
					server->process( payload );

					//cout << endl << serverMgr->toString() << endl;
				}
				break;

			case MSG_SENDJOB:
				{
					cout << "--->> MSG_SENDJOB --->>\n";
					ipmessage *nodeAddress = ((CSendJob*)msg)->mClient;
					COctetBuffer *buffer = ((CSendJob*)msg)->mBuf;
					
					//cout << "((CSendJob*)msg)->mClient port: " << nodeAddress->get_port();

					nodeAddress->send( buffer->buf, buffer->size );
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