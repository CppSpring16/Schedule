//
//  main.cpp
//  ScheduleSorter
//
//  Created by Kimberly Price on 3/12/16.
//  Copyright © 2016 Kimberly Price. All rights reserved.
//

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class Schedule{
private:
    string classSched[14][5];
    bool isOccupied[14][5];
    string incl[5];
    string notIncl[5];
    int numCredits = 0;
    int numCourses = 0;
    int attemptCourses = 0;
    
public:
    Schedule(){
        for (int i = 0; i<14; i++){
            for (int j=0; j<5; j++){
                classSched[i][j] = "";
                isOccupied[i][j] = false;
                incl[j] = "";
                notIncl[j] = "";
            }
        }
    }
    void addClass(string name, int day[7], int period[7], int credits){
        //check if all meet times fit in schedule, if not add to notIncl, if they do, add to classSched
        attemptCourses++;
        //first go through and see if there is a conflict with the meeting times
        //if so add to the notIncl list and return
        for (int i = 0; i < 7; i++){
            if (period[i] == -1)    //array will have -1 as values for any unneeded spots
                break;
            if (isOccupied[period[i]][day[i]]){
                cout << "Conflict! Cannot add class."<< endl; //for testing purposes, will remove
                notIncl[attemptCourses-numCourses-1] = name;
                return;
            }
        }
        //This will go through an update the schedule with the new course
        int i = 0;
        while(period[i]!=-1){
            classSched[period[i]][day[i]] = name;
            isOccupied[period[i]][day[i]] = true;
            i++;
        }
        incl[numCourses++] = name;
        numCredits += credits;
        
    }

    void displaySched(){
        cout << "\n" << setw(10) << "Monday" << setw(10) << "Tuesday" << setw(10) <<  "Wednesday" << setw(10)<< "Thursday" << setw(10)<< "Friday";
        cout << "\n_____________________________________________________________"<<endl;
        for (int i = 0; i<14; i++){
            cout << "|";
            for (int j=0; j<5; j++){
                cout << setw(10) << classSched[i][j] << " |";   //need to format
            }
            cout << "\n_____________________________________________________________"<<endl;
        }
        cout << "\nTotal credits: " << numCredits;
        cout << "\n\nCourses included: ";
        for (int i = 0; i<5; i++)
            cout << incl[i] << " ";
        cout << "\n\nCourses not included: ";
        for (int i = 0; i<5; i++)
            cout << notIncl[i] << " ";
    }

};

int main(int argc, const char * argv[]) {
    int bioD[7] ={0,2,4,-1,-1,-1,-1};
    int bioP[7] = {2,2,2,-1,-1,-1,-1};
    int chemD[7] = {1,1,3,-1,-1,-1,-1};
    int chemP[7] = {2,3,2,-1,-1,-1,-1};
    int calcD[7] = {0,2,4,-1,-1,-1,-1};
    int calcP[7] = {4,4,4,-1,-1,-1,-1};
    int engD[7] = {0,2,4,-1,-1,-1,-1};
    int engP[7] = {3,3,3,-1,-1,-1,-1};
    int labD[7] = {3,3,3,-1,-1,-1,-1};
    int labP[7] = {3,4,5,-1,-1,-1,-1};
    int poopD[7] = {1,1,3,3,-1,-1,-1};
    int poopP[7] = {4,5,4,5,-1,-1,-1};
    Schedule sched;
    sched.addClass("Biology", bioD,bioP,3);
    sched.addClass("Chemistry", chemD, chemP,3);
    sched.addClass("Calculus", calcD, calcP, 3);
    sched.addClass("English", engD, engP, 3);
    sched.addClass("Chem Lab", labD, labP, 1);
    sched.addClass("Poop", poopD, poopP, 4); //Testing class that will not fit the schedule
    sched.displaySched();
    
    return 0;
}