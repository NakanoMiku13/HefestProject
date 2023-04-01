#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<vector>
#include<algorithm>
#include<map>
#include<string>
#include<queue>
#include<stack>
#include<iostream>
#include<string>
#define isNumber (int)i >= 48 && i <= (int)57
#define isVariable ((int)i >= 65 && i <= (int)90) or ((int)i >= 97 && (int)i <= 121)
#define isSymbol (int)i == 43 or (int)i == 47 or (int)i == 45 or (int)i == 42
using namespace std;
class AlgebraException{
    public:
        AlgebraException(string message = "", int code = -1): _message{message},_code{code}{}
        AlgebraException(string message): _message{message},_code{-1}{}
        AlgebraException(int code): _code{code},_message{""}{
            switch(code){
                case 0: _message = "Invalid format string, it must have a '(' opening before ')' character\n"; break;
                case 1: _message = "There must be at least one number\n"; break;
                case 2: _message = "There must be at least one valid character\n"; break;
                case 3: _message = "Must close the parenthesis\n"; break;
                case 4: _message = "The syntax of the equation is incorrect\n"; break;
                case 5: _message = "The operation can not have a symbol following another...\n"; break;
                case 6: _message = "A complex equation must begin with '(' in every block\n"; break;
                case 7: _message = "There is not compatible operation\n"; break;
                case 8: _message = "It must be a single equation\n"; break;
                default: _message = "Unhandled exception\n"; break;
            }
        }
        auto getCode()->int{
            return _code;
        }
        auto getMessage()->string{
            return _message;
        }
        auto getException()->string{
            return "Algebra Exception:\nError code: " + to_string(_code) + "\n" + _message;
        }
        /*friend auto operation<<(AlgebraException& ex){

        }*/
    private:
        string _message;
        int _code;
};
template<typename datatype1, typename datatype2, typename datatype3>
class shortList{
    public:
        datatype1 first;
        datatype2 second;
        datatype3 third;
        shortList(datatype1 first, datatype2 second, datatype3 third): first(first), second(second), third(third){}
        shortList(){}
};
//Function that check if the equation or variable is complex or not
//If its complex, it is like a+b=x
//If it is not complex, is like 45az
auto isComplexEquation(const string equation)->bool{
    try{
        if(equation.size() == 0) throw AlgebraException(2);
        for(auto i : equation) if(isSymbol) return true;
    }catch(AlgebraException exception){
        cout<<exception.getMessage()<<endl;
    }
    return false;
}
//Function that get the real part of a variable, it just allows strings as input, and returns an int that is the constant part of the variable
auto getConstant(const string variable)->int{
    try{
        if(variable.size() == 0) throw AlgebraException(1);
        vector<int> numbers;
        int number = 0;
        for(auto i : variable) if(isNumber) numbers.push_back(((int)i-48));
        reverse(numbers.begin(),numbers.end());
        for(int i = 0, j = 1 ; i < numbers.size() ; number += (numbers[i] * j), i++, j*=10);
        return (number == 0) ? 1 : number;
    }catch(AlgebraException exception){
        cout<<exception.getException()<<endl;
    }
    return 0;
}
//Function that returns the variable (s) from a single equation it just admits single variables or in product
auto getVariable(const string variable)->string{
    try{
        if(variable.size() == 0) throw AlgebraException(2);
        string retVariable = "";
        for(auto i : variable) if(isVariable) retVariable += i;
        return retVariable;
    }catch(AlgebraException exception){
        cout<<exception.getException()<<endl;
    }
    return "";
}
//Function that verify the syntax of the equation
auto verifySyntax(const string equation)->bool{
    try{
        map<char,int> parenthesis;
        parenthesis['('] = parenthesis[')'] = 0;
        short int op = 0;
        for(auto i : equation){
            if(i == ')' &&  parenthesis['('] == 0) throw AlgebraException(0);
            if(i == '('){ parenthesis['(']++; parenthesis[')']++;}
            if(i == ')' && parenthesis['('] > 0) {parenthesis['(']--; parenthesis[')']--;}
            if(!(isSymbol) && op == 1) op = 0;
            if((isSymbol) && op == 1) throw AlgebraException(5);
            else if((isSymbol) && op == 0) op = 1;

        }
        if(parenthesis['('] > 0 && parenthesis[')'] > 0) throw AlgebraException(3);
        if(op > 0) throw AlgebraException(5);
        else return true;
    }catch(AlgebraException exception){
        cout<<exception.getException()<<endl;
    }
    return false;
}
//Function that removes a specific char from a string
auto removeCharFromString(string str, char removeChar)->string{
    string newString = "";
    for(auto i : str){
        if(i != removeChar) newString += i;
    }
    return newString;
}
//Remove N positions from the string, it gets a list of positions to delete
auto removePositionsFromString(string str, initializer_list<int> positions)->string{
    vector<int> items = vector<int>(positions);
    string newString = "";
    for(int i = 0, j = 0 ; i < str.size() ; i++){
        if(i != items[j]) newString += str[i];
        else j++;
    }
    return newString;
}
//Function that simplifies the original equation, if we have "a+b" it will return 'a', 'b', '+', where the las element is the operation symbol
auto getSingleEquation(const string equation)->shortList<string,string,char>{
    try{
        if(!verifySyntax(equation)) throw AlgebraException(4);
        else{
            shortList<string,string,char> result = shortList<string,string,char>();
            int open = 0;
            char operation = ' ';
            string equation1 = "";
            if(equation[0] != '(') throw AlgebraException(6);
            for(auto i : equation){
                if(i == '(') open++;
                if(open > 0){
                    equation1 += i;
                }
                if((operation == ' ' && (isSymbol) && open == 0)){
                    operation = i;
                    result.first = equation1;
                    result.third = operation;
                    equation1 = "";
                }
                if(i == ')') open--;
            }
            result.second = equation1;
            result.first = removePositionsFromString(result.first,{0,(int)result.first.size() - 1});
            result.second = removePositionsFromString(result.second,{0,(int)result.second.size() - 1});
            if(operation != '/'){
                if(result.first.size() == 0) result.first = "0";
                if(result.second.size() == 0) result.second = "0";
            }else{
                if(result.second.size() == 0) result.second = "1";
            }
            return result;
        }
    }catch(AlgebraException exception){
        cout<<exception.getException()<<endl;
        return shortList<string,string,char>();
    }
}
//Function that check if the expression is like 2x², basically if it has power
auto isPower(string equation)->bool{
    for(auto i : equation) if(i == '^') return true;
    return false;
}
//Function that return the constant, variable and equation
//If we have 2x^2, the result will be 2 x 2
auto getSingleEquationPower(string equation)->shortList<int,string,int>{
    int constant = 1, exponent = 1, k = 0;
    string variable = "";
    try{
        if(equation.size() == 0) throw AlgebraException(1);
        vector<int> numbers;
        int number = 0;
        while((int)equation[k] >= 48 && (int)equation[k] <= 57){
            numbers.push_back(((int)equation[k]-48));
            k++;
        }
        reverse(numbers.begin(),numbers.end());
        int pos = 0;
        for(int i = 0, j = 1 ; (int)equation[i] >= 48 && (int)equation[i] <= 57; number += (numbers[i] * j), pos = i, i++, j*=10);
        if(numbers.size()  == 0) constant = 1;
        else constant = number;
        pos++;
        string variable = "";
        variable += equation[pos];
        pos+=2;
        k = pos;
        numbers = vector<int>();
        while((int)equation[k] >= 48 && (int)equation[k] <= 57){
            numbers.push_back(((int)equation[k]-48));
            k++;
        }
        int power = 0;
        for(int i = pos, m = 0, j = 1 ; i < equation.size() ; power += (numbers[m] * j),m++, i++, j *= 10);
        exponent = power;
        return shortList<int,string,int>(constant,variable,exponent);
    }catch(AlgebraException exception){
        cout<<exception.getException()<<endl;
        return shortList<int,string,int>();
    }
}
//Function that make the addition of two variables
auto addition(string first,string second)->string{
    try{
        if(isComplexEquation(first) or isComplexEquation(second)) throw AlgebraException(8);
        string variableA = getVariable(first), variableB = getVariable(second);
        int constantA = getConstant(first), constantB = getConstant(second), powerA = 0, powerB = 0;
        if(isPower(first) && isPower(second)){
            shortList<int,string,int> fir = getSingleEquationPower(first),sec = getSingleEquationPower(second);
            variableA = fir.second;
            variableB = sec.second;
            constantB = sec.first;
            constantA = fir.first;
            powerA = fir.third;
            powerB = sec.third;
        }
        return (isPower(first) && isPower(second)) ? (
            (variableA == variableB && powerA == powerB) ? "(" + to_string(constantA + constantB) + variableA + "^"+to_string(powerA)+")" : "(" + first + ")+(" + second + ")"
        ) : (variableA == variableB) ? "(" + to_string(constantA + constantB) + variableA + ")" : "(" + first + ")+(" + second + ")";
    }catch(AlgebraException exception){
        cout<<exception.getException()<<endl;
        return "0";
    }
}
//Function that makes the difference between two variables
auto difference(string first,string second)->string{
    try{
        if(isComplexEquation(first) or isComplexEquation(second)) throw AlgebraException(8);
        string variableA = getVariable(first), variableB = getVariable(second);
        int constantA = getConstant(first), constantB = getConstant(second), powerA = 0, powerB = 0;
        if(isPower(first) && isPower(second)){
            shortList<int,string,int> fir = getSingleEquationPower(first),sec = getSingleEquationPower(second);
            variableA = fir.second;
            variableB = sec.second;
            constantB = sec.first;
            constantA = fir.first;
            powerA = fir.third;
            powerB = sec.third;
        }
        return (isPower(first) && isPower(second)) ? (
            (variableA == variableB && powerA == powerB) ? "(" + to_string(constantA - constantB) + variableA + "^"+to_string(powerA)+")" : "(" + first + ")-(" + second + ")"
        ) : (variableA == variableB) ? "(" + to_string(constantA - constantB) + variableA + ")" : "(" + first + ")-(" + second + ")";
    }catch(AlgebraException exception){
        cout<<exception.getException()<<endl;
        return "0";
    }
}
//Function that makes the product of two variables
auto product(string first,string second)->string{
    try{
        if(isComplexEquation(first) or isComplexEquation(second)) throw AlgebraException(8);
        string variableA = getVariable(first), variableB = getVariable(second);
        int constantA = getConstant(first), constantB = getConstant(second), powerA = 0, powerB = 0;
        if(isPower(first) && isPower(second)){
            shortList<int,string,int> fir = getSingleEquationPower(first),sec = getSingleEquationPower(second);
            variableA = fir.second;
            variableB = sec.second;
            constantB = sec.first;
            constantA = fir.first;
            powerA = fir.third;
            powerB = sec.third;
        }
        return (isPower(first) && isPower(second)) ? (
            (variableA == variableB) ? "(" + to_string(constantA * constantB) + variableA + "^"+to_string(powerA + powerB)+")" : "(" + first + ")+(" + second + ")"
        ) : (variableA == variableB) ? "(" + to_string(constantA * constantB) + variableA + "^2)" : "(" + first + ")+(" + second + ")";
    }catch(AlgebraException exception){
        cout<<exception.getException()<<endl;
        return "0";
    }
}
//Function that make the division of two variables
auto division(string first,string second)->string{
    try{
        if(isComplexEquation(first) or isComplexEquation(second)) throw AlgebraException(8);
        string variableA = getVariable(first), variableB = getVariable(second);
        int constantA = getConstant(first), constantB = getConstant(second), powerA = 0, powerB = 0;
        if(isPower(first) && isPower(second)){
            shortList<int,string,int> fir = getSingleEquationPower(first),sec = getSingleEquationPower(second);
            variableA = fir.second;
            variableB = sec.second;
            constantB = sec.first;
            constantA = fir.first;
            powerA = fir.third;
            powerB = sec.third;
        }
        return (isPower(first) && isPower(second)) ? (
            (variableA == variableB) ?
                ((powerA != powerB) ?
                    ("(" + to_string(constantA / constantB) + variableA + "^" +to_string(powerA - powerB)+")") :
                    "(" + to_string(constantA / constantB) + ")") :
                "(" + first + ")/(" + second + ")"
        ) : (variableA == variableB) ? "(" + to_string(constantA / constantB) + ")" : "(" + first + ")/(" + second + ")";
    }catch(AlgebraException exception){
        cout<<exception.getException()<<endl;
        return "0";
    }
}
//Function that pow two elements
auto power(string first,string second)->string{
    try{
        if(isComplexEquation(first) or isComplexEquation(second)) throw AlgebraException(8);
        string variableA = getVariable(first), variableB = getVariable(second);
        int constantA = getConstant(first), constantB = getConstant(second);
        return (variableA == variableB) ? "(" + to_string(constantA + constantB) + variableA + ")" : "(" + first + ")+(" + second + ")";
    }catch(AlgebraException exception){
        cout<<exception.getException()<<endl;
        return "0";
    }
}
//Main menu of the operations, this will be selected automatically when it get the equations
auto operation(string first,string second, char operation)->string{
    try{
        if(!verifySyntax(first) or !verifySyntax(second)) throw AlgebraException(4);
        switch(operation){
            case '+': return addition(first,second); break;
            case '-': return difference(first,second); break;
            case '*': return product(first,second); break;
            case '/': return division(first,second); break;
            case '^': return power(first,second); break;
            default: throw AlgebraException(7); break;
        }
    }catch(AlgebraException exception){
        cout<<exception.getException()<<endl;
        return "0";
    }
}