#include<bits/stdc++.h>
using namespace std;

class User{
    string userName;  
    string userEmail;  
    string userPass;  
    string userMob;  
    
    public:
    User(string name, string email,string pass, string mob){
        userName = name;
        userEmail = email;
        userPass = pass;
        userMob = mob;
    }
};

unordered_map<string, User> mp; // email and its object of user class

void Register(){
    string name;
    string email;
    string pass;
    string mob;

    cout<<"Enter Name : ";
    cin >> name;

    cout << "Enter email : ";
    cin >> email;
    
    cout << "Enter Pass : ";
    cin >> pass;

    cout << "Enter Mobile : ";
    cin >> mob;
    
    if(mp.find(email) != mp.end()){
        cout << "User exists" <<endl;
        return;
    }

    User u1(name, email, pass, mob);
    mp[email] = u1;
    cout << "User registered successfully" << endl;
}

void Login(){
    string email;
    string pass;

    cout << "Enter email : ";
    cin >> email;

    cout << "Enter password : ";
    cin >> pass;

    if(mp.find(email) == mp.end()){
        cout << "User not found" << endl;
        return;
    }

    if(mp[email].userPass == pass){
        cout << "Login successful" << endl;
    } else {
        cout << "Invalid password" << endl;
    }
}

int main(){
    Register();
    Login();
    return 0;
}
