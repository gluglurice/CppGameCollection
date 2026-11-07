#include "CHero.h"

GET_SET_FUN_DEFINE(int, CHero, m_hp, HP)

GET_SET_FUN_DEFINE(std::string, CHero, m_name, Name)

CHero::CHero()
{

}

CHero::~CHero()
{

}

void CHero::Say()
{
	std::cout << "I am " << m_name << std::endl;
}
