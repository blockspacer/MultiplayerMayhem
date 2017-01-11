#pragma once
#include "SceneManager.h"
#include "Player.h"
#include "Enemy.h"
#include "Net.h"
#include "Button.h"
#include "GameUI.h"
#include "Countdown.h"

class GameScene : public Scene
{
private:
	Net * net;
	GameUI * ui;
	Player * m_player;
	vector<Enemy*> m_enemys;
	bool m_isHost;

	Countdown * m_counter;
	float currentTime;
	map<string, map<int, float>> m_pingmsg;

	void ResetRound();
	void HandleMessages();
	void HostOperations(float deltaTime);
public:
	GameScene();

	void Update(float deltaTime) override;
	void Render(RenderWindow & r) override;
	void Destroy() override;
	void Enter() override;

	vector<string> DeserializeMessage(string message);

	static bool IsStarted;
};
