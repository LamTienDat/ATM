#include"Account.h"

using namespace std;

vector<Account> list_account;
int bank[501];
vector<string> list_secret_question;


void initData() 
{

    list_account.erase(list_account.begin(), list_account.end());
    list_secret_question.erase(list_secret_question.begin(), list_secret_question.end());
    ifstream file("Account.txt");
    if (file.is_open()) 
    {
        string id, password, money, numFail, posques, ans;
        while (getline(file, id, '.')) {
            getline(file, password, '.');
            getline(file, money, '.');
            getline(file, numFail, '.');
            getline(file, posques, '.');
            getline(file, ans, '.');
            Account p(id, password, stoi(money), stoi(numFail), stoi(posques), ans);
            list_account.push_back(p);
        }
        file.close();
    }
    ifstream f("Bank.txt");
    f >> bank[500];
    f >> bank[200];
    f >> bank[100];
    f >> bank[50];
    f.close();

    ifstream fq("SecretQuestion.txt");
    if (fq.is_open()) {
        while (!fq.eof())
        {
            string s;
            getline(fq, s);
            list_secret_question.push_back(s);
        }
        fq.close();
    }
}

void saveData() 
{
    ofstream file("Bank.txt");
    file << bank[500] << " " << bank[200] << " " << bank[100] << " " << bank[50];
    file.close();
    ofstream f("Account.txt");
    if (f.is_open()) {
        for (Account x : list_account)
        {
            f << x.getInformation();
        }
        f.close();
    }
}

int selectMode() {
    int x = -1;
    while (x == -1) {
        cin >> x;
    }
    return x;
}

int main()
{
LOOP:
    system("cls");
    int choose = 0;
    string id = "", password = "";
    initData();
    while (true) 
    {
        system("cls");
        cout << "1.Dang nhap" << "                   ";
        cout << "2.Tao tai khoan                 3.Quen mat khau" << endl;
        cin >> choose;
        if (choose == 1) 
        {
            cout << "ID: ";
            cin >> id;
            bool checkLogin = false;
            for (int i = 0; i < list_account.size(); i++) 
            {
                if (id == list_account.at(i).getID()) 
                {
                    checkLogin = true;
                    if (list_account.at(i).login()) 
                    {
                        Account* currentAccount = &list_account.at(i);
                    MENU:
                        int ch = 0;
                        system("cls");
                        cout << "1.Nap tien" << endl;
                        cout << "2.Rut tien" << endl;
                        cout << "3.Chuyen tien" << endl;
                        cout << "4.Lich su" << endl;
                        cout << "5.Kiem tra tai khoan" << endl;
                        cout << "6.Doi mat khau" << endl;
                        cin >> ch;
                        if (ch == 1) 
                        {
                            currentAccount->deposit(bank);
                        }
                        else if (ch == 2) 
                        {
                            currentAccount->cashWithDrawals(bank);
                        }
                        else if (ch == 3) 
                        {
                            string receiveId;
                            cout << "Nhap id nguoi nhan: ";
                            cin >> receiveId ;
                            for(int j = 0; j< list_account.size(); j++)
                                if (list_account.at(j).getID() == receiveId) 
                                {
                                    list_account.at(j).receiveMoney(currentAccount->sendMoney());
                                }
                        }
                        else if (ch == 4) 
                        {
                            currentAccount->printHistory();
                        }
                        else if (ch == 5)
                        {
                            currentAccount->checkAccountBalance();
                        }
                        else if (ch == 6) {
                            currentAccount->changePassword();
                        }
                        saveData();
                        cout << "\n1.Tro lai\n2.Dang xuat\n";
                        int sl = selectMode();
                        if (sl == 1) goto MENU;
                        else if (sl == 2) goto LOOP;
                        
                    }
                }
            }
            if (!checkLogin) {
                cout << "Tai khoan nay khong ton tai " << endl;
                cout << "\n1.Tro lai\n";
                int sl = selectMode();
                if (sl == 1) goto LOOP;
            }

        }
        else if (choose == 2) 
        {
            cout << "ID : ";
            cin >> id;
            bool ok = true;
            for (int i = 0; i < list_account.size(); i++) {
                if (list_account.at(i).getID() == id)
                    ok = false;
            }
            if (ok) {
                Account p;
                if (p.creatAccount(id, list_secret_question))
                {
                    list_account.push_back(p);
                    cout << "Thanh cong" << endl;
                }
                else cout << "That bai" << endl;
            }
            else
            {
                cout << "Tai khoan nay da ton tai" << endl;
            }
            cout << "\n1.Tro lai\n";
            saveData();
            int sl = selectMode();
            if (sl == 1) goto LOOP;
        }
        else if (choose == 3) {
            system("cls");
            cout << "Nhap id: ";
            cin >> id;
            for (int i = 0; i < list_account.size(); i++) {
                if (list_account.at(i).getID() == id) {
                    list_account.at(i).forgetPassword(list_secret_question);
                }
            }
            cout << "\n1.Tro lai\n";
            saveData();
            int sl = selectMode();
            if (sl == 1) goto LOOP;
        }

    }
    
    return 0;
}

