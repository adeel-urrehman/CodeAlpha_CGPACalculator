#include <iostream>
#include <vector>
#include <cctype>
#include <limits>
#include <stdexcept>
using namespace std;

class Course {
private:
    string name;
    double gradePoint;
    double creditHours;

public:
    bool isValidName(const string& s) {
        if (s.empty()) return false;

        bool hasLetter = false;
        for (size_t i = 0; i < s.length(); i++) {
            if (isalpha(s[i])) {
                hasLetter = true;
                break;
            }
        }

        return hasLetter;
    }

    void input() {
        do {
            cout << "\nCourse name: ";
            getline(cin, name);
            if (!isValidName(name)) {
                cout << "Invalid name. Course name must contain at least one letter.\n";
            }
        } while (!isValidName(name));

        cout << "Grade point (0.0 - 4.0): ";
        cin >> gradePoint;
        if (gradePoint < 0.0 || gradePoint > 4.0) {
            throw invalid_argument("Grade point must be between 0.0 and 4.0.");
        }

        cout << "Credit hours (1 - 6): ";
        cin >> creditHours;
        if (creditHours <= 0 || creditHours > 6) {
            throw invalid_argument("Credit hours must be between 1 and 6.");
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    double getQualityPoints() const {
        return gradePoint * creditHours;
    }

    double getCreditHours() const {
        return creditHours;
    }

    void display() const {
        cout << name << "\t\t" << gradePoint << "\t\t" << creditHours << "\n";
    }
};

class Semester {
private:
    vector<Course> courses;
    int semesterNumber;

public:
    void input(int number) {
        semesterNumber = number;

        int n;
        cout << "\nEnter number of courses for Semester " << semesterNumber << ": ";
        cin >> n;

        if (n <= 0) {
            throw invalid_argument("Number of courses must be greater than 0.");
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        courses.resize(n);
        for (int i = 0; i < n; i++) {
            courses[i].input();
        }
    }

    double getTotalQualityPoints() const {
        double total = 0;
        for (size_t i = 0; i < courses.size(); i++) {
            total += courses[i].getQualityPoints();
        }
        return total;
    }

    double getTotalCreditHours() const {
        double total = 0;
        for (size_t i = 0; i < courses.size(); i++) {
            total += courses[i].getCreditHours();
        }
        return total;
    }

    double calculateGPA() const {
        double totalCredits = getTotalCreditHours();
        if (totalCredits == 0) {
            throw runtime_error("Total credit hours cannot be zero.");
        }
        return getTotalQualityPoints() / totalCredits;
    }

    void displaySummary() const {
        cout << "\n----- Semester " << semesterNumber << " Summary -----\n";
        cout << "Course\t\tGrade Point\tCredit Hours\n";
        for (size_t i = 0; i < courses.size(); i++) {
            courses[i].display();
        }
        cout << "Semester GPA: " << calculateGPA() << endl;
    }

    int getSemesterNumber() const {
        return semesterNumber;
    }
};

class CGPACalculator {
private:
    vector<Semester> semesters;

public:
    void inputSemesters() {
        int n;
        cout << "Enter number of semesters you have covered so far: ";
        cin >> n;

        if (n <= 0) {
            throw invalid_argument("Number of semesters must be greater than 0.");
        }

        semesters.resize(n);
        for (int i = 0; i < n; i++) {
            semesters[i].input(i + 1);
        }
    }

    double calculateCGPA() const {
        double totalPoints = 0, totalCredits = 0;
        for (size_t i = 0; i < semesters.size(); i++) {
            totalPoints += semesters[i].getTotalQualityPoints();
            totalCredits += semesters[i].getTotalCreditHours();
        }

        if (totalCredits == 0) {
            throw runtime_error("Total credit hours cannot be zero.");
        }

        return totalPoints / totalCredits;
    }

    void displayFullSummary() const {
        for (size_t i = 0; i < semesters.size(); i++) {
            semesters[i].displaySummary();
        }

        cout << "\n===== Overall CGPA: " << calculateCGPA() << " =====" << endl;
    }
};

int main() {
    CGPACalculator calculator;

    try {
        calculator.inputSemesters();
        calculator.displayFullSummary();
    } catch (const exception& e) {
        cout << "\nError: " << e.what() << endl;
    }

    return 0;
}
