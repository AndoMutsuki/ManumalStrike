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

	//int�^�̃X���C�_�[�̏���
	void SetSliderIntProcess(const char _name[100], const int& _value, const int _min, const int _max);

	//float�^�̃X���C�_�[�̏���
	void SetSliderFloatProcess(const char _name[100], const float& _value, const float _min, const float _max);

	//�`�F�b�N�{�b�N�X�̏���
	void SetCheckBox(const char _name[100], const bool& _flg);

	const int GetSliderInt(const char _name[100]);

	const float GetSliderFloat(const char _name[100]);

	const bool GetSliderBool(const char _name[100]);


private:

	ImGuiManager() {};

	void ChangeImGuiDenote();

	//int�^�̒l��\�����鏈��
	void TextIntProcess();

	//float�^�̒l��\�����鏈��
	void TextFloatProcess();

	//int�^�̃X���C�_�[�̏���
	void SliderIntProcess();

	//float�^�̃X���C�_�[�̏���
	void SliderFloatProcess();

	//�`�F�b�N�{�b�N�X�̏���
	void CheckBox();

	//���O�ƒl(int)�̍\����
	struct StrigInt
	{
		char	name[100];
		int		value;
	};

	//���O�ƒl(float)�̍\����
	struct StrigFloat
	{
		char	name[100];
		float	value;
	};

	//���O�ƒl(int)�ƍő�ŏ��̍\����
	struct StrigIntMinMax
	{
		char	name[100];
		int		value;
		int		min;
		int		max;
	};

	//���O�ƒl(float)�ő�ŏ��̍\����
	struct StrigFloatMinMax
	{
		char	name[100];
		float	value;
		float	min;
		float	max;
	};

	//���O�ƒl(bool)�̍\����
	struct StringBool
	{
		char	name[100];
		bool	flg;
	};

	bool ImGuiDenote;	//ImGui�\������t���O

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