#pragma once
#include "GameScene.h"
class ForcesTestScene final : public GameScene
{
public:
	ForcesTestScene() :GameScene(L"ForcesTestScene") {}
protected:
	void Initialize() override;
	void Update() override;
	void Draw() const override;
	void OnSceneActivated() override;
	void OnSceneDeactivated() override;

private:
	GameObject* m_pCube{};

	enum InputIds
	{
		Up,
		Down,
		Left,
		Right,
		Reset
	};
};