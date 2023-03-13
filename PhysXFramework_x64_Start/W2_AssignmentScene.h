#pragma once
#include "GameScene.h"
class W2_AssignmentScene final : public GameScene
{
public:
	W2_AssignmentScene() :GameScene(L"W2_AssignmentScene") {}
	~W2_AssignmentScene() override = default;
	W2_AssignmentScene(const W2_AssignmentScene& other) = delete;
	W2_AssignmentScene(W2_AssignmentScene&& other) noexcept = delete;
	W2_AssignmentScene& operator=(const W2_AssignmentScene& other) = delete;
	W2_AssignmentScene& operator=(W2_AssignmentScene&& other) noexcept = delete;

protected:
	void Initialize() override;
	void Update() override;
	void Draw() const override;
	void OnSceneActivated() override;
	void OnSceneDeactivated() override;

	void onTrigger(PxTriggerPair* pairs, PxU32 count) override;

private:
	GameObject* m_pLevel{};

	GameObject* m_pBlueTrigger{};
	GameObject* m_pBlueBox{};

	GameObject* m_pBlueHatch{};
	GameObject* m_pLeftSphere{};

	GameObject* m_pRedTrigger{};
	GameObject* m_pRedBox{};

	GameObject* m_pRedHatch{};
	GameObject* m_pRightSphere{};

	GameObject* m_pSphere{ nullptr };

	FMOD::Channel* m_pChannel2D{ nullptr };
	FMOD::Sound* m_pBellSound{ nullptr };

};