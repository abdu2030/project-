#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cctype>
#include <cstdio>
#include <sstream>
#include <memory>
#include <stdexcept>
#include <array>
#include <string.h>
#include <algorithm> 
#include<limits>// For std::replace

using namespace std;

string server = "AKME\\SQLEXPRESS"; // Escape backslash
string database = "projectccc";
string username = "sa";
string password = "abdulkerim444";
string connStr = "sqlcmd -S " + server + " -d " + database + " -U " + username + " -P " + password;

struct house
{
    string city;
    int city_code;
    string subcity;
    int subcity_code;
    string house_type;
    int price;
    float size_of_h;
    int num_bed;
    bool avilablity;
    int id;
};

struct bussiness
{
    unsigned long int phone_num;
    string buss_name;
    string name;
    string password;
    string city;
    int ID;
};

struct personal
{
    string name;
    string password;
    string city;
};

int error_handle(char choise[])
{
    if (isdigit(choise[0]) && strlen(choise) == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int get_city_code(const string &city)
{
    if (city == "adama")
        return 1;
    if (city == "addis ababa")
        return 2;
    if (city == "hawasa")
        return 3;
    if (city == "wolkite")
        return 4;
    return -1;
}

int get_subcity_code(const string &city, const string &subcity)
{
    if (city == "adama")
    {
        if (subcity == "mebrathail")
            return 1;
        if (subcity == "postabet")
            return 2;
        if (subcity == "wenjimazoria")
            return 3;
    }
    else if (city == "addis ababa")
    {
        if (subcity == "bole")
            return 1;
        if (subcity == "megenagna")
            return 2;
        if (subcity == "bisrategebrel")
            return 3;
    }
    else if (city == "hawasa")
    {
        if (subcity == "piyasa")
            return 1;
        if (subcity == "tabor")
            return 2;
        if (subcity == "atota")
            return 3;
    }
    else if (city == "wolkite")
    {
        if (subcity == "selamber")
            return 1;
        if (subcity == "adebabay")
            return 2;
        if (subcity == "mariyamsefer")
            return 3;
    }
    return -1;
}

void display_best_choise(vector<house> &hs, string &user_city_for_feed, int best_choises_forfeed[])
{
    int index = 0;
    for (int i = 0; i < hs.size(); ++i)
    {
        if (hs[i].city == user_city_for_feed)
        {
            best_choises_forfeed[index] = i;
            index++;
            if (index >= 4)
                break;
        }
    }

    cout << "--------Best choices in city " << user_city_for_feed << " are:--------" << endl;
    for (int i = 0; i < index; ++i)
    {

        cout << " __________                     "<< endl;
        cout << "/__________\\                   City: " << hs[best_choises_forfeed[i]].city  << endl;
        cout << " | | | |_||                     Subcity: " << hs[best_choises_forfeed[i]].subcity  << endl;
        cout << " | |*|    |                     Price: " << hs[best_choises_forfeed[i]].price << endl;
        cout << " ********** " << endl;
        cout << " House " << i + 1  << endl;
    }   
}

char login(vector<house> hs, vector<personal> &p_i, vector<bussiness> &b_i, string &user_city_for_feed)
{
    char choice[5];
    string name, password, username;
    cout << "   1. personal " << endl;
    cout << "   2. bussiness " << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    while (error_handle(choice) == 0 /* 0 shows there is an error*/)
    {
        cout << "please enter a valid input again: ";
        cin >> choice;
    }
    switch (choice[0])
    {
    case '1': // Personal user
        cout << "Enter your username: ";
        cin >> username;
        cin.ignore();
        cout << "Enter your password: ";
        cin >> password;
        cin.ignore();
        for (int i = 0; i < p_i.size(); i++)
        {
            if (username == p_i[i].name && password == p_i[i].password)
            {
                user_city_for_feed = p_i[i].city;
                cout << "Successful login" << endl;
                // display_best_choise(hs, user_city_for_feed, best_choises_forfeed);
                return 'p'; // Personal home page
            }
        }
        cout << "Invalid username or password." << endl;
        cout << "   1. Would you like to try again " << endl;
        cout << "   2. create a new account ? " << endl;
        cout << "Enter yout choice: ";
        char retryChoice;
        cin >> retryChoice;
        if (retryChoice == '1')
        {
            return login(hs, p_i, b_i, user_city_for_feed);
        }
        else if (retryChoice == '2')
        {
            return 'c'; // Create a new account
        }
        break;
    case '2': // Business user
        cout << "Enter your username(don't put space): ";
        cin >> username;
        cin.ignore();
        cout << "Enter your password: ";
        cin >> password;
        cin.ignore();
        for (int i = 0; i < b_i.size(); i++)
        {
            if (username == b_i[i].name && password == b_i[i].password)
            {
                cout << "Successful login" << endl;
                return 'b'; // Business home page
            }
        }
        cout << "Invalid username or password." << endl;
        cout << "    1. Would you like to try again " << endl;
        cout << "    2. create a new account ? " << endl;
        cout << "Enter yout choice: ";
        cin >> retryChoice;
        if (retryChoice == '1')
        {
            return login(hs, p_i, b_i, user_city_for_feed);
        }
        else if (retryChoice == '2')
        {
            return 'c'; // Create a new account
        }
        break;
    default:
        cout << "Invalid choice." << endl;
        return 'c';
    }
    return 'e'; // Error case
}

void creat_account(vector<personal> &p_i, vector<bussiness> &b_s)
{
    personal get_p;
    bussiness get_b;
    char c;

    cout << "Do you want to create a personal or business account" << endl;
    cout << "Press 'p' for personal account and 'b' for business account: ";
fault:
    cin >> c;
    if (c == 'p')
    {
        cout << "\nEnter personal account details:\n";
    errorp:
        cout << "user Name(don't use space): ";
        cin >> get_p.name;
        cout << "Password: ";
        cin >> get_p.password;
        cout << "City: ";
        cin.ignore();
        getline(cin, get_p.city);
        for (int i = 0; i < p_i.size(); i++)
        {
            if (get_p.name == p_i[i].name)
            {
                cout << "Error: user name already exists. Please choose a different user name.\n";
                goto errorp;
            }
        }
        p_i.push_back(get_p);
        string insert_query = "sqlcmd -S " + server + " -d " + database + " -U " + username + " -P " + password + " -Q \"INSERT INTO personal (name, password, city) VALUES ('" + get_p.name + "', '" + get_p.password + "', '" + get_p.city + "')\"";
        int result = system(insert_query.c_str());
        if (result == 0)
        {
            cout << "\nPersonal account created successfully!" << endl;
        }
        else
        {
            cout << "\nFailed to create personal account." << endl;
        }
    }
    else if (c == 'b')
    {
        cout << "\nEnter Business account details:\n";

        cout << "Enter Business Name(use underscore instead of space): ";
        cin >> get_b.buss_name;
        cin.ignore();
        cout << "Name: ";
        cin >> get_b.name;
        cin.ignore();
        cout << "Password: ";
        cin >> get_b.password;
        cin.ignore();
        cout << "City: ";
        cin >> get_b.city;
        cin.ignore();
        cout << "Phone number: ";
        cin >> get_b.phone_num;
        get_b.ID = b_s.size() + 1;
        cout << "Your ID is " << get_b.ID << endl;
        b_s.push_back(get_b);
        string insert_query = "sqlcmd -S " + server + " -d " + database + " -U " + username + " -P " + password + " -Q \"INSERT INTO bussiness (ID, buss_name, name, password, city, phone_num) VALUES (" + to_string(get_b.ID) + ", '" + get_b.buss_name + "', '" + get_b.name + "', '" + get_b.password + "', '" + get_b.city + "', " + to_string(get_b.phone_num) + ")\"";
        int result = system(insert_query.c_str());
        if (result == 0)
        {
            cout << "\nBusiness account created successfully!" << endl;
        }
        else
        {
            cout << "\nFailed to create business account." << endl;
        }
    }
    else
    {
        cout << "Error input. Please choose either 'p' or 'b': ";
        goto fault;
    }
}

void Add_house(vector<house> &hs)
{
    house new_house;
    char typ_h;
    cout << "Enter city(use underscore instead of space): ";
    cin.ignore();
    getline(cin, new_house.city);
    
    new_house.city_code = get_city_code(new_house.city);
    cout << "Enter subcity(use underscore instead of space): ";
    getline(cin, new_house.subcity);
    //cin.ignore();
    new_house.subcity_code = get_subcity_code(new_house.city, new_house.subcity);
house:
    cout << "Enter house type (1 for apartment, 2 for condo, 3 for normal house): ";
    cin >> typ_h;
    switch (typ_h)
    {
    case '1':
        new_house.house_type = "apartment";
        break;
    case '2':
        new_house.house_type = "condo";
        break;
    case '3':
        new_house.house_type = "normal house";
        break;
    default:
        cout << "Invalid house type entered.";
        goto house;
    }
    cout << "Enter price: ";
    cin >> new_house.price;
    cout << "Enter size of the house: ";
    cin >> new_house.size_of_h;
    cout << "Enter number of bedrooms: ";
    cin >> new_house.num_bed;
    cout << "Enter availability (1 for available, 0 for not available): ";
    cin >> new_house.avilablity;
    new_house.id = hs.size()+1;
    cout << "your id four house is " << new_house.id;
    hs.push_back(new_house);
    string insert_query = connStr + " -Q \"INSERT INTO house (id, city, city_code, subcity, subcity_code, house_type, price, size_of_h, num_bed, availability) VALUES (" + to_string(new_house.id) + ", '" + new_house.city + "', " + to_string(new_house.city_code) + ", '" + new_house.subcity + "', " + to_string(new_house.subcity_code) + ", '" + new_house.house_type + "', " + to_string(new_house.price) + ", " + to_string(new_house.size_of_h) + ", " + to_string(new_house.num_bed) + ", " + to_string(new_house.avilablity) + ")\"";
    int result = system(insert_query.c_str());
    if (result == 0)
    {
        cout << "\nHouse record inserted successfully." << endl;
    }
    else
    {
        cout << "\nFailed to insert house record." << endl;
    }
}

void Update_house_information(vector<house> &hs)
{
    int house_id;
eror:
    cout << " please enter the house id";
    cin >> house_id;
    int house_index;
    bool check = false;
    for (int i = 0; i < hs.size(); ++i)
    {
        if (hs[i].id == house_id)
        {
            house_index = i; // Return index if house with given ID is found
            check = true;
        }
    }
    if (check)
    {
        cout << "Enter new information for the house at index " << house_index << ":" << endl;
        cout << "City(use underscore instead of space): " ;
        cin.ignore();
        getline(cin, hs[house_index].city);
        hs[house_index].city_code=get_city_code(hs[house_index].city);
        cout << "Subcity(use underscore instead of space): ";
        getline(cin, hs[house_index].subcity);
        hs[house_index].subcity_code=get_subcity_code(hs[house_index].city,hs[house_index].subcity);
        cout << "House type( apartment,condo,normal house):: ";
        getline(cin, hs[house_index].house_type);
        cout << "Price: ";
        cin >> hs[house_index].price;
        cout << "Size of house: ";
        cin >> hs[house_index].size_of_h;
        cin.ignore();
        cout << "Number of bedrooms: ";
        cin >> hs[house_index].num_bed;
        cout << "Availability (1 for true, 0 for false): ";
        int availability;
        cin >> availability;
        hs[house_index].avilablity = (availability != 0);

        string update_query = "sqlcmd -S " + server + " -d " + database + " -U " + username + " -P " + password + " -Q \"UPDATE house SET city='" + hs[house_index].city + "', city_code=" + to_string(hs[house_index].city_code) + ", subcity='" + hs[house_index].subcity + "', subcity_code=" + to_string(hs[house_index].subcity_code) + ", house_type='" + hs[house_index].house_type + "', price=" + to_string(hs[house_index].price) + ", size_of_h=" + to_string(hs[house_index].size_of_h) + ", num_bed=" + to_string(hs[house_index].num_bed) + ", availability=" + to_string(hs[house_index].avilablity) + " WHERE id=" + to_string(hs[house_index].id) + "\"";
        int result = system(update_query.c_str());
        if (result == 0)
        {
            cout << "\nHouse record updated successfully!" << endl;
        }
        else
        {
            cout << "\nFailed to update house record." << endl;
        }
    }
    else
    {
        cout << " please enter your id correctly: ";
        goto eror;
    }
}

void view_more(vector<house> &h, int choose)
{
    if (choose < 0 || choose >= h.size())
    {
        cout << "!!!!Invalid house selection!!!!.\n";
        return;
    }
    house &hs = h[choose];

    cout << " ____________________           LOCATION: " << hs.city << endl;
    cout << "/____________________\\          SUBCITY: " << hs.subcity << endl;
    cout << "  | _____  _____   |            HOUSE TYPE: " << hs.house_type << endl;
    cout << "  | |   |  | | |   |            PRICE: " << hs.price << endl;
    cout << "  | |  +|  |_|_|   |            SIZE: " << hs.size_of_h << endl;
    cout << "  |_|___|__________|            BEDROOMS: " << hs.num_bed << endl;
    cout << " ********************           AVAILABILITY: " << (hs.avilablity ? "Available" : "Not available") << endl;
    cout << endl;

}

void search(vector<house> &h)
{
    string city, subcity;
    int price, city_code, subcity_code;
    char choice;
    do
    {
        cout << "   Enter city name(use underscore instead of space): ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the buffer
        getline(cin, city);
        cout << "   Enter subcity name(use underscore instead of space): ";
         getline(cin, subcity);
        cout << "   Enter max price: ";
        cin >> price;

        // Clear the input buffer again before next getline
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

        city_code = get_city_code(city);
        subcity_code = get_subcity_code(city, subcity);
        bool x = true;
        cout << "Matching house/s ";
        for (int i = 0; i < h.size(); i++)
        {
            if (h[i].city_code == city_code && h[i].subcity_code == subcity_code && h[i].price <= price)
            {
                cout << endl;
                cout << " __________ " << endl;
                cout << "/__________\\" << "      City:  " << h[i].city << endl;
                cout << " | | | |_|| " << "      House type: " << h[i].house_type << endl;
                cout << " | |*|    | " << "      Price:  " << h[i].price << endl;
                cout << " ********** " << "      Availablity: " << (h[i].avilablity ? "Available" : "Not available") << endl;
                x = false;
            }
        }
        if (x)
        {
            cout << "are not available with your criteria" << endl;
        }
        cout << "Do you want to search again (y/n): ";
        cin >> choice;
        choice = tolower(choice);
    } while (choice == 'y');
}

void fetchHouses(vector<house> &hs)
{
    string query = "sqlcmd -S " + server + " -d " + database + " -U " + username + " -P " + password + " -Q \"SET NOCOUNT ON; SELECT id, city, city_code, subcity, subcity_code, house_type, price, size_of_h, num_bed, availability FROM house\"";
    array<char, 128> buffer;
    string result;
    unique_ptr<FILE, decltype(&pclose)> pipe(popen(query.c_str(), "r"), pclose);
    if (!pipe)
    {
        throw runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
    {
        result += buffer.data();
    }

    // Debug: Output the raw result string
    // cout << "Raw result: " << endl << result << endl;

    istringstream stream(result);
    string line;

    // Skip the first line which is the header
    getline(stream, line);

    while (getline(stream, line))
    {
        // Skip lines that are empty or contain just formatting
        if (line.empty() || line.find("---") != string::npos || line.find("rows affected") != string::npos)
            continue;

        house h;
        istringstream lineStream(line);

        // Assuming data is space-separated; adjust as necessary
        lineStream >> h.id >> h.city >> h.city_code >> h.subcity >> h.subcity_code >> h.house_type >> h.price >> h.size_of_h >> h.num_bed >> h.avilablity;

        // Debug: Output each parsed line
        // cout << "Parsed line: " << h.id << " " << h.city << " " << h.city_code << " " << h.subcity << " " << h.subcity_code << " " << h.house_type << " " << h.price << " " << h.size_of_h << " " << h.num_bed << " " << h.avilablity << endl;

        hs.push_back(h);
    }
}
void fetchBusinesses(vector<bussiness> &bs)
{
    string query = "sqlcmd -S " + server + " -d " + database + " -U " + username + " -P " + password + " -W -s\\t -Q \"SET NOCOUNT ON; SELECT ID, buss_name, name, password, city, phone_num FROM bussiness\"";
    array<char, 128> buffer;
    string result;
    unique_ptr<FILE, decltype(&pclose)> pipe(popen(query.c_str(), "r"), pclose);
    if (!pipe)
    {
        throw runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
    {
        result += buffer.data();
    }

    // cout << "Raw result: " << endl << result << endl; // Debug: Output the raw result string

    istringstream stream(result);
    string line;

    // Skip the first two lines which are headers and separators
    getline(stream, line); // Header line
    getline(stream, line); // Separator line

    while (getline(stream, line))
    {
        // Skip lines that are empty or contain just formatting
        if (line.empty() || line.find("---") != string::npos || line.find("rows affected") != string::npos)
            continue;

        // Replace backslashes with spaces
        replace(line.begin(), line.end(), '\\', ' ');

        bussiness b;
        istringstream lineStream(line);

        // Rest of your parsing logic...
        lineStream >> b.ID >> b.buss_name >> b.name >> b.password >> b.city >> b.phone_num;

        bs.push_back(b);
    }
}

void fetchPersonal(vector<personal> &ps)
{
    string server = "AKME\\SQLEXPRESS"; // Escape backslash
    string database = "projectccc";
    string username = "sa";
    string password = "abdulkerim444";

    string query = "sqlcmd -S " + server + " -d " + database + " -U " + username + " -P " + password + " -Q \"SET NOCOUNT ON; SELECT name, password, city FROM personal\"";
    array<char, 128> buffer;
    string result;
    unique_ptr<FILE, decltype(&pclose)> pipe(popen(query.c_str(), "r"), pclose);
    if (!pipe)
    {
        throw runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
    {
        result += buffer.data();
    }

    // Debug: Output the raw result string
    // cout << "Raw result: " << endl << result << endl;

    istringstream stream(result);
    string line;

    // Skip the first line which is the header
    getline(stream, line);

    while (getline(stream, line))
    {
        // Skip lines that are empty or contain just formatting
        if (line.empty() || line.find("---") != string::npos || line.find("rows affected") != string::npos)
            continue;

        personal p;
        istringstream lineStream(line);

        // Parsing logic depends on the delimiters used in the sqlcmd output, typically it's spaces
        lineStream >> p.name >> p.password >> p.city;

        // Debug: Output each parsed line
        // cout << "Parsed line: " << p.name << " " << p.password << " " << p.city << endl;

        ps.push_back(p);
    }
}

int main()
{
    int best_choises_forfeed[4];
    char choise[5]; // both variables used to accept values(int or char) when user chooses.
    int choose;
    char help_variable; // we will use it when we need a single character that will be used in many cases.
    vector<house> hs;
    vector<personal> p_i;
    vector<bussiness> b_i;
    string user_city_for_feed;

    // Fetch data from database
    fetchHouses(hs);
    fetchBusinesses(b_i);
    fetchPersonal(p_i);


first_page:
    cout<<endl;
    cout << "WELLCOME TO RENT AND CONNECT!!!" << endl;
    cout << "    1, LOGIN" << endl;
    cout << "    2, DON'T HAVE AN ACCOUNT? CREAT ONE." << endl;
    cout << "    3, EXIT" << endl;
    cout << "ENTER YOUR CHOISE: ";
    cin >> choise;
    while (error_handle(choise) == 0 /* 0 shows their is an error*/)
    {
    error_check1: // acts as a lable when error inputs come.
        cout << "please enter a valid input again" << endl;
        cin >> choise;
    }
    switch (choise[0])
    {
    case '1':
        int best_choises_forfeed[4];
        help_variable = login(hs, p_i, b_i, user_city_for_feed);
        if (help_variable == 'p')
        {
        customer_home_page:
            cout << "----------------------------------------------- " <<endl;
            cout << "               CUSTOMER HOME PAGE               " <<endl;
            cout << "----------------------------------------------- " <<endl;
            display_best_choise(hs, user_city_for_feed, best_choises_forfeed);
            cout << "    1, CHOOSE FROM THIS HOUSES" << endl;
            cout << "    2, SEARCH BY( CITY(use underscore instead of space),ADDRESS(SUBCITY use underscore instead of space),HOUSE TYPE,PRICE RANGE)." << endl;
            cout << "    3, EXIT" << endl;
            cout << "ENTER YOUR CHOISE: ";
            cin >> choise;
            while (error_handle(choise) == 0 /* 0 shows their is an error*/)
            {
            error_check2: // acts as a lable when error inputs come.
                cout << "please enter a valid input again" << endl;
                cin >> choise;
            };
            switch (choise[0])
            {
            case '1':
                cout << "Which house? (1,2,3 or 4) based on the order: " ;
                cin >> choose;
                choose = best_choises_forfeed[choose - 1]; // best choice for feed contain the index of the house which the person lives in
                view_more(hs, choose);
                cout<< "PRESS 1, exit  "<<endl;
                cout<< "      2, continue exploring"<<endl;
                cout<< "ENTER YOUR CHOISE: ";
                cin>>choose;
                if (choose==1){return 0;}
                 goto customer_home_page;
                break;
            case '2':
                search(hs);
                // goto customer_home_page;
                break;
            case '3':
                return 0;
                break;
            default:
                goto error_check2;
                break;
            }
        }
        else if (help_variable == 'b')
        {
        business_home_page:
            cout << "----------------------------------------------- " <<endl;
            cout << "                BUSINESS HOME PAGE              " <<endl;
            cout << "----------------------------------------------- " <<endl;
            cout << "    1. Add house" << endl;
            cout << "    2. Update information about your hourse" << endl;
            cout << "    3. Back to first page" << endl;
            cout << "    4. Exit" << endl;
            cout << "Enter your choise: ";
            cin >> choise;
            while (error_handle(choise) == 0 /* 0 shows their is an error*/)
            {
            error_check3: // acts as a lable when error inputs come.
                cout << "please enter a valid input again" << endl;
                cin >> choise;
            };
            switch (choise[0])
            {
            case '1':
                Add_house(hs);
                goto business_home_page;
                break;
            case '2':
                Update_house_information(hs);
                goto business_home_page;
                break;
            case '3':
                goto first_page;
                break;
            case '4':
                return 0;
            default:
                goto error_check3;
                break;
            }
        }
        else if (help_variable == 'c')
        {
            creat_account(p_i, b_i);
        }
        break;
    case '2':
        creat_account(p_i, b_i);
        break;
    case '3':
        return 0;
        break;
    default:
        goto error_check1;
        break;
    }
    goto first_page;
    return 0;
}
