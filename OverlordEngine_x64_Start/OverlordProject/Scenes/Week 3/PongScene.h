#pragma once

class CubePrefab;
class SpherePrefab;

class PongScene final : public GameScene
{
public:
	PongScene() : GameScene(L"Pong Scene") {};
	~PongScene() override = default;

	PongScene(const PongScene& other) = delete;
	PongScene(PongScene&& other) noexcept = delete;
	PongScene& operator=(const PongScene& other) = delete;
	PongScene& operator=(PongScene&& other) noexcept = delete;

protected:
	void Initialize() override;
	void Update() override;

	void PostInitialize() override;

private:
	GameObject* m_pPlayer1{nullptr};
	GameObject* m_pPlayer2{ nullptr };

	GameObject* m_pBall{ nullptr };

	enum InputIds
	{
		LeftUp,
		LeftDown,
		RightUp,
		RightDown,
		Go
	};

	void ResetBall();
};


