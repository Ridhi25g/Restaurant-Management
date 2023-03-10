#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<fstream.h>
#include<string.h>

class restaurant
{
	int ino;
	char name[50];
	float price,qty,tax,dis;
	public:
	void create_item()
	{
		cout<<"\nPlease Enter The Order No. of The Food Item:-";
		cin>>ino;
		cout<<"\n\nPlease Enter The Name of The Food Item:-";
		gets(name);
		cout<<"\nPlease Enter The Price of The Food Item:-";
		cin>>price;
		cout<<"\nPlease Enter The Discount(%):-";
		cin>>dis;
		cout<<"\n__________________________________________________";
	 }
	void show_item()
	{
		cout<<"\nThe Order No. of The Food Item:-"<<ino;
		cout<<"\nThe Name of The Food Item:-";
		puts(name);
		cout<<"\nThe Price of The Food Item:-"<<price;
		cout<<"\nDiscount:-"<<dis;
	}
	int  retino()
	{
		return ino;
	}
	float retprice()
	{
		return price;
	}
	char* retname()
	{
		return name;
	}
	int retdis()
	{
		return dis;
	}
};
fstream fp;
restaurant pr;

void write_item()
{
	fp.open("Rest.dat",ios::out|ios::app);
	pr.create_item();
	fp.write((char*)&pr,sizeof(pr));
	fp.close();
	cout<<"\n\nThe item Has Been Created ";
	getch();
}

void display_all()
{
	clrscr();
	cout<<"\n\n\n\t\tDISPLAY ALL ITEMS\n\n";
	fp.open("Rest.dat",ios::in);
	while(fp.read((char*)&pr,sizeof(pr)))
	{
		pr.show_item();
		cout<<"\n\n========================================\n";
	}
	fp.close();
	getch();
}

void display_sp(int n)
{
	int flag=0;
	fp.open("Rest.dat",ios::in);
	while(fp.read((char*)&pr,sizeof(pr)))
	{
		if(pr.retino()==n)
		{
			clrscr();
			pr.show_item();
			flag=1;
		}
	}
	fp.close();
	if(flag==0)
	cout<<"\n\nrecord not exist";
	cout<<"\n\n====================================================";
	getch();
}

void modify_item()
{
	int no,found=0;
	clrscr();
	cout<<"\n\n\tTo Modify ";
	cout<<"\n\n\tPlease Enter The Order No. of The Food Item:-";
	cin>>no;
	fp.open("Rest.dat",ios::in|ios::out);
	while(fp.read((char*)&pr,sizeof(pr)) && found==0)
	{
		if(pr.retino()==no)
		{
			pr.show_item();
			cout<<"\nPlease Enter The New Details of Food Item:-"<<endl;
			pr.create_item();
			int pos=-1;
			fp.seekp(pos,ios::cur);
			fp.write((char*)&pr,sizeof(pr));
			cout<<"\n\n\t Record Updated";
			found=1;
		}
	}
	fp.close();
	if(found==0)
	cout<<"\n\n Record Not Found ";
	cout<<"\n__________________________________________________";
	getch();
}

void delete_item()
{
	int no;
	clrscr();
	cout<<"\n\n\n\tDelete Record";
	cout<<"\n\nPlease Enter The Order No. Of The Food Item You Want To Delete:-";
	cin>>no;
	fp.open("Rest.dat",ios::in|ios::out);
	fstream fp2;
	fp2.open("Temp.dat",ios::out);
	fp.seekg(0,ios::beg);  
	while(fp.read((char*)&pr,sizeof(pr)))
	{
		if(pr.retino()!=no)
		{
			fp2.write((char*)&pr,sizeof(pr));
		}
	}
	fp2.close();
	fp.close();
	remove("Rest.dat");
	rename("Temp.dat","Rest.dat");
	cout<<"\n\n\tRecord Deleted ..";
	cout<<"\n\n___________________________________________";
	getch();
}

void menu()
{
	clrscr();
	fp.open("Rest.dat",ios::in);
	if(!fp)
	{
		cout<<"EMPTY FILE!";
		getch();
		exit(0);
	}
	cout<<"\n\n\t\tFOOD MENU\n\n";
	cout<<"====================================================\n";
	cout<<"O.NO.\t\t\tNAME\t\t\tPRICE\n";
	cout<<"====================================================\n";
	while(fp.read((char*)&pr,sizeof(pr)))
	{
		cout<<pr.retino()<<"\t\t\t"<<pr.retname()<<"\t\t\t"<<pr.retprice()<<endl;
	}
	fp.close();
}
void place_order()
{
	int  order_arr[50],quan[50],c=0;
	float amt,damt,total=0;
	char ch='Y';
	menu();
	cout<<"\n============================";
	cout<<"\n  PLACE YOUR ORDER";
	cout<<"\n============================\n";
	do{
		cout<<"\n\nEnter The Order No. Of The Food Item : ";
		cin>>order_arr[c];
		cout<<"\nQuantity in number : ";
		cin>>quan[c];
		c++;
		cout<<"\nDo You Want To Order Another Food Item ? (y/n)";
		cin>>ch;
	}while(ch=='y' ||ch=='Y');
	cout<<"\n\nThank You For Placing The Order";
             getch();
             clrscr();
	cout<<"\n\n*****************************INVOICE******************************\n";
	cout<<"\nOr No.\tOr Name\tQuantity \tPrice \tAmount \tAmount after discount\n";
	for(int x=0;x<=c;x++)
	{
		fp.open("Rest.dat",ios::in);
		fp.read((char*)&pr,sizeof(pr));
		while(!fp.eof())
		{
			if(pr.retino()==order_arr[x])
			{
				 amt=pr.retprice()*quan[x];
				 damt=amt-(amt*pr.retdis()/100);
				 cout<<"\n"<<order_arr[x]<<"\t"<<pr.retname()<<"\t"<<quan[x]<<"\t\t"<<pr.retprice()<<"\t"<<amt<<"\t\t"<<damt;
				 total+=damt;
			}
			fp.read((char*)&pr,sizeof(pr));
		}
		fp.close();
	}
	cout<<"\n\n\t\t\t\t\tTOTAL = "<<total;
	getch();
}

void intro()
{
	clrscr();
	cout<<"\t\t\t\t\tRESTAURANT MANAGEMENT SYSTEM";
	cout<<"\n\n\t\t\t___________________________________\n";
	getch();
}

void admin_menu()
{
	clrscr();
	char ch2;
	cout<<"\n\n\n\tADMIN MENU";
	cout<<"\n\n\t1.CREATE ITEM";
	cout<<"\n\n\t2.DISPLAY ALL FOOD ITEMS";
	cout<<"\n\n\t3.SEARCH ";
	cout<<"\n\n\t4.MODIFY ITEM";
	cout<<"\n\n\t5.DELETE ITEM";
	cout<<"\n\n\t6.VIEW ORDER MENU";
	cout<<"\n\n\t7.BACK TO MAIN MENU";
	cout<<"\n\n\tPlease Enter Your Choice (1-7):-";
	ch2=getch();
	switch(ch2)
	{
		case '1': clrscr();
			  write_item();
			  break;
		case '2': display_all();
			  break;
		case '3': int num;
			  clrscr();
			  cout<<"\n\n\tPlease Enter The Order No:-";
			  cin>>num;
			  display_sp(num);
			  break;
		case '4': modify_item();
			  break;
		case '5': delete_item();
			  break;
		case '6': menu();
			  getch();
		case '7': break;
			  default:cout<<"\a";
			  admin_menu();
	}
}

void main()
{
	char ch;
	intro();
	do
	{
		clrscr();
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t01. CUSTOMER";
		cout<<"\n\n\t02. ADMINISTRATOR";
		cout<<"\n\n\t03. EXIT";
		cout<<"\n\n\tPlease Select Your Option (1-3):-";
		ch=getch();
		switch(ch)
		{
			case '1': clrscr();
				  place_order();
				  getch();
				  break;
			case '2': admin_menu();
				  break;
			case '3': exit(0);
			default : cout<<"\a";
		}
	}while(ch!='3');
getch();
}
