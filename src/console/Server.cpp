#include "Server.h"

namespace annatar {
namespace net
{

void CServer::update(annatar::sim::CSimSubject* sub, annatar::sim::CSimEvent* e)
{
	std::stringstream desc;
	desc << e->getEventType();

	utility::LogManager::getSingletonPtr()->logMessage(
		"CServer::update - event " + desc.str() );
}

void CServer::process( CPayload *payload )
{
	mIncomingADUFilter->append( payload );

	std::list<CPADU*> *lista =  mIncomingADUFilter->getADUSequence(); //payload->getAll();

	std::list<CPADU*>::iterator itr;
	for (itr = lista->begin(); itr != lista->end(); ++itr)
	{
		if ( (*itr)->mType == APData_PR_missingSeq )
		{
			// tu trzeba ponownie wyslac konkretne paczki
			rebroadcast( ((CPMissingSeq*)(*itr))->mMissingSeq );
		}
		if ( (*itr)->mType == APData_PR_connect )
		{
			CPConnect* connect = (CPConnect*)(*itr);
			/*
			annatar::sim::CSimEvent* ev = new annatar::sim::CSimEvent();
			ev->setEvent( annatar::sim::CSimEvent::Connect, connect ); 
			notify( ev );
			delete ev;
			*/
		}
	}
	delete lista;

/*	payload->clear();
	payload = new CPayload();

	CPPhrase *pphrase =
		new CPPhrase( acquireSequenceNumber(), "Phrase");
		//new CPPhrase( 2, "Phrase");
	payload->addPhrase( pphrase );
	delete pphrase;

	broadcast( payload );
*/
}

}
}