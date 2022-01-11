#pragma once

class ImGuiManager
{
public:

	static ImGuiManager& GetInstance()
	{
		static ImGuiManager instance;

		return instance;
	}

	~ImGuiManager();

	void Update();

	void SetTextInt(const char _name[100], const int _value);

	void SetTextFloat(const char _name[100], const float _value);

	//int型のスライダーの処理
	void SetSliderIntProcess(const char _name[100], const int& _value, const int _min, const int _max);

	//float型のスライダーの処理
	void SetSliderFloatProcess(const char _name[100], const float& _value, const float _min, const float _max);

	//チェックボックスの処理
	void SetCheckBox(const char _name[100], const bool& _flg);

	const int GetSliderInt(const char _name[100]);

	const float GetSliderFloat(const char _name[100]);

	const bool GetSliderBool(const char _name[100]);


private:

	ImGuiManager() {};

	void ChangeImGuiDenote();

	//int型の値を表示する処理
	void TextIntProcess();

	//float型の値を表示する処理
	void TextFloatProcess();

	//int型のスライダーの処理
	void SliderIntProcess();

	//float型のスライダーの処理
	void SliderFloatProcess();

	//チェックボックスの処理
	void CheckBox();

	//名前と値(int)の構造体
	struct StrigInt
	{
		char	name[100];
		int		value;
	};

	//名前と値(float)の構造体
	struct StrigFloat
	{
		char	name[100];
		float	value;
	};

	//名前と値(int)と最大最小の構造体
	struct StrigIntMinMax
	{
		char	name[100];
		int		value;
		int		min;
		int		max;
	};

	//名前と値(float)最大最小の構造体
	struct StrigFloatMinMax
	{
		char	name[100];
		float	value;
		float	min;
		float	max;
	};

	//名前と値(bool)の構造体
	struct StringBool
	{
		char	name[100];
		bool	flg;
	};

	bool ImGuiDenote;	//ImGui表示するフラグ

	std::vector<StrigInt>		m_textInt;
	std::vector<StrigFloat>		m_textfloat;
	std::vector<std::string>	m_textIntNmae;
	std::vector<std::string>	m_textFloatName;

	std::map <std::string, StrigIntMinMax>	m_sliderInt;
	std::map <std::string,StrigFloatMinMax>	m_sliderFloat;
	std::map<std::string, int>				m_sliderIntMap;
	std::map<std::string, float>			m_sliderFloatMap;

	std::map <std::string, StringBool>	m_checkBoxFlg;
	std::map<std::string, bool>			m_checkBoxFlgMap;
};
#define IMGUIMANA ImGuiManager::GetInstance()