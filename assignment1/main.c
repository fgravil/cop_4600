#include <stdio.h>
#include <stdlib.h>

struct Process
{
	char name[10];
	int arrival;
	int burst;
	int wait;
	int turnaround;
};

void printProcesses(struct Process *processes, int processCnt);
void fcfs(struct Process *processes, int processCnt, int runFor);
void orderByArrival(struct Process *processes, int processCnt);

int main(){

	int processCnt, runFor, i;
	char word[20], algorithm[10];
	char line [256];

	FILE *file;
	file = fopen("processes.in","r");

	if(file){
			
		fscanf(file, "%s", word);
		fscanf(file, "%d", &processCnt);

		struct Process processes[processCnt];

		//skips comments
		fgets(line, sizeof(line), file);

		fscanf(file, "%s", word);
		fscanf(file, "%d", &runFor);
		
		//skips comments
		fgets(line, sizeof(line), file);

		fscanf(file,"%s", word);
		fscanf(file, "%s", algorithm);
		
		//skips comments
		fgets(line, sizeof(line), file);

		for(i = 0; i < processCnt; i++){
			fscanf(file, "%s", word); //process
			fscanf(file, "%s", word); //name
			fscanf(file, "%s", processes[i].name);
			
			fscanf(file, "%s", word); //arrival
			fscanf(file, "%d", &processes[i].arrival);

			fscanf(file, "%s", word); //burst
			fscanf(file, "%d", &processes[i].burst);
		}

		orderByArrival(processes, processCnt);
		
		if(strcmp(algorithm, "fcfs") == 0){
			fcfs(processes, processCnt, runFor);
		}
		else if(strcmp(algorithm, "sjf") == 0){
			//execute sjf function
		}
		else if(strcmp(algorithm, "rr") == 0){
			//execute rr function
		}

		fclose(file);
	}

	
}

void printProcesses(struct Process *processes, int processCnt){
	int i = 0;
	for(i = 0; i < processCnt; i++){
		printf("Process %s\n", processes[i].name);
		printf("Arrival: %d\n", processes[i].arrival);
		printf("Burst: %d\n\n", processes[i].burst);
	}
}

void fcfs(struct Process *processes, int processCnt, int runFor){
	int i, selectedTime = 0, completionTime = 0, waitTime = 0, turnaroundTime = 0;

	printf("%d processes\n", processCnt);
	printf("Using First Come First Serve\n\n");

	for(i = 0; i < processCnt; i++){
		completionTime = selectedTime + processes[i].burst;

		printf("Time %d: %s arrived\n", processes[i].arrival, processes[i].name);
		printf("Time %d: %s selected (burst %d)\n", selectedTime, processes[i].name, processes[i].burst);
		printf("Time %d: %s finished\n", completionTime, processes[i].name);	

		//if the last process is finished before the arrival of the next
		if((i+1) != processCnt && completionTime < processes[i+1]. arrival){
			printf("Time %d: Idle\n", completionTime);
		}
		//If all processes are finished before the full completion time
		else if((i+1) == processCnt && (runFor - completionTime) > 0){
			printf("Time %d: Idle\n", completionTime);
		}

		processes[i].turnaround = completionTime - processes[i].arrival;
		processes[i].wait = processes[i].turnaround - processes[i].burst;

		selectedTime += processes[i].burst;

	}

	printf("Finished at time %d\n\n", runFor);

	for(i = 0; i < processCnt; i++){
		printf("%s wait %d turnaround %d\n", processes[i].name, processes[i].wait, processes[i].turnaround);
	}

}

void orderByArrival(struct Process *processes, int processCnt){
	int i, j;

	for(i = 0; i < processCnt - 1; i++)
		for(j = 0; j < processCnt - i - 1; j++){
			int arrival1 = processes[j].arrival;
			int arrival2 = processes[j+1].arrival;

			if(arrival1 > arrival2){
				struct Process temp = processes[j];
				processes[j] = processes[j+1];
				processes[j+1] = temp;
			}
		}
}

