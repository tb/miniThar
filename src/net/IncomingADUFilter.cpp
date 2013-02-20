#include "IncomingADUFilter.h"

namespace annatar {
namespace net
{

	CIncomingADUFilter::CIncomingADUFilter()
	{
		mADUList = new std::list<CPADU*>;
		curSeq = 0;
	}

	CIncomingADUFilter::~CIncomingADUFilter()
	{
		delete mADUList; // zle bo nie usuwam zawartosi ##FIXME##
	}

	// dolacza i sortuje
	void CIncomingADUFilter::append( CPayload *payload )
	{
		int seq = 0;
		seq = payload->getMaxSeq();
		if ( seq > curSeq )
		{
			curSeq = seq;
		}

		std::list<CPADU*> *lista = payload->getAll();
		std::list<CPADU*>::iterator itr;
		for (itr = lista->begin(); itr != lista->end(); ++itr)
		{
			mADUList->push_back( *itr );
			//cout << "\ndodaje do mADUList\n";
		}

		//cout << "\nCIncomingADUFilter::append(), dodalo ";
		//cout << (int)lista->size() << " CPADU* do mADUList.\n";

		//mADUList->merge( *lista );
		mADUList->sort( CPADUSortCriterion() );
	}

	// zwraca do przetwarzania
	std::list<CPADU*>* CIncomingADUFilter::getADUSequence()
	{
		std::list<CPADU*> *lista = new std::list<CPADU*>;

		if ( mADUList->size() == 0 )
		{
			//cout << "\nCIncomingADUFilter::getADUSequence(), RETURN NULL";
			return lista;
		}

		std::list<CPADU*>::iterator itr;
		for (itr = mADUList->begin(); itr != mADUList->end();)
		{
			//cout << "\nCIncomingADUFilter::getADUSequence(), for loop1 =";
			//cout << (*itr)->mSeq << "=" << curSeq;
			if ( (*itr)->mSeq < curSeq )
			{
				if ( !CPayload::isSequenceTrigger( (*itr)->mType ) )
				{
					if ( (( curSeq - (*itr)->mSeq ) == 1) ||
						( curSeq == (*itr)->mSeq ) )
					{
						//cout << "\ndodaj do zworcenia";
						// dodaj do zworcenia
						lista->push_back( *itr );
						mADUList->erase( itr );
						itr = mADUList->begin();
					}
					continue;
				}
				else
				{
					//cout << "\nusun totalnie";
					// usun totalnie
					delete *itr;
					mADUList->erase( itr );
					itr = mADUList->begin();
					continue;
				}
			}
			else if ( (*itr)->mSeq == curSeq )
			{
				if ( CPayload::isSequenceTrigger( (*itr)->mType ) )
				{
					curSeq += 1;
				}

				// dodaj do zworcenia
				lista->push_back( *itr );
				mADUList->erase( itr );
				itr = mADUList->begin();

				continue;
			}
			else
			{
				//missingSeq = true;
				break;	// lista jest posortowana wg seq, jak za duzy
				// to nie ma juz sensu sprawdzanie
			}
		}

		// kontynacja petli majaca na celu wypelnienie vektora
		// brakujacych pakietow mMissingSeq

		int missSeq = curSeq+1; // ##FIXME## to moze byc ZLE
		
		for ( mMissingSeq.clear(); itr != mADUList->end(); ++itr )
		{
			//cout << "CIncomingADUFilter::getADUSequence(), for loop2";
			if ( CPayload::isSequenceTrigger( (*itr)->mType ) )
			{	
				if ( (*itr)->mSeq > missSeq )
				{
					for ( ; missSeq < (*itr)->mSeq; ++missSeq )
					{
						mMissingSeq.push_back( missSeq );
					}
				}
				++missSeq;
			}
		}

		return lista;
	}
	
	bool CIncomingADUFilter::hasMissingSequence()
	{
		return mMissingSeq.size() > 0;
	}

	std::vector<int> CIncomingADUFilter::getMissingSequence()
	{
		return mMissingSeq;
	}

}
}