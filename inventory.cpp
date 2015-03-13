// =========================================
// 		HEADER FILES
// =========================================

#include<fstream.h>
#include<dos.h>
#include<conio.h>
#include<process.h>
#include<stdio.h>
#include<string.h>
#include<iomanip.h>

// ========================================
// 	 CLASS DEFINED IN THE PROGRAM
// ========================================

class stock
{
	char name[50];
	int quantity,stockid;
	float price;
	public:
	void in(int);
	void out();
	int retstockid();
	int retquantity();
	float retprice();
	void updatequantity(int);
	char* retname();
	void change();
};

// ===================================================================
//	       DECLARATION OF GLOBAL VARIABLES AND OBJECTS
// ===================================================================

fstream f;
stock s;
long size=sizeof(s);
int static counter=0;
int arraysid[30],arrayquan[30];

// =====================================================================
// 	    EXPLICIT DECLARATION OF FUNCTIONS OF CLASS STOCK
// =====================================================================

void stock::in(int sid)
{
	gotoxy(23,10);
	cout<<"Stock ID of the Item: "<<sid;
	gotoxy(23,11);
	cout<<"Enter the Name of the Item: ";
	gets(name);
	gotoxy(23,12);
	cout<<"Enter Quantity of the item: ";
	cin>>quantity;
	gotoxy(23,13);
	cout<<"Enter the Rate of the Item: ";
	cin>>price;
	stockid=sid;
}

void stock::out()
{
	cout<<setw(6)<<stockid<<setw(17)<<name<<setw(15)<<quantity<<setw(15)<<price;
}

int stock::retstockid()
{
	return(stockid);
}

void stock::change()
{
	gotoxy(15,11);
	cout<<"Enter New Name of the Item: ";
	gets(name);
	gotoxy(15,12);
	cout<<"Enter New Quantity of the Item: ";
	cin>>quantity;
	gotoxy(15,13);
	cout<<"Enter Price of the Item: ";
	cin>>price;
}

int stock::retquantity()
{
	return(quantity);
}

void stock::updatequantity(int q)
{
	quantity=retquantity()-q;
}

float stock::retprice()
{
	return(price);
}

char* stock::retname()
{
	return(name);
}

// ======================================
// 	     AUTOGEN FUNCTION
// ======================================

int autogen()
{
	int p,sid;
	f.open("stock.dat",ios::in|ios::out|ios::binary);
	if(f.fail())
	{
		cerr<<"\n File could not be opened.";
		getch();
		exit(1);
	}
	f.seekg(0,ios::end);
	p=f.tellg();
	if(p==0)
		sid=1;
	else
	{
		f.seekg(-size,ios::end);
		f.read((char*)&s,size);
		sid=s.retstockid();
		sid++;
	}
	f.close();
	return(sid);
}

// ================================
// 	  DISPLAY FUNCTION
// ================================

void display()
{
	void storename();
	int i=0;
	storename();
	f.open("stock.dat",ios::in|ios::binary);
	if(f.fail())
	{
		cerr<<"\n File could not be opened for reading purpose.";
		getch();
		exit(1);
	}
	else
	{
		gotoxy(10,8);
		cout<<"=========================================================";
		gotoxy(10,9);
		cout<<"   Stock ID "<<setw(15)<<" Item Name "<<setw(15)<<" Quantity "<<setw(15)<<" Price ";
		gotoxy(10,10);
		cout<<"=========================================================";

		while(f.read((char*)&s,size))
		{
			gotoxy(10,11+i);
			s.out();
			i++;
		}
		f.close();
	}
}

// ======================================
// 		INPUT FUNCTION
// ======================================

void input()
{
	int sid;char ch;
	clrscr();
	void storename();
	storename();
	sid=autogen();
	f.open("stock.dat",ios::app|ios::binary);
	if(f.fail())
	{
		cerr<<"\n File could not be opened for writing purpose";
		getch();
		exit(1);
	}
	else
	{
		s.in(sid);
		f.write((char*)&s,size);
	}
	f.close();
	gotoxy(26,15);
	cout<<"Item Added Successfully";
	getch();
}


// =======================================
// 		DELETE FUNCTION
// =======================================

void Delete()
{
	clrscr();int fsize,f2size;
	void storename();
	storename();
	f.open("stock.dat",ios::in|ios::binary);
	if(f.fail())
	{
		cerr<<"File can't be opened.";
		getch();
		exit(1);
	}
	fstream f2;int sid;
	f2.open("temp.dat",ios::out|ios::binary);
	if(f2.fail())
	{
		cerr<<"File can't Be opened.";
		getch();
		exit(1);
	}
	gotoxy(15,10);
	cout<<"Enter the Stock ID of the Item to be deleted: ";
	cin>>sid;
	while(f.read((char*)&s,size))
	{
		if(s.retstockid()!=sid)
			f2.write((char*)&s,size);
	}
	f.seekg(0,ios::end);
	fsize=f.tellg()/size;
	f2.seekg(0,ios::end);
	f2size=f2.tellg()/size;
	f.close();f2.close();
	remove("stock.dat");
	rename("temp.dat","stock.dat");
	if(f2size==fsize)
	{
		gotoxy(15,11);
		cout<<"No Item with Stock ID "<<sid<<" found.";
		getch();
	}
	else
	{
		gotoxy(25,12);
		cout<<"Item Removed Successfully";
		getch();
	}
}


// ============================================
//		MODIFY FUNCTION
// ============================================

void modify()
{
	clrscr();
	void storename();
	storename();
	int sid,flag=-1;
	f.open("stock.dat",ios::in|ios::out|ios::binary);
	if(f.fail())
	{
	 cerr<<"File can't be opened.";
	 getch();
	 exit(1);
	}
	gotoxy(15,10);
	cout<<"Enter the Stock ID of the Item to be modified: ";
	cin>>sid;
	while(f.read((char*)&s,size))
	{
		if(s.retstockid()==sid)
		{
			s.change();
			f.seekp(-size,ios::cur);
			f.write((char*)&s,size);
			flag=1;
		}
	}
	if(flag==-1)
	{
		gotoxy(15,11);
		cout<<"No Item with stock ID "<<sid<<" found.";
		getch();
	}
	else
	{
		gotoxy(21,15);
		cout<<"Item Modified Successfully";
		getch();
	}
	f.close();

}

// ====================================
//     	     ADMINPASS FUNTION
// ====================================
void adminpass()
{
	char pass[30],ch; int i=0;
	ofstream ofobj("pass.txt");
	if(ofobj.fail())
	{
		cerr<<"\n File could not be opened for writing purpose";
		getch();
		exit(1);
	}
	gotoxy(15,3);
	cout<<"====================================================";
	gotoxy(20,4);
	cout<<"WELCOME TO THE INVENTORY MANAGEMENT PROGRAM";
	gotoxy(15,5);
	cout<<"====================================================";
	gotoxy(20,7);
	cout<<"You are using the program for the first time";
	gotoxy(20,9);
	cout<<"Create a password for administrative purpose !";
	gotoxy(20,11);
	cout<<"Enter Password: ";
	while(ch!=13)
	{
		ch=getch();
		if(ch!=13)
		{
			cout<<"*";
			pass[i]=ch;
			i++;
		}
	}
	pass[i]='\0';
	ofobj<<pass;
	ofobj.close();
}

// ==============================================
// 		CHANGEPASS FUNCTION
// ==============================================
void changepass()
{
	char password[30],pass[30],ch; int l,i;
	clrscr();
	void storename();
	storename();
	ifstream ifobj("pass.txt");
	if(ifobj.fail())
	{
		cerr<<"\n File could not be opened.";
		getch();
		exit(1);
	}
	while(!ifobj.eof())
	{
		ifobj.getline(password,30,' ');
	}
	ifobj.close();
	l=strlen(password);
	gotoxy(25,10);
	cout<<"Enter Old Password: ";
	for(i=0;i<l;i++)
	{
		pass[i]=getch();
		cout<<"*";
	}
	pass[i]='\0';
	getch();
	if(strcmp(pass,password)==0)
	{
		gotoxy(25,11);
		i=0;
		cout<<"Enter New Passowrd: ";
		while(ch!=13)
		{
			ch=getch();
			if(ch!=13)
			{
				cout<<"*";
				pass[i]=ch;
				i++;
			}
		}
		pass[i]='\0';
		ofstream ofobj("pass.txt");
		ofobj<<pass;
		ofobj.close();
		gotoxy(25,13);
		cout<<"Password Changed Successfully";
		getch();
	}
	else
	{
		gotoxy(25,11);
		cout<<"Wrong Password";
		getch();
	}
}

// =========================================
//		STOCK MENU
// =========================================
void stockmenu()
{
	char choice;
	clrscr();
	void storename();
	storename();
	gotoxy(25,10);
	cout<<"=============================";
	gotoxy(33,11);
	cout<<"MANAGE STOCK";
	gotoxy(25,12);
	cout<<"=============================";
	gotoxy(31,14);
	cout<<"1.Add an Item";
	gotoxy(31,15);
	cout<<"2.View all the Stock";
	gotoxy(31,16);
	cout<<"3.Modify an Item";
	gotoxy(31,17);
	cout<<"4.Remove an Item";
	gotoxy(31,18);
	cout<<"5.Back";
	gotoxy(31,19);
	cout<<"6.Exit";
	gotoxy(29,21);
	cout<<"Enter Your Choice: ";
	choice=getche();
	switch(choice)
	{
		case '1': input();
			  stockmenu();
			  break;
		case '2': clrscr();
			  display();
			  getch();
			  stockmenu();
			  break;
		case '3': clrscr();
			  modify();
			  stockmenu();
			  break;
		case '4': Delete();
			  stockmenu();
			  break;
		case '5': break;
		case '6': clrscr();
			  gotoxy(18,12);
			  cout<<"THANK YOU FOR USING INVENTORY MANAGEMENT PROGRAM";
			  getch();
			  exit(0);
		default:  gotoxy(29,22);
			  cout<<"Wrong Choice";
			  delay(1000);
	}
}

// =========================================
//	   VIEWREPORTS FUNTION
// =========================================

void viewreports()
{
	clrscr();
	void storename();
	fstream fobj; char str[100];
	fobj.open("Reports.txt",ios::in);
	if(fobj.fail())
	{
		cerr<<"\n File Could Not Be Opened";
		getch();
		exit(1);
	}
	storename();
	gotoxy(10,8);
	cout<<"=========================================================";
	gotoxy(15,9);
	cout<<"Date"<<setw(12)<<"Time"<<setw(15)<<"Stock ID"<<setw(15)<<"Quantity";
	gotoxy(10,10);
	cout<<"=========================================================\n";
	while(!fobj.eof())
	{
	   fobj.getline(str,100,'\n');
	   cout<<"           "<<str<<"\n";
	}
	getch();
}

// =========================================
// 	  ADMINISTRATOR MENU FUNCTION
// =========================================

void adminmenu()
{
	clrscr();
	void storename();
	storename();
	char choice2; int sid;
	gotoxy(25,10);
	cout<<"=============================";
	gotoxy(33,11);
	cout<<"ADMINISTRATOR ";
	gotoxy(25,12);
	cout<<"=============================";
	gotoxy(31,14);
	cout<<"1.Manage Stock";
	gotoxy(31,15);
	cout<<"2.View Report";
	gotoxy(31,16);
	cout<<"3.Change Password";
	gotoxy(31,17);
	cout<<"4.Back to Main Menu";
	gotoxy(31,18);
	cout<<"5.Exit";
	gotoxy(29,20);
	cout<<"Enter Your Choice: ";
	choice2=getche();
	switch(choice2)
	{
		case '1': stockmenu();
			  adminmenu();
			  break;
		case '2': viewreports();
			  adminmenu();
			  break;
		case '3': changepass();
			  adminmenu();
			  break;
		case '4': break;
		case '5': clrscr();
			  gotoxy(18,12);
			  cout<<"THANK YOU FOR USING INVENTORY MANAGEMENT PROGRAM";
			  getch();
			  exit(0);
		default:  gotoxy(29,24);
			  cout<<"Wrong Choice";
			  delay(1000);
			  adminmenu();
	   }

}

// ====================================================
// 	          CHECKPASS FUNCTION
// ====================================================

void checkpass()
{
	clrscr();
	void storename();
	storename();
	char choice2,pass[30],password[30] ; int l,i; static int j=0;

	ifstream ifobj("pass.txt");
	if(ifobj.fail())
	{
		cerr<<"\n File could not be opened for reading purpose.(pass.txt)";
		getch();
		exit(1);
	}
	while(!ifobj.eof())
	{
		ifobj.getline(password,30,' ');
	}
	ifobj.close();
	l=strlen(password);
	if(j<5)
	{
		cout<<"\n         Enter Password: ";
		for(i=0;i<l;i++)
		{
			pass[i]=getch();
			cout<<"*";
		}
		pass[i]='\0';
		getch();
		if(strcmp(pass,password)==0)
		{
		       adminmenu();
		}
		else
		{
			j++;
			cout<<"\n         Password is incorrect.";
			cout<<"\n         "<<5-j<<" Attempts remaining.";
			getch();
			checkpass();
		}

	}
	else
	{
		cout<<"\n         All Attempts Failed";
		getch();
	}
}

// ====================================
// 	    CHECKSID FUNCTION
// ====================================
int checksid(int sid)
{
	int flag=0;
	f.open("stock.dat",ios::in|ios::binary);
	if(f.fail())
	{
		cerr<<"\n File could not be opened.";
		getch();
		exit(1);
	}
	while(f.read((char*)&s,size))
	{
		if(s.retstockid()==sid)
		{
			flag=1;
			break;
		}
	}
	f.close();
	return(flag);
}
// =================================================
// 		CHECKQUANTITY FUNCTION
// =================================================
int checkquantity(int q,int sid)
{
	int flag=0;
	f.open("stock.dat",ios::in|ios::binary);
	if(f.fail())
	{
		cerr<<"\n File could not be opened.";
		getch();
		exit(1);
	}
	while(f.read((char*)&s,size))
	{
		if(s.retstockid()==sid)
		{
			if(s.retquantity()>=q)
			flag=1;
			break;

		}
	}
	f.close();
	return(flag);
}

// =======================================
// 		UPDATE FUNCTION
// =======================================
void update(int sid,int q)
{
	f.open("stock.dat",ios::in|ios::out|ios::binary);
	if(f.fail())
	{
		cerr<<"\n File could not be opened.";
		getch();
		exit(1);
	}
	while(f.read((char*)&s,size))
	{
		if(s.retstockid()==sid)
		{
			s.updatequantity(q);
			f.seekg(-size,ios::cur);
			f.write((char*)&s,size);
	}       }
	f.close();
}

// =======================================
//		BILL FUNCTION
// =======================================

void bill()
{
   clrscr();
   struct time t;
   struct date d;
   int i; float price,total=0; char name[30];
   if(f.fail())
   {
	cerr<<"\n File could not be opened.";
	getch();
	exit(1);
   }
   getdate(&d);
   gettime(&t);
   cout<<"\n\n\t\t                AGNEL ENTERPRISES";
   cout<<"\n\t\t\t           GAUTAM NAGAR";
   cout<<"\n \t\t         ********** CASH MEMO ************\n";
   cout<<"\n      Date: "<<int(d.da_day)<<"/"<<int(d.da_mon)<<"/"<<int(d.da_year);
   if(t.ti_min<10)
	cout<<"\t \t \t \t \t    Time: "<<long(t.ti_hour)<<":0"<<long(t.ti_min)<<"\n";
   else if(t.ti_hour<10)
	cout<<"\t \t \t \t \t    Time: 0"<<long(t.ti_hour)<<":"<<long(t.ti_min)<<"\n";
   else

	cout<<"\t \t \t \t \t    Time: "<<long(t.ti_hour)<<":"<<long(t.ti_min)<<"\n";
   cout<<"\n   ========================================================================";
   cout<<"\n    Stock ID "<<setw(15)<<" Item Name "<<setw(15)<<" Quantity "<<setw(15)<<" Rate "<<setw(15)<<" Amount ";
   cout<<"\n   ========================================================================";
   f.open("stock.dat",ios::in,ios::binary);
   while(f.read((char*)&s,size))
   {
      for(i=0;i<counter;i++)
      {
	if(s.retstockid()==arraysid[i])
	 {
		price=s.retprice()*arrayquan[i];
		total+=price;
		cout<<"\n "<<setw(6)<<arraysid[i]<<setw(17)<<s.retname()<<setw(15)<<arrayquan[i]<<setw(15)<<s.retprice()<<setw(15)<<price;
	 }
      }
   }
   f.close();
   cout<<"\n\n  \t\t\t\t\t\t\t----------------";
   cout<<"\n\t\t\t\t\t\t\t  TOTAL Rs "<<total;
   cout<<"\n    \t\t\t\t\t\t\t----------------";
   getch();
}


// ==========================================
// 		PURCHASE FUNCTION
// ==========================================

void purchase()
{
	int sid,check,check1,q;
	char ch;
	do
	{
		clrscr();
		void storename();
		storename();
		display();
		gotoxy(12,21);
		cout<<"Enter the Stock IDs of the Items to be Purchased.";
		gotoxy(12,22);
		cout<<"Enter Stock ID: ";
		cin>>sid;
		check=checksid(sid);
		if(check==0)
		{
			gotoxy(12,23);
			cout<<"Enter Valid Stock ID.";
			getch();
			purchase();
			return;
		}
		else
		{
			gotoxy(12,23);
			cout<<"Enter Quantity: ";
			cin>>q;
			check1=checkquantity(q,sid);
			if(check1==0)
			{
				gotoxy(12,24);
				cout<<"Quantity not Available.";
				getch();
				purchase();
				return;
			}
			else
				update(sid,q);
		}
		if(check!=0 && check1!=0)
		{
			arraysid[counter]=sid;
			arrayquan[counter]=q;
			void report();
			report();
			counter++;
		}
		gotoxy(12,24);
		cout<<"Do you want to purchase more Items ? Press Y/N  ";
		ch=getche();

	}while(ch=='y'|| ch=='Y');

}

// ========================================
//		STORENAME FUNCTION
// ========================================

void storename()
{
	struct date d;
	getdate(&d);
	struct time t;
	gettime(&t);
	gotoxy(30,3);
	cout<<"AGNEL ENTERPRISES";
	gotoxy(33,4);
	cout<<"GAUTAM NAGAR";
	gotoxy(10,6);
	cout<<"DATE:";
	cout<<(int)d.da_day<<"/"<<(int)d.da_mon<<"/"<<(int)d.da_year;
	gotoxy(55,6);
	cout<<"TIME: ";
	if(t.ti_min<10)
		cout<<(int)t.ti_hour<<":0"<<(int)t.ti_min;
	else if(t.ti_hour<10)
		cout<<"0"<<int(t.ti_hour)<<":"<<long(t.ti_min)<<"\n";
	else
		cout<<(int)t.ti_hour<<":"<<(int)t.ti_min;
	cout<<"\n\n";
}

// =========================================
// 		REPORT FUNCTION
// =========================================

void report()
{
	fstream fobj;
	struct date d;
	struct time t;
	getdate(&d);
	gettime(&t);
	fobj.open("Reports.txt",ios::app);
	if(fobj.fail())
	{
		cerr<<"\n File Could Not Be Opened";
		getch();
		exit(0);
	}
	if(d.da_day<10 || d.da_mon<10)
	{
		if(d.da_day<10 && d.da_mon<10)
			fobj<<"0"<<(int)d.da_day<<"/"<<"0"<<(int)d.da_mon<<"/"<<(int)d.da_year<<"    ";
		else if(d.da_mon<10)
			fobj<<(int)d.da_day<<"/"<<"0"<<(int)d.da_mon<<"/"<<(int)d.da_year<<"    ";
		else
			fobj<<"0"<<(int)d.da_day<<"/"<<(int)d.da_mon<<"/"<<(int)d.da_year<<"    ";
	}
	if(d.da_day>10 && d.da_mon>10)
		fobj<<(int)d.da_day<<"/"<<(int)d.da_mon<<"/"<<(int)d.da_year<<"    ";
	if(t.ti_min<10)
		fobj<<(int)t.ti_hour<<":0"<<(int)t.ti_min;
	else
		fobj<<(int)t.ti_hour<<":"<<(int)t.ti_min;
	fobj<<"           "<<arraysid[counter]<<"              "<<arrayquan[counter]<<"\n";
}

// =========================================
// 		MAIN FUNCTION
// =========================================

void main()
{
	char choice;
	do
	{
		clrscr();
		ifstream ifobj("pass.txt");
		if(ifobj.fail())
		{
			adminpass();
			clrscr();
		}
		storename();
		gotoxy(25,10);
		cout<<"============================";
		gotoxy(31,11);
		cout<<"STOCK MANAGEMENT ";
		gotoxy(25,12);
		cout<<"============================";
		gotoxy(31,14);
		cout<<"1.Transactions";
		gotoxy(31,15);
		cout<<"2.Administrator";
		gotoxy(31,16);
		cout<<"3.Exit";
		gotoxy(29,18);
		cout<<"Enter Your Choice: ";
		choice=getche();
		switch(choice)
		{
			case '1': clrscr();
				  counter=0;
				  purchase();
				  bill();
				  break;
			case '2': checkpass();
				  break;
			case '3': clrscr();
				  gotoxy(18,12);
				  cout<<"THANK YOU FOR USING INVENTORY MANAGEMENT PROGRAM";
				  getch();
				  exit(0);
				  break;
			default: gotoxy(29,19);
				 cout<<"Wrong Choice.";
				 delay(1000);
		}
	}while(choice!='3');
}
