#include "Algebra.h"
using namespace std;
auto main()->int{
    string variable = "((99012xy)/78a)+((59z)+(a))";
    auto t = getSingleEquation(variable);
    cout<<t.first<<" "<<t.second<<endl<<t.third<<endl;
    int constant = getConstant(variable);
    string variables = getVariable(variable);
    cout<<variables<<" "<<constant<<endl;
    return 0;
}