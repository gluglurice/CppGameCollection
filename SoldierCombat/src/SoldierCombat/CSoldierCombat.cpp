#include "CSoldierCombat.h"

#include "src/Soldier/CSoldier.h"
#include "src/Soldier/CArcher.h"
#include "src/Soldier/CLancer.h"
#include "src/Soldier/CHeavyArmored.h"

CSoldierCombat::CSoldierCombat() {}

CSoldierCombat::~CSoldierCombat() {}

void CSoldierCombat::RunGame()
{
	CSoldier archer = CArcher(CArcher::Position(10, 10), L"assets/imgs/roles/role_archer.png");

	std::cout << "Archer position: (" << archer.GetPosition().x << ", " << archer.GetPosition().y << ")" << std::endl;
}
