#pragma once
#include "Component.h"
#include "SDL.h"
#include "SDL_render.h"
#include <math.h>

class SpriteComponent : public Component
{
public:
	//Lower draw order
	SpriteComponent(class Actor* owner, int drawOrder = 100);
	~SpriteComponent();
	virtual void Draw(SDL_Renderer* rednerer);
	virtual void SetTexture(SDL_Texture* texture);
	double Convert(double);
	int GetDrawOrder() const { return mDrawOrder; }
	int GetTexHeight() const { return mTexHeight; }
	int GetTexWidth() const { return mTexWidth; }

protected:
	//Texture to draw
	SDL_Texture* mTexture;
	int mDrawOrder;
	int mTexWidth;
	int mTexHeight;
};

