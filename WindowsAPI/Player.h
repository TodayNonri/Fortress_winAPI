#pragma once
#include "Object.h"


class Player :public Object
{
public:
	Player();
	virtual ~Player() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	Pos GetFirePos();

	wstring GetMeshKey();
	
	void SetPlayerType(PlayerType playerType) { _playerType = playerType; }
	void SetPlayerId(int32 playerId) { _playerId = playerId; }
	void SetPlayerTurn(bool playerTurn) { _playerTurn = playerTurn; }

	int32 GetPlayerId() { return _playerId; }
	PlayerType GetPlayerType() { return _playerType; }
	bool GetPlayerTurn() { return _playerTurn; }

	void UpdateFireAngle();

public:
	float _barrelAngle = 0.f;
	float _barrelLength = 100.f;

	int32 _playerId = 0;
	PlayerType _playerType = PlayerType::CanonTank;
	bool _playerTurn = false;
	float _fireAngle = 0.f;
};

