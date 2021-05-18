#include "Account.h"
#include<ctime>
#include<time.h>
#include<conio.h>

Account::Account()
{
    ofstream file(id + ".txt");
    file << getTimeNow() << endl << "Da tao tai khoan " << endl;
    file.close();
}

Account::Account(string id_, string password_, int money, int fail, int pos, string ans)
{
    id = id_;
    password = password_;
    accountBalance = money;
    numFail = fail;
    position_question = pos;
    answer_secret_question = ans;
}

Account::~Account()
{
}

string Account::getTimeNow()
{
    time_t rawtime;
    time(&rawtime);
    string tc = ctime(&rawtime);
    tc.erase(tc.length() - 1, 1);
    return tc;
}
bool Account::creatAccount(string id_, vector<string> list_sec_ques)
{
    id = id_;
    cout << "Nhap mat khau : ";
    cin >> password;
    cout << endl << "Chon cau hoi bao mat:" << endl;
    for (auto x : list_sec_ques) {
        cout << x << endl;
    }
    if (cin >> position_question) {
        cout << "\nCau tra loi: ";
        cin.ignore();
        getline(cin, answer_secret_question);
        accountBalance = 0;
        numFail = 0;
        return 1;
    }
}

string Account::getInformation() const
{
    return id + "." + password + "." + to_string(accountBalance) + "." + to_string(numFail) + "." + to_string(position_question) + "." + answer_secret_question + ".";
}

bool Account::login()
{
    if (numFail < 3) 
    {
        string pw;
        cout << "Mat khau : ";
        cin >> pw;
        if (pw == password) 
        {
            writeHistory("Dang nhap thanh cong");
            numFail = 0;
            cout << "Thanh cong" << endl;
            
            
            return true;
        }
        else 
        {
            writeHistory("Dang nhap that bai");
            numFail += 1;
            cout << "That bai" << endl << "1.Thoat";
            int x = -1;
            cin >> x;
            if(x == 1)
                return false;
        }
    }
    else 
    {
        cout << "Tai khoan da bi khoa"<<endl;
        int x = -1;
        cin >> x;
        if (x == 1)
            return false;
    }
}
void Account::deposit(int bank[])
{
    int cash = 0;
    for (int i = 0; i < 4; i++) 
    {
        int menhgia, sl;
        cout << "Nhap menh gia: ";
        cin >> menhgia;
        cout << "Nhap so luong: ";
        cin >> sl;
        bank[menhgia] += sl;
        cash += menhgia * sl;
    }
    if (accountBalance += cash) 
    {
        cout << "Nap thanh cong " << cash <<"k"  << endl;
        writeHistory("Nap thanh cong +" + to_string(cash));
    }
    else cout << "Nap tien loi"<< endl;
}

void Account::cashWithDrawals(int bank[])
{
    int mn, l5 = 0, l2 = 0, l1 = 0, l50k = 0;
    cout << "So tien hien co : " << accountBalance << "k" << endl;
    cout << "So tien can rut: ";
    cin >> mn;
    if (mn <= accountBalance) 
    {
        while (mn >= 500 && bank[500] > 0) 
        {
            mn -= 500;
            l5 += 1;
        }
        while (mn >= 200 && bank[200] > 0) 
        {
            mn -= 200;
            l2 += 1;
        }
        while (mn >= 100 && bank[100] > 0) 
        {
            mn -= 100;
            l1 += 1;
        }
        while (mn >= 50 && bank[50] > 0)
        {
            mn -= 50;
            l50k += 1;
        }
        if (mn == 0) {
            accountBalance -= l5 * 500 + l2 * 200 + l1 * 100 + l50k * 50;
            bank[500] -= l5;
            bank[200] -= l2;
            bank[100] -= l1;
            bank[50] -= l50k;
            cout << endl;
            cout << "Rut thanh cong " << l5 * 500 + l2 * 200 + l1 * 100 + l50k * 50 << "k" << endl;
            cout << "Menh gia                  So luong" << endl;
            cout << "500k                      " << l5 << endl;
            cout << "200k                      " << l2 << endl;
            cout << "100k                      " << l1 << endl;
            cout << "50k                       " << l50k << endl;
            writeHistory("Rut thanh cong -" + to_string(l5 * 500 + l2 * 200 + l1 * 100 + l50k * 50));
        }
        else
        {
            cout << endl;
            cout << "Rut tien that bai";
        }
    }
    else
    {
        cout << endl;
        cout << "So du tai khoan khong du";
    }
}

int Account::sendMoney()
{
    int mn;
    cout << "Nhap so tien: ";
    cin >> mn;
    if (mn <= accountBalance) 
    {
        accountBalance -= mn;
        cout << "Chuyen tien thanh cong : " << mn <<"k" << endl;
        writeHistory("Gui thanh cong -" + to_string(mn));
        return mn;
    }
    else 
    {
        cout << endl;
        cout << "So du khong du"<< endl;
        return 0;
    }
}

void Account::receiveMoney(int mn)
{
    if (mn > 0) 
    {
        accountBalance += mn;
        writeHistory("Nhan thanh cong +" + to_string(mn));
    }
}

void Account::writeHistory(string s)
{
    fstream file(id + ".txt", ios::app);
    file << getTimeNow() << endl << s << endl << "--------------------------------" << endl;
}

void Account::printHistory()
{
    ifstream file(id + ".txt");
    while (!file.eof()) 
    {
        string s;
        getline(file, s);
        cout << s << endl;
    }
    file.close();
}

void Account::checkAccountBalance()
{
    cout <<"So tien con lai trong tai khoan la : " <<  accountBalance <<"k" << endl;
    writeHistory("Kiem tra tai khoan");
}

void Account::changePassword()
{
    string oldpw;
    cout << endl << "Mat khau cu: ";
    cin >> oldpw;
    if (oldpw == password) {
        cout << endl << "Mat khau moi: ";
        string newpw1, newpw2;
        cin >> newpw1;
        if (newpw1 != password) {
            cout << endl << "Nhap lai mat khau moi: ";
            cin >> newpw2;
            if (newpw1 == newpw2) {
                password = newpw1;
                cout << endl << "Doi mat khau thanh cong";
                writeHistory("Doi mat khau");
            }
            else cout << endl << "Mat khau moi khong khop";
        }
        else cout << endl << "Mat khau moi can khac mat khau cu";
    }
    else cout << endl << "Mat khau cu khong dung";

}

void Account::forgetPassword(vector<string> list_sec_ques)
{
    system("cls");
    cout << "Chon cau hoi:" << endl;
    for (auto x : list_sec_ques) {
        cout << x << endl;
    }
    int pos;
    cin >> pos;
    if (pos == position_question) {
        cout << "Nhap cau tra loi: ";
        string ans;
        cin.ignore();
        getline(cin, ans);
        if (ans == answer_secret_question) {
            cout << endl << "Mat khau moi: ";
            string newpass;
            cin >> newpass;
            password = newpass;
            numFail = 0;
            cout << endl << "Doi mat khau thanh cong" << endl;
            writeHistory("Doi mat khau thanh cong");
        }
        else cout << endl << "Cau tra loi khong chinh xac" << endl;
    }
    else cout << "Cau hoi khong dung" << endl;

}
