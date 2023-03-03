#pragma once
#include "GameScene.h"
class TorqueTestScene final : public GameScene
{
public:
	TorqueTestScene() :GameScene(L"TorqueTestScene") {}
protected:
	void Initialize() override;
	void Update() override;
	void Draw() const override;
	void OnSceneActivated() override;
	void OnSceneDeactivated() override;

private:
	GameObject* m_pCube;

	enum InputIds
	{
		Up,
		Down,
		Left,
		Right,
		Reset
	};
};