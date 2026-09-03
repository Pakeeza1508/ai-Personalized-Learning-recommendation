#ifndef QUIZ_H
#define QUIZ_H
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <stdio.h>
#include <windows.h>
using namespace std;

void loadingbar(void);
void ccolor(int clr);
void pwellcome(const char* message);
string capitalizeFirst(string str);
string constructFilename(const string& subject, const string& level);

struct Question {
    string question;
    string option_a;
    string option_b;
    string option_c;
    string option_d;
    char answer;
};
//subject class
class Subject {
public:
    string name;
    Question questions[20];
    virtual void load_questions() = 0;
    void displayQuestions(const string& filename, int num_questions);
    void ask_questions(int num_questions, const string& filename) const;

    virtual ~Subject() {}
};
//function to load files
void load_file(const string &filename, Question questions[20]) {
    ifstream file(filename.c_str());
    if (!file.is_open()) {
        cerr << "Error opening the file: " << filename << endl;
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < 20; ++i) {
        getline(file, questions[i].question);
        getline(file, questions[i].option_a);
        getline(file, questions[i].option_b);
        getline(file, questions[i].option_c);
        getline(file, questions[i].option_d);
        file >> questions[i].answer;
        file.ignore();
    }
    file.close();
}
//function to display questions
void Subject::displayQuestions(const string& filename, int num_questions) {
    load_file(filename, questions);
    ask_questions(num_questions, filename);
}
//function to display quiz and result
void Subject::ask_questions(int num_questions, const string& filename) const {
	
	cout << filename << endl;
	//add welcome to the quiz function
	pwellcome("Welcome to the Quiz");
	Sleep(100);
    int points = 0;
    for (int i = 0; i < num_questions; ++i) {
    	system("cls");
        cout << "Question " << (i + 1) << ": " << questions[i].question << endl;
        cout << "Options:" << endl;
        cout << "a) " << questions[i].option_a << endl;
        cout << "b) " << questions[i].option_b << endl;
        cout << "c) " << questions[i].option_c << endl;
        cout << "d) " << questions[i].option_d << endl;
        char answer;
        cout << "Your Answer: ";
        cin >> answer;
        answer = tolower(answer);
        if (answer == questions[i].answer) 
		{
            cout << "Correct answer!" << endl;
            points += 1;
        } else {
            cout << "Wrong answer!" << endl;
        }
        for(int i=0; i<3; i++)
			{
        	cout<<" . ";
        	Sleep(1000);
			}
        cin.ignore();
    }
    system("cls");
    cout<<"\n\n\n";
    cout << "\t\t\t\t============ Quiz completed =============" << endl;
    cout << "\n\n\t\tTotal Points: " << points << endl;
    float percentage = (static_cast<float>(points) / num_questions) * 100;
    cout << "\n\t\tYour Percentage: " << percentage << "%" << endl;
    ofstream marks_file;
    marks_file.open("marks.txt", ios::app);
    if (marks_file.is_open()) {
        marks_file << "\nYour total score is: " << points << "Your total percentage is :" << percentage << "%" << endl;
        
           
		     std::string arg2 = std::to_string(percentage);
		     cout << "Loading suggestions..." <<endl;
		     std::string node_path = "\"C:\\Program Files\\nodejs\\node.exe\"";
		   	 std::string command =  "node ../ai-model/script.js " + filename + " " + arg2;
   			 
   			 // Open a pipe to the command and capture its output
   			 
    		FILE* pipe = popen(command.c_str(), "r");
   			 if (!pipe) {
   			     std::cerr << "Error: popen() failed!" << std::endl;
   			     cout << "Error in opening the file";
   			 }
   			
   			 // Read the output of the command
   			 char buffer[128];
   			 while (!feof(pipe)) {
   			     if (fgets(buffer, 128, pipe) != nullptr) {
   			     	 
   			         // Print the output
   			         std::cout << buffer;
   			     }
   			 }
   			
   			 // Close the pipe
   			 pclose(pipe);	
   			 
   			 std::cout << "Press Enter to continue...";
			 std::cin.ignore();
        
    } else {
        cout << "Error in opening the file";
    }
}
//take quiz function
void takequiz( string& subject,  string& level, int num_questions, Subject* subjects[]){
	subject = capitalizeFirst(subject);
    level = capitalizeFirst(level);

    // Construct the filename selected by user
    string filename = constructFilename(subject, level);
    cout<<"\n\n\tYou selected "<<filename<<" and "<<level<<" for the quiz."<<endl;
    system("pause");
    ofstream selectFile("selectedsubject.txt", ios::app);
        if (selectFile.is_open()) 
		{
            selectFile << "Selected Subject : " << subject <<" and "<<"question selected : "<<num_questions<<std::endl;
            selectFile.close();
        } 
    Subject* selectedSubject = NULL;
    // Match user input to the appropriate object
    if (subject == "Math") {
        if (level == "Basic") selectedSubject = subjects[0];
        else if (level == "Moderate") selectedSubject = subjects[1];
        else if (level == "Difficult" || level == "High") selectedSubject = subjects[2];
    } else if (subject == "Physics") {
        if (level == "Basic") selectedSubject = subjects[3];
        else if (level == "Moderate") selectedSubject = subjects[4];
        else if (level == "Difficult" || level == "High") selectedSubject = subjects[5];
    } else if (subject == "Chemistry") {
        if (level == "Basic") selectedSubject = subjects[6];
        else if (level == "Moderate") selectedSubject = subjects[7];
        else if (level == "Difficult" || level == "High") selectedSubject = subjects[8];
    } else if (subject == "Computer") {
        if (level == "Basic") selectedSubject = subjects[9];
        else if (level == "Moderate") selectedSubject = subjects[10];
        else if (level == "Difficult" || level == "High") selectedSubject = subjects[11];
    } else if (subject == "English") {
        if (level == "Basic") selectedSubject = subjects[12];
        else if (level == "Moderate") selectedSubject = subjects[13];
        else if (level == "Difficult" || level == "High") selectedSubject = subjects[14];
    } else if (subject == "Science") {
        if (level == "Basic") selectedSubject = subjects[15];
        else if (level == "Moderate") selectedSubject = subjects[16];
        else if (level == "Difficult" || level == "High") selectedSubject = subjects[17];
    } else if (subject == "General") {
        if (level == "Basic") selectedSubject = subjects[18];
        else if (level == "Moderate" || level == "Difficult" || level == "High") selectedSubject = subjects[19];
    }
    if (selectedSubject != NULL) {
    	system("cls");
        selectedSubject->displayQuestions(filename, num_questions);
    } else {
        cout << "Invalid subject or level entered!" << endl;
    }
    // Clean up
    for (int i = 0; i < 20; ++i) {
        delete subjects[i];
    }
}

//sub classes inheriting from subject class 
class MathBasic : public Subject {
public:
    void load_questions() { load_file("MathBasic.txt", questions); }
};

class MathModerate : public Subject {
public:
    void load_questions() { load_file("MathModerate.txt", questions); }
};

class MathDifficult : public Subject {
public:
    void load_questions() { load_file("MathDifficult.txt", questions); }
};

class PhysicsBasic : public Subject {
public:
    void load_questions() { load_file("PhysicsBasic.txt", questions); }
};

class PhysicsModerate : public Subject {
public:
    void load_questions() { load_file("PhysicsModerate.txt", questions); }
};

class PhysicsDifficult : public Subject {
public:
    void load_questions() { load_file("PhysicsDifficult.txt", questions); }
};

class ChemistryBasic : public Subject {
public:
    void load_questions() { load_file("ChemistryBasic.txt", questions); }
};

class ChemistryModerate : public Subject {
public:
    void load_questions() { load_file("ChemistryModerate.txt", questions); }
};

class ChemistryDifficult : public Subject {
public:
    void load_questions() { load_file("ChemistryDifficult.txt", questions); }
};

class ComputerBasic : public Subject {
public:
    void load_questions() { load_file("ComputerBasic.txt", questions); }
};

class ComputerModerate : public Subject {
public:
    void load_questions() { load_file("ComputerModerate.txt", questions); }
};

class ComputerDifficult : public Subject {
public:
    void load_questions() { load_file("ComputerDifficult.txt", questions); }
};

class EnglishBasic : public Subject {
public:
    void load_questions() { load_file("EnglishBasic.txt", questions); }
};

class EnglishModerate : public Subject {
public:
    void load_questions() { load_file("EnglishModerate.txt", questions); }
};

class EnglishDifficult : public Subject {
public:
    void load_questions() { load_file("EnglishDifficult.txt", questions); }
};

class ScienceBasic : public Subject {
public:
    void load_questions() { load_file("ScienceBasic.txt", questions); }
};

class ScienceModerate : public Subject {
public:
    void load_questions() { load_file("ScienceModerate.txt", questions); }
};

class ScienceDifficult : public Subject {
public:
    void load_questions() { load_file("ScienceDifficult.txt", questions); }
};

class GeneralBasic : public Subject {
public:
    void load_questions() { load_file("GeneralBasic.txt", questions); }
};

class GeneralDifficult : public Subject {
public:
    void load_questions() { load_file("GeneralDifficult.txt", questions); }
};

#endif

//maintains file name+level
string capitalizeFirst(string str)
 {
    if (!str.empty()) 
	{
        str[0] = toupper(str[0]);
    }
    return str;
 }

//constructs file name with selected subject and level
string constructFilename(const string& subject, const string& level) 
{
    string filename = subject + level + ".txt";
    return filename;
}

//color handling function code_________________________________
void ccolor(int clr) {
    HANDLE hConsole;
   hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
   SetConsoleTextAttribute(hConsole, clr);
}

//loading bar_____________________________________________________
//void loadingbar(void) {
//    for (int i = 5; i <= 100; i += 10) 
//	{
//        system("cls");
//       // ccolor(240); // Light Grey background
//        printf("\n\n\n\n\n\n\n\t\t\t\t");
//        printf("%d %% Loading...\n\n\t\t", i);
//        printf("");
//        for (int j = 0; j < i; j += 2) 
//		{
//            //ccolor(240 | (j % 15)); // Light Grey background with varied text colors
//            printf(" ");
//            Sleep(1);//Sleep(100);
//          //  ccolor(240);
//        }
//        Sleep(1);
//        if (i == 90 || i == 50 || i == 96 || i == 83) 
//		{
//         	Sleep(1);
//        }
//    }
//}
//code to display welcome to the quiz message
void pwellcome(const char* message) {
    //ccolor(240); // Light Grey background with Black text

    // Set the background color
    system("color F0");

    // Modify the message here
    char welcome[50] = "WELCOME";
    char welcome2[50] = " TO THE";
    char welcome3[50] = " QUIZ";

    printf("\n\n\n\n\n\t\t\t");
    for (int wlc = 0; wlc < strlen(welcome); wlc++) {
        ccolor(240 | (wlc % 15)); // Light Grey background with varied text colors
        printf(" %c", welcome[wlc]);
        Sleep(200);
    }
    ccolor(240);

    printf("\n\n\t\t\t\t ");
    for (int wlc2 = 0; wlc2 < strlen(welcome2); wlc2++) {
        if (welcome2[wlc2] != ' ') {
            ccolor(240 | (wlc2 % 15)); // Light Grey background with varied text colors
            printf(" %c", welcome2[wlc2]);
        } else {
            ccolor(240 | 1); // Light Grey background with Blue text
            printf(" %c", welcome2[wlc2]);
        }
        Sleep(200);
    }
    ccolor(240);

    printf("\n\n\n\t\t\t ");
    for (int wlc3 = 0; wlc3 < strlen(welcome3); wlc3++) {
        if (welcome3[wlc3] != ' ') {
            ccolor(240 | (wlc3 % 15)); // Light Grey background with varied text colors
            printf(" %c", welcome3[wlc3]);
        } else {
            ccolor(240 | 1); // Light Grey background with Blue text
            printf(" %c", welcome3[wlc3]);
        }
        Sleep(200);
    }
    ccolor(240);
}
