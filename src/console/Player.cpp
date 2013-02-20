#include "Player.h"

namespace annatar
{

CPlayer::CPlayer(Ogre::Vector3 pos,Ogre::Radian ort,std::string name, int id, int secror_id)
{
	mOrientation = ort;
	mPosition = pos;
	mName = name;
	this->id = id;
	this->secror_id = secror_id;
}
//-----------------------------------------------------------------------
CPlayer::~CPlayer(void)
{
}
//-----------------------------------------------------------------------
std::string CPlayer::getName()
{
	return mName;
}
//-----------------------------------------------------------------------
Ogre::Vector3 CPlayer::getPosition()
{
	return mPosition;
}
//-----------------------------------------------------------------------
void CPlayer::setPosition(Ogre::Vector3 vec)
{
	mPosition = vec;
}
//-----------------------------------------------------------------------
void CPlayer::setPosition(Ogre::Real x,Ogre::Real y,Ogre::Real z)
{
	mPosition.x = x;
	mPosition.y = y;
	mPosition.z = z;
}
//-----------------------------------------------------------------------
Ogre::Vector3 CPlayer::getVector()
{
	return mVector;
}
//-----------------------------------------------------------------------
void CPlayer::setVector(Ogre::Vector3 vec)
{
	mVector = vec;
}
//-----------------------------------------------------------------------
void CPlayer::setVector(Ogre::Real x,Ogre::Real y,Ogre::Real z)
{
	mVector.x = x;
	mVector.y = y;
	mVector.z = z;
}
//-----------------------------------------------------------------------
Ogre::Radian CPlayer::getOrientation()
{
	return mOrientation;
}
//-----------------------------------------------------------------------
void CPlayer::setOrientation(Ogre::Radian ort)
{
	mOrientation = ort;
}
//-----------------------------------------------------------------------
/*Ogre::Quaternion CPlayer::getOrientation()
{
	return mOrientation;
}
//-----------------------------------------------------------------------
void CPlayer::setOrientation(Ogre::Quaternion ort)
{
	mOrientation = ort;
}
//-----------------------------------------------------------------------
void CPlayer::setOrientation(Ogre::Real w,Ogre::Real x,Ogre::Real y,Ogre::Real z)
{
	mOrientation.w = w;
	mOrientation.x = x;
	mOrientation.y = y;
	mOrientation.z = z;
}*/
//-----------------------------------------------------------------------
int CPlayer::GetId()
{
	return id;
}
//-----------------------------------------------------------------------
int CPlayer::GetSectorId()
{
	return secror_id;
}
}