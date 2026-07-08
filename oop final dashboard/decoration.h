#include <stdio.h>
#include <windows.h> // For Sleep function
#include <string.h>

////color handling function code_________________________________
//void ccolor(int clr) {
//HANDLE hConsole;
//hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//SetConsoleTextAttribute(hConsole, clr);

//wellcome_code___________________________________________________
void mwellcome() {
   ccolor(240); // Light Grey background with Black text

    char welcome[50] = "WELCOME";
    char welcome2[50] = " TO";
    char welcome3[50] = " AI BASED SMART";
    char welcome4[50] = " RECOMMENDATIONS";
    
    printf("\n\n\n\n\n\t\t\t");
    for (int wlc = 0; wlc < strlen(welcome); wlc++) {
        ccolor(240 | (wlc % 15)); // Light Grey background with varied text colors
        printf(" %c", welcome[wlc]);
        Sleep(200);
    }
    ccolor(240);
    
    printf("\n\n\t\t\t\t ");
    for (int wlc2 = 0; wlc2 < strlen(welcome2); wlc2++) {
        ccolor(240 | (wlc2 % 15)); // Light Grey background with varied text colors
        printf(" %c", welcome2[wlc2]);
        Sleep(200);
    }
    ccolor(240);
    
    printf("\n\n\n\t\t\t ");
    for (int wlc3 = 0; wlc3 < strlen(welcome3); wlc3++) {
        if (welcome3[wlc3] != 'D') {
            ccolor(240 | (wlc3 % 15)); // Light Grey background with varied text colors
            printf(" %c", welcome3[wlc3]);
        } else {
            ccolor(240 | 1); // Light Grey background with Blue text
            printf(" %c", welcome3[wlc3]);
        }
        Sleep(200);
    }
    ccolor(240);
    
    printf("\n\n\n\t\t\t\t ");
    for (int wlc4 = 0; wlc4 < strlen(welcome4); wlc4++) {
        if (welcome4[wlc4] != 'A' && welcome4[wlc4] != 'E') {
            ccolor(240 | (wlc4 % 15)); // Light Grey background with varied text colors
            printf(" %c", welcome4[wlc4]);
        } else {
            ccolor(240 | 1); // Light Grey background with Blue text
            printf(" %c", welcome4[wlc4]);
        }
        Sleep(200);
    }
    ccolor(240);
}


//void qwellcome() {
//    ccolor(240); // Light Grey background with Black text
//
//    char goodbye1[50] = "Okay take care of yourself,";
//    char goodbye2[50] = " GOOD BYE!";
//    
//    printf("\n\n\n\n\n\t\t\t");
//    for (int gb1 = 0; gb1 < strlen(goodbye1); gb1++) {
//        ccolor(240 | (gb1 % 15)); // Light Grey background with varied text colors
//        printf(" %c", goodbye1[gb1]);
//        Sleep(200);
//    }
//    ccolor(240);
//
//    printf("\n\n\n\t\t\t\t ");
//    for (int gb2 = 0; gb2 < strlen(goodbye2); gb2++) {
//        ccolor(240 | (gb2 % 15)); // Light Grey background with varied text colors
//        printf(" %c", goodbye2[gb2]);
//        Sleep(200);
//    }
//    ccolor(240);
//}
//
////code to display welcome to the quiz message
//void pwellcome(const char* message) {
//    ccolor(240); // Light Grey background with Black text
//
//    // Set the background color
//    system("color F0");
//
//    // Modify the message here
//    char welcome[50] = "WELCOME";
//    char welcome2[50] = " TO THE";
//    char welcome3[50] = " QUIZ";
//
//    printf("\n\n\n\n\n\t\t\t");
//    for (int wlc = 0; wlc < strlen(welcome); wlc++) {
//        ccolor(240 | (wlc % 15)); // Light Grey background with varied text colors
//        printf(" %c", welcome[wlc]);
//        Sleep(100);
//    }
//    ccolor(240);
//
//    printf("\n\n\t\t\t\t ");
//    for (int wlc2 = 0; wlc2 < strlen(welcome2); wlc2++) {
//        if (welcome2[wlc2] != ' ') {
//            ccolor(240 | (wlc2 % 15)); // Light Grey background with varied text colors
//            printf(" %c", welcome2[wlc2]);
//        } else {
//            ccolor(240 | 1); // Light Grey background with Blue text
//            printf(" %c", welcome2[wlc2]);
//        }
//        Sleep(100);
//    }
//    ccolor(240);
//
//    printf("\n\n\n\t\t\t ");
//    for (int wlc3 = 0; wlc3 < strlen(welcome3); wlc3++) {
//        if (welcome3[wlc3] != ' ') {
//            ccolor(240 | (wlc3 % 15)); // Light Grey background with varied text colors
//            printf(" %c", welcome3[wlc3]);
//        } else {
//            ccolor(240 | 1); // Light Grey background with Blue text
//            printf(" %c", welcome3[wlc3]);
//        }
//        Sleep(100);
//    }
//    ccolor(240);
//}

//loading bar_____________________________________________________
void loadingbar(void) {
    for (int i = 5; i <= 100; i += 15) 
	{
        system("cls");
        ccolor(240); // Light Grey background
        printf("\n\n\n\n\n\n\n\t\t\t\t");
        printf("%d %% Loading...\n\n\t\t", i);
        printf("");
        for (int j = 0; j < i; j += 2) 
		{
            ccolor(240 | (j % 15)); // Light Grey background with varied text colors
            printf(" ");
            Sleep(100);
            ccolor(240);
        }
        Sleep(1);
        if (i == 90 || i == 50 || i == 96 || i == 83) 
		{
         	Sleep(100);
        }
    }
}

