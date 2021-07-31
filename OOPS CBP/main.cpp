#include <bits/stdc++.h>
#include <iostream>
#include <stdlib.h>
#include <limits>
using namespace std;

class semester
{
    public:
        void courses();
        void stdetails();
        void crkteam();
        void labs();
};

class student_login
{
    protected:
        string username;
        string password;
    public:
        void readCredentials();
        friend bool verifyCreds(student_login);
};

class faculty_login
{
    protected:
        string username;
        string password;
    public:
        void readCredentials();
        friend bool verifyCreds(faculty_login);
};

class student_details: public student_login, public semester
{
    public:
        void printStuDetails();
};

class faculty_details: public faculty_login, public semester
{
    public:
        void printFacDetails();
};

class admin_login:public student_details,public faculty_details
{   
    protected:
        string adminUsername;
        string adminPassword;
        string id;
    public:
        void readCredentials();
        bool uidVerifyCreds(string, string);
        void facultyAccess();
        void studentAccess();
        friend bool verifyCreds(admin_login);

};



// ====================================================================== //
//  NORMAL FUNCTIONS                                                      //
// ====================================================================== //

// Function that prints/displays the header. To be called after clearing the console
void college_header() {
    cout<<"\t\t\t\t\t\t\t\t\tVNR VIGNANA JYOTHI INSTITUTE OF ENGINNERING AND TECHNOLOGY"<<endl;
    cout<<"\t\t\t\t\t\t\t\t\t\t\t             HYDERABAD,TELANGANA"<<endl;
    cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t   Estd.1995"<<endl;
    cout<<"\t\t\t\t\t\t\t\t\t     DEPARTMENT OF COMPUTER SCIENCE AND ENGINEERING-(CSE)"<<endl;    
    cout<<"\t\t\t\t\t\t\t\t\t\t\t   WELCOME TO THE LEARNING MANAGEMENT SYSTEM"<<endl; 
    cout << endl;
}

// Inline Functions to make the application wait for user input...
//documentation
inline void myflush ( std::istream& in ) {
  in.ignore ( std::numeric_limits<std::streamsize>::max(), '\n' );
  in.clear();
}
inline void mypause() { 
  cout<<"\nPress [Enter] to go back to main menu . . .";
  cin.get();
} 

// ====================================================================== //
//  CLASS METHODS                                                         //
// ====================================================================== //

// ---------- CLASS: student_login ---------- //

void student_login::readCredentials() {
    cout << "Enter Username: ";
    cin >> username;
    cout << "Enter Password: ";
    cin >> password;
}


// ---------- CLASS: faculty_login ---------- //

void faculty_login::readCredentials() {
    cout << "Enter Username: ";
    cin >> username;
    cout << "Enter Password: ";
    cin >> password;
}


// ----------- CLASS: semester --------//

void semester::courses() {
    cout<<"\n\n\t\t\t\t\tCOURSES REGISTERED FOR ACADEMIC YEAR(2019-2020)"<<endl;
    cout<<"\n\t\t\tSUBJECT CODE\t\t\tNAME OF SUBJECT\t\t\tNAME OF FACULTY";
    cout<<"\n\t\t\t19PC1CS01\t\t\t\tDLD\t\t\t\t\t\tC.SRI HARI";
    cout<<"\n\t\t\t19PC1CS02\t\t\t\tMFCS\t\t\t\t\tP.BHARATH KUMAR";
    cout<<"\n\t\t\t19PC1IT01\t\t\t\tOOPS\t\t\t\t\tKRITI OHRI";
    cout<<"\n\t\t\t19PC1CS03\t\t\t\tDAA\t\t\t\t\t\tA.MADHAVI";
    cout<<"\n\t\t\t19PC1CS04\t\t\t\tDBMS\t\t\t\t\tDr.C.KIRAN MAI";
    cout<<"\n\t\t\t19MN6HS02\t\t\t\tES\t\t\t\t\t\tDr.A.R.BALA VARDHANA RAO"<<endl;
}

void semester::stdetails() {
    string row;
    fstream stuData;
    stuData.open("stdetails.txt",ios::in);
    system("clear");
    college_header();
    while(getline(stuData, row))
        cout<<row<<endl;
    stuData.close();
}

void semester::labs() {
    string row;
    fstream stuData;
    stuData.open("labs.txt",ios::in);
    system("clear");
    college_header();
    while(getline(stuData, row))
        cout<<row<<endl;
    stuData.close();
}

void semester::crkteam() {
    string row;
    fstream stuData;
    stuData.open("cricket.txt",ios::in);
    system("clear");
    college_header();
    while(getline(stuData, row))
        cout<<row<<endl; 
    stuData.close();
}


// ---------- CLASS: student_details ---------- //

void student_details::printStuDetails() {
    string path, row;
    path = "students/" + username + ".txt";
    fstream stuData;
    stuData.open(path, ios::in);
    system("clear");
    college_header();
    while(getline(stuData, row))
        cout<<row<<endl;
    courses();
    stuData.close();
}


// ---------- CLASS: faculty_details ---------- //

void faculty_details::printFacDetails(){
    string path, row;
    path = "faculty/" + username + ".txt";
    fstream facData;
    facData.open(path, ios::in);
    system("clear");
    college_header();
    while(getline(facData, row))
        cout<<row<<endl;
}


// ---------- CLASS: admin_login ---------- //

void admin_login::readCredentials() {
    cout << "Enter Username: ";
    cin >> adminUsername;
    cout << "Enter Password: ";
    cin >> adminPassword;
    system("clear");
    college_header();
}

bool admin_login::uidVerifyCreds(string path, string id){
    bool userPresent = false;

    // Opening the file
    fstream File;
    File.open(path, ios::in);

    string record, uName, pWord;
    // Checking for Matches in Username
    // Here, for every iter, each row of .txt is being put as String in 'record'
    while(getline(File, record)) {
        // To split space-seperated words using getline()
        stringstream s(record);
        getline(s, uName, ' ');
        getline(s, pWord);
        
        if(uName == id) {
            userPresent = true;
            break;
        }
    }

    // Closing the file
    File.close();

    // Final Validity Check
    if(userPresent) 
        return true;
    else {
        system("clear");
        college_header();
        cout << "Invalid Username..." << endl;
        return false;
    }
}


void admin_login::studentAccess() {
    string username;
    cout << "Enter Student UserID : ";
    cin >> username;
    // If credentials mismatch
    char opt = 'Y';
    while(!uidVerifyCreds("stuLogin.txt", username)) {
        cout << endl;
        cout << "Do you wish to try again?" << endl;
        cout << "Press Y to continue or press any other key to go back to main menu" << endl;
        cout << "Enter your choice: ";
        cin >> opt;

        if(opt == 'Y') {
            system("clear");
            college_header();
            cout << "Enter Student UserID : ";
            cin >> username;
        }
        else {
            system("clear");
            break;
        }
    }     
    string path, row;
    semester sem;
    path = "students/" + username + ".txt";
    fstream stuData;
    stuData.open(path, ios::in);
    system("clear");
    college_header();
    while(getline(stuData, row))
        cout<<row<<endl;
    sem.courses();
    stuData.close();
}

void admin_login::facultyAccess() {
  string username;
    cout << "Enter Faculty UserID : ";
    cin >> username;
    // If credentials mismatch
    char opt = 'Y';
    while(!uidVerifyCreds("facLogin.txt", username)) {
      cout << endl;
      cout << "Do you wish to try again?" << endl;
      cout << "Press Y to continue or press any other key to go back to main menu" << endl;
      cout << "Enter your choice: ";
      cin >> opt;

      if(opt == 'Y') {
        system("clear");
        college_header();
        cout << "Enter Faculty UserID : ";
        cin >> username;
      }
      else {
        system("clear");
        break;
      }
    }     
    string path, row;
    path = "faculty/" + username + ".txt";
    fstream facData;
    facData.open(path, ios::in);
    system("clear");
    college_header();
    while(getline(facData, row))
        cout<<row<<endl;
    facData.close();
}

// ====================================================================== //
//  FRIEND FUNCTIONS                                                      //
// ====================================================================== //

// (Overloaded) function to verify credentials. Accepts object of type student_login. Returns bool: Whether credentials matched or not
bool verifyCreds(student_login student) {
    bool userPresent = false;
    string keyStr = student.username;

    // Opening the file stuLogin.txt
    fstream stuFile;
    stuFile.open("stuLogin.txt", ios::in);

    string record, uName, pWord;
    // Checking for Matches in username and password
    // Here, for every iter, each row of .txt is being put as String in 'record'
    while(getline(stuFile, record)) {
        // To split space-seperated words using getline()
        stringstream s(record);
        getline(s, uName, ' ');
        getline(s, pWord);
        
        if(uName == keyStr) {
            userPresent = true;
            break;
        }
    }

    // Closing the file
    stuFile.close();

    // Final Validity Check
    if(userPresent) {
        if(student.password == pWord) {
            return true;
        }
        else {
            system("clear");
            college_header();
            cout << "Invalid Password..." << endl;
            return false;
        }
    }
    else {
        system("clear");
        college_header();
        cout << "Invalid Username..." << endl;
        return false;
    }
}

// (Overloaded) function to verify credentials. Accepts object of type faculty_login. Returns bool: Whether credentials matched or not
bool verifyCreds(faculty_login faculty) {
    bool userPresent = false;
    string keyStr = faculty.username;

    // Opening the file stuLogin.txt
    fstream facFile;
    facFile.open("facLogin.txt", ios::in);

    string record, uName, pWord;

    // Checking for Matches in username and password
    // Here, for every iter, each row of .txt is being put as String in 'record'
    while(getline(facFile, record)) {
        // To split space-seperated words using getline()
        stringstream s(record);
        getline(s, uName, ' ');
        getline(s, pWord);
        
        if(uName == keyStr) {
            userPresent = true;
            break;
        }
    }

    // Closing the file
    facFile.close();

    // Final Validity Check
    if(userPresent) {
        if(faculty.password == pWord) {
            return true;
        }
        else {
            system("clear");
            college_header();
            cout << "Invalid Password..." << endl;
            return false;
        }
    }
    else {
        system("clear");
        college_header();
        cout << "Invalid Username..." << endl;
        return false;
    }
}

// // (Overloaded) function to verify credentials. Accepts object of type faculty_login. Returns bool: Whether credentials matched or not
bool verifyCreds(admin_login admin) {
    bool userPresent = false;
    string keyStr = admin.adminUsername;

    // Opening the file admin.txt
    fstream admFile;
    admFile.open("admin.txt", ios::in);

    string record, uName, pWord;

    // Checking for Matches in username and password
    // Here, for every iter, each row of .txt is being put as String in 'record'
    while(getline(admFile, record)) {
        // To split space-seperated words using getline()
        stringstream s(record);
        getline(s, uName, ' ');
        getline(s, pWord);
        
        if(uName == keyStr) {
            userPresent = true;
            break;
        }
    }

    // Closing the file
    admFile.close();

    // Final Validity Check
    if(userPresent) {
        if(admin.adminPassword == pWord) {
            return true;
        }
        else {
            system("clear");
            college_header();
            cout << "Invalid Password..." << endl;
            return false;
        }
    }
    else {
        system("clear");
        college_header();
        cout << "Invalid Username..." << endl;
        return false;
    }
}


// ====================================================================== //
//  MAIN                                                                  //
// ====================================================================== //

int main() {

    // Introduction Screen & Menu 
    int choice;
    do {
        system("clear");
        college_header();
        cout << "1. Student login\n2. Faculty login\n3. Admin Login \n4. Student Details\n5. Courses\n6. Labs\n7. CSE Cricket Team\n8. Exit Application\n" << endl;
        cout << "Enter your choice : ";
        cin >> choice;

        system("clear");
        college_header();

        // (1) STUDENT LOGIN
        if(choice == 1){
            // Login object creation
            student_details student;

            // Login
            student.readCredentials();

            // If credentials mismatch
            char opt = 'Y';
            while(!verifyCreds(student)) {
                cout << endl;
                cout << "Do you wish to login again?" << endl;
                cout << "Press Y to continue or press any other key to go back to main menu" << endl;
                cout << "Enter your choice: ";
                cin >> opt;

                if(opt == 'Y') {
                    system("clear");
                    college_header();
                    student.readCredentials();
                }
                else {
                    system("clear");
                    break;
                }
            }
            if(opt != 'Y') {
                // Going back to Main menu
                continue;
            }     
            student.printStuDetails();

        }

        // (2) FACULTY LOGIN
        if(choice==2){
            // Login object creation
            faculty_details faculty;

            // Login
            faculty.readCredentials();

            // If credentials mismatch
            char opt = 'Y';
            while(!verifyCreds(faculty)) {
                cout << endl;
                cout << "Do you wish to login again?" << endl;
                cout << "Press Y to continue or press any other key to go back to main menu" << endl;
                cout << "Enter your choice: ";
                cin >> opt;

                if(opt == 'Y') {
                    system("clear");
                    college_header();
                    faculty.readCredentials();
                }
                else {
                    system("clear");
                    break;
                }
                    
            }
            if(opt != 'Y') {
                // Going back to Main menu
                continue;
            }   
            faculty.printFacDetails();
        }

        // (3) ADMIN LOGIN
        if(choice == 3) {
            admin_login admin;
            admin.readCredentials();
            char opt = 'Y';
            while(!verifyCreds(admin)) {
                cout << endl;
                cout << "Do you wish to login again?" << endl;
                cout << "Press Y to continue or press any other key to go back to main menu" << endl;
                cout << "Enter your choice: ";
                cin >> opt;

                if(opt == 'Y') {
                    system("clear");
                    college_header();
                    admin.readCredentials();
                }
                else {
                    system("clear");
                    break;
                }
                    
            }
            int adminChoice;
            cout << "1. Student Details" << endl;
            cout << "2. Faculty Details" << endl;
            cout << "Enter you choice : " << endl;
            cin >> adminChoice;
            if(adminChoice == 1){
              admin.studentAccess();
            }
            else{
              admin.facultyAccess();
            } 
        }

        // (4) STUDENT DETAILS
        if(choice==4) {
            semester student;
            student.stdetails();
        }

        // (5) COURSES
        if(choice==5) {
            semester student;
            system("clear");
            college_header();
            student.courses();
        }

        // (6) LABS
        if(choice==6) {
            semester student;
            student.labs();
        }

        // (7) CSE CRICKET TEAM
        if(choice==7) {
            semester student;
            student.crkteam();
        }

        // (8) EXIT
        if(choice==8) {
            cout << "Thank you for checking out the application..." << endl;
            exit(0);
        }

        myflush ( std::cin );
        mypause();
    }
    while(choice != 8);
    return 0;
}