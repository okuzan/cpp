//#include <iostream>
//#include <vector>
//#include <sstream>
//#include <string>
//#include <algorithm>
//#include <iterator>
//#include <regex>
//#include "Contact.h"
//using namespace std;

//void normalize(string& str){
//    str = regex_replace(str, regex(R"([\D])"), "");
//    if(str.length() == 12)
//        str = str.erase(0, 2);
//    if(str.length() == 9)
//        str = '0' + str;
//}

//bool check_number(string& number, const Contact& contact){
//    normalize(number);
//    cout << number;
//    remove_if(number.begin(), number.end(), ::isspace);
//    if(number.length() != 10 || number.find_first_not_of("0123456789") != std::string::npos){
//        cout << "Check your input!\n";
//        return false;
//    }
//    for(size_t i; i < contact.numbers().size(); i++){
//        if (contact.numbers()[i] == number) {
//            cout << "That number is already added!\n";
//            return false;
//        }
//    }
//    return true;
//}
//int main(void){
//    Contact a("Oleh Kuzan", "0993492296");
//    check_number("1", a);
//}
