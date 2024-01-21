#include <iostream>
#include <string.h>
#include <iomanip>
using namespace std;

int main()
{

    string search_passport_num, passport_num[101];
    char sex[101][20], name[101][50], age[101][10];
    int i, fcc = 1, ecc = 31;                                   // ecc=economy class count  ,fcc=first class count.
    char choise[10], class_choise[10], y_or_n[10], display[10]; // we use array of characters in choises to handle errors like:
                                                                //  -input other than numbers, -entering more than one characters.

homepage: // Is a label to come to home page (The home page helps not to exit program until flight ends.)

    cout << "\n Welcome to X-AIRLINE home page !! " << endl;
    cout << "  1. Assign a seat\n";
    cout << "  2. Display option (search,seat status)\n"; // Home page section.
    cout << "  3. Exit\n";
    cout << "Enter your choice: ";
invalid_choise_1: // label for invalid choise.
    cin >> choise;

    if (choise[1] != '\0')
    { // Error handle when more than enters more than one character.
        cout << "Please enter a valid input again: ";
        goto invalid_choise_1;
    }

    switch (choise[0])
    {
    case '1': // assigning seat section.

        cout << "--------Assigning a seat-------\n";
    assign_person: // Label when their is need to come to assign for a person again.
        cout << "  1. For first class.";
        if (fcc > 30)
        {
            cout << "(full)";
        }
        cout << endl;
        cout << "  2. For economy class.";
        if (ecc > 100)
        {
            cout << "(full)";
        }
        cout << endl;
        cout << "  3. Return to home page." << endl;

        cout << "Enter your choice: ";
    invalid_choise_2: // Label for invalid class choise.
        cin >> class_choise;
        if (class_choise[1] != '\0')
        { // Error handle when more than enters more than one character.
            cout << "Please enter a valid input again: ";
            goto invalid_choise_2;
        }
        if (class_choise[0] != '1' && class_choise[0] != '2' && class_choise[0] != '3')
        { // error handling when choise is different from 1 or 2.
            cout << "Please enter a valid input again: ";
            goto invalid_choise_2;
        }

        switch (class_choise[0])
        {
        case '1':
        first_class:
            if (fcc > 30)
            {
                cout << "SORRY!! The first class section is full.\n";
                cout << "Is it acceptable to be placed in the economy section? 'Y'for yes..'N'for no: ";
            invalid_choise_3: // label for invalid yes or no choise
                cin >> y_or_n;
                if (y_or_n[1] != '\0')
                { // Error handle when more than enters more than one character.
                    cout << "Please enter a valid input again: ";
                    goto invalid_choise_3;
                }

                y_or_n[0] = toupper(y_or_n[0]);
                if (y_or_n[0] == 'Y')
                {
                    goto economy_class;
                }
                else if (y_or_n[0] == 'N')
                {
                    cout << "The next flight leaves in 3 hours!!\n";
                    cout << "-----------------------------------\n";
                    goto homepage;
                }
                else
                {
                    cout << "Please enter a valid input again: "; // Error handling when input different from y or n.
                    goto invalid_choise_3;
                }
            }
            else
            {
                cin.ignore(); // First class data input section.
                cout << "Enter your name: ";
            empty_name_1:
                cin.getline(name[fcc], 50);
                if (isspace(name[fcc][0]))
                { // Used to handle error when the user enters space before his name.
                    cout << "Please don't enter space before your name: ";
                    goto empty_name_1;
                }
                else if (name[fcc][0] == '\0')
                { // Used to handle error when the user enters ''enter button'' before entering any value.
                    cout << "Please enter your name: ";
                    goto empty_name_1;
                }

                cout << "Enter your sex: ";
            invalid_sex_1:
                cin.getline(sex[fcc], 20); // Uses to limit input to "m,f,male or female" only.
                char str1[10] = {'M'}, str2[10] = {'F'}, str3[10] = {'M', 'A', 'L', 'E'}, str4[10] = {'F', 'E', 'M', 'A', 'L', 'E'};
                if (stricmp(sex[fcc], str1) != 0 && stricmp(sex[fcc], str2) != 0 && stricmp(sex[fcc], str3) != 0 && stricmp(sex[fcc], str4) != 0)
                {
                    cout << "please enter a valid sex input again: ";
                    goto invalid_sex_1;
                }
                cout << "Enter your age: ";
            invalid_age_1:
                cin.getline(age[fcc], 20);
                if (isspace(age[fcc][0]))
                { // Used to handle error when the user enters space before his age.
                    cout << "Please don't enter space before your age: ";
                    goto invalid_age_1;
                }
                else if (age[fcc][0] == '\0')
                { // Used to handle error when the user enters ''enter button'' before entering any value.
                    cout << "Please enter your age: ";
                    goto invalid_age_1;
                }

                for (i = 0; i < strlen(age[fcc]); i++)
                { // Checks whether the input is digit or not.
                    if (isdigit(age[fcc][i]) == false)
                    {
                        cout << "Please enter number only: ";
                        goto invalid_age_1;
                    }
                }
                if (strlen(age[fcc]) > 3)
                { // Checks whether the age is less than 1000.
                    cout << "Please enter age below 1000: ";
                    goto invalid_age_1;
                }

                cout << "Enter your passport number: ";
                cin >> passport_num[fcc];
                cout << "--------------------------\n";
                cout << "SEAT ADDED SUCCESFULLY!!\n";
                cout << "--------------------------\n";
                cout << " ______________________________________________________________" << endl;
                cout << "|       X-AIRLINE                     BOARDING PASS            |" << endl;
                cout << "|______________________________________________________________|" << endl;
                cout << "|NAME                |SEX    |PASSPORT_NUMBER     |SEAT_NUMBER |" << endl;
                cout << "|____________________|_______|____________________|____________|" << endl;
                cout << "|" << setw(20) << left << name[fcc];
                cout << "|" << setw(7) << left << sex[fcc]; // Displaying first class boarding pass.
                cout << "|" << setw(20) << left << passport_num[fcc];
                cout << "|" << setw(12) << left << fcc << "|";
                cout << endl;
                cout << " -------------------------------------------------------------- " << endl;

                ++fcc;
                cout << "If you want to add again press 'Y' OR any single character key to go to home page: ";
            invalid_choise_4: // label for invalid yes or no choise
                cin >> y_or_n;
                if (y_or_n[1] != '\0')
                { // Error handle when more than enters more than one character.
                    cout << "Please enter a valid input again: ";
                    goto invalid_choise_4;
                }

                y_or_n[0] = toupper(y_or_n[0]);
                if (y_or_n[0] == 'Y')
                {
                    goto assign_person;
                }
                else
                {
                    goto homepage;
                }
            }

        case '2':
        economy_class:
            if (ecc > 100)
            {
                cout << "SORRY!! The economy class section is full.\n";
                cout << "Is it acceptable to be placed in the first section? 'Y'for yes..'N'for no: ";
            invalid_choise_5: // label for invalid yes or no choise
                cin >> y_or_n;
                if (y_or_n[1] != '\0')
                { // Error handle when more than enters more than one character.
                    cout << "Please enter a valid input again: ";
                    goto invalid_choise_5;
                }
                y_or_n[0] = toupper(y_or_n[0]);
                if (y_or_n[0] == 'Y')
                {
                    goto first_class;
                }
                else if (y_or_n[0] == 'N')
                {
                    cout << "The next flight leaves in 3 hours!!\n";
                    cout << "-----------------------------------\n";
                    goto homepage;
                }
                else
                {
                    cout << "Please enter a valid input!!\n"; // Error handling when input different from y or n.
                    goto invalid_choise_5;
                }
            }
            else
            {
                cin.ignore(); // Economy class data input section
                cout << "Enter your name: ";
            empty_name_2:
                cin.getline(name[ecc], 50);
                if (isspace(name[ecc][0]))
                { // Used to handle error when the user enters space before his name.
                    cout << "Please don't enter space before your name: ";
                    goto empty_name_2;
                }
                else if (name[ecc][0] == '\0')
                { // Used to handle error when the user enters ''enter button'' before entering any value.
                    cout << "Please enter your name: ";
                    goto empty_name_2;
                }

                cout << "Enter your sex: "; // Economy class data input section.

            invalid_sex_2:
                cin.getline(sex[ecc], 20); // Uses to limit input to "m,f,male or female" only.
                char str1[10] = {'M'}, str2[10] = {'F'}, str3[10] = {'M', 'A', 'L', 'E'}, str4[10] = {'F', 'E', 'M', 'A', 'L', 'E'};
                if (stricmp(sex[ecc], str1) != 0 && stricmp(sex[ecc], str2) != 0 && stricmp(sex[ecc], str3) != 0 && stricmp(sex[ecc], str4) != 0)
                {
                    cout << "please enter a valid sex input again: ";
                    goto invalid_sex_2;
                }
                cout << "Enter your age: ";

            invalid_age_2:
                cin.getline(age[ecc], 20);
                if (isspace(age[ecc][0]))
                { // Used to handle error when the user enters space before his age.
                    cout << "Please don't enter space before your age: ";
                    goto invalid_age_2;
                }
                else if (age[ecc][0] == '\0')
                { // Used to handle error when the user enters ''enter button'' before entering any value.
                    cout << "Please enter your age: ";
                    goto invalid_age_2;
                }

                for (i = 0; i < strlen(age[ecc]); i++)
                {
                    if (isdigit(age[ecc][i]) == false)
                    {
                        cout << "Please enter number only: ";
                        goto invalid_age_2;
                    }
                }
                if (strlen(age[ecc]) > 3)
                {
                    cout << "Please enter age below 1000: ";
                    goto invalid_age_2;
                }

                cout << "Enter your passport number: ";
                cin >> passport_num[ecc];
                cout << "--------------------------\n";
                cout << "SEAT ADDED SUCCESFULLY!!\n";
                cout << "--------------------------\n";

                cout << " ______________________________________________________________" << endl;
                cout << "|       X-AIRLINE                     BOARDING PASS            |" << endl;
                cout << "|______________________________________________________________|" << endl;
                cout << "|NAME                |SEX    |PASSPORT_NUMBER     |SEAT_NUMBER |" << endl;
                cout << "|____________________|_______|____________________|____________|" << endl;
                cout << "|" << setw(20) << left << name[ecc];
                cout << "|" << setw(7) << left << sex[ecc]; // Displaying economy class boarding pass.
                cout << "|" << setw(20) << left << passport_num[ecc];
                cout << "|" << setw(12) << left << ecc << "|";
                cout << endl;
                cout << " -------------------------------------------------------------- " << endl;
                ++ecc;
                cout << "If you want to add again press 'Y' OR any single character key to go to home page: ";
            invalid_choise_6: // label for invalid yes or no choise
                cin >> y_or_n;
                if (y_or_n[1] != '\0')
                { // Error handle when more than enters more than one character.
                    cout << "Please enter a valid input again: ";
                    goto invalid_choise_6;
                }
                y_or_n[0] = toupper(y_or_n[0]);
                if (y_or_n[0] == 'Y')
                {
                    goto assign_person;
                }
                else
                {
                    goto homepage;
                }
            }
        case '3':
            goto homepage;
        }
    case '2': // Displaying option.

    displaying_position:
        cout << "\n----------Display options---------- " << endl;
        cout << "  1. Search person (using passport number)\n";
        cout << "  2. display seat status\n";
        cout << "  3. Return to home page\n";
        cout << "Enter your choice: ";
    invalid_choise_7:
        cin >> display;
        if (display[1] != '\0')
        { // Error handle when more than enters more than one character.
            cout << "Please enter a valid input again: ";
            goto invalid_choise_7;
        }
        if (display[0] != '1' && display[0] != '2' && display[0] != '3')
        { // error handling when choise is different from 1 or 2 or 3.
            cout << "Please enter a valid input again: ";
            goto invalid_choise_7;
        }

        switch (display[0])
        {
        case '1': // For searching.
            cout << "..To search for a person.." << endl;
            cout << "Enter the passport number: ";
            cin >> search_passport_num;

            for (i = 1; i <= 100; i++)
            {

                if (search_passport_num == passport_num[i]) // Searching code.
                {
                    cout << "==PERSON FOUND==" << endl;
                    cout << "Name: " << name[i] << endl;
                    cout << "Sex: " << sex[i] << endl;
                    cout << "Age: " << age[i] << endl;
                    cout << "seat number: " << i << endl;

                    goto displaying_position;
                }
            }

            if (i > 100)
            { // Out put when their is no person with such passport number.
                cout << "--------------------------------------------------------------" << endl;
                cout << "\nTheir is no person with this passport number please try again.\n"
                     << endl;
                cout << "--------------------------------------------------------------" << endl;

                goto displaying_position;
            }
        case '2': // Display seat status.

            cout << "\n--------------------FIRST CLASS STATUS (" << fcc - 1 << "/30)-------------------\n";
            cout << "________________________________________________________________" << endl;
            cout << "|NAME                |SEX    |PASSPORT_NUMBER     |SEAT_NUMBER |" << endl;
            cout << "|____________________|_______|____________________|____________|" << endl;
            for (i = 1; i <= fcc - 1; i++)
            {
                cout << "|" << setw(20) << left << name[i];
                cout << "|" << setw(7) << left << sex[i]; // Displaying all first class assigned persons.
                cout << "|" << setw(20) << left << passport_num[i];
                cout << "|" << setw(12) << left << i << "|";
                cout << endl;
            }
            cout << "|--------------------------------------------------------------|" << endl;

            cout << "\n-------------------ECONOMY CLASS STATUS (" << ecc - 31 << "/70)------------------\n";
            cout << "________________________________________________________________" << endl;
            cout << "|NAME                |SEX    |PASSPORT_NUMBER     |SEAT_NUMBER |" << endl;
            cout << "|____________________|_______|____________________|____________|" << endl;
            for (i = 31; i <= ecc - 1; i++)
            {
                cout << "|" << setw(20) << left << name[i];
                cout << "|" << setw(7) << left << sex[i];
                cout << "|" << setw(20) << left << passport_num[i]; // Displaying all economy class assigned persons.
                cout << "|" << setw(12) << left << i << "|";
                cout << endl;
            }
            cout << "|--------------------------------------------------------------|" << endl;

            goto displaying_position;
            break;
        case '3':
            goto homepage;
        }

    case '3': // Exit.
        cout << "\n-----THANK YOU FOR USING X-AIRLINE------\n"
             << endl;
        break;

    default: // Error handling for invalid input.
        cout << "please enter a valid input again: ";
        goto invalid_choise_1;
    }

    return 0;
}
