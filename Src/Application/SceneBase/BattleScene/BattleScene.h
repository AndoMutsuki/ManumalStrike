#pragma once

class BattleScene
{
public:

	BattleScene();

	~BattleScene();

	void Update();

	void Draw();

private:

	Math::Matrix m_mat1;
	Math::Matrix m_mat2;

};
