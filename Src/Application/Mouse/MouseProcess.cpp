#include"Application/Headers.h"

MouseProcess::MouseProcess()
{
}

MouseProcess::~MouseProcess()
{
}

const POINT& MouseProcess::Update(const POINT& _mousePos)
{
	m_mouse = _mousePos;
	GetCursorPos(&m_mouse);
	ScreenToClient(APP.m_window.GetWndHandle(), &m_mouse);

	m_mouse.x -= 640;
	m_mouse.y = -m_mouse.y + 360;
	return m_mouse;
}
