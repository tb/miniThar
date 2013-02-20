#include "Payload.h"

namespace annatar {
namespace net
{

CPayload::CPayload()
{
	mPayload = (APPayload_t *)calloc(1, sizeof(APPayload_t));
	mMaxSeq = 0;
}
/*
CPayload::CPayload( APPayload_t *payload )
{
	mPayload = payload;
}
*/

CPayload::CPayload( COctetBuffer *buffer )
{
	mPayload = deserialize( buffer->buf, buffer->size, asn_DEF_APPayload );
	// ?? jak tu odzyskac max_seq??? ##FIXME##
}

CPayload::~CPayload()
{
	clear();
}

void CPayload::clear()
{
	asn_DEF_APPayload.free_struct(&asn_DEF_APPayload, mPayload, 0);
	mMaxSeq = 0;
}

bool CPayload::isSequenceTrigger( APData_PR type )
{
	switch( type )
	{
	case APData_PR_connect:
	case APData_PR_close:
	case APData_PR_phrase:
		return true;
	case APData_PR_tick:
	case APData_PR_missingSeq:
	case APData_PR_entityUpdate:
	case APData_PR_entityMoveUpdate:
	default:
		return false;
	}
}

bool CPayload::addConnect( CPConnect* connect )
{
	bool result = false;

	APADU *adu = (APADU *)calloc(1, sizeof(APADU));
	adu->data.present = APData_PR_connect;
	adu->seq = connect->mSeq;

	size_t size = connect->mUsername.size();

	adu->data.choice.connect.login.buf = (uint8_t *)calloc( size, sizeof(uint8_t)); 
	memcpy( adu->data.choice.connect.login.buf, connect->mUsername.c_str(), size );
	adu->data.choice.connect.login.size = size;

	if( !asn_set_add(&mPayload->list, adu))
	{
		result = true;
	}

	return result;
}

bool CPayload::addClose( CPClose* close )
{
	bool result = false;

	APADU *adu = (APADU *)calloc(1, sizeof(APADU));
	adu->data.present = APData_PR_close;
	adu->seq = close->mSeq;

	size_t size = close->mUsername.size();

	adu->data.choice.close.user.buf = (uint8_t *)calloc( size, sizeof(uint8_t)); 
	memcpy( adu->data.choice.close.user.buf, close->mUsername.c_str(), size );
	adu->data.choice.close.user.size = size;

	if( !asn_set_add(&mPayload->list, adu))
	{
		result = true;
	}

	return result;
}

bool CPayload::addPhrase( CPPhrase* phrase )
{
	bool result = false;

	APADU *adu = (APADU *)calloc(1, sizeof(APADU));
	adu->data.present = APData_PR_phrase;
	adu->seq = phrase->mSeq;

	size_t size = phrase->mPhrase.size();

	adu->data.choice.phrase.text.buf = (uint8_t *)calloc( size, sizeof(uint8_t)); 
	memcpy( adu->data.choice.phrase.text.buf, phrase->mPhrase.c_str(), size );
	adu->data.choice.phrase.text.size = size;

	if( !asn_set_add(&mPayload->list, adu))
	{
		result = true;
	}

	return result;
}

bool CPayload::addTick( CPTick* tick )
{
	bool result = false;

	APADU *adu = (APADU *)calloc(1, sizeof(APADU));
	adu->data.present = APData_PR_tick;
	adu->seq = tick->mSeq;

	adu->data.choice.tick.days = tick->mDays;
	adu->data.choice.tick.msecs = tick->mMsecs;

	if( !asn_set_add(&mPayload->list, adu))
	{
		result = true;
	}

	return result;
}

bool CPayload::addMissingSeq( CPMissingSeq* missingSeq )
{
	bool result = false;

	APADU *adu = (APADU *)calloc(1, sizeof(APADU));
	adu->data.present = APData_PR_missingSeq;
	adu->seq = missingSeq->mSeq;

	std::vector<int>::iterator itr;
	itr = missingSeq->mMissingSeq.begin();
	if ( missingSeq->mMissingSeq.size() >= 2 )
	{
		adu->data.choice.missingSeq.missingFirst = *itr; 
		itr = missingSeq->mMissingSeq.end();
		--itr;
		adu->data.choice.missingSeq.missingLast = *itr;
	}
	else if ( missingSeq->mMissingSeq.size() == 1 )
	{
		adu->data.choice.missingSeq.missingFirst = *itr; 
		adu->data.choice.missingSeq.missingLast = *itr;
	}
	else
	{
		adu->data.choice.missingSeq.missingFirst = 0; 
		adu->data.choice.missingSeq.missingLast = 0;
	}

	/*
	std::vector<int>::iterator itr;
	itr = missingSeq->mMissingSeq.begin();
	for (itr = missingSeq->mMissingSeq.begin(); itr != missingSeq->mMissingSeq.end(); ++itr)
	{
		long x = *itr;
		asn_set_add(&adu->data.choice.missingSeq.missing.list, (void*)(long)(x));
	}
	*/

	if( !asn_set_add(&mPayload->list, adu))
	{
		result = true;
	}

	return result;
}

std::list<CPADU*>* CPayload::getAll()
{
	std::list<CPADU*> *list = new std::list<CPADU*>;
	char* nameBuf;
	int s = 0;
	std::vector<int> *missingSeq;

	for (int i = 0; i < mPayload->list.count; ++i)
	{
		switch( mPayload->list.array[i]->data.present )
		{
		case APData_PR_connect:
			s = mPayload->list.array[i]->data.choice.connect.login.size;
			nameBuf = new char[ s+1 ];
			memcpy( nameBuf, mPayload->list.array[i]->data.choice.connect.login.buf, s );
			nameBuf[ s ] = '\0';
			list->push_back( new CPConnect( mPayload->list.array[i]->seq, nameBuf ) );
			delete [] nameBuf;
			break;
		case APData_PR_close:
			s = mPayload->list.array[i]->data.choice.close.user.size;
			nameBuf = new char[ s+1 ];
			memcpy( nameBuf, mPayload->list.array[i]->data.choice.close.user.buf, s );
			nameBuf[ s ] = '\0';
			list->push_back( new CPClose( mPayload->list.array[i]->seq, nameBuf ) );
			delete [] nameBuf;
			break;
		case APData_PR_phrase:
			s = mPayload->list.array[i]->data.choice.phrase.text.size;
			nameBuf = new char[ s+1 ];
			memcpy( nameBuf, mPayload->list.array[i]->data.choice.phrase.text.buf, s );
			nameBuf[ s ] = '\0';
			list->push_back( new CPPhrase( mPayload->list.array[i]->seq, nameBuf ) );
			delete [] nameBuf;
			break;
		case APData_PR_tick:
			list->push_back( new CPTick(
				mPayload->list.array[i]->seq,
				mPayload->list.array[i]->data.choice.tick.days,
				mPayload->list.array[i]->data.choice.tick.msecs
			) );
			break;
		case APData_PR_missingSeq:
			//s = mPayload->list.array[i]->data.choice.missingSeq.missing.list.count;
			missingSeq = new std::vector<int>;
			missingSeq->push_back(
				(int)mPayload->list.array[i]->data.choice.missingSeq.missingFirst );
			missingSeq->push_back(
				(int)mPayload->list.array[i]->data.choice.missingSeq.missingLast );
			list->push_back( new CPMissingSeq( mPayload->list.array[i]->seq, *missingSeq ) );
			delete missingSeq;
			break;
		default:
			;
		}
	}

	return list;
}

int CPayload::getMaxSeq()
{
	int maxSeq = 0;
	std::list<CPADU*> *lista = this->getAll();

	std::list<CPADU*>::iterator itr;
	for (itr = lista->begin(); itr != lista->end(); ++itr)
	{
		if ( (*itr)->mSeq > maxSeq  )
		{
			maxSeq = (*itr)->mSeq;
		}
	}

	delete lista;

	return maxSeq;
}

std::string CPayload::toString()
{
	std::stringstream desc;
	std::list<CPADU*> *lista = this->getAll();

	std::list<CPADU*>::iterator itr;
	for (itr = lista->begin(); itr != lista->end(); ++itr)
	{
		desc << std::endl;
		desc << (*itr)->toString();
	}

	delete lista;

	return desc.str();
}

}
}
