#include "shell.h"
#include "uart.h"
#include "myPrintk.h"
#include "type.h"
#include "vga.h"
#include "string.h"

char cmdBuf[100] = {};
char *argv[100] = {};
int argc = 0;
void getCmd(void) {
    bool inWord = FALSE;
    char *p = cmdBuf;
    char ch = uart_get_char();
    argc = 0;
    while (ch != '\r') {
        if (ch == ' ') {
            if (inWord) {
                inWord = FALSE;
                *p = '\0';
            }  
        } else {
            if (!inWord) {
                inWord = TRUE;
                argv[argc] = p;
                ++argc;
            }
            *p = ch;
        }
        append_char_to_screen(ch, 7);
        uart_put_char(ch);
        ++p;
        ch = uart_get_char();
    }
    uart_put_chars("\r\n");
    append_char_to_screen('\n', 7);
    *p = '\0';
}

char *cmdNames[1000] = {};
cmdFunc cmds[1000] = {};
helpFunc helps[1000] = {};
int cmdCount = 0;
void registerCmd(char* cmdName, cmdFunc cmd, helpFunc help) {
    cmdNames[cmdCount] = cmdName;
    cmds[cmdCount] = cmd;
    helps[cmdCount] = help;
    ++cmdCount;
}

int returnVal = 0;
void initShell(void) {
    argc = 0;
    cmdCount = 0;
    returnVal = 0;
    registerCmd("cmd", cmd, cmdHelp);
    registerCmd("help", help, helpHelp);
}

void startShell(void) {
    clear_screen();
    bool valid = FALSE;
    while (TRUE)
    {
        myPrintf(2, "$ ");
        getCmd();
        for (int i = 0; i < cmdCount; ++i) {
            if (strcmp(cmdNames[i], argv[0]) == 0) {
                valid = TRUE;
                returnVal = cmds[i](argc, argv);
                break;
            }
        }
        if (!valid) {
            myPrintf(7, "command %s doesn't exist.\n", argv[0]);
        }
        argc = 0;
        valid = FALSE;
    }
}

int cmd(int argc, char* argv[]) {
    myPrintf(7, "total %d:\n", cmdCount);
    for (int i = 0; i < cmdCount; ++i)
    {
        myPrintf(7, cmdNames[i]);
        myPrintf(7, "\n");
    }
    return 0;
}

void cmdHelp(void) {
    myPrintf(7, "cmd: cmd\nlist all commands\n");
}

int help(int argc, char* argv[]) {
    bool flag = FALSE;
    if (argc >= 2) {
        for (int i = 0; i < cmdCount; ++i) {
            if (strcmp(cmdNames[i], argv[1]) == 0) {
                flag = TRUE;
                helps[i]();
                break;
            }
        }
        if (!flag) {
            myPrintf(7, "command %s doesn't exist.\n", argv[1]);
        }
    } else {
        helpHelp();
    }
    return 0;
}

void helpHelp(void) {
    myPrintf(7, "help: help [target command] ...\ncall help function of target command.\n");
}
