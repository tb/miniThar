#ifndef __ANNATAR_NET_ENTITYMOVEUPDATE_H__
#define __ANNATAR_NET_ENTITYMOVEUPDATE_H__

#include <OgreVector3.h>
#include <string>
#include "../asn1/asn1c/APEntityMoveUpdate.h"

namespace annatar {

class NetSerializer;

namespace net
{

class CPlayerUpdater;

class CEntityMoveUpdate
{
private:
	APEntityMoveUpdate *moveUpdate;
public:
	CEntityMoveUpdate(Ogre::Vector3 pos,Ogre::Radian ort)
	{
		moveUpdate = new APEntityMoveUpdate;
		moveUpdate->pos.x = pos.x;
		moveUpdate->pos.y = pos.y;
		moveUpdate->pos.z = pos.z;
		moveUpdate->yaw = ort.valueRadians();
	}

	~CEntityMoveUpdate()
	{
		delete moveUpdate;
	}

	Ogre::Vector3 getPosition()
	{
		return Ogre::Vector3( moveUpdate->pos.x, moveUpdate->pos.y,
			moveUpdate->pos.z );
	}

	Ogre::Radian getOrientation()
	{
		return Ogre::Radian( moveUpdate->yaw );
	}	

	friend class NetSerializer;
	friend class CPlayerUpdater;
};

}
}

#endif
