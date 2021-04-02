/**
 * @file demo.c
 * @author Francisco Spínola (fssecur3@outlook.com)
 * @brief Dump Wifi credentials from Windows machines (needs admin privileges)
 * @version 0.2
 * @date 2021-03-10
 * @copyright Copyright (c) 2021
 * 
 * DESCRIPTION
 * Do not redistribute or use this software for malicious purposes!
 * This is the demonstration executable, where the output will be shown in the terminal only 
 * (no file will be created), waiting, at the end, for user input.
 * 
 * COMPILING
 * $ gcc demo.c -o demo.exe
 * 
 * EXECUTION
 * You can execute the program on a terminal or by double clicking the executable.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SSID 32
#define BUFFER 59
#define PWD 64

void to32(char *string) {
    int i = strlen(string);
    while (i < 32) {
        printf(" ");
        i++;
    }
}

//Retrieve the Wifi passwords
char *password (char *ssid) {
    char *pwd = NULL;
    FILE *process;
    char buf[75];
    char cmd[66] = "netsh wlan show profile key=clear \"";
    strncat(cmd, ssid, SSID);
    strncat(cmd, "\"", 1);
    
    if ((process = popen(cmd, "r")) == NULL) {
        printf("Error opening pipe!\n");
        exit(0);
    }
    
    bool go = false;
    
    while (fgets(buf, 75, process) != NULL && !go) {
        
        char *token;

        token = strtok(buf, ":");
        if (strcmp(buf, "    Key Content            ") == 0) {
            go = true;
        }
        
        token = strtok(NULL, ":");
        if (go) {
            if (token != NULL) {
                pwd = token;
            }
            pwd++;
            pwd[strlen(pwd) - 1] = '\0';
        }
    }
    
    if (pclose(process)) {
        printf("Command not found or exited with error status\n");
        exit(0);
    }
    
    if (pwd == NULL || pwd == " " || pwd == "\n") {
        pwd = "";
    }
    
    return pwd;
}

//Retrieve the Wifi SSIDs
void ssid(int *count) {
    char ssids[PWD][SSID];
    char passwords[PWD][PWD];
    char *ssid = NULL;
    char *pwd = NULL;
    FILE *process;
    char *cmd = "netsh wlan show profile";
    char buf[BUFFER];

    if ((process = popen(cmd, "r")) == NULL) {
        printf("Error opening pipe!\n");
        exit(0);
    }

    printf("|               SSID              |            PASSWORD             |\n");
    int i = 0;
    printf("|");
    while (i < 67) {
        printf("-");
        i++;
    }
    printf("|\n");
    while (fgets(buf, BUFFER, process) != NULL) {
        bool go = false;
        char *token;

        token = strtok(buf, ":");
        if (strcmp(buf, "    All User Profile     ") == 0) {
            go = true;
        }
        
        token = strtok(NULL, ":");
        if (go) {
            if (token != NULL) {
                ssid = token;
            }
            ssid++;
            ssid[strlen(ssid) - 1] = '\0';
            strncpy(ssids[(*count)], ssid, SSID);
            pwd = password(ssid);
            strncpy(passwords[(*count)], pwd, PWD);
            printf("| %s", ssids[(*count)]);
            if (strlen(ssid) < 32) {
                to32(ssid);
            }
            printf(":");
            if (strlen(passwords[(*count)]) < 32) {
                to32(passwords[(*count)]);
            }
            printf("%s |", passwords[(*count)]);
            printf("\n");
            (*count)++;
        }
    }

    if (pclose(process)) {
        printf("Command not found or exited with error status\n");
        exit(0);
    }
}

bool checkAdmin () {
    FILE *process;
    char buf[100];
    if ((process = popen("net user %username%", "r")) == NULL) {
        exit(0);
    }

    while (fgets(buf, 100, process) != NULL) {
        if (strstr(buf, "*Administrators") != NULL || strstr(buf, "*Administradores") != NULL || strstr(buf, "*Administrateurs") != NULL || 
            strstr(buf, "*Administratoren") != NULL || strstr(buf, "*Beheerders") != NULL || strstr(buf, "*Amministratori") != NULL || 
            strstr(buf, "*Administratores") != NULL || strstr(buf, "*Administratorer") != NULL || strstr(buf, "*Administratorzy") != NULL) {
            return true;
        }
    }

    return false;
}

//Main
int main(int argc, char **argv) {
    if (!checkAdmin()) {
        return -1;
    }

    int count = 0;
    int i = 0;
    printf(" ");
    while (i < 67) {
        printf("-");
        i++;
    }
    printf("\n");
    i = 0;
    ssid(&count);
    printf(" ");
    while (i < 66) {
        printf("-");
        i++;
    }
    printf("\n");
    system("pause");

    return 0;
}