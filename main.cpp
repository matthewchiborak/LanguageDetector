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

    std::wstring sInput = L"Roger Federer (German:; born 8 August 1981) is a Swiss professional tennis player. He was ranked world No. 1 by the Association of Tennis Professionals (ATP) for 310 weeks, including a record 237 consecutive weeks, and has finished as the year-end No. 1 five times. He has won 103 ATP singles titles, the second most of all time after Jimmy Connors, including 20 Grand Slam titles, a record eight men's singles Wimbledon titles, and a record six year-end championships. Federer has played in an era where he dominated men's tennis along with Rafael Nadal and Novak Djokovic. Referred to as the Big Three, they are considered by some to be the three greatest tennis players of all time.[c] A Wimbledon junior champion in 1998, Federer won his first major singles title at Wimbledon in 2003 at age 21. In 2004, he won three of the four major singles titles and the ATP Finals,[d] a feat he repeated in 2006 and 2007. From 2005 to 2010, he made 18 out of 19 major singles finals. During this span, he won five consecutive titles at both Wimbledon and the US Open. He completed the career Grand Slam at the 2009 French Open after three previous runner-up finishes to Nadal, his main rival until 2010. At age 27, he surpassed Pete Sampras' record of 14 major men's singles titles at Wimbledon in 2009. Although Federer remained in the top 3 during most of the early 2010s, the success of Djokovicand Nadal ended his dominance over grassand hard courts.From mid - 2010 through the end of 2016, he only won one major title.During this period, heand Stan Wawrinka led the Switzerland Davis Cup team to their first title in 2014, adding to the gold medal the pair won together in doubles at the 2008 Beijing Olympics.Federer also won a silver medal in singles from the 2012 London Olympics, where he finished runner - up to Andy Murray.After taking half a year off in late 2016 to recover from knee surgery, he had a renaissance at the majors, winning three more major titles over the next two years, including the 2017 Australian Open over Nadal and a record eighth men's singles Wimbledon title later in 2017. In 2018, he became the oldest ATP world No. 1 at age 36. A versatile all - court player, Federer's perceived effortlessness has made him highly popular among tennis fans. Originally lacking self-control as a junior, he transformed his on-court demeanor to become well-liked for his general graciousness, winning the Stefan Edberg Sportsmanship Award 13 times. He has also won the Laureus World Sportsman of the Year award a record five times. Outside of competing, he played an instrumental role in the creation of the Laver Cup team competition. He is also an active philanthropist. He established the Roger Federer Foundation, which targets impoverished children in southern Africa, and has raised funds in part through the Match for Africa exhibition series. He is routinely one of the top ten highest-paid athletes in any sport and ranked first among all athletes with $100 million in endorsement income in 2020.[4]";

    std::wcout << L"Lang: " << oDetector.DetectLanguage(sInput) << std::endl;

    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds1 = middle - start;
    std::chrono::duration<double> elapsed_seconds2 = end - middle;

    std::wcout << L"Time Elapsed: " << elapsed_seconds1.count() << std::endl << elapsed_seconds2.count() << std::endl;

}

