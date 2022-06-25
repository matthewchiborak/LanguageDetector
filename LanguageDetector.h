#pragma once

#include <string>
#include <set>
#include <vector>
#include <memory>

class CLanguage
{
public:
	CLanguage(const std::wstring sID, const int iWordListID);

	bool HasWord(const std::wstring& sWord);
	std::wstring GetID();

private:
	std::set<std::wstring> m_aWordList;
	std::wstring m_sID;
};

class CLanguageScoreTracker
{
public:
	CLanguageScoreTracker(CLanguage& oLanguage);

	void ProcessWord(const std::wstring& sWord);
	int GetScore();
	std::wstring GetLanguageCode();

private:
	CLanguage& m_oLanguage;
	int m_iScore;
};

class CLanguageDetector
{
public:
	CLanguageDetector();

	std::wstring DetectLanguage(const std::wstring& sText);

private:
	std::vector< std::unique_ptr<CLanguage> > m_aLanguages;
};

