#ifndef __SHELL_H__
#define __SHELL_H__

typedef int (*cmdFunc)(int argc, char* argv[]);
typedef void (*helpFunc)(void);

void initShell(void);
void startShell(void);
void registerCmd(char* cmdName, cmdFunc cmd, helpFunc help);
void getCmd(void);
int cmd (int argc, char* argv[]);
void cmdHelp (void);
int help(int argc, char* argv[]);
void helpHelp(void);

#endif