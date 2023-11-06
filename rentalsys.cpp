#include<conio.h>
#include<iomanip>
#include<fstream>
#include<iostream>
using namespace std;

class product
{
 int pno;
 char name[50];
 float price,qty,tax,dis;
 public:
	void create_product()
	{
	 cout<<"\nPlease Enter The CarNo. ";
	 cin>>pno;
	 cout<<"\n\nPlease Enter The Name of The Car ";
	 fflush(stdin);
	 gets(name);
	 cout<<"\nPlease Enter The Rent Price ";
	 cin>>price;
	 cout<<"\nPlease Enter The Discount (%) ";
	 cin>>dis;
	 }

	void show_product()
	{
	 cout<<"\nThe Car No. of The Car : "<<pno;
	 cout<<"\nThe Name of The Car : ";
	 puts(name);
	 cout<<"\nThe Price of The Car : "<<price<<".Rs/Day";
	 cout<<"\nDiscount : "<<dis;
	 }

  int  retpno()
  {return pno;}

  float retprice()
  {return price;}

  char* retname()
  {return name;}

  int retdis()
  {return dis;}

};       

 fstream fp;
 product pr;

void write_product()
   {
    fp.open("customer.dat",ios::out|ios::app);
    pr.create_product();
    fp.write((char*)&pr,sizeof(product));
    fp.close();
    cout<<"\n\nThe Car has been stored ";
    getch();
   }

void display_all()
{
    system("cls");
    cout<<"\n\n\n\tDISPLAY ALL RECORDS !!! \n\n";
	fp.open("customer.dat",ios::in);
    while(fp.read((char*)&pr,sizeof(product)))
	{
	 pr.show_product();
	 cout<<"\n\n====================================\n";
	 getch();
	 }
    fp.close();
    getch();
}


void display_sp(int n)
{
    int flag=0;
    fp.open("customer.dat",ios::in);
    while(fp.read((char*)&pr,sizeof(product)))
	{
	 if(pr.retpno()==n)
		{
		 system("cls");
		 pr.show_product();
		 flag=1;
		}
	}
    fp.close();
if(flag==0)
 cout<<"\n\nrecord not exist";
    getch();
}

void modify_product()
{
    int no,found=0;
   system("cls");
    cout<<"\n\n\tTo Modify ";
    cout<<"\n\n\tPlease Enter The Car No.";
    cin>>no;
    fp.open("customer.dat",ios::in|ios::out);
    while(fp.read((char*)&pr,sizeof(product)) && found==0)
	   {
	    if(pr.retpno()==no)
		   {
		    pr.show_product();
		    cout<<"\nPlease Enter The New Details For The Car"<<endl;
		    pr.create_product();
		    int pos=-1*sizeof(pr);
		    fp.seekp(pos,ios::cur);
		    fp.write((char*)&pr,sizeof(product));
		    cout<<"\n\n\t Record Updated";
		    found=1;
		   }
	     }
    fp.close();
    if(found==0)
    cout<<"\n\n Record Not Found ";
    getch();
}

void delete_product()
   {
    int no;
    system("cls");
    cout<<"\n\n\n\tDelete Record";
    cout<<"\n\nPlease Enter The CarNo. od the Car you wish to Remove";
    cin>>no;
    fp.open("customer.dat",ios::in|ios::out);
    fstream fp2;
    fp2.open("Temp.dat",ios::out);
    fp.seekg(0,ios::beg);
    while(fp.read((char*)&pr,sizeof(product)))
	{
	 if(pr.retpno()!=no)
		{
		 fp2.write((char*)&pr,sizeof(product));
		 }
	 }
    fp2.close();
    fp.close();
    remove("customer.dat");
    rename("Temp.dat","customer.dat");
    cout<<"\n\n\tRecord Deleted ..";
    getch();
    }

    void menu()
    {
     system("cls");
     fp.open("customer.dat",ios::in);
     if(!fp)
     {
       cout<<"ERROR!!! FILE COULD NOT BE OPEN\n\n\n Go To Admin Menu to create File";
       cout<<"\n\n\n Program is closing ....";
       getch();
       exit(0);
     }

     cout<<"\n\n\t\tCAR MENU\n\n";
	  cout<<"      ====================================================\n";
	  cout<<"      P.NO.\t\tNAME\t\tPRICE\n";
	  cout<<"      ====================================================\n";

      while(fp.read((char*)&pr,sizeof(product)))
	 {
	   cout<<"      "<<pr.retpno()<<"\t\t"<<pr.retname()<<"\t\t"<<pr.retprice()<<endl;
	}
     fp.close();
}


   void place_order()
   {
    int  order_arr[50],quan[50],c=0;
    float amt,damt,total=0;
    char ch='Y';
    menu();
    cout<<"\n          ============================";
    cout<<"\n              PLACE YOUR ORDER";
    cout<<"\n          ============================\n";
    do{
	 cout<<"\n\nEnter The Car No. of the car : ";
	 cin>>order_arr[c];
	 cout<<"\nThe no. of days you wish to take it for rent : ";
	 cin>>quan[c];
	 c++;
	 cout<<"\nDo You Want To Order Another Product ? (y/n)";
	 cin>>ch;
    }while(ch=='y' ||ch=='Y');
    cout<<"\n\nThank You For Placing The Order";getch();system("cls");
      cout<<"\n\n********************************INVOICE************************\n";
      cout<<"\nPr No.\tPr Name  \tQuantity  \tPrice  \tAmount \tAmount after discount\n";
      for(int x=0;x<=c;x++)
	{
		 fp.open("customer.dat",ios::in);
		 fp.read((char*)&pr,sizeof(product));
		  while(!fp.eof())
			{
			if(pr.retpno()==order_arr[x])
				{
				 amt=pr.retprice()*quan[x];
				 damt=amt-(amt*pr.retdis()/100);
				 cout<<"\n"<<order_arr[x]<<"\t"<<pr.retname()<<"  \t"<<quan[x]<<"  \t\t"<<pr.retprice()<<"  \t"<<amt<<"  \t\t"<<damt;
				 total+=damt;
				}
			fp.read((char*)&pr,sizeof(product));
			}

		 fp.close();
	 }
       cout<<"\n\n\t\t\t\t\tTOTAL = "<<total;
    getch();
    }

void admin_menu()
{
 system("cls");
  char ch2;
  cout<<"\n\n\n\tADMIN MENU";
  cout<<"\n\n\t1.CREATE CAR";
  cout<<"\n\n\t2.DISPLAY ALL CARS";
  cout<<"\n\n\t3.QUERY ";
  cout<<"\n\n\t4.MODIFY CAR";
  cout<<"\n\n\t5.DELETE CAR";
  cout<<"\n\n\t6.VIEW CAR MENU";
  cout<<"\n\n\t7.BACK TO MAIN MENU";
  cout<<"\n\n\tPlease Enter Your Choice (1-7) ";
  ch2=getche();
  switch(ch2)
  {
    case '1': system("cls");
	      write_product();
	      break;
    case '2': display_all();break;
    case '3':
	       int num;
	       system("cls");
	       cout<<"\n\n\tPlease Enter The Product No. ";
	       cin>>num;
	       display_sp(num);
	       break;
      case '4': modify_product();break;
      case '5': delete_product();break;
      case '6': menu();
		getch();
      case '7': break;
      default:cout<<"\a";admin_menu();
   }
}

int main()
{
  char ch;
  
  do
    {
	system("cls");
	  cout<<"\n\n\n\tMAIN MENU";
	  cout<<"\n\n\t01. CUSTOMER";
	  cout<<"\n\n\t02. ADMINISTRATOR";
	  cout<<"\n\n\t03. EXIT";
	  cout<<"\n\n\tPlease Select Your Option (1-3) ";
	  ch=getche();
	  switch(ch)
	  {
		 case '1': system("cls");
			   place_order();
			   getch();
			   break;
		  case '2': admin_menu();
			    break;
		  case '3':exit(0);
		  default :cout<<"\a";
	}
    }while(ch!='3');
}

