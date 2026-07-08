#ifndef REGISTER_USER_H
#define REGISTER_USER_H
#include <iostream>
#include <fstream>
#include <cstring>
#include <limits>
#include <cctype>
#include "loginuser.h"
using namespace std;

// Function to validate Gmail email format___________________________________________________		
		bool isValidEmail(const std::string& email) 
	{
		//checks for @ in whole gmail sttring and stores its indes at atPos
    	size_t atPos = email.find('@');
    	if (atPos == std::string::npos) return false;
        //checlks for dot'.'afer @ in remaining gmail string
    	size_t dotPos = email.find('.', atPos);
    	if (dotPos == std::string::npos) return false;
        //stores domain part of gmail string starting after @
    	std::string domain = email.substr(atPos + 1);
    	if (domain != "gmail.com") return false;
        //stores stringbefore @ symbol
    	std::string localPart = email.substr(0, atPos);
    	if (localPart.empty()) return false;
		//checks for validity in emil string as a whole
    	for (size_t i = 0; i < email.length(); ++i) 
		{
        char c = email[i];
        if (!(isalnum(c) || c == '.' || c == '_' || c == '@')) return false;
    	}
		//checks for '.' symbol at the beginnng, end of local part, and repition of symbol
    	if (localPart[0] == '.' || localPart[localPart.length() - 1] == '.' || localPart.find("..") != std::string::npos) {
        return false;
    	}
    return true;
	}
	
	// Function to validate password_______________________________________________________________
	bool isValidPassword(const std::string& password) 
	{
    	if (password.length() < 6) return false;

    	bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;
    	std::string specialChars = "!@#$%^&*()-_+=<>?";

    	for (size_t i = 0; i < password.length(); ++i) 
		{
        if (isupper(password[i])) hasUpper = true;
        else if (islower(password[i])) hasLower = true;
        else if (isdigit(password[i])) hasDigit = true;
        else if (specialChars.find(password[i]) != string::npos) hasSpecial = true;
    	}
    return hasUpper && hasLower && hasDigit && hasSpecial;
	}


	// Function to check if the user details already exist__________________________________________________
bool userExists(const std::string& name, const std::string& email, const std::string& password, std::string& errorMsg) {
    ifstream inFile("users.txt");
    if (!inFile.is_open()) 
	{
        cout << "File cannot be opened for checking exist or not." << endl;
        system("pause");
        return false;
    }
    string line;
    bool userfound = false;
    while (getline(inFile, line)) 
	{
        size_t firstComma = line.find(",");
        if (firstComma == string::npos) {
            continue;  // If there's no comma, skip to the next line
        }
        size_t secondComma = line.find(",", firstComma + 1);
        if (secondComma == string::npos) {
            continue;  // If there's no second comma, skip to the next line
        }
        std::string existingName = line.substr(0, firstComma);
        std::string existingEmail = line.substr(firstComma + 1, secondComma - firstComma - 1);
        std::string existingPassword = line.substr(secondComma + 1);

        // Check if the current user matches the provided email and password
        if (existingEmail == email && existingPassword == password) 
		{
        	cout<<"\n Going for user exist check...";
            userfound = true;  // Set flag to true if user is found
            cout << "\nUser with the same email and password found" << endl;
            system("pause");
            break; // Exit the loop since user is found
        }
    }
    inFile.close();
    // Display error message if user not found after reading the entire file
    if (!userfound) {
         errorMsg = "A user with the same email and password does not exist.";
    }
    return userfound;
}

// Function to register a new user_________________________________________________________
void registerUser() {
    std::string name;
    std::string email;
    std::string password;
    std::string errorMsg;
    system("cls");
    cout<<"\n\n\n\t\t";
    cout << "=== User Registration ===" << endl;
        // Get user name
        while (true) 
		{
        	cin.ignore();
            cout << "\n\n\t Enter your name: ";
            getline(cin, name);
            if (!name.empty()) break;
            else cout << "\nName cannot be empty. Please try again." << endl;
        }
        // Get user email
        while (true) 
		{
            cout << "\n\t Enter your email: ";
            getline(cin, email);
            if (isValidEmail(email)) break;
            else cout << "\t Invalid Gmail address. Please try again.";
        }
        // Get user password
        while (true) 
		{
            cout << "\n\t Enter your password \n\t*At least 6 characters \n\t*Including an uppercase letter\n\t*A lowercase letter \n\t*A digit\n\t*And a special character): ";
            getline(cin, password);
            if (isValidPassword(password)) break;
            else cout << "\nPassword does not meet the requirements. Please try again." << endl;
        }
		 if (userExists(name, email, password, errorMsg)) 
		{
			cout <<"\nPlease enter your confidential details..."<<endl;
			cout<<"Press Enter to continue";
        	registerUser();
        	cout <<"\n\t\tNo match found";
        	cout << "\n\t\t Registration successful!" << endl;
        } 
	// Save user details to a file
    ofstream outFile("users.txt", ios::app);
    if (outFile.is_open()) {
        outFile<< name << "," << email << "," << password << endl;
        outFile.close();
    } else {
        cerr << "Error: Unable to open file for writing." << endl;
    }   
}
#endif	
	
	
