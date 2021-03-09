#include <iostream>
#include <memory>
#include "RandomNumberGenerator.h"
#include "Zadania.hpp"
using namespace std;
void AddTasksParametrs(RandomNumberGenerator Random_2, Task *Tasks_1);
int main(){

    auto i{0}, Number{0}, SeedValue{0};


    cout << "Podaj ilość zadań:  " ;
    cin >> Number;
    cout << endl << "Podaj źródło:  ";
    cin >> SeedValue;

    RandomNumberGenerator Random_1(SeedValue);
    unique_ptr <Task[]> TaskTab(new Task[Number]);







    return 0;
}



void AddTasksParametrs(RandomNumberGenerator Random_2, Task *Tasks_1)
{

    
}