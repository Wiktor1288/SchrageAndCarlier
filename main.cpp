#include <iostream>
#include <memory>
#include "RandomNumberGenerator.h"
#include "Zadania.hpp"
using namespace std;
void AddTasksParametrs(RandomNumberGenerator Random_2, unique_ptr <Task[]> &Tasks_1, int size_1);
int ObjectiveFunction(unique_ptr <Task[]> &Tasks_1, unique_ptr <int []> &TabOrder, int size_1);
int main(){

    auto i{0}, Number{0}, SeedValue{0};


    cout << "Podaj ilość zadań:  " ;
    cin >> Number;
    cout << endl << "Podaj źródło:  ";
    cin >> SeedValue;

    RandomNumberGenerator Random_1(SeedValue);
    unique_ptr <Task[]> TaskTab(new Task[Number]);
    unique_ptr <int []> TabOrder(new int[Number]);
    
    for(i=0; i<Number; i++)
        TabOrder[i]=i;

    AddTasksParametrs(Random_1, TaskTab, Number);
    auto Cmaxx=ObjectiveFunction(TaskTab,TabOrder,Number);

    cout << "ID:  ";
    for ( i=0; i<Number; i++){
        cout << TaskTab[TabOrder[i]].ShowValueOfVariable('I') << " | ";
    }

    cout << endl << "r:  ";
    for ( i=0; i<Number; i++){
        cout << TaskTab[TabOrder[i]].ShowValueOfVariable('P') << " | ";
    }

    cout << endl << "p:  ";
    for ( i=0; i<Number; i++){
        cout << TaskTab[TabOrder[i]].ShowValueOfVariable('E') << " | ";
    }

    cout << endl << "q:  ";
    for ( i=0; i<Number; i++){
        cout << TaskTab[TabOrder[i]].ShowValueOfVariable('H') << " | ";
    }

    cout << endl << "S:  ";
    for ( i=0; i<Number; i++){
        cout << TaskTab[TabOrder[i]].ShowValueOfVariable('M') << " | ";
    }

    cout << endl << "C:  ";
    for ( i=0; i<Number; i++){
        cout << TaskTab[TabOrder[i]].ShowValueOfVariable('T') << " | ";
    }

    cout << endl << "C+q:  ";
    for ( i=0; i<Number; i++){
        cout << TaskTab[TabOrder[i]].ShowValueOfVariable('T')+TaskTab[TabOrder[i]].ShowValueOfVariable('H') << " | ";
    }

    cout << endl << Cmaxx;
    
    
    







    return 0;
}



void AddTasksParametrs(RandomNumberGenerator Random_2, unique_ptr <Task[]> &Tasks_1, int size_1)
{
    auto i{0}, A{0}, X{29};

    for ( i = 0; i < size_1; i++){
        Tasks_1[i].AddTExecution(Random_2.nextInt(1,29));
        A=A+Tasks_1[i].ShowValueOfVariable('E');
    }
    
    for ( i = 0; i < size_1; i++){
        Tasks_1[i].AddTPripare(Random_2.nextInt(1,A));
    }
    for ( i = 0; i < size_1; i++){
        Tasks_1[i].AddTHandober(Random_2.nextInt(1,X));
    }
}

int ObjectiveFunction(unique_ptr <Task[]> &Tasks_1, unique_ptr <int []> &TabOrder_1, int size_1){
    auto i{0}, Cmax{0};

    Tasks_1[TabOrder_1[0]].AddStartMoment(Tasks_1[TabOrder_1[0]].ShowValueOfVariable('P'));
    Tasks_1[TabOrder_1[0]].AddTermiantion();
    Cmax=Tasks_1[TabOrder_1[0]].ShowValueOfVariable('T')+Tasks_1[TabOrder_1[0]].ShowValueOfVariable('H');
    for(i=1; i<size_1; i++){
        Tasks_1[TabOrder_1[i]].AddStartMoment(max(Tasks_1[TabOrder_1[0]].ShowValueOfVariable('P'), Tasks_1[TabOrder_1[i-1]].ShowValueOfVariable('T')));
        Tasks_1[TabOrder_1[i]].AddTermiantion();
        Cmax=max(Cmax,Tasks_1[TabOrder_1[i]].ShowValueOfVariable('T')+Tasks_1[TabOrder_1[i]].ShowValueOfVariable('H'));
    }

    return Cmax;
}
