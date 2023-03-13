#include "stdafx.h"
#include "W2_AssignmentScene.h"
#include "PhysxManager.h"
#include "MeshObject.h"
#include "ContentManager.h"
#include "SoundManager.h"
#include "Logger.h"

#include "CubePosColorNorm.h"
#include "SpherePosColorNorm.h"

void W2_AssignmentScene::Initialize()
{
	EnablePhysxDebugRendering(true);

	const auto pPhysX = PhysxManager::GetInstance()->GetPhysics();
	const auto pDefaultMaterial = pPhysX->createMaterial(.5f, .5f, .2f);

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


	XMFLOAT3 boxDimensions{ 1.5f, .75f, 6.f };
	auto boxShape = PxBoxGeometry{boxDimensions.x/2, boxDimensions.y/2, boxDimensions.z/2  };

	//Blue Trigger
	m_pBlueTrigger = new CubePosColorNorm(boxDimensions.x, boxDimensions.y, boxDimensions.z , XMFLOAT4{Colors::Blue});
	AddGameObject(m_pBlueTrigger);

	auto pTriggerBody = pPhysX->createRigidStatic(PxTransform{PxIdentity});
	auto pShape = PxRigidActorExt::createExclusiveShape(*pTriggerBody, boxShape, *pDefaultMaterial);

	pShape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
	pShape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);

	m_pBlueTrigger->AttachRigidActor(pTriggerBody);

	m_pBlueTrigger->Translate(-7.5f, 2.5f, 0.f);

	//Red Trigger
	m_pRedTrigger = new CubePosColorNorm(boxDimensions.x, boxDimensions.y, boxDimensions.z, XMFLOAT4{ Colors::Red });
	AddGameObject(m_pRedTrigger);

	pTriggerBody = pPhysX->createRigidStatic(PxTransform{ PxIdentity });
	pShape = PxRigidActorExt::createExclusiveShape(*pTriggerBody, boxShape, *pDefaultMaterial);

	pShape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
	pShape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);

	m_pRedTrigger->AttachRigidActor(pTriggerBody);

	m_pRedTrigger->Translate(7.5f, 2.5f, 0.f);





	boxDimensions = XMFLOAT3{ 1.5f, 1.5f, 1.5f };
	boxShape = PxBoxGeometry{ boxDimensions.x / 2, boxDimensions.y / 2, boxDimensions.z / 2 };

	//Blue Box
	m_pBlueBox = new CubePosColorNorm(boxDimensions.x, boxDimensions.y, boxDimensions.z, XMFLOAT4{ Colors::Blue });
	AddGameObject(m_pBlueBox);

	auto pBoxBody = pPhysX->createRigidDynamic(PxTransform{ PxIdentity });
	PxRigidBodyExt::updateMassAndInertia(*pBoxBody, 0.1f);
	pShape = PxRigidActorExt::createExclusiveShape(*pBoxBody, boxShape, *pDefaultMaterial);

	m_pBlueBox->AttachRigidActor(pBoxBody);

	m_pBlueBox->Translate(-5.f, 5.f, 0.f);

	//Red Box
	m_pRedBox = new CubePosColorNorm(boxDimensions.x, boxDimensions.y, boxDimensions.z, XMFLOAT4{ Colors::Red });
	AddGameObject(m_pRedBox);

	pBoxBody = pPhysX->createRigidDynamic(PxTransform{ PxIdentity });
	PxRigidBodyExt::updateMassAndInertia(*pBoxBody, 0.1f);
	pShape = PxRigidActorExt::createExclusiveShape(*pBoxBody, boxShape, *pDefaultMaterial);

	m_pRedBox->AttachRigidActor(pBoxBody);

	m_pRedBox->Translate(4.5f, 5.f, 0.f);


	//LeftSphere
	m_pLeftSphere = new SpherePosColorNorm(1.f, 10, 10, XMFLOAT4(Colors::HotPink));
	AddGameObject(m_pLeftSphere);

	auto pSphereActor = pPhysX->createRigidDynamic(PxTransform{ PxIdentity });
	PxRigidActorExt::createExclusiveShape(*pSphereActor, PxSphereGeometry{ 1.f }, *pDefaultMaterial);
	m_pLeftSphere->AttachRigidActor(pSphereActor);

	m_pLeftSphere->Translate(-4.f, 25.f, 0.f);

	//RightSphere
	m_pRightSphere = new SpherePosColorNorm(1.f, 10, 10, XMFLOAT4(Colors::HotPink));
	AddGameObject(m_pRightSphere);

	pSphereActor = pPhysX->createRigidDynamic(PxTransform{ PxIdentity });
	PxRigidActorExt::createExclusiveShape(*pSphereActor, PxSphereGeometry{ 1.f }, *pDefaultMaterial);
	m_pRightSphere->AttachRigidActor(pSphereActor);

	m_pRightSphere->Translate(4.f, 25.f, 0.f);



	boxDimensions = XMFLOAT3{ 1.5f, .75f, 12.f };
	boxShape = PxBoxGeometry{ boxDimensions.x / 2, boxDimensions.y / 2, boxDimensions.z / 2 };

	//Blue Hatch
	m_pBlueHatch = new CubePosColorNorm(boxDimensions.x, boxDimensions.y, boxDimensions.z, XMFLOAT4{ Colors::Blue });
	AddGameObject(m_pBlueHatch);

	auto pHatchActor = pPhysX->createRigidDynamic(PxTransform{ PxIdentity});
	pHatchActor->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);
	pShape = PxRigidActorExt::createExclusiveShape(*pHatchActor, boxShape, *pDefaultMaterial);

	m_pBlueHatch->AttachRigidActor(pHatchActor);
	m_pBlueHatch->Translate(-9.f, 17.f, 4.f);

	//Red Hatch
	m_pRedHatch = new CubePosColorNorm(boxDimensions.x, boxDimensions.y, boxDimensions.z, XMFLOAT4{ Colors::Red });
	AddGameObject(m_pRedHatch);

	pHatchActor = pPhysX->createRigidDynamic(PxTransform{ PxIdentity });
	pHatchActor->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);
	pShape = PxRigidActorExt::createExclusiveShape(*pHatchActor, boxShape, *pDefaultMaterial);

	m_pRedHatch->AttachRigidActor(pHatchActor);
	m_pRedHatch->Translate(9.f, 17.f, 4.f);



	//Sound
	const auto pFmod = SoundManager::GetInstance()->GetSystem();
	FMOD_RESULT result = pFmod->createSound("Resources/Sounds/bell.mp3", FMOD_DEFAULT, nullptr, &m_pBellSound);
	SoundManager::GetInstance()->ErrorCheck(result);


	//Sphere
	m_pSphere = new SpherePosColorNorm(1.f, 10, 10, XMFLOAT4(Colors::HotPink));
	AddGameObject(m_pSphere);

	pSphereActor = pPhysX->createRigidDynamic(PxTransform{ PxIdentity });
	PxRigidActorExt::createExclusiveShape(*pSphereActor, PxSphereGeometry{ 1.f }, * pDefaultMaterial);
	PxRigidBodyExt::updateMassAndInertia(*pSphereActor, 5.f);
	m_pSphere->AttachRigidActor(pSphereActor);

	m_pSphere->Translate(0.f, 10.f, 0.f);
}

void W2_AssignmentScene::Update()
{
	

	const auto pInput = m_SceneContext.GetInput();

	if (pInput->IsKeyboardKey(InputTriggerState::down, VK_LEFT))
	{
		m_pSphere->GetRigidActor()->is<PxRigidDynamic>()->addTorque({ 0,0, 50.f });
	}

	if (pInput->IsKeyboardKey(InputTriggerState::down, VK_RIGHT))
	{
		m_pSphere->GetRigidActor()->is<PxRigidDynamic>()->addTorque({ 0,0, -50.f });
	}

	if (pInput->IsKeyboardKey(InputTriggerState::pressed, VK_SPACE))
	{
		m_pSphere->GetRigidActor()->is<PxRigidDynamic>()->addForce({0.f, 250.f, 0.f}, PxForceMode::eIMPULSE);
	}
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

void W2_AssignmentScene::onTrigger(PxTriggerPair* pairs, PxU32 count)
{
	for (auto i{ 0 }; i < count; i++)
	{
		//ignore deleted shapes
		if (pairs[i].flags & (PxTriggerPairFlag::eREMOVED_SHAPE_OTHER | PxTriggerPairFlag::eREMOVED_SHAPE_OTHER))
			continue;

		const PxTriggerPair& pair = pairs[i];

		if (pair.triggerActor == m_pBlueTrigger->GetRigidActor() && pair.otherActor == m_pBlueBox->GetRigidActor())//blue trigger
		{
			if (pair.status == PxPairFlag::eNOTIFY_TOUCH_FOUND)//entered
			{
				const auto pFmod = SoundManager::GetInstance()->GetSystem();
				FMOD_RESULT result = pFmod->playSound(m_pBellSound, 0, false, &m_pChannel2D);
				SoundManager::GetInstance()->ErrorCheck(result);

				m_pBlueHatch->Rotate(-PxHalfPi, 0, 0);
			}
		}

		if (pair.triggerActor == m_pRedTrigger->GetRigidActor() && pair.otherActor == m_pRedBox->GetRigidActor())//blue trigger
		{
			if (pair.status == PxPairFlag::eNOTIFY_TOUCH_FOUND)//entered
			{
				const auto pFmod = SoundManager::GetInstance()->GetSystem();
				FMOD_RESULT result = pFmod->playSound(m_pBellSound, 0, false, &m_pChannel2D);
				SoundManager::GetInstance()->ErrorCheck(result);

				m_pRedHatch->Rotate(-PxHalfPi, 0, 0);
			}
		}
	}


}
