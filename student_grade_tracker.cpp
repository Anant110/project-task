#include<bits/stdtr1c++.h>

using namespace std;

struct Student {
    string name;
    int id;
    vector<double> assignments;
    vector<double> exams;
    double overallGrade;
};

double calculateGrade(const vector<double>& assignments, const vector<double>& exams) {
    double assignmentAvg =accumulate(assignments.begin(),assignments.end(),0.0)/assignments.size();
    double examAvg =accumulate(exams.begin(),exams.end(),0.0)/exams.size();
    return 0.4*assignmentAvg+0.6*examAvg; // Weighted average: 40% assignments, 60% exams
}


void Studentinput(Student& student) {
    cout<<"Enter the name of student: ";
    cin>>student.name;
    cout<<"Enter the ID of student: ";
    cin>>student.id;
    
    int numAssignments,numExams;
    cout<<"Enter the total number of assignments: ";
    cin>>numAssignments;
    student.assignments.resize(numAssignments);
    cout << "Enter the assignment grades: ";
    for (double& grade:student.assignments) {
        cin>>grade;
    }
    
    cout<<"Enter the total number of exams: ";
    cin>>numExams;
    student.exams.resize(numExams);
    cout<<"Enter the exam grades: ";
    for(double& grade:student.exams) {
       cin >> grade;
    }
    
    student.overallGrade = calculateGrade(student.assignments, student.exams);
}

void StudentDisplay(const Student& student) {
    cout<<"Enter Student Name: "<<student.name<<"\n";
    cout<<"Enter Student ID: "<<student.id<<"\n";
    cout<<"Enter Overall Grade: "<<student.overallGrade<<"\n";
}

void DisplayClass(const vector<Student>& students) {
    if(students.empty()) return;
    
    double totalGrade = 0.0;
    for(const Student& student : students) {
        totalGrade+=student.overallGrade;
    }
    double classAverage=totalGrade/students.size();
    cout<<"Enter Class Average: "<<classAverage<<"\n";
    
    vector<double> grades;
    for (const Student& student:students) {
        grades.push_back(student.overallGrade);
    }
    sort(grades.begin(), grades.end());
    
    double medianGrade=grades.size()%2==0?
        (grades[grades.size()/2-1]+grades[grades.size()/2])/2:
        grades[grades.size()/2];
    cout<<"Enter Median Grade: "<<medianGrade<<"\n";
    
    double maxGrade=grades.back();
    double minGrade=grades.front();
    cout<<"Enter Highest Grade: "<<maxGrade<<"\n";
    cout<<"Enter Lowest Grade: "<<minGrade<<"\n";
}

void DisplayTopstudents(const vector<Student>& students) {
    vector<Student> sortedStudents=students;
    sort(sortedStudents.begin(),sortedStudents.end(),[](const Student& a,const Student& b) {
        return a.overallGrade>b.overallGrade;
    });
    
    cout <<"Top 3 Students:\n";
    for (int i=0; i<min(3,(int)(sortedStudents.size()));++i) {
        StudentDisplay(sortedStudents[i]);
    }
}

int main() {
    vector<Student> students;
    int numStudents;
    
    cout<<"Enter number of students: ";
    cin>>numStudents;
    
    students.resize(numStudents);
    for (Student& student:students) {
        Studentinput(student);
    }
    
    cout<<"\nClass Statistics:\n";
    DisplayClass(students);
 
   cout<<"\nClass Toppers:\n";
    DisplayTopstudents(students);
    return 0;
}
