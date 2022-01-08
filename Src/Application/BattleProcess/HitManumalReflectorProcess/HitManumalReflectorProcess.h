#pragma once

class HitManumalReflectorProcess
{
public:

	HitManumalReflectorProcess();

	~HitManumalReflectorProcess();

	void Update(manumalData& _manumalData, ReflectorProcess* _reflectorProcess);

private:

	manumalData m_manumalData;
	ReflectorProcess* m_reflectorProcess = nullptr;

};