#include"Application/Headers.h"

ImGuiManager::~ImGuiManager()
{
	m_textInt.clear();
	m_textfloat.clear();
	m_sliderInt.clear();
	m_sliderFloat.clear();
	m_checkBoxFlg.clear();
}

void ImGuiManager::Update()
{
	ChangeImGuiDenote();

	if (!ImGuiDenote) return;

	ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_Once);

	// デバッグウィンドウ
	if (ImGui::Begin("Debug Window"))
	{
		TextIntProcess();

		TextFloatProcess();

		SliderIntProcess();

		SliderFloatProcess();

		CheckBox();
	}
	ImGui::End();
}

void ImGuiManager::SetTextInt(const char _name[100], const int _value)
{
	bool beenFlg = false;	//すでにあるかどうか
	for (UINT i = 0; i < m_textIntNmae.size(); i++)
	{
		beenFlg = m_textIntNmae[i] == _name;
	}
	if (beenFlg) return;

	StrigInt tmpData;
	strcpy_s(tmpData.name, _name);
	tmpData.value = _value;

	m_textInt.push_back(tmpData);

	m_textIntNmae.push_back(_name);
}

void ImGuiManager::SetTextFloat(const char _name[100], const float _value)
{
	bool beenFlg = false;	//すでにあるかどうか
	for (UINT i = 0; i < m_textFloatName.size(); i++)
	{
		beenFlg = m_textFloatName[i] == _name;
	}
	if (beenFlg) return;

	StrigFloat tmpData;
	strcpy_s(tmpData.name, _name);
	tmpData.value = _value;

	m_textfloat.push_back(tmpData);

	m_textFloatName.push_back(_name);
}

void ImGuiManager::SetSliderIntProcess(const char _name[100], const int& _value, const int _min, const int _max)
{
	if (m_sliderIntMap.find(_name) != m_sliderIntMap.end()) return;	//すでに表示していたら

	StrigIntMinMax tmpData;
	strcpy_s(tmpData.name, _name);
	tmpData.value	= _value;
	tmpData.min		= _min;
	tmpData.max		= _max;

	m_sliderInt[_name] = tmpData;
}

void ImGuiManager::SetSliderFloatProcess(const char _name[100], const float& _value, const float _min, const float _max)
{
	if (m_sliderFloat.find(_name) != m_sliderFloat.end()) 	//すでに表示していたら
	{
		m_sliderFloat[_name].value = _value;
		return;
	}

	StrigFloatMinMax tmpData;
	strcpy_s(tmpData.name, _name);
	tmpData.value = _value;
	tmpData.min = _min;
	tmpData.max = _max;

	m_sliderFloat[_name] = tmpData;
}

void ImGuiManager::SetCheckBox(const char _name[100], const bool& _flg)
{
	if (m_checkBoxFlgMap.find(_name) != m_checkBoxFlgMap.end()) return;	//すでに表示していたら

	StringBool tmpData;
	strcpy_s(tmpData.name, _name);
	tmpData.flg = _flg;

	m_checkBoxFlg[_name] = tmpData;
}

const int ImGuiManager::GetSliderInt(const char _name[100])
{
	return m_sliderIntMap[_name];
}

const float ImGuiManager::GetSliderFloat(const char _name[100])
{
	return m_sliderFloatMap[_name];
}

const bool ImGuiManager::GetSliderBool(const char _name[100])
{
	return m_checkBoxFlgMap[_name];
}

void ImGuiManager::ChangeImGuiDenote()
{
#ifdef DEBUG

	if (GetAsyncKeyState('I') & 0x8000)
	{
		ImGuiDenote = true;
	}

	if (GetAsyncKeyState('O') & 0x8000)
	{
		ImGuiDenote = false;
	}

#endif // DEBUG
}

void ImGuiManager::TextIntProcess()
{
	for (auto iter = m_textInt.begin(); iter != m_textInt.end(); ++iter)
	{
		ImGui::Text("%s : %d\n", iter->name, iter->value);
	}
}

void ImGuiManager::TextFloatProcess()
{
	for (auto iter = m_textfloat.begin(); iter != m_textfloat.end(); ++iter)
	{
		ImGui::Text("%s : %f\n", iter->name, iter->value);
	}
}

void ImGuiManager::SliderIntProcess()
{
	for (auto iter = m_sliderInt.begin(); iter != m_sliderInt.end(); ++iter)
	{
		ImGui::SliderInt(iter->second.name, &iter->second.value, iter->second.min, iter->second.max);
		m_sliderIntMap[iter->second.name] = iter->second.value;
	}
}

void ImGuiManager::SliderFloatProcess()
{
	for (auto iter = m_sliderFloat.begin(); iter != m_sliderFloat.end(); ++iter)
	{
		ImGui::SliderFloat(iter->second.name, &iter->second.value, iter->second.min, iter->second.max);
		m_sliderFloatMap[iter->second.name] = iter->second.value;
	}
}

void ImGuiManager::CheckBox()
{
	for (auto iter = m_checkBoxFlg.begin(); iter != m_checkBoxFlg.end(); ++iter)
	{
		ImGui::Checkbox(iter->second.name, &iter->second.flg);
		m_checkBoxFlgMap[iter->second.name] = iter->second.flg;
	}
}
