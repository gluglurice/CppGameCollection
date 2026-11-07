#include "CSoldier.h"

CSoldier::CSoldier()
{

}

CSoldier::~CSoldier()
{

}

void CSoldier::Attack(CSoldier& other)
{

}

void CSoldier::GotAttackedBy(CSoldier& other)
{

}

GET_SET_FUN_DEFINE(int, CSoldier, m_hp, HP)
GET_SET_FUN_DEFINE(int, CSoldier, m_atk, ATK)
GET_SET_FUN_DEFINE(std::string, CSoldier, m_name, Name)
