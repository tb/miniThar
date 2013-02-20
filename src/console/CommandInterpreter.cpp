#include "CommandInterpreter.h"
#include "StringTokenizer.h"

CCommandInterpreter::CCommandInterpreter( annatar::net::CNodesManager *mgr, annatar::net::CNetworkingNode *node )
{
	mPayload = new annatar::net::CPayload();
	mMgr = mgr;
	mNode = node;
}

CCommandInterpreter::~CCommandInterpreter(void)
{
	delete mPayload;
}

void CCommandInterpreter::process( std::string line )
{
	using namespace std;
	using namespace annatar::net;

	//pobierz pierwszy czlon
	StringTokenizer strtok(line," ");
	string cmd = strtok.nextToken();

	if ( strtok.countTokens() == 0 )
	{
		if ( cmd == "flush" )
		{
			flush();
		}
		else
		{
			cout << "UNKNOWN 1long";
		}
	}
	else if(strtok.countTokens() == 2)
	{
		if ( cmd == "con" )
		{
			string name = strtok.nextToken();
			int seq = strtok.nextIntToken();

			CPConnect *pconnect = new CPConnect( seq, name );
			mPayload->addConnect( pconnect );
			delete pconnect;

			cout << "Added \"" << cmd << "\"";
		}
		else if ( cmd == "phr" )
		{
			string name = strtok.nextToken();
			int seq = strtok.nextIntToken();

			CPPhrase *pphraase = new CPPhrase( seq, name );
			mPayload->addPhrase( pphraase );
			delete pphraase;

			cout << "Added \"" << cmd << "\"";
		}
		else if ( cmd == "clo" )
		{
			string name = strtok.nextToken();
			int seq = strtok.nextIntToken();

			CPClose *pclose = new CPClose( seq, name );
			mPayload->addClose( pclose );
			delete pclose;

			cout << "Added \"" << cmd << "\"";
		}
		else
		{
			cout << "UNKNOWN 3long";
		}
	}
	else if(strtok.countTokens() == 3)
	{
		if ( cmd == "tic" )
		{
			int first = strtok.nextIntToken();
			int second = strtok.nextIntToken();
			int seq = strtok.nextIntToken();

			CPTick *ptick = new CPTick( seq, first, second );
			mPayload->addTick( ptick );
			delete ptick;

			cout << "Added \"" << cmd << "\"";
		}
		else if ( cmd == "mis" )
		{
			int first = strtok.nextIntToken();
			int second = strtok.nextIntToken();
			int seq = strtok.nextIntToken();

			std::vector<int> vec;
			vec.push_back( first );
			vec.push_back( second );
			CPMissingSeq *pmiss = new CPMissingSeq( seq, vec );
			mPayload->addMissingSeq( pmiss );
			delete pmiss;

			cout << "Added \"" << cmd << "\"";
		}
		else
		{
			cout << "UNKNOWN 4long";
		}
	}
	else
	{
		std::cout << "!-Error-!" << std::endl;
	}
	
}

void CCommandInterpreter::flush()
{
	std::cout << "\nF_L_U_S_H\n";
	annatar::net::CNetworkingNode *nn;
	nn = mNode; //mMgr->acquire( mNode );
	nn->broadcast( mPayload );
	//mPayload = new annatar::net::CPayload();
	//delete buffer;
}