#include<iostream>
#include<stdlib.h>
#include<conio.h>
#include<string>
#include<string.h>
#include<fstream>
using namespace std;
int i=0;
class Bank
{
  private:
  char accholder[30];
  char acctype;
  float balance=0;
  int limit=0;

  public:
  int accno;
  void get()
  {  accountno:
      cout<<"Enter the 4 digit account no: ";
      cin>>accno;
      int temp=accno,n,counnt=0;
      while(temp!=0)
      { n=temp%10;
         temp=temp/10;
          counnt++;
      }
      if(counnt!=4)
      {
          cout<<"Kindly,enter a valid 4 digit acount no"<<endl;
          goto accountno;
      }
      cout<<"Enter account holder's name: ";
      cin>>accholder;
      cout<<"Enter the account type:( c for checking or s for savings): ";
      cin>>acctype;
  accounttype:
        if(acctype=='s'||acctype=='S')
      { cout<<"For saving accounts,initial amount should be more than 1000"<<endl;
        cout<<"Enter your initial amount: ";
        cin>>balance;
        if(balance<1000)
        {   cout<<"Insufficient amount for savings account!"<<endl;
            goto accounttype;
        }
        i++;
        cout<<"Savings account created successfully"<<endl;
        //saving every entry in txt file
       ofstream file("bankfile.txt",ios::app);
       file<<"---New Entry---"<<endl;
       file<<"Account number: "<<accno<<endl;
       file<<"Account Holder: "<<accholder<<endl;
       file<<"Account Type: "<<acctype<<endl;
       file<<"Account Balance: "<<balance<<"/-"<<endl;
       file.close();


      }
      else if(acctype=='c'||acctype=='C')
      { cout<<"For Checking account initial amount should be more than 3000"<<endl;
        cout<<"Enter your initial amount: ";
        cin>>balance;
        if(balance<3000)
        {    cout<<"Insufficient amount for checkinng account!"<<endl;
            goto accounttype;

        }
        i++;
       cout<<"Current account created successsfully"<<endl;
       //saving every entry in txt file
       ofstream file("bankfile.txt",ios::app);
       file<<"---New Entry---"<<endl;
       file<<"Account number: "<<accno<<endl;
       file<<"Account Holder: "<<accholder<<endl;
       file<<"Account Type: "<<acctype<<endl;
       file<<"Account Balance: "<<balance<<"/-"<<endl;
       file.close();


      }

      else{
        cout<<"Enter valid acctype!!"<<endl;
        goto accounttype;
      }
  }
  void display()
  {
     if(i=0)
     {
       cout<<"No accounts made yet! Please make an account first"<<endl;

      }
      else
    {


      cout<<"-------------Displaying your details for acc no "<<accno<<" ----------------"<<endl;
      cout<<"Account number: "<<accno<<endl;
      cout<<"Account Holder: "<<accholder<<endl;
      cout<<"Account Type: "<<acctype<<endl;
      cout<<"Account Balance: "<<balance<<"/-"<<endl;
    }

  }
  float getbalance();
  void deposit();
  void withdraw();
  bool eligible(float n);
  void deleteacc();
  friend void transfer(Bank &a,Bank &b);
};


//getbalance
float Bank::getbalance()
{
    return balance;
}


//eligiblity for withdrawal and transfer
bool Bank::eligible(float n)
{
    if(acctype=='c'||acctype=='C')
    {
        if(((balance-n)<1000)||(balance==3000))
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    else
    {
        if(((balance-n)<3000)||(balance==1000))
        {
           return false;
        }
        else
        {
            return true;
        }
    }
}



//withdraw money
void Bank::withdraw()
{

     float n;
    cout<<"Enter the amount to be withdrawed: ";
    cin>>n;
    if(eligible(n))
    {
        balance=balance-n;
        cout<<"Withdraw successfull..Remaining balance is "<<balance<<"/-"<<endl;
        ofstream file("bankfile.txt",ios::app);
       file<<"---Change in Entry due to withdrawal---"<<endl;
       file<<"Account number: "<<accno<<endl;
       file<<"Account Holder: "<<accholder<<endl;
       file<<"Account Type: "<<acctype<<endl;
       file<<"Account Balance: "<<balance<<"/-"<<endl;
       file.close();
    }
    else
    {
     cout<<"Insufficient balance!"<<endl;
    }

}



//tranfer money from acc a to b
void transfer(Bank &a,Bank &b)
{
         int n;
    cout<<"Enter the amount to be transfered to the acc "<<b.accno<<": ";
    cin>>n;
    if(a.eligible(n))
    {
       if(a.acctype=='s'||a.acctype=='S')
       { if(a.limit<=10)
        {a.balance=a.balance-n;
         b.balance=b.balance+n;
         cout<<"Transaction successful!"<<endl;
         cout<<"Balance after this transaction in acc no "<<a.accno<<" : "<<a.balance<<"/-"<<endl;
         cout<<"Balance after this transaction in acc no "<<b.accno<<" : "<<b.balance<<"/-"<<endl;
         ofstream file("bankfile.txt",ios::app);
       file<<"---Change in Entry due to transaction---"<<endl;
       file<<"Account number: "<<a.accno<<endl;
       file<<"Account Holder: "<<a.accholder<<endl;
       file<<"Account Type: "<<a.acctype<<endl;
       file<<"Account Balance: "<<a.balance<<"/-"<<endl;
       file<<"---Change in Entry due to transaction---"<<endl;
       file<<"Account number: "<<b.accno<<endl;
       file<<"Account Holder: "<<b.accholder<<endl;
       file<<"Account Type: "<<b.acctype<<endl;
       file<<"Account Balance: "<<b.balance<<"/-"<<endl;
       file.close();


        }
        else
        {
            cout<<"You've reached the limit for your number of transactions!"<<endl;
        }
       }
       else
       {
        a.balance=a.balance-n;
        b.balance=b.balance+n;
        cout<<"Transaction successful!"<<endl;
        cout<<"Balance after this transaction in acc no "<<a.accno<<" : "<<a.balance<<"/-"<<endl;
        cout<<"Balance after this transaction in acc no "<<b.accno<<" : "<<b.balance<<"/-"<<endl;
        ofstream file("bankfile.txt",ios::app);
        file<<"---Change in Entry due to transaction---"<<endl;
        file<<"Account number: "<<a.accno<<endl;
        file<<"Account Holder: "<<a.accholder<<endl;
        file<<"Account Type: "<<a.acctype<<endl;
        file<<"Account Balance: "<<a.balance<<"/-"<<endl;
        file<<"---Change in Entry due to transaction---"<<endl;
        file<<"Account number: "<<b.accno<<endl;
        file<<"Account Holder: "<<b.accholder<<endl;
        file<<"Account Type: "<<b.acctype<<endl;
        file<<"Account Balance: "<<b.balance<<"/-"<<endl;
        file.close();

       }

    }


    else
    {
     cout<<"Insufficient balance!"<<endl;
    }



}




//deposit money in account
void Bank::deposit()
{    float n;
    cout<<"Enter the amount to be deposited to the acc"<<accno<<": ";
    cin>>n;
    balance=balance+n;
    cout<<"Deposit successful!..Total balance after deposit is "<<balance<<"/-"<<endl;
     ofstream file("bankfile.txt",ios::app);
       file<<"---Change in Entry due to deposition---"<<endl;
       file<<"Account number: "<<accno<<endl;
       file<<"Account Holder: "<<accholder<<endl;
       file<<"Account Type: "<<acctype<<endl;
       file<<"Account Balance: "<<balance<<"/-"<<endl;
       file.close();


}




int getaccno(Bank a[],int i)
{   int k=0,j,accntno,ch=0;

    //goto of invalid accno to for loop
    accntnumber:
    cout<<"Enter the 4 digit,valid account no: ";
    cin>>accntno;
   /* for(j=0;j<i;j++)
    {
        a[j].get();
    } */
   for(j=0;j<i;j++)
    {
        if(a[j].accno==accntno)
        {
            k=j;
            ch=1;
          //  cout<<k<<endl;
        }
    }

    if(ch==0)
    {
        cout<<"Invalid account no!";
        goto accntnumber;

    }
    return k;

}

/*void displayall(Bank a[])
{
    int c;
         cout<<"This privilege is only for staff...enter your staff password";
         string s;
        int j;
        for (j= 0;j< 10;j++) {
          s[j] = _getch(); _putch('*');
          if (s[j] == 13)
          {   s[j]=NULL;
              break;
          }
          if(s.compare("hdfc1331")==0)
          { cout<<"Displaying all the details...."<<endl;
           for(c=0;c<i;c++)
           {
            a[c].display();
            cout<<endl;
           }
          }
         else
          {
            cout<<"The password is incorrect!";

          }

}
} */
int auth()
{



cout << "Please enter login password:";
    char pass[10] = { 0 };
    char temp[10] = "1331";
    for (int j = 0; j < 10;j++)
    {
        pass[i] = _getch();
        if (pass[i] == 13)
        {
            pass[i] = '\0';
            break;
        }
        else
        {
            _putch('*');
        }
    }
    if(strcmp(temp,pass)==0)
    {
        cout<<endl;
       // cout<<"Login Successful!"<<endl;
        return 1;
    }
    else
        return 0;
}

//Delete an account
void Bank::deleteacc()
{

    ofstream myfile("bankfile.txt",ios::app);
    myfile<<"---Deleted an account---"<<endl;
    myfile<<accno<<" Account was deleted by the account holder"<<endl;
    myfile.close();
    accno=0;
    cout<<"Account deleted successfully!"<<endl;

}

int main()
{
  int ch;
  Bank *user=new Bank;
  int n1,n2,check;
  while(1)
  {
      cout<<"*************************Welcome to our bank*****************************"<<endl;
      cout<<"#########################Here's our menu#################################"<<endl;
      cout<<"1.New account"<<endl;
      cout<<"2.Get balance"<<endl;
      cout<<"3.Withdraw"<<endl;
      cout<<"4.Deposit"<<endl;
      cout<<"5.Display your account details"<<endl;
      //cout<<".Display your account"<<endl;
      cout<<"6.Display all the accounts' details"<<endl;
      cout<<"7.Transfer money to an account"<<endl;
      cout<<"8.Delete an account"<<endl;
      cout<<"9.Exit(all accounts will be closed if you exit"<<endl;
      cout<<"Enter your choice: ";
      cin>>ch;
      switch(ch)
      {
       case 1:
       (*(user+i)).get();
        break;

         case 2:
           //  cout<<i<<endl;
         n1=getaccno(user,i);
         //cout<<n1<<endl;
         cout<<"The balance is: "<<user[n1].getbalance()<<"/-"<<endl;
         break;

         case 3:
         n1=getaccno(user,i);
         user[n1].withdraw();
         break;

         case 4:
         n1=getaccno(user,i);
         user[n1].deposit();
         break;

         case 5:
         n1=getaccno(user,i);
         user[n1].display();
         break;

         case 6:
             check=auth();
             if(!check)
             { int c;
             cout<<endl<<"Displaying all the details...."<<endl;
             for(c=0;c<i;c++)
             {  if(user[c].accno==0)
                {
                  continue;
                }
                 else
                    {
                    user[c].display();
                     cout<<endl;
                    }
             }
            }
            else
            {
                cout<<"Password is incorrect!"<<endl;
            }





          // displayall(user);
          break;


         case 7:
            cout<<"Enter for the account from which money is to be transfered: "<<endl;
            n1=getaccno(user,i);
            cout<<"Enter for the account to which money is to be transfered: "<<endl;
            n2=getaccno(user,i);
            transfer(user[n1],user[n2]);
            break;





          case 8:
         n1=getaccno(user,i);
         user[n1].deleteacc();
         break;


         case 9:
         exit(0);
         break;


         default:
         cout<<"Please enter a valid choice!"<<endl;
      }
      system("PAUSE");
    system("CLS");

  }

return 0;
}
