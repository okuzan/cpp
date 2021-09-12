#ifndef PHONEBOOK_H
#define PHONEBOOK_H
#include "Contact.h"
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <regex>

using namespace std;

class Phonebook{
private:
    vector<Contact> _contacts;

    bool check_name(string name){
        for(size_t i = 0; i < _contacts.size(); i++)
        {
            if (_contacts[i].name() == name){
                cout <<"That person is already added";
                return false;
            }
        }
        return true;
    }

    bool check_alpha(const string &str){
        bool a = std::all_of(str.begin(), str.end(), [](unsigned char c){return std::isalpha(c) || std::isspace(c);});
        return a;
    }
    string lowercase(string s){
        ::for_each(s.begin(), s.end(), [](char & c){
            c = ::tolower(c);
        });
        return s;
    }

    void normalize(string& str){
        str = regex_replace(str, regex(R"([\D])"), "");
        if(str.length() == 12)
            str = str.erase(0, 2);
        if(str.length() == 9)
            str = '0' + str;
    }

    bool check_number(string& number, const Contact& contact){
        normalize(number);
        remove_if(number.begin(), number.end(), ::isspace);
        if(number.length() != 10 || number.find_first_not_of("0123456789") != std::string::npos){
            cout << "Check your input!\n";
            return false;
        }
        for(size_t i = 0; i < contact.numbers().size(); i++){
            if (contact.numbers()[i] == number) {
                cout << "That number is already added!\n";
                return false;
            }
        }
        return true;
    }

public:
    Phonebook(){
#ifndef NDEBUG
        cout << "Phrasebook created!\n";
#endif

    }
    ~Phonebook(){
#ifndef NDEBUG
        cout << "Phrasebook deleted!\n";
#endif

    }

    void fill_with_data(){
        _contacts.push_back(Contact("Oleh Kuzan", "0993492296"));
        _contacts.push_back(Contact("Zanku Nazuk", "0993425975"));
        _contacts.push_back(Contact("Abraham Lincoln", "0993492598"));
        _contacts.push_back(Contact("Donald Trump", "0993435598"));
        vector<string> numbers;
        numbers.push_back("0993422590");
        numbers.push_back("0993425591");
        numbers.push_back("0993442592");
        _contacts.push_back(Contact("Barak Obama", numbers));
    }
    vector<int> find_by_name(string& name){
        vector<int> arr;
        for (size_t t = 0; t < _contacts.size(); t++)
        {
            string full_name = lowercase(_contacts[t].name());
            istringstream iss(full_name);
            vector<string> parts{istream_iterator<string>{iss},
                                 istream_iterator<string>{}};
            for(size_t k = 0; k < parts.size(); k++){
                if (parts[k] == lowercase(name))
                    arr.push_back(t);
            }
        }
        return arr;
    }

    vector<int> find_by_number(string& number){
        normalize(number);
        vector<int> arr;
        for (size_t t = 0; t < _contacts.size(); t++)
            for(size_t k = 0; k < _contacts[t].numbers().size(); k++)
                if (_contacts[t].numbers()[k] == number)
                    arr.push_back(k);
        return arr;
    }

    void editor(Contact& contact){
        cout << "1 - edit name\n2 - edit phonelist\n";
        string s;
        getline(cin, s);
        if(s.find_first_not_of("0123456789") != std::string::npos || s.empty()) return;
        int d = stoi(s);
        switch (d) {
        case 1:{
            cout << "Enter new name\n";
            string name;
            getline(cin, name);

            if(check_alpha(name)){
                contact.name(name);
            }
            else{
                cout << "Name cannot contain other symbols than letters!\n";
            }
            break;
        }
        case 2:{
            cout << "Enter T to delete existent phone numbers, or proceed to adding new ones\n";
            string s;
            getline(cin, s);
            if (lowercase(s) == "t"){
                while(true){
                    cout << contact.phone_list();
                    int d;

                    if(contact.numbers().size() != 1) {
                        cout << "Enter index of entry you need to delete\n";

                        string s;
                        getline(cin, s);
                        if (s.empty()) break;
                        if(s.find_first_not_of("0123456789") != std::string::npos) continue;
                        d = stoi(s);

                        if(d > contact.numbers().size())
                        {
                            cout << "Index is too big! Did you mean last entry?\n";
                            getline(cin, s);
                            if(lowercase(s) == "t") d = contact.numbers().size();
                            else break;
                        }
                        if(d < 1)
                        {
                            cout << "Index is too small! Did you mean first entry?\n";
                            getline(cin, s);
                            if(lowercase(s) == "t") d = 1;
                            else break;
                        }
                        string num = Contact::format_number(contact.numbers()[d - 1]);
                        cout <<"Approve deleting this number: " << num <<"\n";
                        string t;
                        getline(cin, t);
                        if (lowercase(t) == "t"){
                            contact.delete_number(d);
                            cout <<"Successfully deleted!\n";
                        }
                    }
                    else {
                        cout << "Warning! This person has only one saved number, if you delete, whole entry will be deleted too!\n";
                        d = 1;
                        string a;
                        getline(cin, a);
                        if(lowercase(a)== "t"){
                            _contacts.erase(std::remove(_contacts.begin(), _contacts.end(), contact), _contacts.end());
                            cout << "Entry deleted!\n";
                        }
                        return;
                    }
                }
            }
            else{
                cout << "Enter new numbers\n";
                while (true) {
                    string s;
                    getline(cin, s);
                    if (s.empty()) break;
                    if (check_number(s, contact)) contact.add_number(s);
                }
            }
            break;
        }
        default:
            cout << "Nothing is assigned to that code\n\n";
        }
    }
    void start(){
        while(true){
            cout << "\nChoose your option:\n"
                    "1 - show entries\n"
                    "2 - search by name\n"
                    "3 - search by number\n"
                    "4 - edit entries\n"
                    "5 - add new person\n"
                    "0 - exit\n";
            string s;
            getline(cin, s);
            if(s.find_first_not_of("0123456789") != std::string::npos || s.empty()){
                cout << "Nothing is assigned to that code!\n";
                continue;
            }
            int d = stoi(s);
            switch (d) {
            case 0:{
                cout << "See you soon!\n";
                exit(0);
            }
            case 1:{
                if (_contacts.size() == 0) {
                    cout << "Phonebook is empty!\n";
                    break;
                }
                for(size_t t = 0; t < _contacts.size(); t++)
                    cout << _contacts[t] << endl;
                break;
            }
            case 2:{
                if (_contacts.size() == 0){
                    cout << "Phonebook is empty!\n";
                    break;
                }
                cout << "Enter name\n";
                string info;
                getline(cin, info);
                if(info.empty()) break;
                vector<int> found = find_by_name(info);
                cout << found.size() << " entries match\n";
                for(size_t t = 0; t < found.size(); t++)
                    cout << _contacts[t] << "\n";
                break;
            }
            case 3:{
                if (_contacts.size() == 0) {
                    cout << "Phonebook is empty!\n";
                    break;
                }
                cout << "Enter number\n";
                string info;
                getline(cin, info);
                if(info.empty()) break;
                vector<int> found = find_by_number(info);
                stringstream s;
                cout << found.size() << " entries match\n";
                for(size_t t = 0; t < found.size(); t++)
                    cout << _contacts[t] << "\n";
                if(found.size() == 0) cout << "Nothing found!\n";
                break;

            }
            case 4:{
                if (_contacts.size() == 0){
                    cout << "Phonebook is empty!\n";
                    break;
                }
                cout << "Select entry you want to edit. Enter you data\n";
                string info;
                getline(cin, info);
                vector<int> found;
                if(info.empty()) break;

                if (info.find_first_not_of("0123456789") == std::string::npos) {
                    cout << "Your input is treated as a number\n\n";
                    found = find_by_number(info);
                }
                else{
                    cout << "Your input is treated as name\n\n";
                    found = find_by_name(info);
                }

                if(found.size() == 0) {
                    cout << "No entry match\n\n";
                }
                else{
                    for(size_t i = 0; i < found.size(); i++){
                        stringstream s;
                        s << "[" << (i+1) << "]\n" << _contacts[found[i]];
                        cout << s.str();
                    }

                    //                    for(size_t t = 0; t < found.size(); t++)
                    //                        cout << _contacts[found[t]] << endl;

                    int d;
                    if(found.size() == 1) d = 1;
                    else {
                        cout << "Enter index of entry you need";
                        string s;
                        getline(cin, s);
                        d = stoi(s);
                        if(s.find_first_not_of("0123456789") != std::string::npos) continue;
                        if (s.empty()) return;
                        if(d < 1) d = 1;
                        if(d > found.size()) d = found.size();
                    }
                    editor(_contacts[found[d - 1]]);
                }
                break;

            }
            case 5:{
                cout << "Enter name\n";
                string name;
                getline(cin, name);
                if(name.empty()) break;
                if(!check_alpha(name)){
                    cout << "Name cannot contain other symbols than letters!\n";
                    break;
                }
                Contact contact(name);
                cout << "Enter numbers\n";
                while (true) {
                    string s;
                    getline(cin, s);
                    if (s.empty()) break;
                    if (check_number(s, contact)) contact.add_number(s);
                }
                if(contact.numbers().size() > 0){
                    _contacts.push_back(contact);
                }
                else{
                    cout << "You can't add a person w/o numbers!\n\n";
                }
                break;
            }
            default:{
                cout << "Nothing is assigned to that code\n\n";
                break;}
            }
        }
    }
};

#endif // PHONEBOOK_H
