
//***************************************************************
//                   HEADER FILE USED IN PROJECT
//****************************************************************

#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;


//***************************************************************
//                   CLASS USED IN PROJECT
//****************************************************************

class movie
{
	int serialno;
	char name[50];
	int r1_rating, r2_rating, r3_rating, r4_rating, r5_rating;
	double ave;
	char review;
	void calculate();	//function to calculate review
public:
	void getdata();		//function to accept data from user
	void showdata() const;	//function to show data on screen
	void show_tabular() const;
	int retserialno() const;
}; //class ends here


void movie::calculate()
{
	ave=(r1_rating+r2_rating+r3_rating+r4_rating+r5_rating)/5.0;
	if(ave>=4)
	    review='E';
	else if(ave>=3)
		review='G';
	else if(ave>=2)
		review='A';
	else
		review='B';
}

void movie::getdata()
{
	cout<<"\nEnter The Serial Number of The Movie ";
	cin>>serialno;
	cout<<"\n\nEnter The Name of Movie ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nEnter The rating for movie  out of 5 by reviwer 1: ";
	cin>>r1_rating;
	cout<<"\nEnter The rating for movie  out of 5 by reviwer 2: ";
	cin>>r2_rating;
	cout<<"\nEnter The rating for movie  out of 5 by reviwer 3: ";
	cin>>r3_rating;
	cout<<"\nEnter The rating for movie  out of 5 by reviwer 4: ";
	cin>>r4_rating;
	cout<<"\nEnter The rating for movie  out of 5 by reviwer 5: ";
	cin>>r5_rating;
	calculate();
}

void movie::showdata() const
{
	cout<<"\nSerial number of movie : "<<serialno;
	cout<<"\nName of movie : "<<name;
	cout<<"\nRating by reviwer1 : "<<r1_rating;
	cout<<"\nRating by reviwer2 : "<<r2_rating;
	cout<<"\nRating by reviwer3 : "<<r3_rating;
	cout<<"\nRating by reviwer4 : "<<r4_rating;
	cout<<"\nRating by reviwer5 : "<<r5_rating;
	cout<<"\naverage rating of the movie is  :"<<ave;
	cout<<"\nReview of the movie is :"<<review;
}

void movie::show_tabular() const
{
	cout<<serialno<<setw(6)<<" "<<name<<setw(10)<<r1_rating<<setw(4)<<r2_rating<<setw(4)<<r3_rating<<setw(4)
		<<r4_rating<<setw(4)<<r5_rating<<setw(8)<<ave<<setw(6)<<review<<endl;
}

int  movie::retserialno() const
{
	return serialno;
}


//***************************************************************
//    	function declaration
//****************************************************************

void write_movie();	//write the record in binary file
void display_all();	//read all records from binary file
void display_sp(int);	//accept serial no and read record from binary file
void delete_movie(int);	//accept serial and delete selected records from binary file
void mov_result();	//display all records in tabular format from binary file
void result();		//display result menu
void intro();		//display welcome screen
void entry_menu();	//display entry menu on screen


//***************************************************************
//    	THE MAIN FUNCTION OF PROGRAM
//****************************************************************


int main()
{
	char ch;
	cout.setf(ios::fixed|ios::showpoint);
	cout<<setprecision(2); // program outputs decimal number to two decimal places
	intro();
	do
	{
		system("cls");
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t01. RECORD MENU";
		cout<<"\n\n\t02. ENTRY/EDIT MENU";
		cout<<"\n\n\t03. EXIT";
		cout<<"\n\n\tPlease Select Your Option (1-3) ";
		cin>>ch;
		switch(ch)
		{
			case '1': result();
				break;
			case '2': entry_menu();
				break;
			case '3':
				break;
			default :cout<<"\a";
		}
    }while(ch!='3');
	return 0;
}

//***************************************************************
//    	function to write in file
//****************************************************************

void write_movie()
{
	movie mv;
	ofstream outFile;
	outFile.open("movie.dat",ios::binary|ios::app);
	mv.getdata();
	outFile.write(reinterpret_cast<char *> (&mv), sizeof(movie));
	outFile.close();
    	cout<<"\n\nMOVIE REVIEW HAS BEEN RECEIVED ";
	cin.ignore();
	cin.get();
}

//***************************************************************
//    	function to read all records from file
//****************************************************************

void display_all()
{
	movie mv;
	ifstream inFile;
	inFile.open("movie.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	cout<<"\n\n\n\t\tDISPLAY ALL RATING AND REVIEWS !!!\n\n";
	while(inFile.read(reinterpret_cast<char *> (&mv), sizeof(movie)))
	{
		mv.showdata();
		cout<<"\n\n====================================\n";
	}
	inFile.close();
	cin.ignore();
	cin.get();
}

//***************************************************************
//    	function to read specific record from file
//****************************************************************

void display_sp(int n)
{
	movie mv;
	ifstream inFile;
	inFile.open("movie.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	bool flag=false;
	while(inFile.read(reinterpret_cast<char *> (&mv), sizeof(movie)))
	{
		if(mv.retserialno()==n)
		{
	  		 mv.showdata();
			 flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nmovie does not exist";
	cin.ignore();
	cin.get();
}


//***************************************************************
//    	function to delete movie of file
//****************************************************************

void delete_movie(int n)
{
	movie mv;
	ifstream inFile;
	inFile.open("movie.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	ofstream outFile;
	outFile.open("Temp.dat",ios::out);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&mv), sizeof(movie)))
	{
		if(mv.retserialno()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&mv), sizeof(movie));
		}
	}
	outFile.close();
	inFile.close();
	remove("movie.dat");
	rename("Temp.dat","movie.dat");
	cout<<"\n\n\tMovie Deleted ..";
	cin.ignore();
	cin.get();
}

//***************************************************************
//    	function to display all movie reviwes
//****************************************************************

void mov_result()
{
	movie mv;
	ifstream inFile;
	inFile.open("movie.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	cout<<"\n\n\t\tALL MOVIE RATINGS AND REVIEWS \n\n";
	cout<<"==========================================================\n";
	cout<<"Sl.No       Name        r1   r2   r3   r4   r5   AVG   Review"<<endl;
	cout<<"==========================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&mv), sizeof(movie)))
	{
		mv.show_tabular();
	}
	cin.ignore();
	cin.get();
	inFile.close();
}

//***************************************************************
//    	function to display result menu
//****************************************************************

void result()
{
	char ch;
	int slno;
	system("cls");
	cout<<"\n\n\n\tRATINGS MENU";
	cout<<"\n\n\n\t1. Final Ratings";
	cout<<"\n\n\t2. Individual movie details";
	cout<<"\n\n\t3. Back to Main Menu";
	cout<<"\n\n\n\tEnter Choice (1/2/3)? ";
	cin>>ch;
	system("cls");
	switch(ch)
	{
	case '1' :	mov_result(); break;
	case '2' :	cout<<"\n\n\tEnter Serial number of the movie: "; cin>>slno;
				display_sp(slno); break;
	case '3' :	break;
	default:	cout<<"\a";
	}
}

//***************************************************************
//    	INTRODUCTION FUNCTION
//****************************************************************

void intro()
{
	cout<<"\n\n\n\t\t  MOVIE";
	cout<<"\n\n\t\tRATINGS AND REVIEW";
	cout<<"\n\n\t\t  PROJECT";
	cout<<"\n\n\n\tMADE BY : 18121a1203\n18121A1219\n18121a1242\n18121A1233";
	cout<<"\n\tCOLLEGE:SREE VIDYANIKETHAN ENGINEERING COLLEGE";
	cin.get();
}

//***************************************************************
//    	ENTRY / EDIT MENU FUNCTION
//****************************************************************

void entry_menu()
{
	char ch;
	int num;
	system("cls");
	cout<<"\n\n\n\tENTRY MENU";
	cout<<"\n\n\t1.CREATE MOVIE RECORD";
	cout<<"\n\n\t2.DISPLAY ALL MOVIE RATINGS AND REVIEWS";
	cout<<"\n\n\t3.SEARCH MOVIENAME ";
    cout<<"\n\n\t4.DELETE MOVIE RECORD";
	cout<<"\n\n\t5.BACK TO MAIN MENU";
	cout<<"\n\n\tPlease Enter Your Choice (1-5) ";
	cin>>ch;
	system("cls");
	switch(ch)
	{
	case '1':	write_movie(); break;
	case '2':	display_all(); break;
	case '3':	cout<<"\n\n\tPlease Enter The serial number of the movie "; cin>>num;
			display_sp(num); break;
	case '4':	cout<<"\n\n\tPlease Enter The serial number of the movie "; cin>>num;
			delete_movie(num);break;
	case '5':	break;
	default:	cout<<"\a"; entry_menu();
	}
}

//***************************************************************
//    			END OF PROJECT
//***************************************************************
