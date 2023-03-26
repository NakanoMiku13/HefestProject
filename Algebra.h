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
        return number;
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
                if(open > 0 && operation == ' '){
                    equation1 += i;
                }
                if((operation == ' ' && (isSymbol)) or (operation == ' ' && i == ')')){
                    if(open == 0){
                        operation = i;
                        result.first = equation1;
                        result.third = operation;
                        equation1 = "";
                    }else{
                        open--;
                    }
                }else equation1 += i;
            }
            result.second = equation1;
            return result;
        }
    }catch(AlgebraException exception){

    }
}
auto addition(const string variable1, const string variable2){
    if(variable1 == variable2){
        int c1 = getConstant(variable1);
    }
}