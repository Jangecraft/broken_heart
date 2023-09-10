#include <iostream>

using namespace std;

int main(){
    int scroe;
    cout << "input scroe : ";
    cin >> scroe;

    if (scroe >= 80){
        cout << "grade A";
    }
    else if (scroe >= 70){
        cout << "grade B";
    }
    else if (scroe >= 60){
        cout << "grade C";
    }
    else if (scroe >= 50){
        cout << "grade D";
    }
    else{
        cout << "grade F";
    }

    return 0;
}