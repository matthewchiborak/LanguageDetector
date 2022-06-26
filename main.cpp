#include <iostream>

#include <chrono>
#include <fstream>
#include <codecvt>
#include <sstream>

#include "LanguageDetector.h"

int main(int argc, char* argv[])
{
    auto start = std::chrono::system_clock::now();

    CLanguageDetector oDetector;

    auto middle = std::chrono::system_clock::now();

    for (int i = 1; i < 11; ++i)
    {
        std::ifstream t(argv[i], std::ios::binary);
        t.seekg(0, std::ios::end);
        size_t size = t.tellg();
        std::string buffer(size, ' ');
        t.seekg(0);
        t.read(&buffer[0], size);

        //std::wstring sInput = std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>().from_bytes(buffer);
        std::wstring sInput(buffer.begin(), buffer.end());

        std::wcout << argv[i] << L" Lang : " << oDetector.DetectLanguage(sInput) << std::endl;
    }

    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds1 = middle - start;
    std::chrono::duration<double> elapsed_seconds2 = end - middle;

    std::wcout << L"Time Elapsed Init: " << elapsed_seconds1.count() << std::endl << L"Time Elapsed Processing: " << elapsed_seconds2.count() << std::endl;

}

