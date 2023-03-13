#include "stdafx.h"
#include "PongScene.h"

#include "Prefabs/CubePrefab.h"
#include "Prefabs/SpherePrefab.h"

void PongScene::Initialize()
{
	//m_SceneContext.settings.enableOnGUI = true;

	m_SceneContext.settings.clearColor = XMFLOAT4{ Colors::Black };

	GameObject* pCamera = new FixedCamera();
	pCamera->GetTransform()->Translate(0, 100, 0);
	pCamera->GetTransform()->Rotate(90, 0, 0, true);
	AddChild(pCamera);

	SetActiveCamera(pCamera->GetComponent<CameraComponent>());

	auto& physX = PxGetPhysics();
	auto pBouncyMaterial = physX.createMaterial(0.f, 0.f, 1.1f);

	XMFLOAT3 cubeDimensions{ 120.f, 2.f, 2.f };
	auto pTopCube = new CubePrefab(cubeDimensions, XMFLOAT4(Colors::Transparent));
	pTopCube->AddComponent(new RigidBodyComponent(true))->AddCollider(PxBoxGeometry(cubeDimensions.x / 2, cubeDimensions.y/2, cubeDimensions.z/2), * pBouncyMaterial);
	pTopCube->GetTransform()->Translate(0.f, 0.f, 25.f);
	AddChild(pTopCube);

	auto pBotCube = new CubePrefab(cubeDimensions, XMFLOAT4(Colors::Transparent));
	pBotCube->AddComponent(new RigidBodyComponent(true))->AddCollider(PxBoxGeometry(cubeDimensions.x / 2, cubeDimensions.y / 2, cubeDimensions.z / 2), *pBouncyMaterial);
	pBotCube->GetTransform()->Translate(0.f, 0.f, -25.f);
	AddChild(pBotCube);


	cubeDimensions = XMFLOAT3{ 2.f, 2.f, 50.f };
	auto pLeftTrigger = new CubePrefab(cubeDimensions, XMFLOAT4(Colors::Transparent));
	pLeftTrigger->AddComponent(new RigidBodyComponent(true))->AddCollider(PxBoxGeometry(cubeDimensions.x / 2, cubeDimensions.y / 2, cubeDimensions.z / 2), *pBouncyMaterial, true);
	pLeftTrigger->GetTransform()->Translate(-55.f, 0.f, 0.f);
	AddChild(pLeftTrigger);
	pLeftTrigger->SetOnTriggerCallBack([=](GameObject*, GameObject* pOther, PxTriggerAction action) {
		if (action == PxTriggerAction::ENTER && pOther == m_pBall)
		{
			ResetBall();
		}
		});


	auto pRightTrigger = new CubePrefab(cubeDimensions, XMFLOAT4(Colors::Transparent));
	pRightTrigger->AddComponent(new RigidBodyComponent(true))->AddCollider(PxBoxGeometry(cubeDimensions.x / 2, cubeDimensions.y / 2, cubeDimensions.z / 2), *pBouncyMaterial, true);
	pRightTrigger->GetTransform()->Translate(55.f, 0.f, 0.f);
	AddChild(pRightTrigger);
	pRightTrigger->SetOnTriggerCallBack([=](GameObject*, GameObject* pOther, PxTriggerAction action) {
		if (action == PxTriggerAction::ENTER && pOther == m_pBall)
		{
			ResetBall();
		}
		});


	//Ball
	m_pBall = new SpherePrefab(2, 10, XMFLOAT4{ Colors::Red });
	auto pRigidBody = m_pBall->AddComponent(new RigidBodyComponent());
	pRigidBody->AddCollider(PxSphereGeometry{ 1.f }, *pBouncyMaterial);
	AddChild(m_pBall);


	auto pInput = m_SceneContext.pInput;
	pInput->AddInputAction(InputAction{ LeftUp, InputState::down , 'Q'});
	pInput->AddInputAction(InputAction{ LeftDown, InputState::down , 'A' });
	pInput->AddInputAction(InputAction{ RightUp, InputState::down , VK_UP });
	pInput->AddInputAction(InputAction{ RightDown, InputState::down , VK_DOWN });
	pInput->AddInputAction(InputAction{ Go, InputState::pressed , VK_SPACE });

	//Paddles
	cubeDimensions = XMFLOAT3{ 2.f, 2.f, 10.f };
	m_pPlayer1 = new CubePrefab(cubeDimensions, XMFLOAT4(Colors::White));
	pRigidBody = m_pPlayer1->AddComponent(new RigidBodyComponent(true));
	pRigidBody->AddCollider(PxBoxGeometry(cubeDimensions.x / 2, cubeDimensions.y / 2, cubeDimensions.z / 2), *pBouncyMaterial);
	pRigidBody->SetKinematic(true);
	m_pPlayer1->GetTransform()->Translate(-50.f, 0.f, 0.f);
	AddChild(m_pPlayer1);

	m_pPlayer2 = new CubePrefab(cubeDimensions, XMFLOAT4(Colors::White));
	pRigidBody = m_pPlayer2->AddComponent(new RigidBodyComponent(true));
	pRigidBody->AddCollider(PxBoxGeometry(cubeDimensions.x / 2, cubeDimensions.y / 2, cubeDimensions.z / 2), *pBouncyMaterial);
	pRigidBody->SetKinematic(true);
	m_pPlayer2->GetTransform()->Translate(50.f, 0.f, 0.f);
	AddChild(m_pPlayer2);

}

void PongScene::Update()
{
	const auto pInput = m_SceneContext.pInput;

	constexpr float movement{ 20.f };

	if (pInput->IsActionTriggered(Go))
	{
		m_pBall->GetComponent<RigidBodyComponent>()->AddForce(XMFLOAT3{ 20.f, 0.f, 20.f }, PxForceMode::eIMPULSE);
	}

	if (pInput->IsActionTriggered(LeftUp))
	{
		const auto pos = m_pPlayer1->GetTransform()->GetPosition();
		m_pPlayer1->GetTransform()->Translate(pos.x, pos.y, pos.z + movement*m_SceneContext.pGameTime->GetElapsed());
	}

	if (pInput->IsActionTriggered(LeftDown))
	{
		const auto pos = m_pPlayer1->GetTransform()->GetPosition();
		m_pPlayer1->GetTransform()->Translate(pos.x, pos.y, pos.z - movement * m_SceneContext.pGameTime->GetElapsed());
	}

	if (pInput->IsActionTriggered(RightUp))
	{
		const auto pos = m_pPlayer2->GetTransform()->GetPosition();
		m_pPlayer2->GetTransform()->Translate(pos.x, pos.y, pos.z + movement * m_SceneContext.pGameTime->GetElapsed());
	}

	if (pInput->IsActionTriggered(RightDown))
	{
		const auto pos = m_pPlayer2->GetTransform()->GetPosition();
		m_pPlayer2->GetTransform()->Translate(pos.x, pos.y, pos.z - movement * m_SceneContext.pGameTime->GetElapsed());
	}
}

void PongScene::PostInitialize()
{
	m_pBall->GetComponent<RigidBodyComponent>()->GetPxRigidActor()->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
	m_pBall->GetComponent<RigidBodyComponent>()->GetPxRigidActor()->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
}

void PongScene::ResetBall()
{
	m_pBall->GetTransform()->Translate(0, 0, 0);
}
