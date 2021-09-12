#ifndef CONTACT_H
#define CONTACT_H
#include <string>
#include <vector>
#include <iostream>
using namespace std;
class Contact{
private:
    string _name;
    vector<string> _numbers;

public:

    Contact(string name) : _name(name){
#ifndef NDEBUG
//        cout << "Contact created!\n";
#endif
    }

    Contact(string name, string number) : _name(name){
#ifndef NDEBUG
        _numbers.push_back(number);
//        cout << "Contact created!\n";
#endif
    }

    Contact(string name, vector<string> nums) : _name(name), _numbers(nums){
#ifndef NDEBUG
//        cout << "Contact created!\n";
#endif
    }

    ~Contact(){
#ifndef NDEBUG
//        cout << "Contact deleted!\n";
#endif
    }

    static string format_number(string n) {
        return ": +38 (" + n.substr(0, 3) + ") " + n.substr(3, 3) + " " + n.substr(6, 4) + "\n";
    }

    void name(string name){
        _name = name;
        cout << "Name changed!\n";
    }

    const string& name() const {
        return _name;
    }

    vector<string> numbers() {
        return _numbers;
    }

    const vector<string> numbers() const{
        return _numbers;
    }
    void add_number(string number){
        _numbers.push_back(number);
        cout << "Added number!\n";
    }

    void delete_number(string number){
        _numbers.push_back(number);
        cout << "Added number!\n";
    }

    void delete_number(int index){
        _numbers.erase(_numbers.begin() + index - 1);
        cout << "Number erased!\n";
    }

    string phone_list() const{
        string os;
        for(size_t i= 0; i < numbers().size(); i++){
            string n = numbers()[i];
            os += "#"+to_string(i+1) + format_number(n);
        }
        return os;
    }
    bool operator==(const Contact other){
        return other.name() == name() && other.numbers() == numbers();
    }
};
ostream& operator<<(ostream& os, const Contact& contact) {
    os << "Name: " << contact.name() << "\nPhone list:\n" << contact.phone_list();
    return os;
}

#endif // CONTACT_H
