/***************************************************************
 Author: Charbel Boutros
 File Name: parse.h
 ***************************************************************/
#ifndef _parse_h
#define _parse_h

/* Define constants */
/**
 * MAXARGS the maximum number of arguments for the argumentVector array
 */
#define MAXARGS 32

/**
 * MAXSTRING the maximum length of user entered string
 */
#define MAXSTRING 150

typedef struct PARAM
{
	char *inputRedirect;
	char *outputRedirect;
	int background;
	int argumentCount;
	char *argumentVector[MAXARGS];
}*ParamP;

void input(ParamP, char[]);
void parse(ParamP,char[]);
void handleInRedir(ParamP, char*);
void handleOutRedir(ParamP, char*);
void handleSpace(ParamP, char*, char[]);
void handleBlank(ParamP, char[]);
void handleAmpersand(ParamP, char[]);
void reset(ParamP);

#endif
