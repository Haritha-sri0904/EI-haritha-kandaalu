#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <stdexcept>

class Assignment {
public:
    std::string details;
    Assignment(const std::string &details) : details(details) {}
};

class Student {
public:
    std::string id;
    std::vector<Assignment> submissions;

    Student() = default; // Default constructor

    Student(const std::string &id) : id(id) {}
    
    void submitAssignment(const Assignment &assignment) {
        submissions.push_back(assignment);
    }
};

class Classroom {
public:
    std::string name;
    std::unordered_map<std::string, Student> students;
    std::vector<Assignment> assignments;

    Classroom() = default; // Default constructor

    Classroom(const std::string &name) : name(name) {}
    
    void addStudent(const Student &student) {
        students[student.id] = student;
    }

    void scheduleAssignment(const Assignment &assignment) {
        assignments.push_back(assignment);
    }
};

class VirtualClassroomManager {
public:
    std::unordered_map<std::string, Classroom> classrooms;

    void addClassroom(const std::string &name) {
        classrooms[name] = Classroom(name);
        std::cout << "Classroom " << name << " has been created." << std::endl;
    }

    void addStudent(const std::string &studentId, const std::string &className) {
        if (classrooms.find(className) != classrooms.end()) {
            classrooms[className].addStudent(Student(studentId));
            std::cout << "Student " << studentId << " has been enrolled in " << className << "." << std::endl;
        } else {
            std::cout << "Classroom " << className << " does not exist." << std::endl;
        }
    }

    void scheduleAssignment(const std::string &className, const std::string &assignmentDetails) {
        if (classrooms.find(className) != classrooms.end()) {
            classrooms[className].scheduleAssignment(Assignment(assignmentDetails));
            std::cout << "Assignment for " << className << " has been scheduled." << std::endl;
        } else {
            std::cout << "Classroom " << className << " does not exist." << std::endl;
        }
    }

    void submitAssignment(const std::string &studentId, const std::string &className, const std::string &assignmentDetails) {
        if (classrooms.find(className) != classrooms.end()) {
            if (classrooms[className].students.find(studentId) != classrooms[className].students.end()) {
                classrooms[className].students[studentId].submitAssignment(Assignment(assignmentDetails));
                std::cout << "Assignment submitted by Student " << studentId << " in " << className << "." << std::endl;
            } else {
                std::cout << "Student " << studentId << " is not enrolled in " << className << "." << std::endl;
            }
        } else {
            std::cout << "Classroom " << className << " does not exist." << std::endl;
        }
    }
};

int main() {
    VirtualClassroomManager manager;
    std::string input;

    while (true) {
        std::getline(std::cin, input);
        std::istringstream iss(input);
        std::string command;
        iss >> command;

        if (command == "add_classroom") {
            std::string className;
            iss >> className;
            manager.addClassroom(className);
        } else if (command == "add_student") {
            std::string studentId, className;
            iss >> studentId >> className;
            manager.addStudent(studentId, className);
        } else if (command == "schedule_assignment") {
            std::string className, assignmentDetails;
            iss >> className;
            std::getline(iss, assignmentDetails);
            manager.scheduleAssignment(className, assignmentDetails);
        } else if (command == "submit_assignment") {
            std::string studentId, className, assignmentDetails;
            iss >> studentId >> className;
            std::getline(iss, assignmentDetails);
            manager.submitAssignment(studentId, className, assignmentDetails);
        } else {
            std::cout << "Invalid command." << std::endl;
        }
    }

    return 0;
}
