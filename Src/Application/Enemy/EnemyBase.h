#pragma once

class EnemyBase
{
public:

	EnemyBase();

	virtual ~EnemyBase();

	virtual void Update();

	virtual void Draw()const;

	void SetManumalData(const ManumalStrikeNamespace::manumalData& _manumalData);

	virtual const ManumalStrikeNamespace::manumalData& GetManumalData()const;

private:

	ManumalStrikeNamespace::manumalData m_manumalData;

};