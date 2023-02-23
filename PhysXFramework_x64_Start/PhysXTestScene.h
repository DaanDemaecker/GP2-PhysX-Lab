#pragma once
#include "GameScene.h"

class PhysXTestScene final : public GameScene
{
public:
	PhysXTestScene() :GameScene(L"PhysXTestScene") {}

protected:
	void Initialize() override;
	void Update() override;
	void Draw() const override;
	void OnSceneActivated() override;
	void OnSceneDeactivated() override;

private:

	GameObject* m_pCube;

};

