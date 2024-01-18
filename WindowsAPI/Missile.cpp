#include "pch.h"
#include "Missile.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "ObjectManager.h"

Missile::Missile() : Object(ObjectType::Projectile)
{
}

Missile::~Missile()
{
}

void Missile::Init()
{
	//TODO:: Data
	_stat.hp = 1;
	_stat.maxHp = 1;
	_stat.speed = 600;
}

void Missile::Update()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	//삼각함수를 이용해 포신 방향대로 미사일 날리기
	//_pos.x += _stat.speed * deltaTime * ::cos(_angle);
	//_pos.y -= _stat.speed * deltaTime * ::sin(_angle);

	//벡터를 이용 유도탄 날리기
	if (_target == nullptr)
	{
		_pos.x += _stat.speed * deltaTime * ::cos(_angle);
		_pos.y -= _stat.speed * deltaTime * ::sin(_angle);

		_sumTime += deltaTime;
		if (_sumTime >= 0.2f)
		{
			const vector<Object*>& objects = GET_SINGLE(ObjectManager)->GetObjects();
			for (Object* object : objects)
			{
				if (object->GetObjectType() == ObjectType::Monster)
				{
					_target = object;
					break;
				}
			}

		}
	}
	else
	{
		Vector dir = _target->GetPos() - GetPos(); // 타켓의 좌표에서 내 좌표를 빼서 방향 벡터를 구함
		dir.Normalize();
		Vector moveDir = dir* _stat.speed* deltaTime;
		_pos += moveDir;
	}

	// 충돌
	const vector<Object*> objects = GET_SINGLE(ObjectManager)->GetObjects();
	for (Object* object : objects)
	{
		if (object == this)
			continue;

		if (object->GetObjectType() != ObjectType::Monster)
			continue;

		Vector p1 = GetPos();
		Vector p2 = object->GetPos();

		/*const float dx = p1.x - p2.x;
		const float dy = p1.y - p2.y;

		float dist = sqrt(dx * dx + dy * dy);*/

		Vector dir = p2 - p1;
		float dist = dir.Length();

		if (dist < 25)
		{
			GET_SINGLE(ObjectManager)->Remove(object);
			GET_SINGLE(ObjectManager)->Remove(this);
			return;
		}
	}

	//TODO
	if (_pos.y <= -100)
	{
		GET_SINGLE(ObjectManager)->Remove(this);
		return;
	}


}

void Missile::Render(HDC hdc)
{
	Utils::DrawCircle(hdc, _pos, 25);
}
