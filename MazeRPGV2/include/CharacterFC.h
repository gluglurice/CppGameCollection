#pragma once

#include <Singleton.h>

#include "Character.h"

class CCharacterFC : public CSingleton<CCharacterFC>
{
	friend CSingleton<CCharacterFC>;

protected:
	map<CCharacter::Camp, CCharacter*> m_character_map;

	CCharacterFC();

public:
	~CCharacterFC();

	CCharacter* CreateCharacter(CVector3D position_logic, CCharacter::Camp camp);
};
