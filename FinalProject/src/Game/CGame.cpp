#include "CGame.h"

#include <iostream>

#include <conio.h>
#include <graphics.h>
#include <tinyxml/tinyxml.h>
#include <Utils/Utils.h>

#include "src/Actor/CActor.h"
#include "src/Actor/CShip.h"
#include "src/Actor/CShipFC.h"
#include "src/Actor/CNormalBullet.h"
#include "src/Actor/CNormalBulletFC.h"
#include "src/Actor/CBomb.h"
#include "src/Actor/CItem.h"

const std::string CGame::GAME_INI_PATH = "config/game_ini.xml";
const int CGame::ONE_SEC = 1000;

int CGame::GRAPH_WIDTH;
int CGame::GRAPH_HEIGHT;
int CGame::FPS;

CGame* CGame::m_instance;

CGame* CGame::GetInstance()
{
	if (!m_instance)
	{
		m_instance = new CGame();
	}
	return m_instance;
}

CGame::CGame()
{
	TiXmlDocument xml_doc;
	if (!xml_doc.LoadFile(CGame::GAME_INI_PATH.c_str()))
	{
		std::cerr << "读取XML文件失败：" << CGame::GAME_INI_PATH << std::endl;
		return;
	}

	TiXmlElement* xml_root = xml_doc.RootElement();
	xml_root->QueryIntAttribute("graph_width", &GRAPH_WIDTH);
	xml_root->QueryIntAttribute("graph_height", &GRAPH_HEIGHT);
	xml_root->QueryIntAttribute("fps", &FPS);
}

CGame::~CGame() {}

void CGame::Run()
{
	IMAGE background;
	loadimage(&background, L"assets/img/background.jpg");

	initgraph(CGame::GRAPH_WIDTH, CGame::GRAPH_HEIGHT);
	CShip* ship = CShipFC::GetInstance()->CreateShip(CVector3D(CGame::GRAPH_WIDTH / 2, CGame::GRAPH_HEIGHT - 50, 0), CShip::EShipCamp::SC_PLAYER, CShip::EShipType::ST_BLUE_S);

	static unsigned tick_ship_shoot = clock();
	static unsigned tick_bullet_move = clock();

	while (true)
	{
		BeginBatchDraw();
		putimage_alpha_zoom(0, 0, 1.0f, &background);
		ship->Draw();
		EndBatchDraw();

		if (clock() - tick_ship_shoot > CGame::ONE_SEC / ship->GetFiringRate())
		{
			ship->Shoot();
			tick_ship_shoot = clock();
		}

		if (clock() - tick_bullet_move > CGame::ONE_SEC / CGame::FPS)
		{
			for (CNormalBullet* bullet : ship->GetNormalBullets())
			{
				bullet->Move(CVector3D(0, -bullet->GetVelocity(), 0));
			}
			tick_bullet_move = clock();
		}

		if (isKeyDown('W'))
		{
			ship->Move(CVector3D(0, -ship->GetVelocity(), 0));
		}
		if (isKeyDown('S'))
		{
			ship->Move(CVector3D(0, ship->GetVelocity(), 0));
		}
		if (isKeyDown('A'))
		{
			ship->Move(CVector3D(-ship->GetVelocity(), 0, 0));
		}
		if (isKeyDown('D'))
		{
			ship->Move(CVector3D(ship->GetVelocity(), 0, 0));
		}
	}

	_getch();
	closegraph();
}
