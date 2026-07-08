#ifndef LOGIN_USER_H
#define LOGIN_USER_H
#include <iostream>
#include <fstream>
#include <cstring>
#include <limits>
#include "registeruser.h" // Include the register_user.h header file
using namespace std;

bool isValidEmail(const std::string& email);
bool isValidPassword(const std::string& password);

// Function to check login credentials
bool check(const string& email, const string& password)
 {
    ifstream file("users.txt"); // Open the file
    if (!file) 
	{
        cerr << "Unable to open file" << endl;
        return false;
    }
    string storedEmail, storedPassword;
    while (file >> storedEmail >> storedPassword) { // Read email and password from file
        if (storedEmail == email && storedPassword == password) {
			return true; // Match found
        }
    }
    return false; // No match found
}

//declared user login function
void loginUser()
		{
			string repeat;
			string email, password, name, errorMsg;
			do{
			system("cls");
    		cin.ignore();
    		cout<<"\n\n\n\t\t";
    		cout << "=== Login User ===" << endl;
    	while (true) 
		{
            cout << "\n\t Enter your email: ";
            getline(cin, email);
            if (isValidEmail(email)) break;
            else cout << "\t Invalid Gmail address. Please try again.";
        }
    	while (true) 
		{
            cout << "\n\t Enter your password \n\t*At least 6 characters \n\t*Including an uppercase letter\n\t*A lowercase letter \n\t*A digit\n\t*And a special character): ";
            getline(cin, password);
            if (isValidPassword(password)) break;
            else cout << "\nPassword does not meet the requirements. Please try again." << endl;
        }
            if (!check(email, password)){
            	cout<<"\n\n\t\t CONGRATULATIONS          ";
            	cout<<"\n\n\t You logged In Successfully...";            	
			}
			else{
				cout<<"\n\n\t Login failed...\n Please try again!";
			}
   		    cout<<"\n\n Do you want to repeat?  (yes/no)  ";
   		    cin >>repeat;
   		    }while(repeat == "yes" || repeat == "y");
		}    	    
#endif

