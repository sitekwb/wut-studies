
#include <string>

#include "StudentBase.h"

StudentBase::StudentBase(int i, int y, int gr, std::string lang)
    {
        id = i;
        age = y;
        group = gr;
        language = lang;
}

int StudentBase::getID()
{
    return id;
}

std::string StudentBase::getLang()
{
    return language;
}

void StudentBase::setLang(std::string newlang)
{
    language = newlang;
}

void StudentBase::setGroup(int x)
{
    group = x;
}

void StudentBase::increaseAge()
{
    age++;
}
