#include "stdafx.h"
#include "TorqueTestScene.h"

#include "CubePosColorNorm.h"

void TorqueTestScene::Initialize()
{
	EnablePhysxDebugRendering(true);

	const auto pPhysX = PhysxManager::GetInstance()->GetPhysics();

	const PxMaterial* pDefaultMaterial = pPhysX->createMaterial(.5f, .5f, 0.f);

	//groundplane
	const auto pGroundActor = pPhysX->createRigidStatic(PxTransform{ PxQuat{PxPiDivTwo, PxVec3{0, 0, 1}} });
	PxRigidActorExt::createExclusiveShape(*pGroundActor, PxPlaneGeometry{ }, *pDefaultMaterial);
	m_pPhysxScene->addActor(*pGroundActor);

	//cube
	const XMFLOAT3 cubeDimensions{ 1.f, 1.f, 1.f };
	PxBoxGeometry cubeGeometry = PxBoxGeometry{ cubeDimensions.x / 2.f, cubeDimensions.y / 2.f, cubeDimensions.z / 2.f };

	m_pCube = new CubePosColorNorm(cubeDimensions.x, cubeDimensions.y, cubeDimensions.z);
	AddGameObject(m_pCube);

	const auto pCubeActor = pPhysX->createRigidDynamic(PxTransform{ PxIdentity });
	PxRigidActorExt::createExclusiveShape(*pCubeActor, cubeGeometry, *pDefaultMaterial);
	m_pCube->AttachRigidActor(pCubeActor);

	//INPUT
	const auto pInput = m_SceneContext.GetInput();
	pInput->AddInputAction({ Up, InputTriggerState::down , VK_UP });
	pInput->AddInputAction({ Down, InputTriggerState::down , VK_DOWN });
	pInput->AddInputAction({ Right, InputTriggerState::down , VK_RIGHT });
	pInput->AddInputAction({ Left, InputTriggerState::down , VK_LEFT });
	pInput->AddInputAction({ Reset, InputTriggerState::pressed , 'R' });
}

void TorqueTestScene::Update()
{
	const auto pInput = m_SceneContext.GetInput();

	if (pInput->IsActionTriggered(Right))
	{
		m_pCube->GetRigidActor()->is<PxRigidDynamic>()->addTorque({ 0.f, 0.f, -5.f }, PxForceMode::eACCELERATION);
	}

	if (pInput->IsActionTriggered(Left))
	{
		m_pCube->GetRigidActor()->is<PxRigidDynamic>()->addTorque({ 0.f, 0.f, 5.f }, PxForceMode::eACCELERATION);
	}

	if (pInput->IsActionTriggered(Up))
	{
		m_pCube->GetRigidActor()->is<PxRigidDynamic>()->addTorque({ 5.f, 0.f, 0.f }, PxForceMode::eACCELERATION);
	}

	if (pInput->IsActionTriggered(Down))
	{
		m_pCube->GetRigidActor()->is<PxRigidDynamic>()->addTorque({ -5.f, 0.f, 0.f }, PxForceMode::eACCELERATION);
	}

	if (pInput->IsActionTriggered(Reset))
	{
		m_pCube->GetRigidActor()->is<PxRigidDynamic>()->setLinearVelocity(PxVec3{ 0.f, 0.f, 0.f });
		m_pCube->Translate(0, 0, 0);
		m_pCube->Rotate(0, 0, 0);
	}

}

void TorqueTestScene::Draw() const
{
}

void TorqueTestScene::OnSceneActivated()
{
}

void TorqueTestScene::OnSceneDeactivated()
{
}
