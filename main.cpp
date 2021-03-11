#include <iostream>
#include <memory>
#include <vector>
#include "RandomNumberGenerator.h"
#include "Zadania.hpp"
using namespace std;
void AddTasksParametrs(RandomNumberGenerator Random_2, shared_ptr <Task[]> Tasks_1, int size_1);
int ObjectiveFunction(shared_ptr <Task[]> Tasks_1, shared_ptr <int []> TabOrder, int size_1);
int LookforMinR(vector<Task> TaskVector);
int LookforMaxH(vector<Task> TaskVector);
void ShowInformation(shared_ptr <Task[]> Tasks_1, shared_ptr <int []> TabOrder, int size_1);
shared_ptr <int []>  SchrageAlgorithm(shared_ptr <Task[]> Tasks_1, shared_ptr <int []> TabOrder, int size_1);



int main(){

    auto i{0}, Number{0}, SeedValue{0};


    cout << "Podaj ilość zadań:  " ;
    cin >> Number;
    cout << endl << "Podaj źródło:  ";
    cin >> SeedValue;

    RandomNumberGenerator Random_1(SeedValue);
    shared_ptr <Task[]> TaskTab(new Task[Number]);
    shared_ptr <int []> TabOrder(new int[Number]);
    
    
    for(i=0; i<Number; i++)
        TabOrder[i]=i;

    AddTasksParametrs(Random_1, TaskTab, Number);
    auto Cmaxx=ObjectiveFunction(TaskTab,TabOrder,Number);
    ShowInformation(TaskTab,TabOrder,Number);
    cout << endl << endl << "Cmax:  " << Cmaxx << endl;
    TabOrder=SchrageAlgorithm(TaskTab,TabOrder,Number);
    Cmaxx=ObjectiveFunction(TaskTab,TabOrder,Number);
    ShowInformation(TaskTab,TabOrder,Number);
    cout << endl << endl << "Cmax:  " << Cmaxx << endl;

    cout <<endl;
    return 0;
}



void AddTasksParametrs(RandomNumberGenerator Random_2, shared_ptr <Task[]> Tasks_1, int size_1)
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
        Tasks_1[i].AddTHandober(Random_2.nextInt(1,A));
    }
}

int ObjectiveFunction(shared_ptr <Task[]> Tasks_1, shared_ptr <int []> TabOrder_1, int size_1){
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


void ShowInformation(shared_ptr <Task[]> TaskTab, shared_ptr <int []> TabOrder, int size_1){
    auto i{0};
        cout << "ID:  ";
    for ( i=0; i<size_1; i++){
        cout << TaskTab[TabOrder[i]].ShowValueOfVariable('I') << " | ";
    }

    cout << endl << "r:  ";
    for ( i=0; i<size_1; i++){
        cout << TaskTab[TabOrder[i]].ShowValueOfVariable('P') << " | ";
    }

    cout << endl << "p:  ";
    for ( i=0; i<size_1; i++){
        cout << TaskTab[TabOrder[i]].ShowValueOfVariable('E') << " | ";
    }

    cout << endl << "q:  ";
    for ( i=0; i<size_1; i++){
        cout << TaskTab[TabOrder[i]].ShowValueOfVariable('H') << " | ";
    }

    cout << endl << "S:  ";
    for ( i=0; i<size_1; i++){
        cout << TaskTab[TabOrder[i]].ShowValueOfVariable('M') << " | ";
    }

    cout << endl << "C:  ";
    for ( i=0; i<size_1; i++){
        cout << TaskTab[TabOrder[i]].ShowValueOfVariable('T') << " | ";
    }

    cout << endl << "C+q:  ";
    for ( i=0; i<size_1; i++){
        cout << TaskTab[TabOrder[i]].ShowValueOfVariable('T')+TaskTab[TabOrder[i]].ShowValueOfVariable('H') << " | ";
    }

}


shared_ptr <int []>  SchrageAlgorithm(shared_ptr <Task[]> Tasks_1, shared_ptr <int []> TabOrder, int size_1){

    auto k{0}, t{0}, i{1}, rmin{0},j{0};
    vector <Task> Gset;
    vector <Task> Nset;
    
    
    for (i=0; i<size_1; i++){
        Nset.push_back(Tasks_1[i]);
    }


    
    t=Nset[LookforMinR(Nset)].ShowValueOfVariable('P');
    

    while(Gset.size()!=0 || Nset.size()!=0){
        while( Nset.size()!=0 && Nset[LookforMinR(Nset)].ShowValueOfVariable('P')<=t){
            j=LookforMinR(Nset);
            Gset.push_back(Nset[j]);
            Nset.erase(Nset.begin()+j);
        }
        if(Gset.size()!=0){
            j=LookforMaxH(Gset);
            TabOrder[k]=Gset[j].ShowValueOfVariable('I')-1;
            t+=Gset[j].ShowValueOfVariable('E');
            Gset.erase(Gset.begin()+j);
            k+=1;
        }
        else{
            t=Nset[LookforMinR(Nset)].ShowValueOfVariable('P');
        }

    }


    return TabOrder;

}


int LookforMinR(vector<Task> TaskVector){
    auto i{0}, minValue{0},x{0};
    minValue=TaskVector[0].ShowValueOfVariable('P');
    for(i=0; i<TaskVector.size(); i++)
       minValue = min(minValue,TaskVector[i].ShowValueOfVariable('P'));

    for(i=0; i<TaskVector.size(); i++){
        if(TaskVector[i].ShowValueOfVariable('P')==minValue){
            x=i;
            break;
        }
            
    }

    return x;
}

int LookforMaxH(vector<Task> TaskVector){
    auto i{0}, maxValue{0},x{0};
    maxValue=TaskVector[0].ShowValueOfVariable('H');
    for(i=1; i<TaskVector.size(); i++)
       maxValue = max(maxValue ,TaskVector[i].ShowValueOfVariable('H'));

    for(i=0; i<TaskVector.size(); i++){
        if(TaskVector[i].ShowValueOfVariable('H')==maxValue){
            x=i;
            break;
        }
    }

    return x;
}