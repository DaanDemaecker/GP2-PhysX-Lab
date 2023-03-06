#include "stdafx.h"
#include "W2_AssignmentScene.h"
#include "PhysxManager.h"
#include "MeshObject.h"
#include "ContentManager.h"

void W2_AssignmentScene::Initialize()
{
	EnablePhysxDebugRendering(true);

	const auto pPhysX = PhysxManager::GetInstance()->GetPhysics();
	const auto pDefaultMaterial = pPhysX->createMaterial(.5f, .5f, 1.2f);

	//Ground Plane
	const auto pGroundActor = pPhysX->createRigidStatic(PxTransform({ PxPiDivTwo, {0, 0, 1} }));
	PxRigidActorExt::createExclusiveShape(*pGroundActor, PxPlaneGeometry{}, *pDefaultMaterial);
	m_pPhysxScene->addActor(*pGroundActor);

	//Level
	m_pLevel = new MeshObject(L"Resources/Meshes/Level.ovm");

	const auto pTriangleMesh = ContentManager::GetInstance()->Load<PxTriangleMesh>(L"Resources/Meshes/Level.ovpt");
	const auto pTriangleActor = pPhysX->createRigidDynamic(PxTransform{ PxIdentity });
	pTriangleActor->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);
	PxRigidActorExt::createExclusiveShape(*pTriangleActor, PxTriangleMeshGeometry{ pTriangleMesh }, *pDefaultMaterial);

	m_pLevel->AttachRigidActor(pTriangleActor);
	AddGameObject(m_pLevel);
}

void W2_AssignmentScene::Update()
{
}

void W2_AssignmentScene::Draw() const
{
}

void W2_AssignmentScene::OnSceneActivated()
{
}

void W2_AssignmentScene::OnSceneDeactivated()
{
}
