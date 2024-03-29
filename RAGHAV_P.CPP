#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<process.h>
#include<graphics.h>
#include<dos.h>
void prn()
{  int gdriver = DETECT, gmode;
   initgraph(&gdriver,&gmode,"C:\\Turboc3\\BGI");
   setcolor(3);
   settextstyle(4,0,8);
   outtextxy(150,23*5,"WELCOME");
   delay(5000);
}
 void prn1()
{  int gdriver = DETECT, gmode;
   initgraph(&gdriver,&gmode,"C:\\Turboc3\\BGI");
   setcolor(6);
   settextstyle(3,0,4);
   outtextxy(0,40*3,"PROGRAM On Stream Allocation");
   setcolor(7);
   settextstyle(4,0,4);
   outtextxy(140,80*3, "Made By - Raghav Agarwal");
   setcolor(7);
   delay(4000);
   closegraph();
}
void prn2()
{  int gdriver = DETECT, gmode;
   initgraph(&gdriver,&gmode,"C:\\Turboc3\\BGI");
   setcolor(6);
   settextstyle(4,0,4);
   outtextxy(80,35*5,"Thank You For Using This Program");
   delay(4000);
   closegraph();
   exit(0);
}


int ctoi(char c){
    return c - '0';
}

struct marks_criteria {
    int sc_min,com_min,arts_min, seat_sc, seat_com, seat_arts;
} crit;

struct administrator {
    char user_name[10];
    char password[10];
} admin;
enum Stream {
    NOT_ALLOTTED = -1,
    NIL,
    SCIENCE,
    COMMERCE,
    ARTS
};

char stream_files[4][20] = {"","elig_sc","eligcom","eligart"};
char stream_names[4][20] = {"NIL","SCIENCE","COMMERCE","ARTS"};
char stream_sel_files[4][20] = {"", "sell_sc","sellcom","sellarts"};

class student {
private:
    char name[20];
    int regno, m_eng, m_math, m_sc, m_sst, m_lang;
    Stream pref_code, stream;
    void input_new_student(fstream& file);
public:
    void new_file();
    void input_data();
    void allot_stream();
    int get_stream();
    void display();
    float get_per() { return((m_eng+m_math+m_sc+m_sst+m_lang)/5.0f); }
};

void welcome();
void menu();
int verify_password();
void assign_user();
void input_criteria();
void read_criteria();
void read_student();
void create_eligible_sc();
void create_eligible_com();
void create_eligible_arts();
char * stream_name(int strm);
void select_list( char *in_file, char *out_file);
void thanks();
void read_student_file(fstream&);
student s;

void main()  {
    clrscr();
    prn();
    clrscr();
    prn1();
    fstream fin, fout;
    fstream fsc, fcom, farts;

    char ch;
    while(1) {
	clrscr();
	cout<<"\n\t====================== MAIN MENU =======================\n";
	cout<<"\n\n\t[1] CREATE / MODIFY ADMISSION CRITERIA(Administrator only)";
	cout<<"\n\n\t[2] ENTER STUDENT'S DATA ";
	cout<<"\n\n\t[3] ALLOTMENT OF STREAM";
	cout<<"\n\n\t[4] DISPLAY CRITERIA FOR SELECTION";
	cout<<"\n\n\t[5] DISPLAY ALLOTMENT OF STUDENT'S STREAM";
	cout<<"\n\n\t[6] DISPLAY ALL STUDENT'S REGISTERED";
	cout<<"\n\n\t[7] CREATE / DISPLAY MERIT LIST";
	cout<<"\n\n\t[8] QUIT";
	cout<<"\n\t=============================================================\n";
	cout<<"\n\n\t\tEnter your choice : ";
	char opt;
	cin>>opt;
	clrscr();
	switch(opt) {
	    case '1':{
		int p;
		assign_user();
		p=verify_password();
		if(p==0) {
		    input_criteria();
		} else {
		    cout<<"\n\tYou Not a Valid User.";
		    cout<<"\n\tYou Don't have the Authority to Modify/Create Criteria\n\n";
		}
	    }  break;
	    case '2':{
		char option;
		cout<<"\nWhat do u want --\n\n\n\n\n\t"
		    <<"Create a new student information file or Append to the existing file?\n\n\t"
		    <<"(press 1 for new creation and 2 for appending): ";
		    cin>>option;
		    clrscr();
		    if(option=='1') {
		    s.new_file();
		} else {
		    s.input_data();
		}
	    }break;
	    case '3':
		fin.open("student" ,ios::in|ios::out);
		fsc.open(stream_files[SCIENCE],ios::out);
		fcom.open(stream_files[COMMERCE],ios::out);
		farts.open(stream_files[ARTS],ios::out);
		while(fin.read((char*)& s,sizeof(s))) {
		    s.allot_stream();
		    s.get_stream();
		    if(s.get_stream()==NOT_ALLOTTED)
			cout<<"\nApplication Rejected. Not Eligible\n";
		    if(s.get_stream()==SCIENCE)
			fsc.write((char*)& s,sizeof(s));
		    if(s.get_stream()==COMMERCE)
			fcom.write((char*)& s,sizeof(s));
		    if(s.get_stream()==ARTS)
			farts.write((char*)& s,sizeof(s));
		}

		fin.close();
		fsc.close();
		fcom.close();
		farts.close();

		cout<<"\n*******************************************";
		cout<<"\n\n\tSTREAM ALLOCATION DONE.";
		cout<<"\n*******************************************";
		break;

	    case '4':
		read_criteria();
		cout<<"Stream Allocation Criteria:\n";
		cout<<"\n Stream     Min Percentage Required";
		cout<<"\n Sc      :  "<<crit.sc_min;
		cout<<"\n Com     :  "<<crit.com_min;
		cout<<"\n Arts    :  "<<crit.arts_min;
		break;
	    case '5':
		cout << "\n Enter 1 for Sc, \n 2 for Com, \n 3 for Arts : ";
		cin>>ch;
		char ans;
		fstream fout;
		fout.open(stream_files[ctoi(ch)],ios::in);
		read_student_file(fout);
		fout.close();
		break;
	    case '6':
		read_student();
		break;
	    case '7': {
		char c;
		char k=1;
		cout<<"\n****************************************";
		cout<<"\n****************************************";
		cout<<"\n M E R I T    L I S T";
		cout<<"\n ==================";
		cout<<"\n\tPress 1 for MERIT LIST SCIENCE ";
		cout<<"\n\tPress 2 for MERIT LIST COMMERCE ";
		cout<<"\n\tPress 3 for MERIT LIST ARTS \t";
		cout<<"\n****************************************";
		cout<<"\n****************************************";
		cout<<"\n";
		cin>>k;
		if(k>='1' && k<='3') {
		    select_list(stream_files[ctoi(k)],stream_sel_files[ctoi(k)]);
		    fin.open(stream_sel_files[ctoi(k)],ios::in);

			while(fin.read((char*)& s,sizeof(s))) {
			s.display();

			c = getch();
			if(c=='n') break;
		    }
		}

		fin.close();
		break;
	    }
	    case '8':
			 prn2();
	    default:
		cout << "NO SUCH OPTION\n";
	} //END OF SWITCH
	cout << "\n\n\nPress any key to continue\n";
	getch();
    }//END OF WHILE LOOP
}

void assign_user() {
    strcpy(admin.user_name, "raghav");
    strcpy(admin.password, "raghav");
}

int verify_password() {
    char u_name[10];
    char u_pwd[10],temp[2];
    int x=1;
    cout<<"\n\n Enter user name : ";
    cin>>u_name;
    cout<<"\n\n Enter Password : ";
    cin>>u_pwd;
    clrscr();
    x=strcmp(admin.user_name,u_name);
    if (x==0) {
	x=strcmp(admin.password,u_pwd);
    }

    cin.getline(temp,2);
    return(x);
}

void student::allot_stream() {
    float per=get_per();
    read_criteria();
    switch(pref_code) {
	case SCIENCE:
	    if(per>=crit.sc_min) stream=pref_code;
	    else stream=NOT_ALLOTTED;
	    break;
	case COMMERCE:
	    if(per>=crit.com_min) stream=pref_code;
	    else stream=NOT_ALLOTTED;
	    break;
	case ARTS:
	    if(per>=crit.arts_min) stream=pref_code;
	    else stream=NOT_ALLOTTED;
	    break;
    }
}

int student::get_stream() {
    return(stream);
}

void input_criteria() {
    fstream fout;
    fout.open("criteria" ,ios::out);
    cout<<"\nEnter the required marks for SCIENCE stream(in percentage): ";
    cin>>crit.sc_min;
    cout<<"\nEnter No. of Seats for SCIENCE stream: ";
    cin>>crit.seat_sc;
    cout<<"\nEnter the required marks for COMMERCE stream(in percentage): ";
    cin>>crit.com_min;
    cout<<"\nEnter No. of Seats for COMMERCE stream: ";
    cin>>crit.seat_com;
    cout<<"\nEnter the required marks for ARTS stream(in percentage): ";
    cin>>crit.arts_min;
    cout<<"\nEnter No. of Seats for ARTS stream: ";
    cin>>crit.seat_arts;
    fout.write((char*)& crit,sizeof(crit)); fout.close();
}

void read_criteria() {
    fstream fin;
    fin.open("criteria" ,ios::in);
    fin.read((char*)& crit,sizeof(crit));
    fin.close();
}

void student::input_data() {
    fstream fin;
    fin.open("student",ios::app|ios::out);
    input_new_student(fin);
    fin.close();
}
void student::input_new_student(fstream& file){
   char t[2], ans;
   while(1) {
	cout<<"\nEnter the name of the student : ";
	gets(name);
	cout<<"\nEnter the roll of the student : ";
	cin>>regno;
	cout<<"\nEnter marks in English : ";
	cin>>m_eng;
	cout<<"\nEnter marks in Maths : ";
	cin>>m_math;
	cout<<"\nEnter marks in Science : ";
	cin>>m_sc;
	cout<<"\nEnter marks in Sst : ";
	cin>>m_sst;
	cout<<"\nEnter marks in Language : ";
	cin>>m_lang;
	cout<<"==================STREAM PREFERED?================ \n";
	cout<<"\t"<<"[1] for SCIENCE\n";
	cout<<"\t"<<"[2] for COMMERCE\n";
	cout<<"\t"<<"[3] for ARTS ";
	cout<<"\n================================================= \n\tENTER PREFERENCE CODE : ";
	cin>>(int)pref_code;
	cout << "RREFERRED STREAM  is " << stream_names[pref_code];
	stream=NOT_ALLOTTED;
	file.write((char*)&s,sizeof(s));
	cin.getline(t,2);
	cout<<"\n\tEnter More Student ? (y/n)";
	cin>>ans;
	if (ans=='n') break;
    }
}
void student::new_file() {
    fstream fin;
    fin.open("student",ios::out);
    input_new_student(fin);
    fin.close();
}

void student::display() {
    cout <<"\n============================================\n";
    cout <<"\n\tNAME	            : "<<name;
    cout <<"\n\tREGISTRATION NO.    : "<<regno;
    cout <<"\n\tPERCENTAGE OF MARKS : "<<get_per()<<'%';
    cout <<"\n\tSTREAM APPLIED FOR  : "<<stream_name(pref_code);
    cout <<"\n=============================================\n";
}

void read_student(){
    fstream fin;
    fin.open("student",ios::in|ios::binary);
    while(fin.read((char*)&s,sizeof(s))){
	s.display();
	cout << "\n\tPress any no. to continue ";
	getch();
	cout << "\n";
    }
    fin.close();
}

void read_student_file(fstream& file){
    while(file.read((char*)& s,sizeof(s))) {
	s.display();
    }
}

char * stream_name(int strm) {
	return stream_names[strm];
}

void select_list( char *in_file, char *out_file) {
	fstream sel, fin;
	int n=0, i,j;
	student sl[100], t;

	sel.open(out_file, ios::out);
	fin.open(in_file,ios::in);

	while(fin.read((char*)& sl[n],sizeof(s))) {
		n++;
	}

	cout<<"\nNo of Eligible Students = "<< n <<endl;
	for(i = 0;i<n;i++){
		for(j = i+1;j <=n;j++){
			if(sl[i].get_per()<sl[j].get_per()){
				t=sl[j];
				sl[j]=sl[i];
				sl[i]=t;
			}
		}
	}

	for(i = 0; i<n; i++){
		sel.write((char*)&sl[i],sizeof(s));
	}

	sel.close();
	fin.close();
}

