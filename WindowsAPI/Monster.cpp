#include "pch.h"
#include "Monster.h"
#include "InputManager.h"

Monster::Monster() : Object(ObjectType::Monster)
{
}

Monster::~Monster()
{
}

void Monster::Init()
{
	_stat.hp = 100;
	_stat.maxHp = 100;
	_stat.speed = 10;
	
	_pos = Pos{ 400, 300 };

	_lookPos = Pos{ 400, 70 };
	_lookDir = _lookPos - _pos;
	_lookDir.Normalize();
}

void Monster::Update()
{
	/*Vector mousePos = GET_SINGLE(InputManager)->GetMousePos();
	Vector v1 = _end = _start;
	Vector v2 = mousePos - _start;

	float maxLength = v1.Length();
	v1.Normalize();

	float dot = v1.Dot(v2);
	Pos pos = _start + v1 * dot;

	if (dot <   0 || dot>maxLength)
		return;

	_pos = pos;*/
}

void Monster::Render(HDC hdc)
{
	Utils::DrawCircle(hdc, _pos, 100);

	//FrontDir
	HPEN pen = ::CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	HPEN oldPen = (HPEN)::SelectObject(hdc, pen);
	{
		/*Utils::DrawLine(hdc, _pt1, _pt2);
		Utils::DrawLine(hdc, _pt2, _pt3);
		Utils::DrawLine(hdc, _pt3, _pt1);*/

		Utils::DrawLine(hdc, _pos, _lookPos);
		
	}
	::SelectObject(hdc, oldPen);
	::DeleteObject(pen);

	////
	Vector mousePos = GET_SINGLE(InputManager)->GetMousePos();
	Vector monsterToMouseDir = mousePos - _pos;
	monsterToMouseDir.Normalize();

	Vector dir = _lookDir;
	dir.Normalize();

	float dot = monsterToMouseDir.Dot(dir);
	float radian = ::acos(dot);
	float angle = radian * 180 / 3.14f;

	//1)
	float cross = _lookDir.Cross(monsterToMouseDir);
	if (cross < 0)
		angle = 360 - angle;
	{
		wstring str = format(L"angle({0})", angle);
		Utils::DrawTextW(hdc, { 20, 50 }, str);
	
	}

	/////

	/*Utils::DrawLine(hdc, _pt1, mousePos);

	Vector v12 = _pt2 - _pt1;
	Vector v1m = mousePos - _pt1;
	Vector v13 = _pt3 - _pt1;

	v12.Normalize();
	v1m.Normalize();
	v13.Normalize();

	float c1 = v12.Cross(v1m);
	float c2 = v1m.Cross(v13);

	if (c1 >= 0 && c2 >= 0)
	{

	}
	else
	{

	}  

	wstring str = std::format(L"c1({0}), c2({1})", c1, c2);
	Utils::DrawTextW(hdc, { 20, 50 }, str);*/
}
