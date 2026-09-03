#ifndef PROGRESS_H
#define PROGRESS_H
#include <iostream>
#include <fstream>
#include <string>
//#include <limits>

using namespace std;
void progress(){
		string line;	
		string lastName;
		size_t firstComma;
		cout << "\n\n\n\n\t\t";
	    cout << "================== Displaying Your Progress ===================";
	    cout <<" \n\n\t your progress in current test is follows...";
	   // Reads the last name from the file
    ifstream name_file("users.txt");  // 'ios::app' is unnecessary when opening for reading
    if (name_file.is_open()) {
        while (getline(name_file, line)) {
            firstComma = line.find(",");
            if (firstComma != string::npos) {
                lastName = line.substr(0, firstComma);  // Keep updating lastName with the current line's name
            }
        }
        name_file.close();  // Close the file
        
        if (!lastName.empty()) {
            cout << "\n\n\t Your Name is : " << lastName;
        } else {
            cout << "\n\t No valid name found in users.txt";
        }
    } else {
        cout << "\n\t Error opening users.txt";
    }
     // Read points and percentage from marks.txt
     string lastLine;
    ifstream marks_file("marks.txt");
    if (marks_file.is_open()) {
        while (getline(marks_file, line)) {
            lastLine = line;  // This will hold the last line after the loop
        }
        marks_file.close();  // Close the file

        if (!lastLine.empty()) {
            // Split the lastLine into score and percentage parts
            size_t firstTabPos = lastLine.find("\t ");
            size_t secondTabPos = lastLine.find("\t ", firstTabPos + 1);
            
            if (firstTabPos != string::npos && secondTabPos != string::npos) {
                string score = lastLine.substr(0, firstTabPos);
                string percentage = lastLine.substr(secondTabPos + 1);
                cout << "\n\n\t" << score << "\n\t" << percentage << endl;
            } else {
                // In case the tabs are not found, just print the entire lastLine
                cout << "\n\n\t" << lastLine << endl;
            }
        } else {
            cout << "\n\t The marks.txt file is empty" << endl;
        }
    } else {
        cout << "\n\t Error opening marks.txt";
    }
}

#endif   

        
        
