#include <iostream> 
#include "Filter.h"

using namespace std;


Filter::Filter(vector<Employee *> *pEmpVector,
               DATA_FIELDS field,
               SELECTION_CRITERIA selectCrit,
               pair<string, string> dataLimit
):
        field_(field), firstField_(field), selectCrit_(selectCrit)
{
    string start = dataLimit.first, end = dataLimit.second;
    pEmpVector_ = new vector<Employee*>;
    for (int i = 0; i < pEmpVector->size(); i++){
        Employee *employee = pEmpVector->at(i);
        switch (field_){
            case SALARY:
                switch (selectCrit_){
                    case IS_EQUAL:
                        if (fabs(employee->salary_ - stof(start)) <= 0.01)
                            pEmpVector_->push_back(employee);
                        break;
                    case BETWEEN:
                        if (employee->salary_ >= stof(start) && employee->salary_ <= stof(end))
                            pEmpVector_->push_back(employee);
                        break;
                    case GREATER:
                        if (employee->salary_ > stof(start))
                            pEmpVector_->push_back(employee);
                        break;
                    case LESS:
                        if (employee->salary_ < stof(start))
                            pEmpVector_->push_back(employee);
                        break;
                }
                break;

            case STATUS:
                switch (selectCrit_) {
                    case IS_EQUAL:
                        if (employee->status_ == start)
                            pEmpVector_->push_back(employee);
                        break;
                    case BETWEEN:
                        if (employee->status_ >= start && employee->status_ <= end)
                            pEmpVector_->push_back(employee);
                        break;
                    case GREATER:
                        if (employee->status_ > start)
                            pEmpVector_->push_back(employee);
                        break;
                    case LESS:
                        if (employee->status_ < start)
                            pEmpVector_->push_back(employee);
                        break;
                }
                break;
            case NAME:
                switch (selectCrit_) {
                    case IS_EQUAL:
                        if (employee->name_ == start)
                            pEmpVector_->push_back(employee);
                        break;
                    case BETWEEN:
                        if (employee->name_ >= start && employee->name_ <= end)
                            pEmpVector_->push_back(employee);
                        break;
                    case GREATER:
                        if (employee->name_ > start)
                            pEmpVector_->push_back(employee);
                        break;
                    case LESS:
                        if (employee->name_ < start)
                            pEmpVector_->push_back(employee);
                        break;
                }
                break;
            case PAY_BASIS:
                switch (selectCrit_) {
                    case IS_EQUAL:
                        if (employee->payBasis_ == start)
                            pEmpVector_->push_back(employee);
                        break;
                    case BETWEEN:
                        if (employee->payBasis_ >= start && employee->payBasis_ <= end)
                            pEmpVector_->push_back(employee);
                        break;
                    case GREATER:
                        if (employee->payBasis_ > start)
                            pEmpVector_->push_back(employee);
                        break;
                    case LESS:
                        if (employee->payBasis_ < start)
                            pEmpVector_->push_back(employee);
                        break;
                }
                break;
            case POSITION:
                switch (selectCrit_) {
                    case IS_EQUAL:
                        if (employee->positionTitle_ == start)
                            pEmpVector_->push_back(employee);
                        break;
                    case BETWEEN:
                        if (employee->positionTitle_ >= start && employee->positionTitle_ <= end)
                            pEmpVector_->push_back(employee);
                        break;
                    case GREATER:
                        if (employee->positionTitle_ > start)
                            pEmpVector_->push_back(employee);
                        break;
                    case LESS:
                        if (employee->positionTitle_ < start)
                            pEmpVector_->push_back(employee);
                        break;
                }
                break;
        }
    }
}

void Filter::printFilter()
{
    cout << getEmployeeFileHeader();
    for (size_t i = 0; i < pEmpVector_->size(); i++)
    {
        cout << *(pEmpVector_->at(i));
    }
}


void Filter::addFilter(vector<Employee *> *pEmpVector,
                       DATA_FIELDS field,
                       SELECTION_CRITERIA selectCrit,
                       pair<string, string> dataLimit,
                       FILTER_TYPE filterType
){
    Filter *filter = new Filter(pEmpVector, field, selectCrit, dataLimit);
    int length = pEmpVector->size();
    auto &empVector = filter->pEmpVector_, result = new vector<Employee *>(length + length);
    std::sort(empVector->begin(), empVector->end(), CompareClass(NAME, true));
    std::sort(pEmpVector_->begin(), pEmpVector_->end(), CompareClass(NAME, true));
    switch(static_cast<int>(filterType)){
        case 1: {
            std::vector<Employee *>::iterator unionIterator = std::set_union(pEmpVector_->begin(), pEmpVector_->end(),
                                                                             empVector->begin(), empVector->end(),
                                                                             result->begin(), CompareClass(NAME, true));
            result->resize(unionIterator - result->begin());
            std::sort(result->begin(), result->end(), CompareClass(NAME, true));
            break;
        }
        case 2: {
            std::vector<Employee *>::iterator intersectionIterator = std::set_intersection(pEmpVector_->begin(),
                                                                                           pEmpVector_->end(),
                                                                                           empVector->begin(),
                                                                                           empVector->end(),
                                                                                           result->begin(), CompareClass(NAME, true));
            result->resize(intersectionIterator - result->begin());
            std::sort(result->begin(), result->end(), CompareClass(NAME, true));
            break;
        }
    }
    this->pEmpVector_ = result;
}