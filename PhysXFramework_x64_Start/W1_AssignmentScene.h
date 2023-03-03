#pragma once
#include "GameScene.h"
#include <vector>

class W1_AssignmentScene final : public GameScene
{
public:
	W1_AssignmentScene() :GameScene(L"W1_AssignmentScene") {}
protected:
	void Initialize() override;
	void Update() override;
	void Draw() const override;
	void OnSceneActivated() override;
	void OnSceneDeactivated() override;

private:
	GameObject* m_pGround{};

	GameObject* m_pSphere{};

	std::vector<GameObject*> m_pWall{};
	const size_t m_WallSize{10};
	const float m_CubeSize{ 1.f };

	enum InputIds
	{
		Up,
		Down,
		Left,
		Right,
		Reset
	};

	void ResetScene();
};