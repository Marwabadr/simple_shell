#ifndef _SIMPLESHELL_H_
#define _SIMPLESHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>


#define READBUFSIZE 1024
#define WRITEBUFSIZE 1024
#define BUFFLUSH -1

#define CMDNORM	0
#define CMDOR		1
#define CMDAND		2
#define CMDCHAIN	3

#define CONVERTLOWERCASE	1
#define CONVERTUNSIGNED	2

#define USEGETLINE 0
#define USESTRTOK 0

#define HISTFILE	".simple_shell_history"
#define HISTMAX	4096

extern char **environ;


/**
 * struct stringList - LinkedList of string
 * @num: number
 * @str: string
 * @next: next pointer
 */
typedef struct stringList
{
	int num;
	char *str;
	struct stringList *next;
} listS;

/**
 *struct passInf - information passing
 *@arg: arguments
 *@argv: argv
 *@path: path
 *@argc: argc
 *@line_count: count error
 *@err_num: error number
 *@linecount_flag: flag of line count
 *@fname: filename
 *@env: environ
 *@environ: env
 *@history: history
 *@alias: alias
 *@env_changed: environ changing
 *@status: status
 *@cmd_buf: address of pointer
 *@cmd_buf_type: command type
 *@readfd: read file descriptor
 *@histcount: history count
 */
typedef struct passInf
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	listS *env;
	listS *history;
	listS *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} infoP;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtInTable - buildin string
 *@type: type
 *@func: function
 */
typedef struct builtInTable
{
	char *type;
	int (*func)(infoP *);
} builtinTable;


int hsh(infoP *, char **);
int findBuiltin(infoP *);
void findCmd(infoP *);
void forkCmd(infoP *);

int isCmd(infoP *, char *);
char *dupChars(char *, int, int);
char *findPath(infoP *, char *, char *);

int loophsh(char **);

void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

int _strlen(char *);
int _strcmp(char *, char *);
char *startsWith(const char *, const char *);
char *_strcat(char *, char *);

char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

char **strtow(char *, char *);
char **strtow2(char *, char);

char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

int bfree(void **);

int interactive(infoP *);
int isDelim(char, char *);
int _isalpha(int);
int _atoi(char *);

int _erratoi(char *);
void printError(infoP *, char *);
int print_d(int, int);
char *convertNumber(long int, int, int);
void removeComments(char *);

int _myexit(infoP *);
int _mycd(infoP *);
int _myhelp(infoP *);

int _myhistory(infoP *);
int _myalias(infoP *);

ssize_t getInput(infoP *);
int _getline(infoP *, char **, size_t *);
void sigintHandler(int);

void clearInfo(infoP *);
void setInfo(infoP *, char **);
void freeInfo(infoP *, int);

char *_getenv(infoP *, const char *);
int _myenv(infoP *);
int _mysetenv(infoP *);
int _myunsetenv(infoP *);
int populateEnvList(infoP *);

char **getEnviron(infoP *);
int _unsetenv(infoP *, char *);
int _setenv(infoP *, char *, char *);

char *getHistoryFile(infoP *info);
int writeHistory(infoP *info);
int readHistory(infoP *info);
int buildHistoryList(infoP *info, char *buf, int linecount);
int renumberHistory(infoP *info);

listS *addNode(listS **, const char *, int);
listS *addNodeEnd(listS **, const char *, int);
size_t printListStr(const listS *);
int deleteNodeAtIndex(listS **, unsigned int);
void freeList(listS **);

size_t listLen(const listS *);
char **listToStrings(listS *);
size_t printList(const listS *);
listS *nodeStartsWith(listS *, char *, char);
ssize_t getNodeIndex(listS *, listS *);

int isChain(infoP *, char *, size_t *);
void checkChain(infoP *, char *, size_t *, size_t, size_t);
int replaceAlias(infoP *);
int replaceVars(infoP *);
int replaceString(char **, char *);

#endif
