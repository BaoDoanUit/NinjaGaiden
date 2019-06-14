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
	//AddTexture(eType::MAP4, new Texture("Resources/maps/tileset_map2.png", 22, 4, 88));
	//AddTexture(eType::RENDERBBOX, new Texture("Resources/bbox.png")); // dùng để vẽ BBOX
	/*
	//gameobject ground
	AddTexture(eType::TEX_BRICK_MODEL_1, new Texture("Resources/ground/2.png")); // loại dành cho state 1
	AddTexture(eType::TEX_BRICK_MODEL_2, new Texture("Resources/ground/2-2.png")); // dành cho state 2
	AddTexture(eType::TEX_BRICK_MODEL_3, new Texture("Resources/ground/8.png")); // loại nhỏ
	AddTexture(eType::TEX_BRICK_TRANSPARENT, new Texture("Resources/ground/brick_transparent.png")); // loại trong suốt

	AddTexture(eType::TEX_BRICK_MODEL_3_3_32, new Texture("Resources/ground/8-2.png")); // loại nhỏ 4 ô
	AddTexture(eType::TEX_BRICK_MODEL_3_4_32, new Texture("Resources/ground/8-1.png")); // loại nhỏ 4 ô





	AddTexture(eType::GATE, new Texture("Resources/ground/Gate1.png", 4, 1, 4));

	AddTexture(eType::TORCH, new Texture("Resources/ground/0.png", 2, 1, 2));
	AddTexture(eType::CANDLE, new Texture("Resources/ground/1.png", 2, 1, 2));
	*/

	//item
	AddTexture(eType::TIMEFREEZE, new Texture("Resources/item/timefrezee.png", 1, 1, 1, 0, 128, 128));
	AddTexture(eType::BLUEMONEY, new Texture("Resources/item/BlueMoney.png", 1, 1, 1, 0, 128, 128));
	AddTexture(eType::REDMONEY, new Texture("Resources/item/RedMoney.png", 1, 1, 1, 0, 128, 128));
	AddTexture(eType::SPIRITUAL1, new Texture("Resources/item/Spiritual1.png", 1, 1, 1, 0, 128, 128));
	AddTexture(eType::SPIRITUAL2, new Texture("Resources/item/Spiritual2.png", 1, 1, 1, 0, 128, 128));




	// Weapon
	AddTexture(eType::KATANA1, new Texture("Resources/Weapon/katana1.png", 4, 1, 4, 0, 146, 190));
	AddTexture(eType::KATANA2, new Texture("Resources/weapon/katana2.png", 4, 1, 4));



	//player
	AddTexture(eType::NINJAGAIDEN, new Texture("Resources/NinjaGaiden.png", 8, 4, 32, 0, 255, 255));
	//AddTexture(eType::SIMON_TRANS, new Texture("Resources/simon_trans.png", 8, 3, 24));
	AddTexture(eType::NINJAGAIDEN_DEADTH, new Texture("Resources/simondeath.png", 1, 1, 1, 255, 255, 255));

	/*
	//effect
	AddTexture(eType::FIRE, new Texture("Resources/other/1.png", 4, 1, 4));
	AddTexture(eType::HIT, new Texture("Resources/other/0.png", 2, 1, 2));
	AddTexture(eType::BROKENBRICK, new Texture("Resources/other/BrokenBrick.png", 2, 1, 2));//, 4,4,16));
	AddTexture(eType::STEAM, new Texture("Resources/other/2.png"));
	AddTexture(eType::EFFECT_MONEY_700, new Texture("Resources/other/effect700.png", 2, 1, 2));
	AddTexture(eType::EFFECT_MONEY_100, new Texture("Resources/other/effect100.png", 2, 1, 2));
	AddTexture(eType::EFFECT_MONEY_1000, new Texture("Resources/other/effect1000.png", 2, 1, 2));
	AddTexture(eType::EFFECT_MONEY_400, new Texture("Resources/other/effect400.png", 2, 1, 2));
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
	/*AddTexture(eType::PHANTOMBAT, new Texture("Resources/boss/0.png", 3, 1, 3));*/



}

TextureManager::TextureManager()
{
	LoadResource();
}


TextureManager::~TextureManager()
{
	SAFE_DELETE(__Instance);
}
