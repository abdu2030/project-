#include <iostream>
using namespace std;
int main() {
 char lowercaseChar, uppercaseChar, x,y;
    int  n=0,b=0,a=1;
    label:
    cout << "Enter the letter: ";
    cin >> x;
    x = toupper(x);
    y=x;
    if(y=='A'||isdigit(y)||!isalpha(y) && !isdigit(y) ){
        cout<<"invalid input\n\n----------------------\nplease enter the letter b-z/B-Z \n"<<endl;
        goto label;
       
    }
    for (char i = 'A'; i < y; i++)
    {
        for (char j = 'A'; j <=(y-n); j++) 
        {
            cout << j << " ";
        }
         for (int j = 0; j < n ; j++)
        {
            cout<<"  ";
        }
        for (int j = 0; j < (n-1); j++)
        {
            cout<<"  ";
        }
        for (char k = (y-b); k >='A'; k--)
        {
             if(k!=y)
            cout<<k<<" ";
        }
          cout << "\n";
          n++;
          b++;
    }
    for ( char i = 'A'; i <=y; i++)
    {
        for (char j = 'A'; j <= i; j++)
        { 
           cout<<j<<" ";
        }
        for ( char k = 'A'; k <(y-a); k++)
        { 
            cout<<"  ";
        }
         for ( char k = 'A'; k <=(y-a); k++)
        {
            cout<<"  ";
         }
        for ( char j = i; j >='A'; j--)
        {
            if(j!=y)
            cout<<j<<" ";
        }
        cout<<"\n";
        a++;
        
    }
    return 0;
}
