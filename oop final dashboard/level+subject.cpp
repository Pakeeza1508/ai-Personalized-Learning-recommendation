#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <stdio.h>
#include <windows.h>
#include "quiz.h"
using namespace std;
//void takequiz( string& subject,  string& level, int num_questions, Subject* subjects[]);
int main() {
   Subject* subjects[20] = {
    new MathBasic(), new MathModerate(), new MathDifficult(),
    new PhysicsBasic(), new PhysicsModerate(), new PhysicsDifficult(),
    new ChemistryBasic(), new ChemistryModerate(), new ChemistryDifficult(),
    new ComputerBasic(), new ComputerModerate(), new ComputerDifficult(),
    new EnglishBasic(), new EnglishModerate(), new EnglishDifficult(),
    new ScienceBasic(), new ScienceModerate(), new ScienceDifficult(),
    new GeneralBasic(), new GeneralDifficult()
};
    string subject, level;
    int num_questions;
    loadingbar();
    Sleep(500);
    system("cls");
    // Get user input
	 cout << "\n\n\n\n\t\t";
    cout << "================== Ready for the Quiz ===================";
    cout << "\n\n\tSelect the subject for the quiz:\n\t (Math, Physics, Chemistry, Computer, English, Science, General): ";
    cin >> subject;
    cout << "\n\tEnter the level (basic, moderate, difficult ): ";
    cin >> level;
    cout << "\nAlso select the number of questions you want to have in your test (1 to 20): ";
    cin >> num_questions;
     takequiz(subject, level, num_questions, subjects);
    return 0;
}
