#include "Algebra.h"
using namespace std;
auto main()->int{
    string variable = "2x^2";
    cout<<variable<<endl;
    auto t = getSingleEquationPower(variable);
    cout<<t.first<<" "<<t.second<<" "<<t.third<<endl;
    return 0;
}