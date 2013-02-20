#ifndef __ANNATAR_NET_PAYLOAD_H__
#define __ANNATAR_NET_PAYLOAD_H__

#include "../utility/LogManager.h"
#include "../asn1/ASN1Serializer.h"
#include "APPayload.h"

#include <vector>
#include <list>

namespace annatar {
namespace net
{

class CPADU
{
public:
	APData_PR mType;
	int mSeq;

	inline bool operator < ( const CPADU& rhs ) const
	{
		if( mSeq < rhs.mSeq )
			return true;
		return false;
	}

	std::string typeAsString( APData_PR type )
	{
		switch( type )
		{
		case APData_PR_connect:
			return "connect";
		case APData_PR_close:
			return "close";
		case APData_PR_phrase:
			return "phrase";
		case APData_PR_tick:
			return "tick";
		case APData_PR_missingSeq:
			return "missingSeq";
		case APData_PR_entityUpdate:
			return "entityUpdate";
		case APData_PR_entityMoveUpdate:
			return "entityMoveUpdate";
		default:
			return "unknown";
		}
	}

	std::string toString()
	{
		std::stringstream desc;
		
		desc << "ADU seq: " << mSeq ;
		desc << ", type: " << typeAsString( mType );

		return desc.str();
	}
};

class CPADUSortCriterion
{
public:
	bool operator() (annatar::net::CPADU const* p1, annatar::net::CPADU const* p2)
	{
		if(!p1)
			return true;
		if(!p2)
			return false;
		return p1->mSeq < p2->mSeq;
	}
};

class CPConnect : public CPADU
{
public:
	std::string mUsername;

	CPConnect( int seq, std::string username )
	{
		mType = APData_PR_connect;
		mSeq = seq;
		mUsername = username;
	}

	inline CPConnect( const CPConnect& rhs )
	{
		mUsername = rhs.mUsername;
		mSeq = rhs.mSeq;
	}
};

class CPClose : public CPADU
{
public:
	std::string mUsername;

	CPClose( int seq, std::string username )
	{
		mType = APData_PR_close;
		mUsername = username;
		mSeq = seq;
	}

	inline CPClose( const CPClose& rhs )
	{
		mUsername = rhs.mUsername;
		mSeq = rhs.mSeq;
	}
};

class CPPhrase : public CPADU
{
public:
	std::string mPhrase;

	CPPhrase( int seq, std::string phrase )
	{
		mType = APData_PR_phrase;
		mPhrase = phrase;
		mSeq = seq;
	}

	inline CPPhrase( const CPPhrase& rhs )
	{
		mPhrase = rhs.mPhrase;
		mSeq = rhs.mSeq;
	}
};

class CPTick : public CPADU
{
public:
	int mDays;
	int mMsecs;

	CPTick( int seq, int days, int msecs )
	{
		mType = APData_PR_tick;
		mSeq = seq;
		mDays = days;
		mMsecs = msecs;
	}

	inline CPTick( const CPTick& rhs )
	{
		mDays = rhs.mDays;
		mMsecs = rhs.mMsecs;
	}
};

class CPMissingSeq : public CPADU
{
public:
	std::vector<int> mMissingSeq;

	CPMissingSeq( int seq, std::vector<int> missingSeq )
	{
		mType = APData_PR_missingSeq;
		mMissingSeq = missingSeq;
		mSeq = seq;
	}

	inline CPMissingSeq( const CPMissingSeq& rhs )
	{
		mMissingSeq = rhs.mMissingSeq;
		mSeq = rhs.mSeq;
	}
};

class CPayload
{
public:
	APPayload_t *mPayload;
	int mMaxSeq;

public:
	CPayload();
	//CPayload( APPayload_t *payload );
	CPayload( COctetBuffer *buffer );
	~CPayload();

	void clear();
	void zero();

	static bool isSequenceTrigger( APData_PR type );

	bool addConnect( CPConnect* connect );
	bool addClose( CPClose* close );
	bool addPhrase( CPPhrase* phrase );
	bool addTick( CPTick* tick );
	bool addMissingSeq( CPMissingSeq* missingSeq );

	std::list<CPADU*>* getAll();
	int getMaxSeq();
	std::string toString();

	COctetBuffer* serialize()
	{
		COctetBuffer *outputBuf = new COctetBuffer();

		try
		{
			ASN1Serializer::_genericSerialize( outputBuf, asn_DEF_APPayload, this->mPayload );
		}
		catch ( ::annatar::ASN1Exception e )
		{
			utility::LogManager::getSingletonPtr()->logMessage( e.getMessage() );
			return false;
		}

		return outputBuf;
	};


	static APPayload_t* deserialize(
		const void *buffer, size_t buf_size, struct asn_TYPE_descriptor_s &type_descriptor )
	{ 
		APPayload_t *rect = 0;
		asn_dec_rval_t rval;

		rval = ber_decode(0, &type_descriptor, (void **)&rect, (void *)buffer, buf_size); 

		if(rval.code != RC_OK)
		{
			// Free partially decoded rect
			asn_DEF_APPayload.free_struct(
				&asn_DEF_APPayload, rect, 0);
			return 0;
		}

		return rect;
	};

};

}
}

#endif
