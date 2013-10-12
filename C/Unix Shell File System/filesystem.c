/*************************************************************** 
  Student Name: Charbel Boutros 
  File Name: filesystem.c
***************************************************************/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/********************************************
 *Used for files or directories
 *Contains pointer to parent, left sibling,
  right sibling, and child nodes. Info node 
  is used for names
 ******************************************/
typedef struct Node
{
	struct Node *parent;
	struct Node *siblingL;
	struct Node *siblingR;
	struct Node *child;
	char info[100];
}*NodeP;

/********************************************
 *Used for current position node
*******************************************/
typedef struct List
{
	struct Node *current;
}*ListP;

/********************************************
*Function prototypes
*******************************************/
void ls(ListP);
void add(ListP, NodeP, char[]);
void mv(ListP, char[], char[]);
void rm(ListP, char[]);
void cd(ListP, char[], char[]);
void cddot(ListP, NodeP, char[]);
void whereis(ListP, NodeP, char[], char[]);
void whereisRec(ListP, char[], char[]);

int main()
{
	ListP list = malloc(sizeof(struct List));
	NodeP rootNode = malloc(sizeof(struct Node));
	NodeP tempNode = malloc(sizeof(struct Node));
	rootNode->parent = NULL;
	rootNode->siblingL = NULL;
	rootNode->siblingR = NULL;
	rootNode->child = tempNode;
	tempNode->parent = rootNode;
	tempNode->siblingL = NULL;
	tempNode->siblingR = NULL;
	tempNode->child = NULL;
	strcpy(tempNode->info, " ");
	list->current= tempNode;
	strcpy(rootNode->info, "boutros/root");
	char pwd[200];
	memset (pwd,'\0',200);
	strcat(pwd, rootNode->info);
	char input[80], param1[7], param2[60], param3[60], *a, *b, *c;
	top: 
	memset (input,'\0',80);
	printf("$ ");
	fgets (input , 80 , stdin);
	a = strtok(input, " ");
	b = strtok (NULL, " ");
	c = strtok (NULL, " ");
	strcpy(param1, a);
	if (strlen(param1) == 1) goto top;
	if (b != NULL) strcpy(param2, b);
	if (c != NULL) strcpy(param3, c);
	if (!strcmp(param1, "ls\n") || !strcmp(param1, "ls") && strlen(param2) == 6 && strlen(param3) < 1) ls(list);
	else if (strcmp(param1, "mkdir") == 0 || strcmp(param1, "mkdir") == 10 && strlen(param2) > 1 && strlen(param3) < 1) add(list, rootNode, param2);
	else if (!strcmp(param1, "cd"))
	{
		if (!strcmp(param2, "..\n")) cddot(list, rootNode, pwd);
		else cd(list, param2, pwd);
	}
	else if (!strcmp(param1, "pwd\n")) printf("%s\n", pwd);
	else if (strcmp(param1, "addf") == 0 || strcmp(param1, "addf") == 10 && strlen(param2) > 1 && strlen(param3) < 1) add(list, rootNode, param2);
	else if (strcmp(param1, "mv") == 0 || strcmp(param1, "mv") == 10 && strlen(param2) && strlen(param3) > 0) mv(list, param2, param3);
	else if (strcmp(param1, "rm") == 0 || strcmp(param1, "rm") == 10 && strlen(param2) > 1 && strlen(param3) < 1) rm(list, param2);
	else if (strcmp(param1, "whereis") == 0 || strcmp(param1, "whereis") == 10 && strlen(param2) > 1 && strlen(param3) < 1) whereis(list, rootNode, param2, pwd);
	else if (strcmp(param1, "bye\n") == 0 || !strcmp(param1, "bye") == 10 && strlen(param2) == 6 && strlen(param3) < 1) return 0;
	goto top;
	return 0;
}

/**********************************************************
*Lists all files contained in the current directory
*Parameter (ListP) list contains current file or directory
**********************************************************/
void ls(ListP list)
{
	while (list->current->siblingL != NULL)
	{
		list->current = list->current->siblingL;
	}
	while (list->current->siblingR != NULL)
	{
		if (list->current->child == NULL) printf("F %s", list->current->info);
		else if (!strcmp(list->current->child->info, " ")) printf("F %s", list->current->info);
		else printf("D %s", list->current->info);
		list->current = list->current->siblingR;
	}
	if (!strcmp(list->current->info, " "))return;
	else if (list->current->child == NULL) printf("F %s", list->current->info);
	else if (!strcmp(list->current->child->info, " ")) printf("F %s", list->current->info);
	else printf("D %s", list->current->info);
	return;
}

/***************************************************************
*Adds a file or directory to the current directory
*Paramater (ListP list) contains current file or direct
*Parameter (NodeP rootNode) contains root of file system
*Paramater (Char param2) contains users input for the file name
***************************************************************/
void add(ListP list, NodeP rootNode, char param2[60])
{
	if (!strcmp(list->current->info, " "))
		{
		NodeP newNode = malloc(sizeof(struct Node));
		newNode->parent = list->current->parent;
		newNode->siblingL = NULL;
		newNode->siblingR = NULL;
		newNode->child = NULL;
		strcpy(newNode->info, param2);
		list->current->parent->child = newNode;
		list->current = newNode;
		printf("%s", newNode->info);
		return;
	}
	while (list->current->siblingL != NULL)
	{
		list->current = list->current->siblingL;
	}
	if (!strcmp(list->current->info, param2))
	{
		printf("Name is already in use\n");
		return;
	}
	while (list->current->siblingR != NULL)
	{
		if (!strcmp(list->current->siblingR->info, param2))
		{
			printf("Name is already in use\n");
			return;
		}
		else if (strcmp(list->current->siblingR->info, param2) > 0) break;
		list->current = list->current->siblingR;
	}
	if (list->current->siblingL == NULL && list->current->siblingR == NULL && strcmp(list->current->info, param2) > 0)
	{
		NodeP newNode = malloc(sizeof(struct Node));
		newNode->parent = list->current->parent;
		newNode->siblingL = NULL;
		list->current->siblingL = newNode;
		newNode->siblingR = list->current;
		newNode->child = NULL;
		strcpy(newNode->info, param2);
		list->current = newNode;
		printf("%s", newNode->info);
		return;
	}
	if (list->current->siblingL == NULL && list->current->siblingR == NULL && strcmp(list->current->info, param2) < 0)
	{
		NodeP newNode = malloc(sizeof(struct Node));
		newNode->parent = list->current->parent;
		newNode->siblingR = NULL;
		list->current->siblingR = newNode;
		newNode->siblingL = list->current;
		newNode->child = NULL;
		strcpy(newNode->info, param2);
		list->current = newNode;
		printf("%s", newNode->info);
		return;
	}
	else if (list->current->siblingL == NULL && strcmp(list->current->info, param2) > 0)
	{
		NodeP newNode = malloc(sizeof(struct Node));
		newNode->parent = list->current->parent;
		newNode->siblingL = NULL;
		list->current->siblingL = newNode;
		newNode->siblingR = list->current;
		newNode->child = NULL;
		strcpy(newNode->info, param2);
		list->current = newNode;
		printf("%s", newNode->info);
		return;
	}
	else if(list->current->siblingR == NULL && strcmp(list->current->info, param2) < 0)
	{
		NodeP newNode = malloc(sizeof(struct Node));
		newNode->parent = list->current->parent;
		newNode->siblingR = NULL;
		list->current->siblingR = newNode;
		newNode->siblingL = list->current;
		newNode->child = NULL;
		strcpy(newNode->info, param2);
		list->current = newNode;
		printf("%s", newNode->info);
		return;
	}
	else if(list->current->siblingL != NULL && list->current->siblingR != NULL)
	{
		NodeP newNode = malloc(sizeof(struct Node));
		newNode->parent = list->current->siblingR->parent;
		list->current->siblingR->siblingL = newNode;
		newNode->siblingR = list->current->siblingR;
		list->current->siblingR = newNode;
		newNode->siblingL = list->current;
		newNode->child = NULL;
		strcpy(newNode->info, param2);
		list->current = newNode;
		printf("%s", newNode->info);
		return;
	}
}

/***************************************************************
*Renames a file in the current directory if it exists
*Paramater (ListP list) contains current file or direct
*Parameter (char param2) contains name of file to be changed
*Paramater (char param3) contains name to be changed to
***************************************************************/
void mv(ListP list, char param2[60], char param3[60])
{
	while (list->current->siblingL != NULL)
	{
		list->current = list->current->siblingL;
	}
	if (strcmp(list->current->info, param2) == 10 || 0)
	{
		strcpy(list->current->info, param3);
		return;
	}
	while (list->current->siblingR != NULL)
	{
		if (strcmp(list->current->siblingR->info, param2) == 10)
		{
			strcpy(list->current->siblingR->info, param3);
			return;
		}
		list->current = list->current->siblingR;
	}
	printf("No such file or directory\n");
	return;
}

/***************************************************************
*Removes a file or directory in the current directory if it exists
*Paramater (ListP list) contains current file or direct
*Paramater (char param2) contains name of file to be removed
***************************************************************/
void rm(ListP list, char param2[60])
{
	while (list->current->siblingL != NULL)
	{
		list->current = list->current->siblingL;
	}

	while(list->current->siblingR != NULL)
	{
		if (!strcmp(list->current->info, param2) && list->current->siblingL == NULL && list->current->siblingR == NULL)
		{
			strcpy(list->current->info, " ");
			return;
		}
		else if (!strcmp(list->current->info, param2) && list->current->siblingL == NULL && list->current->siblingR != NULL)
		{
			NodeP tempNode = malloc(sizeof(struct Node));
			tempNode = list->current;
			list->current = list->current->siblingR;
			tempNode->parent = list->current;
			list->current->siblingL = NULL;
			free(tempNode);
			return;
		}
		else if (!strcmp(list->current->info, param2) && list->current->siblingL != NULL && list->current->siblingR == NULL)
		{
			NodeP tempNode = malloc(sizeof(struct Node));
			tempNode = list->current;
			list->current = list->current->siblingL;
			list->current->siblingR = NULL;
			free(tempNode);
			return;
		}
		else if (!strcmp(list->current->info, param2) && list->current->siblingL != NULL && list->current->siblingR != NULL)
		{
			NodeP tempNode = malloc(sizeof(struct Node));
			tempNode = list->current;
			list->current = list->current->siblingL;
			tempNode->siblingR->siblingL = tempNode->siblingL;
			tempNode->siblingL->siblingR = tempNode->siblingR;
			free(tempNode);
			return;
		}
		list->current = list->current->siblingR;
	}
	if (!strcmp(list->current->info, param2) && list->current->siblingL == NULL && list->current->siblingR == NULL)
	{
		strcpy(list->current->info, " ");
		return;
	}
	else if (!strcmp(list->current->info, param2) && list->current->siblingL == NULL && list->current->siblingR != NULL)
	{
		NodeP tempNode = malloc(sizeof(struct Node));
		tempNode = list->current;
		list->current = list->current->siblingR;
		tempNode->parent = list->current;
		list->current->siblingL = NULL;
		free(tempNode);
		return;
	}
	else if (!strcmp(list->current->info, param2) && list->current->siblingL != NULL && list->current->siblingR == NULL)
	{
		NodeP tempNode = malloc(sizeof(struct Node));
		tempNode = list->current;
		list->current = list->current->siblingL;
		list->current->siblingR = NULL;
		free(tempNode);
		return;
	}
	else if (!strcmp(list->current->info, param2) && list->current->siblingL != NULL && list->current->siblingR != NULL)
	{
		NodeP tempNode = malloc(sizeof(struct Node));
		tempNode = list->current;
		list->current = list->current->siblingL;
		tempNode->siblingR->siblingL = tempNode->siblingL;
		tempNode->siblingL->siblingR = tempNode->siblingR;
		free(tempNode);
		return;
	}
	printf("No such file or directory\n");
	return;
}

/***************************************************************
*Changes current directory to supplied directory name if it exists
*Paramater (ListP list) contains current file or direct
*Paramater (char param2) contains directory name to switch to
*Parameter (char pwd) contains present working directory 
***************************************************************/
void cd(ListP list, char param2[60], char pwd[200])
{
	while (list->current->siblingL != NULL)
	{
		list->current = list->current->siblingL;
	}
	while (list->current->siblingR != NULL)
	{
		if ((strcmp(list->current->info, param2) == 0 || strcmp(list->current->info, param2) == 10) && list->current->child == NULL)
		{
			NodeP tempN = malloc(sizeof(struct Node));
			tempN->parent = list->current;
			tempN->siblingL = NULL;
			tempN->siblingR = NULL;
			tempN->child = NULL;
			list->current->child = tempN;
			strcpy(tempN->info, " ");
			strcat(pwd, "/");
			strcat(pwd, param2);
			int i = strlen(pwd);
			pwd[i-1] = '\0';
			printf("%s\n", pwd);
			list->current = tempN;
			return;
		}
		else if (strcmp(list->current->info, param2) == 0 || strcmp(list->current->info, param2) == 10)
		{
			NodeP tempN = malloc(sizeof(struct Node));
			tempN = list->current;
			strcat(pwd, "/");
			strcat(pwd, param2);
			int i = strlen(pwd);
			pwd[i-1] = '\0';
			printf("%s\n", pwd);
			list->current = tempN->child;
			return;
		}
		list->current = list->current->siblingR;
	}
	if ((strcmp(list->current->info, param2) == 0 || strcmp(list->current->info, param2) == 10) && list->current->child == NULL)
	{
		NodeP tempN = malloc(sizeof(struct Node));
		tempN->parent = list->current;
		tempN->siblingL = NULL;
		tempN->siblingR = NULL;
		tempN->child = NULL;
		list->current->child = tempN;
		strcpy(tempN->info, " ");
		strcat(pwd, "/");
		strcat(pwd, param2);
		int i = strlen(pwd);
		pwd[i-1] = '\0';
		printf("%s\n", pwd);
		list->current = tempN;
		return;
	}
	else if (strcmp(list->current->info, param2) == 0 || strcmp(list->current->info, param2) == 10)
	{
		NodeP tempN = malloc(sizeof(struct Node));
		strcat(pwd, "/");
		strcat(pwd, param2);
		int i = strlen(pwd);
		pwd[i-1] = '\0';
		list->current = tempN->child;
		return;
	}
	printf("No such file or directory\n");
	return;
}

/***************************************************************
*Moves up one directory level if the parent directory is not root
*Paramater (ListP list) contains current file or direct
*Paramater (NodeP rootNode) contains root of file system
*Parameter (char pwd) contains present working directory 
***************************************************************/
void cddot(ListP list, NodeP rootNode, char pwd[200])
{
	if (!strcmp(list->current->parent->info, "boutros/root"))
	{
		printf("%s\n", pwd);
		return;
	}
	int x = strlen(pwd);
	int y = (strlen(list->current->parent->info));
	int z = x;
	x -= y;
	for (x; x<z; x++) pwd[x] = '\0';
	list->current = list->current->parent;
	printf("%s\n", pwd);
	return;
}

/***************************************************************
*Searches for supplied file name throughout file system and 
 prints present working directory for all instances
*Paramater (ListP list) contains current file or direct
*Paramater (NodeP rootNode) contains root of file system
*Paramater (char param2) contains file name to search for
*Parameter (char pwd) contains present working directory 
***************************************************************/
void whereis(ListP list, NodeP rootNode, char param2[60], char pwd[200])
{
	NodeP tempNode = malloc(sizeof(struct Node));
	tempNode = list->current;
	list->current = rootNode->child;
	char pwdT[200];
	strcpy(pwdT, "boutros/root");
	while(list->current->siblingL != NULL) list->current = list->current->siblingL;
	if (!strcmp(list->current->info, param2)) printf("%s\n", pwdT);
	if (list->current->child != NULL) 
	{

		strcat(pwdT, "/");
		strcat(pwdT, list->current->info);
		int i = strlen(pwdT);
		pwdT[i-1] = '\0';
		list->current = list->current->child;
		whereisRec(list, param2, pwdT);
	}
	if (list->current->siblingR != NULL)
	{
		list->current = list->current->siblingR;
		whereisRec(list, param2, pwdT);
	}
	list->current = tempNode;
}

/***************************************************************
*Recursive call for whereis function
*Searches for supplied file name throughout file 
 system and prints present working directory for all instances
*Paramater (ListP list) contains current file or direct
*Paramater (char param2) contains file name to search for
*Parameter (char pwd) contains present working directory 
***************************************************************/
void whereisRec(ListP list, char param2[60], char pwdT[200])
{
	if (!strcmp(list->current->info, param2)) printf("%s\n", pwdT);
	if (list->current->child != NULL) 
	{
		char pwdTemp[200];
		strcpy (pwdTemp, pwdT);
		strcat(pwdT, "/");
		strcat(pwdT, list->current->info);
		int i = strlen(pwdT);
		pwdT[i-1] = '\0';
		list->current = list->current->child;
		whereisRec(list, param2, pwdT);
		memset (pwdT,'\0',200);
		strcpy(pwdT, pwdTemp);
	}

	if (list->current->siblingR != NULL)
	{
		list->current = list->current->siblingR;
		whereisRec(list, param2, pwdT);
	}
	else if (list->current->siblingR == NULL) list->current = list->current->parent;
}
