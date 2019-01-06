#ifndef STUDENTBASE_H
#define STUDENTBASE_H
#include <string>

class StudentBase
{
protected:
    int id; //unique id, unique for every student
    int age;
    int group;
    std::string language;
public:
    StudentBase(int i, int y, int gr, std::string lang);

    int getID() const;

    void setGroup(int x);
    std::string getLang();
    void setLang(std::string newlang);
    int getID();
    void increaseAge();

    virtual void print(std::ostream &str) const = 0;

};

#endif // STUDENT_H
