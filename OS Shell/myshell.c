/***************************************************************
 Author: Charbel Boutros
 File Name: myshell.c
 ***************************************************************/

//include standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "parse.h"

/*Struct declaration*/
typedef struct PidS {
	int pidCount;
	int pidVector[MAXARGS];
}*PidP;

/* Function declarations */
void init(ParamP, PidP);
void shell(ParamP, PidP);
void handleRW(ParamP);
void handleExecvp(ParamP);
void handleZombies(PidP);



int main() {
	ParamP param = malloc(sizeof(struct PARAM));
	PidP pidList = malloc(sizeof(struct PidS));
	pidList->pidCount = 0;
	param->background = 0;
	param->argumentCount = 0;
	init(param, pidList);
	free(param);
	free(pidList);
	return 0;
}

/**
 * Intializes shell program
 * @param param pointer to the PARAM struct
 * @param pidP pointer to the PID struct
 */
void init(ParamP param, PidP pidList) {
	char userIn[MAXSTRING] = { 0 };
	while (strcmp(userIn, "exit") != 0) {
		input(param, userIn);
		shell(param, pidList);
	}
	handleZombies(pidList);
}

/**
 * Shell implementation using fork and execvp
 * @param param pointer to the PARAM struct
 * @param pidP pointer to the PID struct
 */
void shell(ParamP param, PidP pidList) {
	pid_t pid = fork();
	if (pid) //parent code
	{
		if (param->background == 1) {
			pidList->pidVector[pidList->pidCount] = pid;
			pidList->pidCount++;
			return;
		} else {
			waitpid(pid, NULL, 0);
		}
	} else //child code
	{
		handleRW(param);
		handleExecvp(param);
	}
}

/**
 * Handles read/write operations
 * @param param pointer to the PARAM struct
 */
void handleRW(ParamP param) {
	if (param->outputRedirect != NULL) {
		freopen(param->outputRedirect, "w", stdout);
	}
	if (param->inputRedirect != NULL) {
		freopen(param->inputRedirect, "r", stdin);
	}
}

/**
 * Error handler for execvp
 * @param param pointer to the PARAM struct
 */
void handleExecvp(ParamP param) {
	if (execvp(param->argumentVector[0], param->argumentVector) == -1) {
		if (strcmp(param->argumentVector[0], "exit") != 0)
			fprintf(stderr, "Command not found\n");
		exit(EXIT_FAILURE);

	} else
		execvp(param->argumentVector[0], param->argumentVector);
	fclose(stdin);
	fclose(stdout);
}

/**
 * Handles zombie processes
 * @param pidP pointer to the PID struct
 */
void handleZombies(PidP pidList){
	int i;
	for (i = 0; i < pidList->pidCount; i++) {
		int status;
		while (waitpid(pidList->pidVector[i], &status, 0) == -1);
	}
}
