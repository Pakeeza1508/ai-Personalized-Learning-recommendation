#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <cctype>
#include <ctime>
#include <map>
#include <deque>
#include <cstdlib>
#include <unistd.h>
#include <windows.h>
#include <algorithm>
#include <utility>
#include "registeruser.h"
#include "loginuser.h"
#include "quiz.h"
#include "decoration.h"
#include "progress.h"
#include "minhalchat.h"
#include <memory>
#include <stdexcept>
#include <array>
using namespace std;

int main(){
	int choice;
	bool Register = false;
	mwellcome();
	Sleep(1000);
	while(true)
	{
	system("cls");
	cout<<" \n\n\n\t\t";
	cout<<"____________Welcome to your dashboard____________"<<endl;
	cout<<"\n\n\t 1. Register";
	cout<<"\n\n\t 2. Login";
	cout<<"\n\n\t 3. Select your Level + Subject and take quiz";
	cout<<"\n\n\t 4. Chat Group";
	cout<<"\n\n\t 5. Quit";
	cout<<"\nPlease enter your choice to proceed to your choice(1 -8) :\t";
	cin>>choice;
	switch(choice)
	{
	case 1:
         registerUser();
			break;
	case 2:	
	system("cls");
		    loginUser();
   		    break;
	case 3:
		{
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
    		 cout<< "\n\n\n\n";
    		 system("pause");
			break;
			}
//		case 4:
//			system("cls");
//			progress();
//			system("pause");
//			break;
//		case 5:
//			break;
		case 4:
			{
				system("cls");
			 wellcomechat();
    		sleep(3);
    		system("cls");
    		int choice;
    		string sender, receiver;

    	do {
        	cout << "\n\n\t\tChoose an option:\n";
        	cout << "\n\t 1. Register as Sender and Receiver\n";
        	cout << "\n\t 2. Login as Sender and Receiver\n";
        	cout << "\n\t 3. Send a message\n";
        	cout << "\n\t 4. View chat history\n";
        	cout << "\n\t 5. Display online status\n";
        	cout << "\n\t 6. Logout\n";
        	cout << "\n\t 7. Exit\n";
        	cout << "\n\t\tEnter your choice: \t";
        	cin >> choice;
        	sleep(2);
        	system("cls");
        switch (choice) {
            case 1:
                cout << "\n\n\n\t\t Sender's Registration:\n";
                registerUser("sender");
                cout << " \t\t";
               //cout << dotdelay();
                cout << "\n\n\t\t Receiver Registration:\n";
                registerUser("receiver");
                sleep(2);
                system("cls");
                break;
            case 2:
                cout << "\n\n\n\t\t Sender Login:\n";
                loginUser("sender");
                cout << "\n\n\n\t\t Receiver Login:\n";
                loginUser("receiver");
                cout << "\n\t Both sender and receiver logged in successfully.\n";
                sleep(2);
                system("cls");
                break;
            case 3:
                cout << "Sender: ";
                cin >> sender;
                cout << "Recipient: ";
                cin >> receiver;
                sendMessage(sender, receiver);
                break;
            case 4:
                cout << "\nChat History:\n";
                displayMessages();
                break;
            case 5:
                displayOnlineStatus();
               //updateUserStatus(const string& username, bool online);
                break;
            case 6:
                cout << "\nLogout:\n";
                logoutUser("Sender");
                logoutUser("Receiver");
                break;
            case 7:
                cout << "Exiting the application.\n";
                cout << "probably you have had a fine buddy chat...";
                cout << "===============Good Luck=================== ";
                break;
            default:
                cout << "\n\n\n Invalid choice. Please try again.\n";
                sleep(3);
				system("cls");
        }
    } while (choice != 7);
		}
			break;
		
		case 5:
			system("cls");
			cout<<"\n\n\t";
			cout<<"=============Okay take care of yourself, GOOD BYE==================";
			exit(0);
		default:
			cout<<"\t\tInvalid choice try again!";	
			system("pause");
			system("cls");
				
		}
	}

	return 0;
}
