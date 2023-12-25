#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include <math.h>

void printHelp(char *executable_name);

void printMenu();

int isPowerOftwo(int num) {
    return (num & (num - 1)) == 0;
}

/*void printArray(int arr[]) {
    printf("Array elements: ");
    for (int i = 0; i < sizeof(arr) * 4; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}*/

int main(int argc, char *argv[]) {
    // parse command line arguments
    int BLOCKSIZE = 4;
    int NUM_BLOCKS = 32;
    if (argc < 2) {
        printHelp(*argv);
    }
    if (argc >= 2) {
        if (argc < 5) {
            printHelp(*argv);
            return 1;
        }
        for (int i = 1; i < argc; i += 2) {
            if (strcmp(argv[i], "-b") == 0 && i + 1 < argc) {
                BLOCKSIZE = atoi(argv[i + 1]);
                if (!isPowerOftwo(BLOCKSIZE)) {
                    printHelp(*argv);
                    return 1;
                }
            } else if (strcmp(argv[i], "-n") == 0 && i + 1 < argc) {
                NUM_BLOCKS = atoi(argv[i + 1]);
                if (!isPowerOftwo(NUM_BLOCKS)) {
                    printHelp(*argv);
                    return 1;
                }
            } else {
                printHelp(*argv);
                return 1;
            }
        }
    }
    printMenu();
    int buf[NUM_BLOCKS];
    int flags[NUM_BLOCKS];
    int flag = 0;
    int history[NUM_BLOCKS];
    for (int i = 0; i < NUM_BLOCKS; i++) {
        buf[i] = log2(NUM_BLOCKS) + 1;
        history[i] = log2(NUM_BLOCKS) + 1;
        flags[i] = 0;
    }
    while (1) {
        char input[50];
        fgets(input, sizeof(input), stdin);
        // read commands and execute them
        char cmd[10];
        int index;
        if (sscanf(input, "%s", cmd) == 1 && strcmp(cmd, "q") == 0) {
            exit(0);
        } else if (sscanf(input, "%s", cmd) == 1 && strcmp(cmd, "l") == 0) {
            for (int i = 0; i < (int)sizeof(buf) / 4; i++) {
                if (buf[i] != 0) {
                    printf("F");
                } else {
                    printf("P");
                }
            }
            printf("\n");
        } else if (sscanf(input, "%s %d", cmd, &index) == 2 && strcmp(cmd, "m") == 0) {
            int m = index;
            int i = 1;
            while (i * BLOCKSIZE * 1024 < m) {
                i *= 2;
            }
            int found = 0;
            for (int j = log2(i) + 1; j <= log2(NUM_BLOCKS) + 1; j++) {
                for (int z = 0; z < (int)sizeof(buf) / 4; z++) {
                    if (buf[z] == j) {
                        found = 1;
                        flag += 1;
                        //printf("i: %d", i);
                        //printf("z; %d", buf[z]);
                        while (log2(i) + 1 < buf[z]) {
                            for (int a = z; a < z + pow(2, buf[z]); a++) {
                                buf[a] -= 1;
                                //printf("hui");
                                //printArray(buf);
                            }
                        }
                        for (int a = z; a < z + i; a++) {
                            history[a] = buf[a];
                            buf[a] = 0;
                            flags[a] = flag;
                        }
                        //printArray(buf);
                        //printArray(history);
                        z = sizeof(buf) / 4;
                        j = log2(NUM_BLOCKS) + 1;
                    }
                }
            }
            if (found) {
                printf("success");
                printf("\n");
            } else {
                printf("error\n");
            }
        } else if (sscanf(input, "%s %d", cmd, &index) == 2 && strcmp(cmd, "f") == 0) {
            int f = index;
            int found = 0;
            for (int i = 0; i < NUM_BLOCKS; i++) {
                if (flags[i] == f && buf[i] == 0) {
                    int check = i;
                    found = 1;
                    while (flags[i] == f) {
                        flags[i] = 0;
                        //printArray(history);
                        buf[i] = history[i];
                        i += 1;
                    }
                    //printf("i: %d\n", check);
                    //printf("buf[check]: %d\n", buf[check]);
                    //printf("buf[check + (int)pow(2, buf[check])] %d\n", buf[check + (int)pow(2, buf[check])]);
                    while (check + (int) pow(2, buf[check]) - 1 < NUM_BLOCKS &&
                           buf[check] == buf[check - 1 + (int) pow(2, buf[check])]) {
                        int max = check + (int) pow(2, buf[check]);
                        for (int j = check; j < max; j++) {
                            buf[j]++;
                        }
                    }
                    if (check - (int) pow(2, buf[check]) + 1 >= 0 &&
                        check - 1 >= 0 &&
                        buf[check] == buf[check - 1]&&
                        buf[check] == buf[check + 1 - (int) pow(2, buf[check])]) {
                        check = check - (int) pow(2, buf[check]) + 1;
                        while (check + (int) pow(2, buf[check]) - 1 < NUM_BLOCKS &&
                               buf[check] == buf[check - 1 + (int) pow(2, buf[check])]) {
                            int max = check + (int) pow(2, buf[check]);
                            for (int j = check; j < max; j++) {
                                buf[j]++;
                            }
                            //printf("hui: \n");
                        }
                    }
                    //printArray(buf);
                    break;
                }
            }
            if (!found) {
                printf("Could not free %d - number is invalid !\n", f);
            } else {
                printf("success\n");
            }
        } else {
            printMenu();
        }
    }
}

/* Tester expects these exact (formatted) strings
 * V   V   V   V   V   V   V   V   V   V    */
void printHelp(char *executable_name) {
    printf("Usage: %s [-b BLOCKSIZE] [-n NUM_BLOCKS]\n"
           "BLOCKSIZE: integer, interpreted as kiB (i.e. -b 4 => 4096 Bytes). Has to be power of 2! The default is 4.\n"
           "NUM_BLOCKS: integer, number of blocks to be used. Has to be power of 2! The default is 32.\n",
           executable_name);
}

void printMenu() {
    printf("Type your command, then [enter]\n"
           "Available commands:\n"
           "m SIZE\t\tallocate SIZE Bytes of memory. SIZE has to be > 0.\n"
           "f POINTER\tfree the memory referenced by POINTER. If it is invalid, an error is shown and nothing else happens.\n"
           "l\t\tprint current memory layout.\n"
           "q\t\tquit the program.\n");
}
/* /\  /\  /\  /\  /\  /\  /\  /\  /\  /\ */
