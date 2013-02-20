#ifndef __ANNATAR_PLAYER_H__
#define __ANNATAR_PLAYER_H__

#include <OgreVector3.h>
#include <string>

namespace annatar
{

class NetSerializer;
class DBaseSerializer;

class CPlayer
{
private:
	Ogre::Vector3			mPosition;
	Ogre::Vector3			mVector;
	Ogre::Radian			mOrientation;
	std::string				mName;
	int						id;
	int						secror_id;
public:
	CPlayer(Ogre::Vector3 pos,Ogre::Radian ort,std::string name, int id=1, int secror_id=1);
	~CPlayer(void);
	
	std::string getName();
	Ogre::Vector3 getPosition();
	Ogre::Vector3 getVector();
	Ogre::Radian getOrientation();

	void setPosition(Ogre::Vector3 vec);
	void setPosition(Ogre::Real x,Ogre::Real y,Ogre::Real z);
	void setVector(Ogre::Vector3 vec);
	void setVector(Ogre::Real x,Ogre::Real y,Ogre::Real z);
	void setOrientation(Ogre::Radian);
	//void setOrientation(Ogre::Real w,Ogre::Real x,Ogre::Real y,Ogre::Real z);
	
	int GetId();
	int GetSectorId();

	friend class NetSerializer;
	friend class DBaseSerializer;
};

}

#endif
