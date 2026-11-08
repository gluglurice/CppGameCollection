#pragma once

#include <string>

#include <graphics.h>
#include <Utils/Utils.h>

class CRPGBattleRole
{
public:
	enum RoleType
	{
		RT_HERO = 0,
		RT_ENEMY_SWORD = 1,
		RT_ENEMY_GUN = 2,
	};

private:
	bool m_is_alive;
	RoleType m_type;
	std::string m_name;

	int m_hp;
	int m_atk;
	int m_def;

public:
	/* Constructions */
	CRPGBattleRole();

	~CRPGBattleRole();

	CRPGBattleRole(RoleType type, std::string name);

	/* Logic methods */
	void Attack(CRPGBattleRole& target);

	/* Getters and setters */
	bool GetIsAlive();

	void SetIsAlive(bool is_alive);

	RoleType GetType();

	void SetType(RoleType type);

	std::string GetName();

	void SetName(std::string name);

	int GetHP();

	void SetHP(int hp);

	int GetATK();

	void SetATK(int atk);

	int GetDEF();

	void SetDEF(int def);
};
