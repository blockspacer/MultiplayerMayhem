#pragma once
#include "SceneManager.h"
#include "LobbyUI.h"

class LobbyScene : public Scene
{
private:
	LobbyUI * ui;
public:
	LobbyScene();

	void Update(float deltaTime) override;
	void Render(RenderWindow & r) override;
	void Destroy() override;
	void Enter() override;
};