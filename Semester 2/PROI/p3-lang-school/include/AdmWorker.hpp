//
// Created by wojtek on 22.05.18.
//

#ifndef PROJECT_TWO_ADMINISTRATIONWORKER_HPP
#define PROJECT_TWO_ADMINISTRATIONWORKER_HPP

#include "Worker.hpp"

class AdmWorker: public Worker{
    int startYear;
public:
    void print();
    AdmWorker(int admId, std::string admName, int admSalary, int admStartYear);
    std::string getLang();
};

#endif //PROJECT_TWO_ADMINISTRATIONWORKER_HPP
