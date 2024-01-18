#include "pch.h"
#include "Player.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "ObjectManager.h"
#include "ResourceManager.h"
#include "LineMesh.h"
#include "UIManager.h"
#include "Bullet.h"

Player::Player() : Object(ObjectType::Player)
{

}

Player::~Player()
{
}

void Player::Init()
{
	//TODO :: Data
	_stat.hp = 100;
	_stat.maxHp = 100;
	_stat.speed = 500;

	_pos.x = 400;
	_pos.y = 500;

}

void Player::Update()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	//거리 = 시간*속도
	if (_playerTurn == false)
		return;

	UpdateFireAngle();

	if (GET_SINGLE(InputManager)->GetButton(KeyType::A))
	{
		_pos.x -= deltaTime * _stat.speed;

		_dir = Dir::Left;
	}
	if (GET_SINGLE(InputManager)->GetButton(KeyType::D))
	{
		_pos.x += deltaTime * _stat.speed;

		_dir = Dir::Right;
	}
	if (GET_SINGLE(InputManager)->GetButton(KeyType::W))
	{
		_fireAngle = ::clamp(_fireAngle + 50 * deltaTime, 0.f, 75.f);
		//_pos.y -= deltaTime * _stat.speed;
	}
	if (GET_SINGLE(InputManager)->GetButton(KeyType::S))
	{
		_fireAngle = ::clamp(_fireAngle - 50 * deltaTime, 0.f, 75.f);
		//_pos.y += deltaTime * _stat.speed;
	}
	if (GET_SINGLE(InputManager)->GetButton(KeyType::Q))
	{
		//_barrelAngle += 10*deltaTime;
	}
	if (GET_SINGLE(InputManager)->GetButton(KeyType::E))
	{
		//_barrelAngle -= 10 * deltaTime;
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::SpaceBar))
	{
		//미사일 발사
		/*Missile* missile = GET_SINGLE(ObjectManager)->CreateObject<Missile>();
		missile->SetPos(GetFirePos());
		missile->SetAngle(_barrelAngle);
		GET_SINGLE(ObjectManager)->Add(missile);*/
		float percent = GET_SINGLE(UIManager)->GetPowerPercent();
		percent = min(100, percent + 100 * deltaTime);
		GET_SINGLE(UIManager)->SetPowerPercent(percent);
	}if (GET_SINGLE(InputManager)->GetButtonUp(KeyType::SpaceBar))
	{
		//슈팅
		_playerTurn = false;

		float percent = GET_SINGLE(UIManager)->GetPowerPercent();
		float speed = 10.f * percent;
		float angle = GET_SINGLE(UIManager)->GetBarrelAngle();

		//TODO
		Bullet* bullet = GET_SINGLE(ObjectManager)->CreateObject<Bullet>();
		bullet->SetOwner(this);
		bullet->SetPos(_pos);
		bullet->SetSpeed(Vector{ speed * ::cos(angle * PI / 180), -1* speed * ::sin(angle * PI / 180) });
		GET_SINGLE(ObjectManager)->Add(bullet);

	}
}

void Player::Render(HDC hdc)
{
	//Utils::DrawCircle(hdc, _pos, 50);
	if (_dir == Dir::Left)
	{
		const LineMesh* mesh = GET_SINGLE(ResourceManager)->GetLineMesh(GetMeshKey());
		if (mesh)
			mesh->Render(hdc, _pos, 0.5f, 0.5f);
	}
	else
	{
		const LineMesh* mesh = GET_SINGLE(ResourceManager)->GetLineMesh(GetMeshKey());
		if (mesh)
			mesh->Render(hdc, _pos, -0.5f, 0.5f);
	}

	if (_playerTurn)
	{
		RECT rect;
		rect.bottom = static_cast<LONG>(_pos.y-60);
		rect.left = static_cast<LONG>(_pos.x-10);
		rect.right = static_cast<LONG>(_pos.x+10);
		rect.top = static_cast<LONG>(_pos.y-80);
		

		HBRUSH Brush, oBrush;
		Brush = ::CreateSolidBrush(RGB(255, 236, 197));
		oBrush = (HBRUSH)::SelectObject(hdc, Brush);

		::Ellipse(hdc, rect.left, rect.top, rect.right, rect.bottom);

		::SelectObject(hdc, oBrush);
		::DeleteObject(Brush);
	}
	

	HPEN pen = ::CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	HPEN oldPen = (HPEN)::SelectObject(hdc, pen);

	//Utils::DrawLine(hdc, _pos, GetFirePos());

	::SelectObject(hdc, oldPen);
	::DeleteObject(pen);
}

Pos Player::GetFirePos()
{
	Pos firePos = _pos;

	firePos.x += _barrelLength * ::cos(_barrelAngle);
	firePos.y -= _barrelLength * ::sin(_barrelAngle);

	return firePos;
}

wstring Player::GetMeshKey()
{
	if (_playerType == PlayerType::MissileTank)
		return L"MissileTank";
	if (_playerType == PlayerType::CanonTank)
		return L"CanonTank";
}

void Player::UpdateFireAngle()
{
	if (_dir == Dir::Left)
	{
		GET_SINGLE(UIManager)->SetPlayerAngle(180);
		GET_SINGLE(UIManager)->SetBarrelAngle(180-_fireAngle);
	}
	else
	{
		GET_SINGLE(UIManager)->SetPlayerAngle(0);
		GET_SINGLE(UIManager)->SetBarrelAngle(_fireAngle);
	}
}
