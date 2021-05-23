#include <iostream>  // for debugging
#include "spreader.h"
#include "BinaryHeap.h"
using namespace std;

Spreader::Spreader(const Person *people, int population)
{
   people2 = new Person2[population];
   for(int i=0; i<population; i++){
   	people2[i].ID =people[i].ID;
   	people2[i].peopleMet=people[i].peopleMet;
   	people2[i].visitors = new Visitor[people[i].peopleMet]; 
   	for(int j=0;j<people[i].peopleMet;j++) {
   		people2[i].visitors[j]= people[i].visitors[j];
   	}  


   }


  // Students write this. 
  // Note that people will be deleted before simulate() is called.
} // Spreader()
int Spreader::simulate(int starterIDs[], int starterCount, int commandLineOption)
{
	BinaryHeap <Person2> heap (1000000);
	for (int i = 0; i<starterCount; i++){
		people2[starterIDs[i]].dv = 0;
		heap.insert(people2[starterIDs[i]]);
	}
        int tempID, adjID, adjPer, popoff, diff, tempDv, formula;
	popoff = 0;
	while (!heap.isEmpty()){
		tempID = heap.findMin().ID;
		heap.deleteMin();
		if(people2[tempID].isKnown == false){
			for(int i = 0; i < people2[tempID].peopleMet; i++){
				adjID = people2[tempID].visitors[i].ID;
				adjPer = people2[tempID].visitors[i].period;
				if(people2[adjID].isKnown == false){
					if (popoff < starterCount){
						tempDv = adjPer;
					}
					else{
						formula = ((adjPer - people2[tempID].dv) % adjPer);
						if (formula < 0)
							formula += adjPer;
						tempDv = people2[tempID].dv + formula;
					}
					diff = tempDv - people2[tempID].dv;
					if(diff < 3){
						while (diff < 3){
							tempDv += adjPer;
							 diff = tempDv - people2[tempID].dv;
						}
					}
					if(people2[adjID].dv > tempDv){
					       people2[adjID].dv = tempDv; 
					       heap.insert(people2[adjID]);
                                        }				
				}
			}
			people2[tempID].isKnown = true;
			popoff ++;
			//cout << "Infected count: " << popoff << " day: " << people2[tempID].dv << " ID: " << tempID << endl;
		}
	}
	return people2[tempID].dv; 

  // commandLineOption may be used to signal the program to do whatever the students 
  // want, or nothing at all.
  // return 0;
  // Students write this.  Returns days until of last person catches the virus
}

