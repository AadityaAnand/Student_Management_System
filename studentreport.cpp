#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;
class student
{
    int rollno;
    char name[50];
    int eng_marks, math_marks, science_marks, language2_marks, cs_marks;
    double average;
    char grade;

    public:
    void getdata();
    void showdata () const;
    void calculate();
    int retrollno() const;
};
void student::calculate()

{
    average = (eng_marks+math_marks+science_marks+language2_marks+cs_marks)/5.0;
    if(average>=90){
        grade='A';
    }
    else if(average>=80){
        grade='B';
    }
    else if(average>=60){
        grade = 'C';
    }
    else if (average>=50)
    {
        grade = 'D';
    }
    else
    {
        grade='Fail';
    }

}
void student::getdata()
{
    cout<<"\nEnter the roll number:";
    cin>>rollno;
    cout<<"\n Enter the name of the student:";
    cin.ignore();
    cin.getline(name,50);
    cout<<"\nEnter marks in English out of 100";
    cin>>eng_marks;
    cout<<"\nEnter marks in Math out of 100";
    cin>>math_marks;
    cout<<"\nEnter marks in Science out of 100";
    cin>>science_marks;
    cout<<"\nEnter marks in Second Language out of 100";
    cin>>language2_marks;
    cout<<"\nEnter marks in Computer Science out of 100";
    cin>>cs_marks;
    calculate();
}
void student::showdata() const
{
    cout<<"\nRoll number: "<<rollno;
    cout<<"\nName: "<<name;
    cout<<"\nEnglish: "<<eng_marks;
    cout<<"\nMath: "<<math_marks;
    cout<<"\nScience: "<<science_marks;
    cout<<"\nSecond Langauge: "<<language2_marks;
    cout<<"\nComputer Science: "<<cs_marks;
    cout<<"\nAverage Marks: "<<average;
    cout<<"\nGrade of student is: "<<grade;
}
int student::retrollno() const
{
    return rollno;
}

void create_student()
{
    student stud;
    ofstream oFile;
    oFile.open("student.dat",ios::binary|ios::app);
    stud.getdata();
    oFile.write(reinterpret_cast<char*> (&stud), sizeof(student));
    oFile.close();
    cout<<"\nStudent record has been created";
    cin.ignore();
    cin.get();
}

void display_all()
{
    student stud;
    ifstream inFile;
    inFile.open("student.dat", ios::binary);
    if (!inFile)
    {
        cout<<"File could not be opened. Press any key to exit";
        cin.ignore();
        cin.get();
        return;
    }
    cout<<"\n\t All Records";
    while (inFile.read(reinterpret_cast<char*> (&stud), sizeof(student)))
    {
        stud.showdata();
    }
    inFile.close();
    cin.ignore();
    cin.get();
}

void display_sp(int n)
{
    student stud;
    ifstream iFile;
    iFile.open("student.dat", ios::binary);
    if(!iFile)
    {
        cout<<"File can not be openened. Press any key to exit.";
        cin.ignore();
        cin.get();
        return;
    }
    bool flag=false;
    while (iFile.read(reinterpret_cast<char*> (&stud), sizeof(student)))
    {
        if(stud.retrollno()==n)
        {
            stud.showdata();
            flag=true;
        }
    }
    iFile.close();
    if(flag==false){
        cout<<"\n Record does not exist";
    }
    cin.ignore();
    cin.get();
}

void change_student(int n)
{
    bool found=false;
    student stud;
    fstream f1;
    f1.open("student.dat", ios::binary|ios::in|ios::out);
    if (!f1)
    {
        cout<<"File could not be opened. Press any key to exit.";
        cin.ignore();
        cin.get();
        return;        
    }
    while (!f1.eof() && found==false)
    {
        f1.read(reinterpret_cast<char*> (&stud), sizeof(student));
        if (stud.retrollno()==n)
        {
            stud.showdata();
            cout<<"\n Enter new student details: "<<endl;
            stud.getdata();
                int pos=(-1)*static_cast<int>(sizeof(stud));
                f1.seekp(pos,ios::cur);
                f1.write(reinterpret_cast<char*> (&stud), sizeof(student));
                cout<<"\n Record Updated";
                found=true;
        }
    }
    f1.close();
    if (found==false)
    {
        cout<<"\n Record not found";
    }
    cin.ignore();        
    cin.get();
}

void delete_student(int n)
{
    student stud;
    ifstream iFile;
    iFile.open("student.dat",ios::binary);
    if(!iFile)
    {
        cout<<"File could not be opened... Press any Key to exit...";
        cin.ignore();
        cin.get();
        return;
    }
    ofstream oFile;
    oFile.open("Temp.dat",ios::out);
    iFile.seekg(0,ios::beg);
    while(iFile.read(reinterpret_cast<char *> (&stud), sizeof(student)))
    {   
        if(stud.retrollno()!=n)
        {
            oFile.write(reinterpret_cast<char *> (&stud), sizeof(student));
        }
    }
    oFile.close();
    iFile.close();
    remove("student.dat");
    rename("Temp.dat","student.dat");
    cout<<"\n Record Deleted.";
    cin.ignore();
    cin.get();
}


int main()

{
    char ch;
    cout<<setprecision(2);
    do{
        char ch;
        int num;
        system("cls");
        cout<<"\n\t MENU";
        cout<<"\n1. Create Student Record";
        cout<<"\n2. Search Student Record";
        cout<<"\n3. Display All Studets Record";
        cout<<"\n4. Delete Student Record";
        cout<<"\n5. Modify Student Record";
        cout<<"\n6. Exit";
        cout<<"\n Please enter your choice: ";
        cin>>ch;
        system("cls");
        
        switch (ch)
        {
            case '1': create_student(); break;
            case '2': cout<<"\n Enter roll number";
            cin>>num;
            display_sp(num); 
            break;
            case '3': display_all(); 
            break;
            case '4': cout<<"\n Enter the roll number";
            cin>>num;
            delete_student(num);
            break;
            case '5': cout<<"\n Enter the roll number";
            cin>>num;
            change_student(num);
            break;
            case '6': cout<<"Exiting. Thank you!";
            exit(0);
        }
    } while(ch!=6);
}

