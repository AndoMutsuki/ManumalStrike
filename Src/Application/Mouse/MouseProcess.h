#pragma once

//�}�E�X�̏���
class MouseProcess
{
public:

	MouseProcess();

	~MouseProcess();

	const POINT& Update(const POINT& _mousePos);

private:

	POINT m_mouse;
};