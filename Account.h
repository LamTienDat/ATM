#pragma once
#include<iostream>
#include<vector>
#include<fstream>
#include<string>

using namespace std;

class Account {
private:
    string id;
    string password;
    int accountBalance;
    int numFail;
    int position_question;
    string answer_secret_question;
public:
    Account();
    Account(string id_, string password_, int money, int fail, int pos, string ans);
    ~Account();
    string getTimeNow();
    bool creatAccount(string id_, vector<string> list_sec_ques);
    string getID() const { return id; }
    string getInformation() const;
    bool login();
    void deposit(int bank[]);
    void cashWithDrawals(int bank[]);
    int sendMoney();
    void receiveMoney(int mn);
    void writeHistory(string s);
    void printHistory();
    void checkAccountBalance();
    void changePassword();
    void forgetPassword(vector<string> list_sec_ques);
};

