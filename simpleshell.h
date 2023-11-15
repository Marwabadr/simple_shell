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

/* for read/write buffers */
#define MY_READ_BUF_S 1024
#define MY_WRITE_BUF_S 1024
#define MY_BUF_F -1

/* for command chaining */
#define MY_CAMD_NORM	0
#define MY_CAMD_OR		1
#define MY_CAMD_AND		2
#define MY_CAMD_CHAIN	3

/* for convert_number() */
#define MY_CVRT_LOWERCASE	1
#define MY_CVRT_UNSIGNED	2

/* 1 if using system getline() */
#define MY_USE_GETLINE 0
#define MY_USE_STRTOK 0

#define MY_HIST_FILE	".simple_shell_history"
#define MY_HIST_MAX	4096

extern char **Myenv;


/**
 * struct MyListstring - a linked list structure of string
 * @n: interger
 * @string: string
 * @suc: pointeur au suivant
 */
typedef struct MyListstring
{
	int n;
	char *string;
	struct MyListstring *suc;
} strL;

/**
 *struct infoPassing - arg to pass info
 *@arg: args
 *@argv: array of args
 *@path: path for current cmd
 *@argc: args count
 *@lCount: arr count
 *@errn: exit err
 *@lCountFlag: count line in
 *@fileName: filename of the prog
 *@env: linked list environ
 *@envi:  copy of environ env
 *@his: history
 *@al:  alias
 *@envChanged: env changing
 *@stat: status of the last cmd
 *@cmdBuf: address to cmdBuf
 *@cmdBufType: CMDType
 *@readFd:  read line input
 *@hisCount:  history count
 */
typedef struct infoPassing
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int lCount;
	int errn;
	int lCountFlag;
	char *fileName;
	strL *env;
	strL *his;
	strL *al;
	char **envi;
	int envChanged;
	int stat;

	char **cmdBuf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmdBufType; /* CMD_type ||, &&, ; */
	int readFd;
	int hisCount;
} infoP;

#define MY_INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtIn - builtin str
 *@t: type of buildin
 *@fct: function of buildin
 */
typedef struct builtIn
{
	char *t;
	int (*fct)(infoP *);
} builtInTable;

int hsh(infoP *, char **);
int findBuiltin(infoP *);
void findCmd(infoP *);
void forkCmd(infoP *);

int isCmd(info_t *, char *);
char *dupChars(char *, int, int);
char *findPath(info_t *, char *, char *);

int loophsh(char **);

void _eputs(char *);
int _eputchar(char);
int _putfld(char ch, int fld);
int _putsfd(char *string, int filed);

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

strL *addNode(strL **, const char *, int);
strL *addNodeEnd(strL **, const char *, int);
size_t printListStr(const strL *);
int deleteNodeAtIndex(strL **, unsigned int);
void freeList(strL **);

size_t listLen(const strL *);
char **listToStrings(strL *);
size_t printList(const strL *);
strL *nodeStartsWith(strL *, char *, char);
ssize_t getNodeIndex(strL *, strL *);

int isChain(infoP *, char *, size_t *);
void checkChain(infoP *, char *, size_t *, size_t, size_t);
int replaceAlias(infoP *);
int replaceVars(infoP *);
int replaceString(char **, char *);
#endif
