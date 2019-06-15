#include "TextureManager.h"

TextureManager* TextureManager::__Instance = NULL;

TextureManager * TextureManager::GetInstance()
{
	if (__Instance == NULL)
		__Instance = new TextureManager();
	return __Instance;
}

void TextureManager::AddTexture(eType type, Texture *texture)
{
	_ArrTextures[type] = texture;
}

Texture * TextureManager::GetTexture(eType type)
{
	return _ArrTextures[type];
}

void TextureManager::LoadResource()
{
	/*
	// Intro
	AddTexture(eType::MAINMENU, new Texture("Resources/mainmenu.png"));
	AddTexture(eType::INTRO_BAT, new Texture("Resources/intro_bat.png", 2, 1, 2));
	AddTexture(eType::INTRO_BAT_MENU, new Texture("Resources/IntroBatMenu.png", 5, 3, 15));
	AddTexture(eType::INTRO_GO_SCENE1, new Texture("Resources/intro_go_scene_1.png"));
	AddTexture(eType::HELICOPTER, new Texture("Resources/helicopter.png"));

	//board
	AddTexture(eType::FONT, new Texture("Resources/font/1.png", 13, 3, 37));

	AddTexture(eType::BOARD, new Texture("Resources/blackboard.png", 1, 1, 1));
	AddTexture(eType::BOARD_TRANS, new Texture("Resources/blackboard.png", 1, 1, 1, 0, 0, 0));

	AddTexture(eType::BOARDHEALTH, new Texture("Resources/heal.png", 3, 1, 3));

	*/
	//MAP
	AddTexture(eType::RENDERBBOX, new Texture("Resources/bbox.png")); // dùng để vẽ BBOX
	AddTexture(eType::MAP3, new Texture("Resources/maps/3-1.png", 5, 16, 80));


	//item
	AddTexture(eType::TIMEFREEZE, new Texture("Resources/item/timefrezee.png", 1, 1, 1, 0, 128, 128));
	AddTexture(eType::BLUEMONEY, new Texture("Resources/item/BlueMoney.png", 1, 1, 1, 0, 128, 128));
	AddTexture(eType::REDMONEY, new Texture("Resources/item/RedMoney.png", 1, 1, 1, 0, 128, 128));
	AddTexture(eType::SPIRITUAL1, new Texture("Resources/item/Spiritual1.png", 1, 1, 1, 0, 128, 128));
	AddTexture(eType::SPIRITUAL2, new Texture("Resources/item/Spiritual2.png", 1, 1, 1, 0, 128, 128));




	// Weapon
	AddTexture(eType::KATANA1, new Texture("Resources/Weapon/katana1.png", 4, 1, 4, 0, 146, 190));
	AddTexture(eType::KATANA2, new Texture("Resources/weapon/katana2.png", 4, 1, 4));
	AddTexture(eType::WINDMILLSTAR, new Texture("Resources/weapon/windmillstar.png", 2, 1, 2));


	//weapon Enemy
	AddTexture(eType::SWORD, new Texture("Resources/weapon/sword.png", 4, 1, 4));
	
	//player
	AddTexture(eType::NINJAGAIDEN, new Texture("Resources/NinjaGaiden.png", 8, 4, 32, 255, 255, 255));
	AddTexture(eType::NINJAGAIDEN_DEADTH, new Texture("Resources/simondeath.png", 1, 1, 1, 255, 255, 255));

	/*
	//effect
	*/


	//enemy
	AddTexture(eType::ENEMY1, new Texture("./Resources/enemy/enemy1.png", 3, 1, 3));
	AddTexture(eType::ENEMY2, new Texture("./Resources/enemy/enemy2.png", 3, 1, 3));
	AddTexture(eType::STANDSOLIDER, new Texture("./Resources/enemy/StandSolider.png", 4, 1, 4));
	AddTexture(eType::SITGUN, new Texture("./Resources/enemy/sitgun.png", 2, 1, 2));
	AddTexture(eType::BEE, new Texture("./Resources/enemy/bee.png", 2, 1, 2));
	AddTexture(eType::BIRD, new Texture("./Resources/enemy/bird.png", 2, 1, 2));
	AddTexture(eType::DOG, new Texture("./Resources/enemy/dog.png", 2, 1, 2));
	AddTexture(eType::EAGLE, new Texture("./Resources/enemy/eagle.png", 2, 1, 2));


	//boss



}

TextureManager::TextureManager()
{
	LoadResource();
}


TextureManager::~TextureManager()
{
	SAFE_DELETE(__Instance);
}
