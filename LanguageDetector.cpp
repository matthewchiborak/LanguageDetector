#include "LanguageDetector.h"

#include <Windows.h>
#include <sstream>
#include <cwctype>
#include <codecvt>
#include <iostream>

#include "resource.h"

HMODULE GCM()
{
	HMODULE hModule = NULL;
	GetModuleHandleEx(
		GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS,
		(LPCTSTR)GCM,
		&hModule);
	return hModule;
}

CLanguage::CLanguage(const std::wstring sID, const int iWordListID)
	: m_sID(sID)
{
	HRSRC hRes = FindResource(GCM(), MAKEINTRESOURCE(iWordListID), MAKEINTRESOURCE(TEXTFILE));
	HGLOBAL hData = LoadResource(GCM(), hRes);
	DWORD hSize = SizeofResource(GCM(), hRes);
	char* hFinal = (char*)LockResource(hData);

	std::string sWordListData;
	sWordListData.assign(hFinal, hSize);

	std::wstring sWordList = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(sWordListData);

	std::wstringstream ssWordList(sWordList);
	std::wstring sLine;
	std::getline(ssWordList, sLine);
	double totalScore = std::stod(sLine.substr(sLine.find(' '), std::string::npos));

	while (std::getline(ssWordList, sLine))
	{
		m_aWordList.insert(std::pair<std::wstring, double>(sLine.substr(0, sLine.find(' ')), std::stod(sLine.substr(sLine.find(' '), std::string::npos)) / totalScore));
	}
}

double CLanguage::GetWordScore(const std::wstring& sWord) const
{
	if(m_aWordList.find(sWord) == m_aWordList.end())
		return 0;

	return m_aWordList.at(sWord);
}

std::wstring CLanguage::GetID() const
{
	return m_sID;
}

CLanguageDetector::CLanguageDetector()
{
	m_aLanguages.push_back(std::move(std::make_unique<CLanguage>(L"en", LANGUAGE_DETECTOR_WORDLIST_EN)));
	m_aLanguages.push_back(std::move(std::make_unique<CLanguage>(L"da", LANGUAGE_DETECTOR_WORDLIST_DA)));
	m_aLanguages.push_back(std::move(std::make_unique<CLanguage>(L"de", LANGUAGE_DETECTOR_WORDLIST_DE)));
	m_aLanguages.push_back(std::move(std::make_unique<CLanguage>(L"es", LANGUAGE_DETECTOR_WORDLIST_ES)));
	m_aLanguages.push_back(std::move(std::make_unique<CLanguage>(L"fr", LANGUAGE_DETECTOR_WORDLIST_FR)));
	m_aLanguages.push_back(std::move(std::make_unique<CLanguage>(L"it", LANGUAGE_DETECTOR_WORDLIST_IT)));
	m_aLanguages.push_back(std::move(std::make_unique<CLanguage>(L"nb", LANGUAGE_DETECTOR_WORDLIST_NB)));
	m_aLanguages.push_back(std::move(std::make_unique<CLanguage>(L"pl", LANGUAGE_DETECTOR_WORDLIST_PL)));
	m_aLanguages.push_back(std::move(std::make_unique<CLanguage>(L"pt", LANGUAGE_DETECTOR_WORDLIST_PT)));
	m_aLanguages.push_back(std::move(std::make_unique<CLanguage>(L"sv", LANGUAGE_DETECTOR_WORDLIST_SV)));
}

std::wstring CLanguageDetector::DetectLanguage(const std::wstring& sText)
{
	if (m_aLanguages.size() <= 0)
		return L"Unknown";

	std::vector<std::unique_ptr<CLanguageScoreTracker>> aTrackers(m_aLanguages.size());

	for (unsigned int i = 0; i < m_aLanguages.size(); ++i)
	{
		aTrackers[i].reset(new CLanguageScoreTracker(*m_aLanguages[i].get()));
	}

	std::wstring sWord;
	std::wstringstream ssText(sText);

	while (std::getline(ssText, sWord, L' '))
	{
		for(unsigned int i = 0; i < aTrackers.size(); ++i)
		{
			aTrackers[i]->ProcessWord(sWord);	
		}
	}

	int iCurrentMax = 0;
	for (unsigned int i = 1; i < aTrackers.size(); ++i)
	{
		if (aTrackers[i]->GetScore() > aTrackers[iCurrentMax]->GetScore())
			iCurrentMax = i;
	}

	std::wcout << L"Scores: \n";

	for (unsigned int i = 0; i < aTrackers.size(); ++i)
	{
		std::wcout << aTrackers[i]->GetLanguageCode() << L": " << aTrackers[i]->GetScore() << std::endl;
	}

	return aTrackers[iCurrentMax]->GetLanguageCode();
}

CLanguageScoreTracker::CLanguageScoreTracker(CLanguage& oLanguage)
	: m_oLanguage(oLanguage), m_iScore(0)
{
}

void CLanguageScoreTracker::ProcessWord(const std::wstring& sWord)
{
	m_iScore += m_oLanguage.GetWordScore(sWord);
}

double CLanguageScoreTracker::GetScore() const
{
	return m_iScore;
}

std::wstring CLanguageScoreTracker::GetLanguageCode() const
{
	return m_oLanguage.GetID();
}
