#pragma once
#include "GameScene.h"
class TriggerTestScene final : public GameScene
{
public:
	TriggerTestScene() :GameScene(L"TriggerTestScene") {}
	~TriggerTestScene() override = default;

protected:
	void Initialize() override;
	void Update() override;
	void Draw() const override;
	void OnSceneActivated() override;
	void OnSceneDeactivated() override;

	void onTrigger(PxTriggerPair* pairs, PxU32 count) override;

private:
	GameObject* m_pSphere{ nullptr };
	PxRigidStatic* m_pTriggerLeft{ nullptr };
	PxRigidStatic* m_pTriggerRight{ nullptr };

	bool m_TriggeredLeft = false;
	bool m_TriggeredRight = false;
};

