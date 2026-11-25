#pragma once

#include <Singleton.h>
#include <Sprite.h>

#include "Character.h"

class CCharacterFC : public CSingleton<CCharacterFC>
{
	friend CSingleton<CCharacterFC>;

protected:
	map<CCharacter::Type, CCharacter*> m_character_map;

	CCharacterFC();

public:
	~CCharacterFC();

	CCharacter* CreateCharacter(D3DXVECTOR3 position_logic, CCharacter::Type type);
};
