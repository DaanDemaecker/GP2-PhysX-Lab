#pragma once
#include "GameScene.h"

class FrictionTestScene final : public GameScene
{
public:
	FrictionTestScene() :GameScene(L"FrictionTestScene") {}

protected:
	void Initialize() override;
	void Update() override;
	void Draw() const override;
	void OnSceneActivated() override;
	void OnSceneDeactivated() override;

private:
	GameObject* m_pPlatform1{};
	GameObject* m_pPlatform2{};
	GameObject* m_pPlatform3{};

	GameObject* m_pCube1{};
	GameObject* m_pCube2{};
	GameObject* m_pCube3{};
};