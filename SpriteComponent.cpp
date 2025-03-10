#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"
#include <cmath> 


void SpriteComponent::SetTexture(SDL_Texture* texture) {
	mTexture = texture;
	SDL_QueryTexture(texture, nullptr, nullptr, &mTexWidth, &mTexHeight);
}

double SpriteComponent::Convert(double degrees) {
	return degrees * (M_PI / 180.0);
}

void SpriteComponent::Draw(SDL_Renderer * renderer)
	{
		if (mTexture)
		{
			SDL_Rect r;
			// Scale the width/height by owner's scale
			r.w = static_cast<int>(mTexWidth * mOwner->GetScale());
			r.h = static_cast<int>(mTexHeight * mOwner->GetScale());
			// Center the rectangle around the position of the owner
			r.x = static_cast<int>(mOwner->GetPosition().x - r.w / 2);
			r.y = static_cast<int>(mOwner->GetPosition().y - r.h / 2);

			// Draw (have to convert angle from radians to degrees, and clockwise to counter)
			SDL_RenderCopyEx(renderer,
				mTexture,
				nullptr,
				&r,
				Convert(mOwner->GetRotation()),
				nullptr,
				SDL_FLIP_NONE);
		}
	}