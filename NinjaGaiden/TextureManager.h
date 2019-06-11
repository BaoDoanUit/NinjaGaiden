#ifndef __TEXTUREMANAGER_H__
#define __TEXTUREMANAGER_H__


#include "Global.h"
#include "Texture.h"
using namespace std;
class TextureManager
{
	unordered_map<eType, Texture*> _ArrTextures;

public:
	static TextureManager* __Instance;
	static TextureManager* GetInstance();

	void AddTexture(eType type, Texture* texture);
	Texture* GetTexture(eType type);

	void LoadResource();

	TextureManager();
	~TextureManager();
};

#endif