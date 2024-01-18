#pragma once
class SGame
{
public:
	SGame();
	~SGame();
public:
	void Init(HWND hwnd);
	void Update();
	void Render();
private:
	HWND _hwnd = {};
	HDC _hdc = {};

private:
	//Double Buffering
	RECT _rect;
	HDC _hdcBack = {};
	HBITMAP _bmpBack = {};


};

