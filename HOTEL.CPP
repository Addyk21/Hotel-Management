

#include<fstream.h>
	#include<constream.h>
	#include<dos.h>
	#include<stdio.h>
	#include<string.h>

	fstream file,file1;
	 class customer
	{ char name[20];
	int mobno;
	 char *add;
	 public:
	int c_rno;
	 void getdata()
	{ gotoxy(25,7);
	cout<<"Enter customer name :";
	gotoxy(47,7);
	gets(name);
	gotoxy(25,9);
	cout<<"Enter mobile number :" ;
	gotoxy(47,9);
	cin>>mobno;
	gotoxy(25,11);
	cout<<"Enter address       :";
	gotoxy(47,11);
gets(add);
	  }

	int getname(char nm[])
	{  return(strcmpi(name,nm));
	 }

	 void dispname()
	{ puts(name);
	 }

	int mno()
	{ return mobno;
	 }
};

	 class room : public customer
	{
	int rno;
	int type;
	 float charges;
	int status;
	 float amt;

	 public:
	  void gendata ();
	  void display();
	  void checkin();
	  void checkout();
	  void inquiry();
	  void report();

	}o1,rp1,a1;



	void main()
{int ch;
	  do
	  {
	clrscr();

	gotoxy (30,2);
	cout<<"##  HOTEL  SERVICE  ##";
	gotoxy (30,5);
	cout<<" -HOTEL RESERVATION-"  ;
	gotoxy (24,8);
	cout<<"THE MENU";
	gotoxy(25,10);
	cout<<"1.INQUIRY" ;
	gotoxy(25,11) ;
	cout<<"2.REPORT" ;
	gotoxy(25,12);
	cout<<"3.CHECK IN";
	gotoxy(25,13);
	cout<<"4.CHECK OUT";
	gotoxy(25,14);
	cout<<"5.ROOM STATUS";
	gotoxy(25,15);
	cout<<"6.GENERATE DATABASE";
	gotoxy(25,16);
	cout<<"7.EXIT";
	gotoxy(20,17);
	cout<<"Enter your choice - ";
	cin>>ch;

     switch(ch)
	{ case 1:o1.inquiry();
		       break;
		case 2:o1.report();
		       break;
		case 3:o1.checkin();
		       break;
		case 4:o1.checkout();
		       break;
		case 5:o1.display();
		       break;
		case 6:o1.gendata();
		       break;
		case 7:break ;
		default:gotoxy(40,17);
cout<<"Invalid choice";
	      }
	getch();
	   }while(ch!=7);
	}


	void  room::gendata()
{clrscr();
	   char choice;
	   do
	{ gotoxy(30,2);
	cout<<"-- GENERATE DATABASE --";
	gotoxy(25,8);
	cout<<"# Room no.:" ;
	gotoxy(25,10);
	cout<<"# type    : ";
	gotoxy(18,20);
	cout<<"Enter '0' for ordinary room and '1' for delux room";
	gotoxy(25,12);
	cout<<"# charges :";
	fstream file;
	file.open("room.dat",ios::app|ios::binary);

	gotoxy(40,8);
	cin>>o1.rno;
	gotoxy(40,10);
	cin>>o1.type;
	gotoxy(40,12);
	cin>>o1.charges;
	     o1.status=0;
	gotoxy(25,14);
	file.write((char*)&o1,sizeof(o1));
	file.close();
	gotoxy(25,16);

	cout<<"Want to enter more? (y/n) ";
	cin>>choice;
	clrscr();
	}while(choice=='y'||choice=='Y');
	  }



 void room:: display()
	{ file.open("room.dat",ios::in |ios::binary);
	room  r1;
	int r=5;
	clrscr();
	gotoxy(30,2);
	cout<<"-- ROOM STATUS --";
	gotoxy(5,4);
	cout<<"Room no:";
	gotoxy(25,4);
	cout<<"Type:";
	gotoxy(45,4);
	cout<<"Charges:";
	gotoxy(65,4);
	cout<<"Status:";
	while((file.read((char *) &r1,sizeof(r1))))
	{ r++;
	gotoxy(5,r);
	cout<<r1.rno ;
	     if(r1.type==0)
	{ gotoxy(25,r);
		cout<<"Ordinary";
	       }
	     else
	{ gotoxy(25,r);
		cout<<"Deluxe";
	       }
	gotoxy(45,r);
	cout<<r1.charges;
	gotoxy(65,r);
	     if(r1.status==0)
	{ gotoxy(65,r);
		cout<<"Vacant";
	       }

 else
	{ gotoxy(65,r);
		cout<<"Occupied";
	       }
	   }
	file.close();
	  }


	   void room::checkin()
{clrscr();
	int ty,flag=0;
	gotoxy(32,2);
	cout<<"-- CHECK IN --";
	gotoxy(25,5);
	cout<<"Enter room type:";
	gotoxy(18,22);
	cout<<"Enter '0' for Ordinary and '1' for Deluxe";
	gotoxy(43,5);
	cin>>ty;
	file1.open("report.dat",ios::app|ios::binary);
	file.open("room.dat",ios::in|ios::out|ios::binary);
	    long pos=file.tellg();

	while(file.read((char *)&a1,sizeof(a1)))
	{ pos=file.tellg();
	    if(a1.type==ty)
	{ if(a1.status==0)
	       {
		a1.getdata();
		gotoxy(25,13);
		cout<<"Your room no is     : "<<a1.rno;
		a1.status=1;
		file.seekp(pos-sizeof(a1),ios::beg);
		file.write((char*)&a1,sizeof(a1));
		file1.write((char*)&a1,sizeof(a1));
		flag=1;
		break;
	       }
	     }
	   }

	 if(flag==0)
	{ gotoxy(25,7);
	cout<<"No room available.";
	}

		file.close();
		file1.close();
	 }


	 void room :: checkout()
{ clrscr();
	    long pos=file.tellg();
	int rmno,days,flag=0;
	gotoxy(32,2);
	cout<<"-- CHECK OUT --";
	gotoxy(25,6);
	cout<<"Enter room number:";
	gotoxy(45,6);
	cin>>rmno;

	file.open("room.dat",ios::in|ios::out|ios::binary);
	   file1.open("report.dat",ios::in|ios::out|ios::binary);

	while(file.read((char *)&o1,sizeof(o1)))
	{ pos=file.tellg();
	      if(o1.rno==rmno)
		{ if(o1.status==1)
		{ o1.status=0;
		file.seekp(pos-sizeof(o1),ios::beg);
		file.write((char*)&o1,sizeof(o1));

			gotoxy(25,8);
	cout<<"Enter no. of days stayed: ";
			cin>>days;
		       if(o1.type==0)
			{ o1.amt=days*o1.charges;
			gotoxy(25,10);
			cout<<"Your total amount= "<<o1.amt;
			 }
		       else
			{ o1.amt=days*o1.charges;
			gotoxy(25,10);
	cout<<"Your total amount= "<<o1.amt;
			 }
		gotoxy(25,12);
	cout<<"Checkout successfull.";
		       flag=1;
		       break;
		     }
		}

	    }
	   while(!file1.eof())
	{ pos=file1.tellg();
	       file1.read((char*)&a1,sizeof(a1));
		{ if(a1.rno==o1.rno)
		{ if(a1.mno()==o1.mno())
		{ a1.amt=o1.amt;
		      file1.seekp(pos);
		      file1.write((char*)&a1,sizeof(a1));
		    }
		   }
		}
	    }

	   if(flag==0)
	{ gotoxy(25,8);
	cout<<"Invalid room";
	    }
	file.close();
	   file1.close();
	  }



void room  :: inquiry()
{ clrscr();
	    char nm[20];
	int flag=0;
	    room c1;
	gotoxy(32,2);
	cout<<"-- INQUIRY --";
	gotoxy(25,6);
	cout<<"Enter your name: ";
	    gets(nm);
	file.open("room.dat",ios::in|ios::binary);
	while(file.read((char *)&c1,sizeof(c1)))
	      {
	       if(c1.getname(nm)==0)
		  {
		gotoxy(25,8);
	cout<<"Your room no.is:"<<c1.rno;
		    flag=1;
		    break;
		  }
	      }
	    if(flag==0)
	{ gotoxy(25,8);
		cout<<"No room booked by this name";
	      }
	file.close();
	  }

	  void room :: report()
	{  clrscr();
		int r=5;
		file1.open("report.dat",ios::in|ios::binary);
		gotoxy(30,2);
		cout<<"-- REPORT --";
		gotoxy(5,4);
		cout<<"Room no:";
		gotoxy(25,4);
		cout<<"Name:";
		gotoxy(45,4);
		cout<<"Charged:";

	while((file1.read((char *) &rp1,sizeof(rp1))))
	{ r++;
		gotoxy(5,r);
		cout<<rp1.rno ;
		gotoxy(25,r);
		 rp1.dispname();
		gotoxy(45,r);
		{ if(rp1.amt==0)
		cout<<"Not yet checked out";
		   else
		cout<<rp1.amt;
		 }
	       }
	file1.close();
  }
