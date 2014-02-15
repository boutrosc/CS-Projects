/***************************************************************
 Author: Charbel Boutros
 File Name: parse.c
 ***************************************************************/

//include standard libraries
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "parse.h"

/** 
 * Input function takes input from the user.
 * @param param pointer to the PARAM struct
 */
void input(ParamP param, char userIn[]) {
	reset(param);
	printf("$ ");
	fgets(userIn, MAXSTRING, stdin); //get input from user
	parse(param, userIn);
}

/**
 * Parse function parses the user input and stores the results in the PARAM struct.
 * @param param pointer to the PARAM struct
 * @param input char array that contains the user input
 */
void parse(ParamP param, char userIn[]) {
	//check if user only hit enter with no tokens
	handleBlank(param, userIn);
	char *parser = strtok(userIn, " \t\n");
	while (parser != NULL) {
		if (!strncmp(parser, "<", 1) || !strncmp(parser, ">", 1)) //check for redirects
				{
			handleSpace(param, parser, userIn);
			handleInRedir(param, parser);
			parser = strtok(NULL, " \t\n");
		} else //add tokens to argumentVector array
		{
			param->argumentVector[param->argumentCount] = parser;
			param->argumentCount++;
			parser = strtok(NULL, " \t\n");
		}
	}
	handleAmpersand(param, userIn);
}

/**
 * Handles blank input
 * @param param pointer to the PARAM struct
 * @param userIn[] char array containing the user input
 */
void handleBlank(ParamP param, char userIn[]) {
	if (*userIn == 10) {
		input(param, userIn);
	}
}

/**
 * Handles input redirect
 * @param param pointer to the PARAM struct
 * @param parser contains the user input
 */
void handleInRedir(ParamP param, char *parser) {
	if (!strncmp(parser, "<", 1)) {
		memmove(&parser[0], &parser[0 + 1], strlen(parser) - 0);
		param->inputRedirect = strdup(parser);
		strcpy(param->inputRedirect, parser);
	} else
		handleOutRedir(param, parser);
}

/**
 * Handles output redirect
 * @param param pointer to the PARAM struct
 * @param parser contains the user input
 */
void handleOutRedir(ParamP param, char *parser) {
	memmove(&parser[0], &parser[0 + 1], strlen(parser) - 0);
	param->outputRedirect = strdup(parser);
	strcpy(param->outputRedirect, parser);
}

/**
 * Checks if space is placed after redirect
 * @param param pointer to the PARAM struct
 * @param parser contains the user input
 */
void handleSpace(ParamP param, char *parser, char userIn[]) {
	if (!strcmp(parser, "<") || !strcmp(parser, ">")) {
		printf("Spaces not allowed following the redirect indicator!\n");
		input(param, userIn);
	}

}

/**
 * Checks if ampersand is used properly
 * @param param pointer to the PARAM struct
 */
void handleAmpersand(ParamP param, char userIn[]) {
	if (param->argumentCount) {
		if (!strncmp(param->argumentVector[param->argumentCount - 1], "&", 1)
				&& strlen(param->argumentVector[param->argumentCount - 1]) <= 2) //check for Ampersand
						{
			param->background = 1;
			param->argumentCount--;
			param->argumentVector[param->argumentCount] = '\0'; //overwrite & so it is not in the argumentVector
		}
	}
	int i;
	for (i = 0; i < param->argumentCount; i++) {
		if (!strncmp(param->argumentVector[i], "&", 1)
				&& strlen(param->argumentVector[i]) < 2) {
			printf("Ampersand (&) must be last character in string!\n");
			input(param, userIn);
			break;
		}
	}
}

/**
 * Clears struct array
 * @param param pointer to the PARAM struct
 */
void reset(ParamP param) {
	param->argumentCount = 0;
	param->inputRedirect = NULL;
	param->outputRedirect = NULL;
	memset(param->argumentVector, 0, sizeof param->argumentVector);
}
