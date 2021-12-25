#pragma once

class BattleScene
{
public:

	BattleScene();

	~BattleScene();

	void Update();

	void Draw();

private:

	Math::Vector3 mMmat1;
	Math::Vector3 mMmat2;

};
