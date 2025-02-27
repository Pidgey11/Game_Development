#include "AnimSpriteComponent.h"


void AnimSpriteComponent::Update(float deltaTime) {
	SpriteComponent::Update(deltaTime);
	if (mAnimTextures.size() > 0) {
		//Update the current frame based on frame rate
		// and delta time
		mCurrFrame += mAnimFPS * deltaTime;

		//Wrap current frame if needed

		while (mCurrFrame >= mAnimTextures.size()) {
			mCurrFrame -= mAnimTextures.size();
		}

		//Set the current texture
		SetTexture(mAnimTextures[static_cast<int>(mCurrFrame)]);
	}
}