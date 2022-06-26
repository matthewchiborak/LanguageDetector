#pragma once

#include <string>
#include <map>
#include <vector>
#include <memory>

/*class CWordInfo
{
public:
	CWordInfo(const std::wstring sWord, const int iScore);

	std::wstring GetWord() const;
	int GetScore() const;

private:
	std::wstring m_sWord;
	int m_iScore;
};*/

class CLanguage
{
public:
	CLanguage(const std::wstring sID, const int iWordListID);

	int GetWordScore(const std::wstring& sWord) const;
	std::wstring GetID() const;

private:
	std::map<std::wstring, int> m_aWordList;
	std::wstring m_sID;
};

class CLanguageScoreTracker
{
public:
	CLanguageScoreTracker(CLanguage& oLanguage);

	void ProcessWord(const std::wstring& sWord);
	long GetScore() const;
	std::wstring GetLanguageCode() const;

private:
	CLanguage& m_oLanguage;
	long m_iScore;
};

class CLanguageDetector
{
public:
	CLanguageDetector();

	std::wstring DetectLanguage(const std::wstring& sText);

private:
	std::vector< std::unique_ptr<CLanguage> > m_aLanguages;
};

