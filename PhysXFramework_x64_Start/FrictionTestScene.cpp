#include "stdafx.h"
#include "FrictionTestScene.h"

#include "CubePosColorNorm.h"

void FrictionTestScene::Initialize()
{
	EnablePhysxDebugRendering(true);

	//create materials
	const auto pPhysX = PhysxManager::GetInstance()->GetPhysics();
	const PxMaterial* pNonFriction = pPhysX->createMaterial(.0f, .0f, .2f);
	const PxMaterial* pHalfFriction = pPhysX->createMaterial(.2f, .2f, .2f);
	const PxMaterial* pFriction = pPhysX->createMaterial(1.f, 1.f, 0.2f);

	//Ground plane
	const auto pGroundActor = pPhysX->createRigidStatic(PxTransform{ PxQuat{PxPiDivTwo, PxVec3{0, 0, 1}} });
	PxRigidActorExt::createExclusiveShape(*pGroundActor, PxPlaneGeometry{ }, *pNonFriction);
	m_pPhysxScene->addActor(*pGroundActor);

	//Create the platforms
	const XMFLOAT3 platformDimensions{ 6.f, 1.f, 4.f };
	PxBoxGeometry platformGeometry = PxBoxGeometry{ platformDimensions.x / 2.f, platformDimensions.y / 2.f, platformDimensions.z / 2.f };
	m_pPlatform1 = new CubePosColorNorm(platformDimensions.x, platformDimensions.y, platformDimensions.z);
	AddGameObject(m_pPlatform1);
	m_pPlatform2 = new CubePosColorNorm(platformDimensions.x, platformDimensions.y, platformDimensions.z);
	AddGameObject(m_pPlatform2);
	m_pPlatform3 = new CubePosColorNorm(platformDimensions.x, platformDimensions.y, platformDimensions.z);
	AddGameObject(m_pPlatform3);

	const auto pPlatform1Actor = pPhysX->createRigidStatic(PxTransform{ PxIdentity });
	PxRigidActorExt::createExclusiveShape(*pPlatform1Actor, platformGeometry, *pNonFriction);
	m_pPlatform1->AttachRigidActor(pPlatform1Actor);

	const auto pPlatform2Actor = pPhysX->createRigidStatic(PxTransform{ PxIdentity });
	PxRigidActorExt::createExclusiveShape(*pPlatform2Actor, platformGeometry, *pHalfFriction);
	m_pPlatform2->AttachRigidActor(pPlatform2Actor);

	const auto pPlatform3Actor = pPhysX->createRigidStatic(PxTransform{ PxIdentity });
	PxRigidActorExt::createExclusiveShape(*pPlatform3Actor, platformGeometry, *pFriction);
	m_pPlatform3->AttachRigidActor(pPlatform3Actor);




	//Create the cube
	const XMFLOAT3 cubeDimensions{ 1.f, 1.f, 1.f };
	PxBoxGeometry cubeGeometry = PxBoxGeometry{ cubeDimensions.x / 2.f, cubeDimensions.y / 2.f, cubeDimensions.z / 2.f };
	m_pCube1 = new CubePosColorNorm(cubeDimensions.x, cubeDimensions.y, cubeDimensions.z);
	AddGameObject(m_pCube1);
	m_pCube2 = new CubePosColorNorm(cubeDimensions.x, cubeDimensions.y, cubeDimensions.z);
	AddGameObject(m_pCube2);
	m_pCube3 = new CubePosColorNorm(cubeDimensions.x, cubeDimensions.y, cubeDimensions.z);
	AddGameObject(m_pCube3);

	const auto pCubeActor1 = pPhysX->createRigidDynamic(PxTransform{ PxIdentity });
	PxRigidActorExt::createExclusiveShape(*pCubeActor1, cubeGeometry, *pNonFriction);
	m_pCube1->AttachRigidActor(pCubeActor1);

	const auto pCubeActor2 = pPhysX->createRigidDynamic(PxTransform{ PxIdentity });
	PxRigidActorExt::createExclusiveShape(*pCubeActor2, cubeGeometry, *pHalfFriction);
	m_pCube2->AttachRigidActor(pCubeActor2);

	const auto pCubeActor3 = pPhysX->createRigidDynamic(PxTransform{ PxIdentity });
	PxRigidActorExt::createExclusiveShape(*pCubeActor3, cubeGeometry, *pFriction);
	m_pCube3->AttachRigidActor(pCubeActor3);

	//Move the platforms
	m_pPlatform1->Translate(-10, 5, 0);
	m_pPlatform2->Translate(0, 5, 0);
	m_pPlatform3->Translate(10, 5, 0);

	//Rotate the platforms
	m_pPlatform1->Rotate(0, 0, -PxPiDivFour/2);
	m_pPlatform2->Rotate(0, 0, -PxPiDivFour / 2);
	m_pPlatform3->Rotate(0, 0, -PxPiDivFour / 2);

	//Move the cubes
	m_pCube1->Translate(-10, 5, 0);
	m_pCube2->Translate(0, 5, 0);
	m_pCube3->Translate(10, 5, 0);

}

void FrictionTestScene::Update()
{
	if (m_SceneContext.GetInput()->IsKeyboardKey(InputTriggerState::pressed, 'R'))
	{
		//Move the platforms
		m_pPlatform1->Translate(-10, 5, 0);
		m_pPlatform2->Translate(0, 5, 0);
		m_pPlatform3->Translate(10, 5, 0);

		//Rotate the platforms
		m_pPlatform1->Rotate(0, 0, -PxPiDivFour / 2);
		m_pPlatform2->Rotate(0, 0, -PxPiDivFour / 2);
		m_pPlatform3->Rotate(0, 0, -PxPiDivFour / 2);

		//Move the cubes
		m_pCube1->Translate(-10, 5, 0);
		m_pCube2->Translate(0, 5, 0);
		m_pCube3->Translate(10, 5, 0);

		//Rotate the cubes
		m_pCube1->Rotate(0, 0, 0);
		m_pCube2->Rotate(0, 0, 0);
		m_pCube3->Rotate(0, 0, 0);
	}
}

void FrictionTestScene::Draw() const
{
}

void FrictionTestScene::OnSceneActivated()
{
}

void FrictionTestScene::OnSceneDeactivated()
{
}
