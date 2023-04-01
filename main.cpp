#include "Algebra.h"
using namespace std;
auto main()->int{
    string variable = "2x^2", var2 = "6x^2";
    cout<<variable<<" + "<<var2<<endl;
    string result = addition(variable,var2);
    cout<<result;
    return 0;
}