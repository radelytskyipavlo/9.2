#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

enum Specialnist { KN, ME, IN, FI, TN };
string specialnistList[] = { "KN", "ME", "IN", "FI", "TN" };

struct Student {
    string surname;
    int course;
    Specialnist spec;
    int fiz;
    int mat;
    double average;
    union {
        int prog;
        int chis_metod;
        int pedagog;
    };
};

void Create(Student* p, const int N);
void Print(Student* p, const int N);
void Sort(Student* p, const int N);
int* IndexSort(Student* p, const int N);
void PrintIndexSorted(Student* p, int* I, const int N);
bool BinarySearch(Student* p, const int N, string surname, int course, int grade);

int main() {
    int N;
    cout << "Type the number of students: "; cin >> N;
    Student* p = new Student[N];
    int menuItem;
    do {
        cout << endl << endl << endl;
        cout << "Choose an action: " << endl << endl;
        cout << " [1] - Data entry from the keyboard" << endl;
        cout << " [2] - Outputting data to the screen" << endl;
        cout << " [3] - Sorting" << endl;
        cout << " [4] - Index sorting and its output" << endl;
        cout << " [5] - Binary search for a student" << endl;
        cout << " [0] - Quit" << endl << endl;
        cout << "Enter the value: "; cin >> menuItem;
        cout << endl << endl << endl;
        switch (menuItem) {
        case 1:
            Create(p, N);
            break;
        case 2:
            Print(p, N);
            break;
        case 3:
            Sort(p, N);
            cout << "Table was sorted!";
            break;
        case 4:
            PrintIndexSorted(p, IndexSort(p, N), N);
            break;
        case 5: {
            string searchSurname;
            int searchCourse, searchGrade;
            cout << "Enter the surname to search: "; cin >> searchSurname;
            cout << "Enter the course to search: "; cin >> searchCourse;
            cout << "Enter the grade to search: "; cin >> searchGrade;
            bool found = BinarySearch(p, N, searchSurname, searchCourse, searchGrade);
            if (found)
                cout << "Student not found!" << endl;
            else
                cout << "Student found!" << endl;
            break;
        }
        case 0:
            break;
        default:
            cout << "Wrong value!" << endl;
        }
    } while (menuItem != 0);
    return 0;
}

void Create(Student* p, const int N) {
    int spec;
    for (int i = 0; i < N; i++) {
        cout << "Student # " << i + 1 << ":" << endl;
        cin.get();
        cin.sync();
        cout << "Surname: "; getline(cin, p[i].surname);
        cout << "Course: "; cin >> p[i].course;
        cout << "Grades in physics: "; cin >> p[i].fiz;
        cout << "Grades in math: "; cin >> p[i].mat;
        cout << "A specialty (0 - KN, 1 - ME, 2 - IN, 3 - FI, 4 - TN): "; cin >> spec;
        if (spec > 4) {
            cout << "Wrong value, selected 2 (IN)" << endl;
            spec = 2;
        }
        p[i].spec = (Specialnist)spec;
        switch (p[i].spec) {
        case KN:
            cout << "Grades in programming: "; cin >> p[i].prog;
            p[i].average = (p[i].mat + p[i].fiz + p[i].prog) / 3.0;
            break;
        case ME:
            cout << "Grades in pedagogy: "; cin >> p[i].pedagog;
            p[i].average = (p[i].mat + p[i].fiz + p[i].pedagog) / 3.0;
            break;
        case IN:
            cout << "Grades in num.methods : "; cin >> p[i].chis_metod;
            p[i].average = (p[i].mat + p[i].fiz + p[i].chis_metod) / 3.0;
            break;
        case FI:
        case TN:
            cout << "Grades in pedagogy: "; cin >> p[i].pedagog;
            p[i].average = (p[i].mat + p[i].fiz + p[i].pedagog) / 3.0;
            break;
        }
        cout << endl;
    }
}

void Print(Student* p, const int N) {
    cout << "==========================================================================================================="
        << endl;
    cout << "| # | Surname | Course | Specialization | Physic | Mathematics | Programming | Numerical Methods | Pedagogy |"
        << endl;
    cout << "-----------------------------------------------------------------------------------------------------------"
        << endl;
    for (int i = 0; i < N; i++) {
        cout << "|" << setw(2) << right << i + 1 << " ";
        cout << "| " << setw(8) << left << p[i].surname
            << "| " << setw(4) << right << p[i].course << "  "
            << " | " << setw(14) << left << specialnistList[p[i].spec]
            << setw(4) << "| " << setw(3) << left << p[i].fiz << "  "
            << setw(6) << "| " << setw(6) << left << p[i].mat << " ";
        switch (p[i].spec) {
        case KN:
            cout << setw(8) << "| " << setw(5) << left << p[i].prog << setw(21)
                << " | " << setw(10) << left
                << "| " << left << " |" << endl;
            break;
        case ME:
            cout << "" << setw(13) << "| " << " "
                << "" << setw(20) << "| "
                << setw(6) << "| " << setw(4) << left << p[i].pedagog << " |" << endl;
            break;
        case IN:
            cout << "" << setw(13) << "| " << setw(10) << " |" << " "
                << setw(9) << p[i].chis_metod << " |" << " "
                << setw(8) << "" << " |" << endl;
            break;
        case FI:
        case TN:
            cout << "" << setw(13) << "| " << " "
                << "" << setw(20) << "| " << setw(6) << "| " << setw(4) << left << p[i].pedagog << " |" << endl;
            break;
        }
    }
    cout << "==========================================================================================================="
        << endl;
    cout << endl;
}

void Sort(Student* p, const int N) {
    sort(p, p + N, [](const Student& a, const Student& b) {
        if (a.average != b.average)
            return a.average > b.average;
        if (a.course != b.course)
            return a.course < b.course;
        return a.surname > b.surname;
        });
}

int* IndexSort(Student* p, const int N) {
    vector<pair<double, int>> indices(N);
    for (int i = 0; i < N; ++i)
        indices[i] = { p[i].average, i };
    sort(indices.begin(), indices.end(), greater<pair<double, int>>());
    int* I = new int[N];
    for (int i = 0; i < N; ++i)
        I[i] = indices[i].second;
    return I;
}

void PrintIndexSorted(Student* p, int* I, const int N) {
    cout << "==========================================================================================================="
        << endl;
    cout << "| # | Surname | Course | Specialization | Physic | Mathematics | Programming | Numerical Methods | Pedagogy |"
        << endl;
    cout << "-----------------------------------------------------------------------------------------------------------"
        << endl;
    for (int i = 0; i < N; i++) {
        int index = I[i];
        cout << "|" << setw(2) << right << i + 1 << " ";
        cout << "| " << setw(8) << left << p[index].surname
            << "| " << setw(4) << right << p[index].course << "  "
            << " | " << setw(14) << left << specialnistList[p[index].spec]
            << setw(4) << "| " << setw(3) << left << p[index].fiz << "  "
            << setw(6) << "| " << setw(6) << left << p[index].mat << " ";
        switch (p[index].spec) {
        case KN:
            cout << setw(8) << "| " << setw(5) << left << p[index].prog << setw(21)
                << " | " << setw(10) << left
                << "| " << left << " |" << endl;
            break;
        case ME:
            cout << "" << setw(13) << "| " << " "
                << "" << setw(20) << "| "
                << setw(6) << "| " << setw(4) << left << p[index].pedagog << " |" << endl;
            break;
        case IN:
            cout << "" << setw(13) << "| " << setw(10) << " |" << " "
                << setw(9) << p[index].chis_metod << " |" << " "
                << setw(8) << "" << " |" << endl;
            break;
        case FI:
        case TN:
            cout << "" << setw(13) << "| " << " "
                << "" << setw(20) << "| "
                << setw(6) << "| " << setw(4) << left << p[index].pedagog << " |" << endl;
            break;
        }
    }
    cout << "==========================================================================================================="
        << endl;
    cout << endl;
}

bool BinarySearch(Student* p, const int N, string surname, int course, int average) {
    int low = 0, high = N - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (p[mid].surname == surname && p[mid].course == course && p[mid].average == average)
            return true;
        else if (p[mid].surname < surname || (p[mid].surname == surname && p[mid].course < course) || (p[mid].surname == surname && p[mid].course == course && p[mid].average < average))
            low = mid + 1;
        else
            high = mid - 1;
    }
    return false;
}
