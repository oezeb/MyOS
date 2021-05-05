/* 
 * 请确保以下的代码可以原封不动的成功编译和执行
 * 助教测试时会替换相应的参数
 * 不需要修改
 * （全部划掉）
 */

#include "io.h"
#include "myPrintk.h"
#include "uart.h"
#include "vga.h"
#include "shell.h"

int echo(int argc, char* argv[]) {
    for (int i = 1; i < argc; ++i) {
        myPrintf(7, "%s ", argv[i]);
    }
    myPrintf(7, "\n");
    return 0;
}

void echoHelp(void) {
    myPrintf(7, "echo: echo [arguments ...]\nprint arguments, divided by space\n");
}

void myMain(void)
{
    initShell();
    registerCmd("echo", echo, echoHelp);
    startShell();
}
