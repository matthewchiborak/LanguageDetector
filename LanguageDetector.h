#pragma once

#include <string>
#include <map>
#include <vector>
#include <memory>

class CLanguage
{
public:
	CLanguage(const std::wstring sID, const int iWordListID);

	double GetWordScore(const std::wstring& sWord) const;
	std::wstring GetID() const;

private:
	std::map<std::wstring, double> m_aWordList;
	std::wstring m_sID;
};

class CLanguageScoreTracker
{
public:
	CLanguageScoreTracker(CLanguage& oLanguage);

	void ProcessWord(const std::wstring& sWord);
	double GetScore() const;
	std::wstring GetLanguageCode() const;

private:
	CLanguage& m_oLanguage;
	double m_iScore;
};

class CLanguageDetector
{
public:
	CLanguageDetector();

	std::wstring DetectLanguage(const std::wstring& sText);

private:
	std::vector< std::unique_ptr<CLanguage> > m_aLanguages;
};

