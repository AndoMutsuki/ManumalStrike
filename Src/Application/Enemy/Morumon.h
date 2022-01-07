#pragma once

class Morumon :public EnemyBase
{
public:

	Morumon();

	~Morumon();

	void Update();

	void Draw()const;

private:

	ManumalStrikeNamespace::manumalData m_manumalData;

};