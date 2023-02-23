#include "stdafx.h"
#include "BouncingBallScene.h"

#include "SpherePosColorNorm.h"
#include "Logger.h"

void BouncingBallScene::Initialize()
{
	EnablePhysxDebugRendering(true);

	const auto pPhysX = PhysxManager::GetInstance()->GetPhysics();
	const PxMaterial* pBall1Material = pPhysX->createMaterial(.5f, .5f, 1.f);
	const PxMaterial* pBall2Material = pPhysX->createMaterial(.5f, .5f, .5f);
	const PxMaterial* pBall3Material = pPhysX->createMaterial(.5f, .5f, 0.f);

	//Spheres
	const float ballSize{ 1.f };

	m_pBall1 = new SpherePosColorNorm{ballSize, 5, 5, XMFLOAT4(Colors::Green)};
	AddGameObject(m_pBall1);
	m_pBall1->Translate(-5.f, 10.f, 0.f);

	m_pBall2 = new SpherePosColorNorm{ ballSize, 5, 5, XMFLOAT4(Colors::Green) };
	AddGameObject(m_pBall2);
	m_pBall2->Translate(0.f, 10.f, 0.f);

	m_pBall3 = new SpherePosColorNorm{ ballSize, 5, 5, XMFLOAT4(Colors::Green) };
	AddGameObject(m_pBall3);
	m_pBall3->Translate(5.f, 10.f, 0.f);

	//Sphere actor
	PxRigidDynamic* pSphere1Actor = pPhysX->createRigidDynamic(PxTransform{ PxIdentity });
	PxSphereGeometry sphere1Geometry = PxSphereGeometry{ ballSize };

	PxRigidActorExt::createExclusiveShape(*pSphere1Actor, sphere1Geometry, *pBall1Material);
	m_pBall1->AttachRigidActor(pSphere1Actor);

	PxRigidDynamic* pSphere2Actor = pPhysX->createRigidDynamic(PxTransform{ PxIdentity });
	PxSphereGeometry sphere2Geometry = PxSphereGeometry{ ballSize };

	PxRigidActorExt::createExclusiveShape(*pSphere2Actor, sphere2Geometry, *pBall2Material);
	m_pBall2->AttachRigidActor(pSphere2Actor);

	PxRigidDynamic* pSphere3Actor = pPhysX->createRigidDynamic(PxTransform{ PxIdentity });
	PxSphereGeometry sphere3Geometry = PxSphereGeometry{ ballSize };

	PxRigidActorExt::createExclusiveShape(*pSphere3Actor, sphere3Geometry, *pBall3Material);
	m_pBall3->AttachRigidActor(pSphere3Actor);





	const auto pGroundActor = pPhysX->createRigidStatic(PxTransform{ PxQuat{PxPiDivTwo, PxVec3{0, 0, 1}} });
	PxRigidActorExt::createExclusiveShape(*pGroundActor, PxPlaneGeometry{ }, *pBall3Material);
	m_pPhysxScene->addActor(*pGroundActor);
}

void BouncingBallScene::Update()
{
	if (m_SceneContext.GetInput()->IsKeyboardKey(InputTriggerState::pressed, 'R'))
	{
		m_pBall1->Translate(-5.f, 10.f, 0.f);
		m_pBall2->Translate(0.f, 10.f, 0.f);
		m_pBall3->Translate(5.f, 10.f, 0.f);
	}
}

void BouncingBallScene::Draw() const
{
}

void BouncingBallScene::OnSceneActivated()
{
}

void BouncingBallScene::OnSceneDeactivated()
{
}
