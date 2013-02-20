#include "Client.h"

namespace annatar {
namespace net
{

void CClient::update(annatar::sim::CSimSubject* sub, annatar::sim::CSimEvent* e)
{
	std::stringstream desc;
	desc << e->getEventType();

	utility::LogManager::getSingletonPtr()->logMessage(
		"CClient::update - event " + desc.str() );
}

void CClient::process( CPayload *payload )
{
	mIncomingADUFilter->append( payload );

	//std::list<CPADU*> *lista = payload->getAll();
	std::list<CPADU*> *lista = mIncomingADUFilter->getADUSequence();
	
//	cout << "\nCClient::process(), przetworzy ";
//	cout << (int)lista->size() << " CPADU*.\n";

	std::list<CPADU*>::iterator itr;
	for (itr = lista->begin(); itr != lista->end(); ++itr)
	{
		if ( (*itr)->mType == APData_PR_missingSeq )
		{
			// tu trzeba ponownie wyslac konkretne paczki
			rebroadcast( ((CPMissingSeq*)(*itr))->mMissingSeq );
		}
		if ( (*itr)->mType == APData_PR_tick )
		{
			CPTick* tick = (CPTick*)(*itr);
			// nic
		}
		if ( (*itr)->mType == APData_PR_connect )
		{
			CPConnect* connect = (CPConnect*)(*itr);
			/*
			annatar::sim::CSimEvent* ev = new annatar::sim::CSimEvent();
			ev->setEvent( annatar::sim::CSimEvent::Null, connect ); 
			notify( ev );
			delete ev;
			*/
			CPayload *payload2 = new CPayload();

			CPPhrase *pphrase =
				new CPPhrase( acquireSequenceNumber(), "Phrase");
			payload2->addPhrase( pphrase );
			delete pphrase;

			broadcast( payload2 );
		}
	}
	delete lista;
}

}
}