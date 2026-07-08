#ifndef MINHALCHAT_H
#define MINHALCHAT_H

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <map>
#include <deque>
#include <cstdlib>
#include <unistd.h>
#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// Define constant for maximum number of messages
const int MAX_MESSAGES = 100;

// Global Variables
 map<string, bool> userStatus;
// Function Declarations
void wellcomechat();
void updateUserStatus(const string& username, bool online);
bool authenticateUser(const string& username, const string& password);
void displayOnlineStatus();
void sendMessage(const string& sender, const string& recipient);
void displayMessages();
void registerUser(const string& userType);
void loginUser(const string& userType);
void logoutUser(const string& userType);
void dotdelay();

#endif

//void ccolor(int color) {
  //  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
//}

//function to display well come screen
void wellcomechat() {
    ccolor(240); // Light Grey background with Black text

    char line1[] = "W E L C O M E ";
    char line2[] = " T O  T H E ";
    char line3[] = " C H A T _ M A T E ";
    
    printf("\n\n\n\n\n\t\t\t");
    for (int i = 0; i < strlen(line1); i++) {
        ccolor(240 | (i % 15)); // Light Grey background with varied text colors
        printf("%c", line1[i]);
        Sleep(200);
    }
    ccolor(240); // Reset to default color
    printf("\n\n\n\t\t\t");
    
    for (int i = 0; i < strlen(line2); i++) {
        ccolor(240 | (i % 15)); // Light Grey background with varied text colors
        printf("%c", line2[i]);
        Sleep(200);
    }
    ccolor(240); // Reset to default color
    printf("\n\n\n\t\t\t");
    
    for (int i = 0; i < strlen(line3); i++) {
        ccolor(240 | (i % 15)); // Light Grey background with varied text colors
        printf("%c", line3[i]);
        Sleep(200);
    }
    ccolor(240); // Reset to default color
}
//delay using dot screen
void dotdelay(){
	for(int i = 0; i<3; i++){
		cout<<" . ";
	}
}


// Function to register a user
void registerUser(const string& userType) {
    string username, password;
    cout <<" \n\t\t Enter "<< userType <<" name :  ";
    cin >> username;
    cout <<" \n\t\t Enter "<<userType <<" password :  ";
    cin >> password;

    ofstream outFile(" userchat.txt ", ios::app);
    if (outFile.is_open()) {
        outFile << username << " " << password << endl;
        cout << "\n\t\t User " << username << " registered successfully.\n";
        outFile.close();
    } else {
        cerr << "\n Unable to open file.\n";
    }
}

// Function for user login
void loginUser(const string& userType) {
    string username, password;
    cout <<" \n\t\t Enter "<< userType <<" name :  ";
    cin >> username;
    cout <<" \n\t\t Enter "<<userType <<" password :  ";
    cin >> password;

    if (authenticateUser(username, password)) {
        cout << "\n\t\t Login successful.\n";
        updateUserStatus(username, true); // Set user online
    } else {
       // cout << "\n Authentication failed. Invalid username or password.\n";
    }
}

// Function to authenticate user
bool authenticateUser(const string& username, const string& password) {
    ifstream inFile("userchat.txt");
    string storedUsername, storedPassword;
    while (inFile >> storedUsername >> storedPassword) {
        if (storedUsername == username && storedPassword == password) {
            inFile.close();
            return true; // User found
        }
    }
    inFile.close();
    return false; // User not found
}

 //Function to update user status
void updateUserStatus(const string& username, bool online) {
    userStatus[username] = online;
}

// Function to send a message
void sendMessage(const string& sender, const string& recipient) {
    string message;
    cout << "Type your message: ";
    getline(cin >> ws, message);

    // Open the chat history file in append mode
    ofstream outFile("messages.txt", ios::app);
    if (outFile.is_open()) {
        time_t currentTime = time(0); // Get current time
        string timeStr = ctime(&currentTime); // Convert time to string
        timeStr.erase(timeStr.length() - 1); // Remove trailing newline
        outFile << timeStr << " " << sender << " to " << recipient << ": " << message << endl;
        outFile.close();
        cout << "Message sent successfully.\n";

        // Check the number of messages in the chat history file
        ifstream inFile("messages.txt");
        deque<string> messages;
        string line;
        while (getline(inFile, line)) {
            messages.push_back(line);
        }
        inFile.close();

        // If the number of messages exceeds the limit, remove the oldest message
        if (messages.size() > MAX_MESSAGES) {
            // Display a message indicating that the message limit has been exceeded
            cout << "Warning: Message limit exceeded. You cannot send more than 100 messages.\n";

            // Remove the oldest message
            ofstream tempFile("temp.txt");
            for (size_t i = messages.size() - MAX_MESSAGES; i < messages.size(); ++i) {
                tempFile << messages[i] << endl;
            }
            tempFile.close();
            remove("messages.txt");
            rename("temp.txt", "messages.txt");
        }
    } else {
        cerr << "Unable to open file.\n";
    }
}

// Function to display messages
void displayMessages() {
    ifstream inFile("messages.txt");
    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            cout << line << endl;
        }
        inFile.close();
    } else {
        cerr << "Unable to open file.\n";
    }
}

// Function to display online status
void displayOnlineStatus() {
    cout << "Online Users:" << endl;
       for (map<string, bool>::const_iterator it = userStatus.begin(); it != userStatus.end(); ++it) {
        cout << it->first << ": " << (it->second ? "Online" : "Offline") << endl;
    }
}

// Function for user logout
void logoutUser(const string& userType) {
    string username;
    cout << "Enter " << userType << " username: ";
    cin >> username;

    if (userStatus.find(username) != userStatus.end() && userStatus[username]) {
        updateUserStatus(username, false); // Set user offline
        cout << userType << " logged out successfully.\n";
    } else {
        cout << "User is not logged in.\n";
    }
}
