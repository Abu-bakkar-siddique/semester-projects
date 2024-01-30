#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include<map>
#include <iomanip>
#include <limits>
using namespace std;
// A key value pair of courses storing indexes for each course
const map<int , string> Courses = {
    {1,"Programming With Python"}, {2,"Web Development"}, {3,"Databases with SQL"},
    {4,"Math for Computer Science"}, {5,"Introduction to Artificial Intelligence"},
    {6, "Introduction to Computer technology"}

};
struct Student
{
    string name;
    int studentID;
    string password;
    string courses;
};

// Function declarations
void RegisterStudent();
bool Login(string *name, string *password);
vector<vector<string>> ReadCSV(string filename);
void WriteCSV(string filename, Student& student);
void displayData(const vector<Student>& students);
string Enroll();
void displayProfile(const vector<string>& profileData);

int main() 
{
    int option; 
    cout<<"1-Login"<<endl<<"2-register"<<endl;
    cin >>option;
    if (option == 1)
    {
        string name, password;
        cin.ignore();
        cout << "Enter your username: ";
        getline(cin, name);
        cout << endl;
    
        cout << "Enter your password: ";
        getline(cin, password);
        cout << '\n';

        if (Login(&name, &password))
        {
            //Display user profile
                //there username and id
                //courses enrolled
                //total fee
            
            return 0;
        }
        else
            cout<<"Login Failed";

    return 0;
    }

    else if (option == 2)
    {

        RegisterStudent();
        return 0;
    }
    
    }


void RegisterStudent()
{
    fstream students;
    Student student;
    cin.ignore();

    cout << "Enter student ID : ";
    cin >> student.studentID;
    cout << endl;
    cin.ignore();

    cout << "Enter your name: ";
    getline(cin, student.name);
    cout << endl;
    cin.ignore(); // Ignore the newline character in the buffer

    cout << "Enter password : ";
    getline(cin, student.password);
    cin.ignore(); // Ignore the newline character in the buffer

    string StudentCourses = Enroll();
    student.courses = StudentCourses;

    WriteCSV("students.csv", student);
    return;

}
//tested
bool Login(string* name, string* password)
{
    vector<vector<string>> Data = ReadCSV("students.csv");

    for (int i = 0; i < Data.size(); i++)
    {
        if (Data[i][1] == *name && Data[i][2] == *password)
        {
            //call display profile here
            displayProfile(Data[i]);
            return true;
        }
        else if (Data[i][1] == *name && Data[i][2] != *password)
        {
            cout << "Incorrect password" << endl;
            return false;
        }
    }

    cout << "User not registered" << endl;
    char r;
    cout << "Do you want to register? (Y/N) : ";
    cin >> r;

    if (r == 'N' || r == 'n')
    {
        return false;
    }
    else if (r == 'Y' || r == 'y')
    {
        RegisterStudent();
        cout << "*************REGISTERED SUCCESSFULLY, LOGGED IN*************" << endl;
        return true;
    }
    else
    {
        cout << "Invalid Input";
        return false;
    }
}

//tested
vector<vector<string>> ReadCSV(string filename)
{
    ifstream data;
    data.open(filename);
    string line;

    vector<vector<string>> Data;
    while (getline(data, line))
    {
        stringstream Row(line);
        string attribute;

        Data.push_back(vector<string>());

        while (getline(Row, attribute, ','))
        {
            Data.back().push_back(attribute);
        }
    }
    data.close();
    return Data;
}

void displayTable(const vector<Student>& students)
 {
    // Display table header
    cout << setw(20) << "Name" << setw(20) << "Student ID" << setw(15) << "Password" <<endl;
    cout << setfill('-') << setw(45) << "" << setfill(' ') << endl;

    // Display table rows
    for (const auto& student : students) {
        std::cout << std::setw(20) << student.name << std::setw(10) << student.studentID << std::setw(15) << student.password << std::endl;
    }
}

//tested
void WriteCSV(string filename, Student& studentData) {
    fstream file;
    file.open(filename, ios::app);

    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    file << studentData.studentID << ",";
    file << studentData.name << ",";
    file << studentData.password << ",";
    file << studentData.courses<<endl;
    
    file.close();
}
//tested and optimized by chat gpt
string Enroll()
{
    int fee = 0;
    cout << "The available courses are" << endl;
    int numC = 0;
    string EnrolledCourses;

    // Displaying the available courses
    for (const auto& course : Courses)
    {
        cout << course.first << "-" << course.second << endl;
    }

    cout << "Press 0 to exit" << endl;

    while (numC < 6)
    {
        int courseIndx;
        cout << "Select the course index you wish to enroll (enter 0 to exit): ";

        // Validate input
        while (!(cin >> courseIndx) || (courseIndx < 0 || courseIndx > Courses.size()))
        {
            cin.clear();
            cin.ignore();
            cout << "Invalid input. Please enter a valid course index: ";
        }

        if (courseIndx == 0)
        {
            break; // Exit the loop if the user enters 0
        }
        else
        {
            auto it = Courses.find(courseIndx);
            if (it != Courses.end())
            {
                if (!EnrolledCourses.empty())
                {
                    EnrolledCourses.append("-");
                }
                EnrolledCourses.append(it->second);
                fee += 20000;
                numC += 1;
            }
        }
    }

    EnrolledCourses.append(",");
    EnrolledCourses.append("PKR ");
    EnrolledCourses.append(to_string(fee)); // Convert 'fee' to string before appending
    return EnrolledCourses;
}

//   *************Functionality left*****************
//          Delete Course, Delete Profile

void displayProfile(const vector<string>& profileData)
{

    cout<<"****************Login Successful****************"<<endl;
    cout << "-------------------------" << endl;
    cout << "|   Profile Information   |" << endl;
    cout << "-------------------------" << endl;
    cout << "Name:       " << profileData[1] << endl;
    cout << "Student ID: " << profileData[0] << endl;

    cout << "Courses Enrolled: " << endl;
    stringstream coursesStream(profileData[3]);
    string course;
    while (getline(coursesStream, course, '-'))
    {
        cout << "  - " << course << endl;
    }

    cout << "Total Fee: " << profileData[4] << endl;
    cout << "-------------------------" << endl;   
}