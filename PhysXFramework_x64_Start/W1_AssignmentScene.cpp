#include "stdafx.h"
#include "W1_AssignmentScene.h"

#include "CubePosColorNorm.h"
#include "SpherePosColorNorm.h"

void W1_AssignmentScene::Initialize()
{
	EnablePhysxDebugRendering(true);

	const auto pPhysX = PhysxManager::GetInstance()->GetPhysics();

	const PxMaterial* pFloorMaterial = pPhysX->createMaterial(.5f, .5f, 0.f);
	const PxMaterial* pSphereMaterial = pPhysX->createMaterial(.4f, .4f, .05f);
	const PxMaterial* pCubeMaterial = pPhysX->createMaterial(.3f, .3f, .2f);

	//groundplane
	XMFLOAT3 groundDimensions{100.f, 1.f, 100.f};
	PxBoxGeometry groundGeometry = PxBoxGeometry{groundDimensions.x/2, groundDimensions.y/2, groundDimensions.z/2};

	m_pGround = new CubePosColorNorm(groundDimensions.x, groundDimensions.y, groundDimensions.z);
	AddGameObject(m_pGround);

	const auto pGroundActor = pPhysX->createRigidStatic(PxTransform{PxIdentity});
	PxRigidActorExt::createExclusiveShape(*pGroundActor, groundGeometry, *pFloorMaterial);
	m_pGround->AttachRigidActor(pGroundActor);

	m_pGround->Translate(0, -groundDimensions.y / 2, 0);

	//Wall
	PxBoxGeometry cubeGeometry = PxBoxGeometry{ m_CubeSize / 2, m_CubeSize / 2, m_CubeSize / 2 };

	m_pWall.resize(m_WallSize * m_WallSize);

	for (int i{}; i < m_WallSize * m_WallSize; i++)
	{
		m_pWall[i] = new CubePosColorNorm(m_CubeSize, m_CubeSize, m_CubeSize);
		AddGameObject(m_pWall[i]);
		const auto pCubeActor = pPhysX->createRigidDynamic(PxTransform{ PxIdentity });
		PxRigidActorExt::createExclusiveShape(*pCubeActor, cubeGeometry, *pCubeMaterial);
		PxRigidBodyExt::updateMassAndInertia(*pCubeActor, 0.1f);
		m_pWall[i]->AttachRigidActor(pCubeActor);
	}


	//sphere
	const float sphereRad{ 1.f };
	PxSphereGeometry sphereGeometry = PxSphereGeometry{1.f};

	m_pSphere = new SpherePosColorNorm(sphereRad, 10, 10, XMFLOAT4{Colors::HotPink});
	AddGameObject(m_pSphere);

	const auto pSphereActor = pPhysX->createRigidDynamic(PxTransform{ PxIdentity });
	PxRigidActorExt::createExclusiveShape(*pSphereActor, sphereGeometry, *pSphereMaterial);
	PxRigidBodyExt::updateMassAndInertia(*pSphereActor, 5.f);
	m_pSphere->AttachRigidActor(pSphereActor);

	//INPUT
	const auto pInput = m_SceneContext.GetInput();
	pInput->AddInputAction({ Up, InputTriggerState::down , VK_UP });
	pInput->AddInputAction({ Down, InputTriggerState::down , VK_DOWN });
	pInput->AddInputAction({ Right, InputTriggerState::down , VK_RIGHT });
	pInput->AddInputAction({ Left, InputTriggerState::down , VK_LEFT });
	pInput->AddInputAction({ Reset, InputTriggerState::pressed , 'R' });

	ResetScene();
}

inline PxVec3 ToPX(XMFLOAT3 v)//DirectX vector to FMOD vector
{
	return PxVec3(v.x, v.y, v.z);
}

void W1_AssignmentScene::Update()
{
	const auto pInput = m_SceneContext.GetInput();

	constexpr float torque{ 5.f };

	if (pInput->IsActionTriggered(Up))
	{
		m_pSphere->GetRigidActor()->is<PxRigidDynamic>()->addTorque(
			ToPX(m_SceneContext.GetCamera()->GetRight()) * torque,
			PxForceMode::eACCELERATION);
	}

	if (pInput->IsActionTriggered(Down))
	{
		m_pSphere->GetRigidActor()->is<PxRigidDynamic>()->addTorque(
			-ToPX(m_SceneContext.GetCamera()->GetRight()) * torque,
			PxForceMode::eACCELERATION);
	}

	if (pInput->IsActionTriggered(Right))
	{
		m_pSphere->GetRigidActor()->is<PxRigidDynamic>()->addTorque(
			-ToPX(m_SceneContext.GetCamera()->GetForward()) * torque,
			PxForceMode::eACCELERATION);
	}

	if (pInput->IsActionTriggered(Left))
	{
		m_pSphere->GetRigidActor()->is<PxRigidDynamic>()->addTorque(
			ToPX(m_SceneContext.GetCamera()->GetForward()) * torque,
			PxForceMode::eACCELERATION);
	}

	

	if (pInput->IsActionTriggered(Reset))
	{
		ResetScene();
	}

}

void W1_AssignmentScene::Draw() const
{
}

void W1_AssignmentScene::OnSceneActivated()
{
}

void W1_AssignmentScene::OnSceneDeactivated()
{
}

void W1_AssignmentScene::ResetScene()
{
	m_pSphere->GetRigidActor()->is<PxRigidDynamic>()->setLinearVelocity(PxVec3{ 0.f, 0.f, 0.f });
	m_pSphere->Translate(0, .5f, -5);
	m_pSphere->Rotate(0, 0, 0);

	const float zTranslate{ 5.f };
	const float margin{ m_CubeSize/2.f };

	for (int x{}; x < m_WallSize; x++)
	{
		const float xTranslate{-((m_WallSize/2.f) * (m_CubeSize + margin)) + x*(m_CubeSize + margin)};
		for (int y{}; y < m_WallSize; y++)
		{
			const float yTranslate{y* m_CubeSize + m_CubeSize/2};
			const int index{static_cast<int>(x * m_WallSize) + y};

			m_pWall[index]->Translate(xTranslate, yTranslate, zTranslate);
			m_pWall[index]->Rotate(0, (rand() % 314)/200.f, 0);
		}
	}
}
