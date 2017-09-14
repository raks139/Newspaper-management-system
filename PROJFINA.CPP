#include<iostream.h>
#include<conio.h>
#include<fstream.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<process.h>
#include<iomanip.h>

int chk(int f);
int amonth=11;
class news
{public:
 char name[30];
 float price;     //monthly
 };

class user
{
	private:
	char username[20];
	int flatno;
	char password[10];
	float bal;               //balance amount to be paid
	float sale;              //amount earned by selling your newspaper
	float money;             //monthly amount
	int rep;                 //repetition of
	int n;                   //no of days for newspapers not needed
	int wt;                  //weight of newspapers
	int s;                   //no of subscriptions
   public:
   news subs[5];       //array of subscribed newspapers
   int ddays[30];     //array of dates for which newspapers not needed
   int month;          //current month
   char *getusername()
   {return username;}

   int getflatno()
   {return flatno;}

   char *getpassword()
   {return password;}

   int getbal()
   {return bal;}

   int getsale()
   {return sale;}

   int getmoney()
   {return money;}

   int getrep()
   {return rep;}

   int getn()
   {return n;}

   int getwt()
   {return wt;}

   void putwt(int y)
   { wt=y;}

   int gets()
   {return s;}

   void upsale(int y)
   {sale=sale+5*y;}

   void paybill();
   void showbill();
   void allot();
   void newinput();
   user()
   {
		bal=0;
		sale=0;
		month=0;
		n=0;
		wt=0;
		rep=0;
	}
 };
 void user :: showbill()
 {int t;
  money=0;
  if(month==1||month==3||month==5||month==7||month==8||month==10||month==12)
  t=31-n;
  else if (month==2)
  t=28-n;
  else t=30-n;
  cout<<setw(30)<<"BILL"<<endl;
  cout<<"Name"<<setw(30)<<"Price per day"<<setw(20)<<"Monthly price"<<endl;
  cout<<"--------------------------------------------------------------"<<endl;
  for (int h=0;h<s;h++)
  {	if(strcmp((subs[h].name),"et")==0)
	cout<<"Economic Times           "<<subs[h].price;
	else
	if(strcmp((subs[h].name),"bm")==0)
	cout<<"Bangalore Times          "<<subs[h].price      ;
	else
	if(strcmp((subs[h].name),"toi")==0)
	cout<<"Times of India           "<<subs[h].price;
	else
	if(strcmp((subs[h].name),"h")==0)
	cout<<"Hindu                    "<<subs[h].price;
	else
	if(strcmp((subs[h].name),"kn")==0)
	cout<<"Kannada Newspaper        "<<subs[h].price;
	cout<<setw(20)<<subs[h].price*t<<endl;
	money+=subs[h].price*t;}
	cout<<endl;
	cout<<endl<<"This month's newspaper bill : "<<money<<endl;
  }

 void user::paybill()
 {
	float cash;
	showbill();
	if(rep==0)
	{
	cout<<"The balance amount is :"<<bal<<endl;
	bal+=money;
	cout<<"Amount for resold papers :"<<sale<<endl;
	bal-=sale;
	}
	else
	{
	cout<<"Balance amount from previous transactions:"<<bal<<endl;
	cout<<"Amount for resold papers:"<<sale<<endl;
	}
	cout<<"Total amount to be payed : "<<bal-sale<<endl;
	cout<<"How much do you want to pay now? "<<endl;
	cin>>cash;
	bal-=cash;
	rep++;
 }
void user::allot ()
{   rep=0;
	cout<<"New subscription month : "<<amonth<<endl;
	cout<<"Enter number of days when subscription is not needed"<<endl;
	cin>>n;
	if(n!=0)
	{
	cout<<"Enter the dates (only day)"<<endl;
	for(int j=0;j<n;j++)
		cin>>ddays[j];
		}
	cout<<"Choose your newspapers"<<endl;
	cout<<"NEWSPAPER OPTIONS                    Price"<<endl;
	cout<<"---------------------------------------------------"<<endl;
	cout<<"1.TIMES OF INDIA (toi)               Rs 6"<<endl;       //enter price
	cout<<"2.HINDU (h)                          Rs 7"<<endl;
	cout<<"3.ECONOMIC TIMES (et)                Rs 9"<<endl;
	cout<<"4.KANNADA NEWSPAPER (kn)             Rs 5"<<endl;
	cout<<"5.BANGALORE MIRROR (bm)              Rs 6"<<endl;
	cout<<"Enter number of subscriptions"<<endl;
	cin>>s;
	for(int i=0;i<s;i++)
	{
		cout<<"Enter name of newspaper abbreviation "<<i+1<<" : "<<endl;
		cin>>subs[i].name;
		if (strcmp(subs[i].name,"toi")==0)
		subs[i].price=6 ;
		else
		if (strcmp(subs[i].name,"h")==0)
		subs[i].price=7 ;
		else
		if (strcmp(subs[i].name,"et")==0)
		subs[i].price=9 ;
		else
		if (strcmp(subs[i].name,"kn")==0)
		subs[i].price=5 ;
		else
		if (strcmp(subs[i].name,"bm")==0)
		subs[i].price=6 ;
	}
}

void user::newinput()        //inputing data for a new account
{
	char c;
	int i=0,r=0;
	cout<<"Enter your username(no spaces)"<<endl;
	cin>>username;
	cout<<"Enter your flat number"<<endl;
	cin>>flatno;
	r=chk(flatno);
	 if (r==1)
	 cout<<"Flat number already exists"<<endl;
	 else
	 {cout<<"Enter your password"<<endl;
	  while(c!=13)
			  { c=getch();
				if(c==13)
				break;
				cout<<"*";
				password[i++]=c;
				}
				password[i]='\0';
				cout<<endl;
				allot();
	  cout<<"Congratulations! Your account has been made succesfully "<<endl;
	 }
}

user u;     //global object
int y,r;
int chk(int f)
{
	ifstream fin;
	fin.open("user.dat",ios::binary);
	while(1)
	{
	 fin.read((char*)&u,sizeof(u));
	 if(fin.eof())
	  break;
	 if(u.getflatno()==f)
	 {
	  fin.close();
	  return 1;
	 }
	}
	fin.close();
	return 0;
}

void update(int mon)
{

	fstream f;
	ofstream fout,fo;
	fo.open("newuser.dat",ios::binary|ios::out|ios::app);
	f.open("user.dat",ios::binary|ios::in|ios::out);
	fout.open("wrong.dat",ios::binary|ios::app|ios::out);
	while(1)
	{

		f.read((char*)&u,sizeof(u));
		if(f.eof())
			break;
		if (u.getbal()>600)
			fout.write((char*)&u,sizeof(u));
		else
		{u.month=mon;
		 fo.write((char*)&u,sizeof(u));
		 }

	 }
	 fo.close();
	 fout.close();
	 f.close();
	 remove("user.dat");
	 rename("newuser.dat","user.dat");


}

void disday(int date)
{
	int t=0;
	ifstream fin;
	fin.open("user.dat",ios::binary|ios::in);
	while(!fin.eof())
	{
		r=0;
		fin.read((char*)&u,sizeof(u));
		if(fin.eof())
		break;
		for(int z=0;z<u.getn();z++)
		{ 	if(date!=u.ddays[z])
			r++;
		}
	if (r==u.getn())
	{
		cout<<"Flat Number"<<u.getflatno()<<endl;
		for (int a=0;a<u.gets();a++)
		cout<<u.subs[a].name<<endl;
		t++;
	}
	}
	if(t==0)
	cout<<"No orders today"<<endl;

fin.close();
}

void main()
{
 ofstream fout;	//user
 fstream f;
 user ob;
 char pword[10],a1,a2,a3;
 int flat,flag=0;
 int choice,c1,c2,c3,pos;
 textcolor(12);
 clrscr();
 cout<<setw(1020)<<"WELCOME TO NEWSPAPER MANAGEMENT PROGRAM";
 getch();
 do
 {clrscr();
 cout<<setw(30)<<"WELCOME"<<endl;
 cout<<"Choose your login-"<<endl;
 cout<<"1.Login as a user"<<endl;
 cout<<"2.Login as the agency"<<endl;
 cout<<"3.Exit"<<endl;
 cout<<"Enter your option -"<<endl;
 cin>>choice;
 switch(choice)
	{ case 1:
		 clrscr();
		 cout<<setw(20)<<"USER"<<endl;
		 cout<<"1.Make a new account"<<endl;
		 cout<<"2.Login"<<endl;
		 cout<<"3.Exit"<<endl;
		 cout<<"Enter your choice - "<<endl;
		 cin>>c1;
		 switch(c1)
		 {case 1:clrscr();             //new account
				 cout<<"New account details"<<endl;
				 ob.newinput();
				 fout.open("user.dat",ios::binary|ios::app);
				 fout.write((char*)&ob,sizeof(ob));

				 fout.close();
				 break;
		  case 2:char c = 'a';
				 int i=0;
				 clrscr();                          //log in
				 cout<<"Enter your flat number"<<endl;
				 cin>>flat;
				 cout<<"Enter your password"<<endl;
				 while(c!=13)
				 {	 c=getch();
					 if(c==13)
					 break;
					 cout<<"*";
					 pword[i++]=c;
				 }
				 pword[i]='\0';
				 cout<<endl;

				 f.open("user.dat",ios::binary|ios::in|ios::out);
				 flag=0;
				 while(!f.eof())
				{
					f.read((char*)&ob,sizeof(ob));
					if(f.eof())
					break;
					if(flat==ob.getflatno() && strcmpi(pword,ob.getpassword())==0)
					flag=1;

				}
				f.close();
				if(flag==0)
				{	cout<<"Account does not exist"<<endl;
					getch();
					f.open("wrong.dat",ios::binary|ios::in);
					while(!f.eof())
					{
					 f.read((char*)&ob,sizeof(ob));
					 if(f.eof())
					  break;
					 if(flat==ob.getflatno() && strcmp(pword,ob.getpassword())==0)
					 {
					  cout<<"PS: You have violated our terms and conditions"<<endl;
					  getch();
					  break;
					 }
					}
					f.close();
					break;
				}
			   else
			   if (flag==1)
			   {
			   do{
			  clrscr();
			  cout<<"1.Change newspapers"<<setw(20)<<"current month: "<<amonth<<endl;
			  cout<<"2.Show bill"<<endl;
			  cout<<"3.Pay bill"<<endl;
			  cout<<"4.Call collector"<<endl;
			  cout<<"5.Log out"<<endl;
			  cout<<"Enter your choice - "<<endl;
			  cin>>c2;
			  switch(c2)
			  {
			  case 1:pos=0;
					 f.open("user.dat",ios::binary|ios::in|ios::out);
					 while(!f.eof())
					 {
					 pos=f.tellg();
					 f.read((char*)&ob,sizeof(ob));
					 if(f.eof())
					 break;
					 if(flat==ob.getflatno() && strcmpi(pword,ob.getpassword())==0)
					 {ob.allot();
					 f.seekg(pos,ios::beg);
					 f.write((char*)&ob,sizeof(ob));
					 }
					 }
					 f.close();
					 break;
			  case 2:pos=0;
					 f.open("user.dat",ios::binary|ios::in|ios::out);
					 while(!f.eof())
					{
					pos=f.tellg();
					f.read((char*)&ob,sizeof(ob));
					if(f.eof())
					break;
					if(flat==ob.getflatno() && strcmpi(pword,ob.getpassword())==0)
					{ob.showbill();
					f.seekg(pos,ios::beg);
					f.write((char*)&ob,sizeof(ob));
					}
					}
					f.close();
					break;
			  case 3:
					pos=0;
					f.open("user.dat",ios::binary|ios::in|ios::out);
					cout<<"paying bill"<<endl;
					while(!f.eof())
					{
					pos = f.tellg();
					f.read((char*)&ob,sizeof(ob));
					if(f.eof())
					break;
					if(flat==ob.getflatno() && strcmpi(pword,ob.getpassword())==0)
					{ob.paybill();
					f.seekg(pos,ios::beg);
					f.write((char*)&ob,sizeof(ob));
					}
					}
					f.close();
					break;
			 case 4:pos=0;
					int y;
					clrscr();
					float p;
					cout<<"calling collector"<<endl;
					f.open("user.dat",ios::binary|ios::in|ios::out);
					while(!f.eof())
					{
					pos=f.tellg();
					f.read((char*)&ob,sizeof(ob));
					if(f.eof())
					break;
					if(flat==ob.getflatno() && strcmpi(pword,ob.getpassword())==0)
					{
					cout<<"Enter the weight of newspaper(in kgs)"<<endl;
					cin>>y;
					ob.putwt(y);
					cout<<"Price per kg is Rs.5"<<endl;
					ob.upsale(y);
					f.seekg(pos,ios::beg);
					f.write((char*)&ob,sizeof(ob));
					 }
					}
					f.close();
					break;
			 case 5:break;
					} //end switch for user login
					cout<<"Do you want to go back to your homepage?(enter y or n)"<<endl;
					cin>>a1;
					}while(a1=='y');
					}//end of if
					break;
		  case 3:break;		}  //end of user
					break;


 case 2:
	 char c = 'a',pass[30];
	 int i=0;
	 clrscr();
	 cout<<setw(30)<<"WELCOME TO AGENCY"<<endl;
	 cout<<"Enter agency password : "<<endl;
	 while(c!=13)
	 {c=getch();
	  if(c==13)
	  break;
	  cout<<"*";
	  pass[i++]=c;
	  }
	  pass[i]='\0';
	  if(strcmp(pass,"agency")!=0)
	  {
	 cout<<endl<<"Wrong password"<<endl;
	 break;}
	 if (strcmp(pass,"agency")==0)
	 {
	 do
	 {clrscr();
	 cout<<"AGENCY HOMEPAGE"<<endl;      //agency
	 cout<<"1.Update month and check wrong doers"<<endl;
	 cout<<"2.Display particular day's orders"<<endl;
	 cout<<"3.Exit"<<endl;
	 cout<<"Enter your choice-"<<endl;
	 cin>>c3;
	 switch(c3)            //newspaper distributor
	 {case 1:
		  clrscr();
		  cout<<"Updating month"<<endl;
		  cout<<"Enter new month-"<<endl;
		  cin>>amonth;
		  update(amonth);
		  break;

	  case 2: int d;
		 clrscr();
		 cout<<"Particular day order"<<endl;
		 cout<<"Enter todays date-"<<endl;
		 cin>>d;
		 disday(d);
		 break;

	  case 3: exit(0);
			  break;
	 }
	 cout<<"Do you wish to go back to agency menu?(enter y or n)"<<endl;
	 cin>>a3;}while(a3=='y');
	}
	}  //end of switch case
	cout<<"Do you want to go back to login menu?(enter y or n)"<<endl;
	cin>>a2;
	}while(a2=='y');

	getch();
	}


