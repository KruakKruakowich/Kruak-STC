#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <windows.h>
#include <locale.h>
#include <stdlib.h>

void get_exe_dir(char *dir, int maxlen) {
    GetModuleFileName(NULL, dir, maxlen);
    char *last_slash = strrchr(dir, '\\');
    if (last_slash != NULL) {
        *(last_slash + 1) = '\0';
    }
}
int main()
{
    setlocale(LC_ALL, "");
    printf("   Welcome in Kruak STC, instruction - i\n");
    unsigned short symbolsnum = 1000, namenum = 100; // you can change it
    printf("   Max symbols - %d\n   Max file name length - %d\n", symbolsnum, namenum);
    char symbols[symbolsnum];
    char filename[namenum];
    char option[20]; // change for bigger options length
    char exe_dir[512];
    char choice[6]; //change for bigger choice lenght
    unsigned short basicpathlength = 256; //change for bigger file path length
    get_exe_dir(exe_dir, sizeof(exe_dir));

    char texts_dir[512 + namenum];
    strcpy(texts_dir, exe_dir);
    strcat(texts_dir, "STC Texts\\");

    if (CreateDirectory(texts_dir, NULL)) {
    }

    do {
        printf("Enter work option:\n");
        fgets(option,sizeof(option), stdin);
        option[strcspn(option, "\n")] = '\0';

    if (strcmp(option, "create") == 0 || strcmp(option, "2") == 0) {
        printf("Input file name:\n");
        fgets(filename,sizeof(filename), stdin);
        filename[strcspn(filename, "\r\n")] = '\0';
        printf("Input text in file:\n");
        fgets(symbols, sizeof(symbols), stdin);
        char fullpath[basicpathlength + namenum];
        strcpy(fullpath, texts_dir);
        strcat(fullpath, filename);
        FILE *fp = fopen(fullpath, "w");

        if (fp != NULL) {
            fprintf(fp, "%s", symbols);
            fclose(fp);
            printf("   File '%s' created.\n", filename);
        } else {
            printf("   Error creating file.\n");
        }
    }
        else if (strcmp(option, "delete") == 0 || strcmp(option, "3") == 0) {
            printf("Input file name:\n");
            fgets(filename,sizeof(filename), stdin);
            filename[strcspn(filename, "\r\n")] = '\0';
            printf("Are you sure? ' %s ' will deleted forever. (yes/no)\n", filename);
            fgets(choice,sizeof(choice), stdin);
            choice[strcspn(choice, "\n")] = '\0';
            if (strcmp(choice, "yes") == 0 || strcmp(choice, "y") == 0){

                char fullpath[basicpathlength + namenum];
                strcpy(fullpath, texts_dir);
                strcat(fullpath, filename);
                DeleteFile(fullpath);
                printf("   File %s deleted. Do you regret it?\n", filename);
            }
        }
        else if (strcmp(option, "edit") == 0 || strcmp(option, "4") == 0) {
            printf("Input file name for edit: ");
            fgets(filename, sizeof(filename), stdin);
            filename[strcspn(filename, "\r\n")] = '\0';

            printf("Text for edit:\n");
            fgets(symbols, sizeof(symbols), stdin);

            char fullpath[basicpathlength + namenum];
            strcpy(fullpath, texts_dir);
            strcat(fullpath, filename);
            FILE *fp = fopen(fullpath, "a");

            if (fp != NULL) {
                fprintf(fp, "%s", symbols);
                fclose(fp);
                printf("   Text added to '%s'.\n", filename);
            } else {
                printf("   Can't edit file '%s'.\n", filename);
            }
        }
    else if (strcmp(option, "instruction") == 0 || strcmp(option, "i") == 0 || strcmp(option, "1") == 0) {
        printf("   Options list:\n\n 1. instruction\n 2. create\n 3. delete\n 4. edit\n 5. open \n 6. info\n 7. quit\n 8. list\n\n");
    }
    else if (strcmp(option, "open") == 0 || strcmp(option, "5") == 0) {
        printf("Input file name:\n");
        fgets(filename, sizeof(filename), stdin);
        filename[strcspn(filename, "\r\n")] = '\0';
        char fullpath[basicpathlength + namenum];
        strcpy(fullpath, texts_dir);
        strcat(fullpath, filename);
        FILE *fp = fopen(fullpath, "r");
        if (fp != NULL) {
            while (fgets(symbols, sizeof(symbols), fp) != NULL) {
                printf("%s", symbols);
                }
            fclose(fp);
        }
        else {
            printf("   Input file name correctly or create a new, please\n");
            printf("   Error: %s\n", strerror(errno));
        }
    }
    else if (strcmp(option, "list") == 0 || strcmp(option, "8") == 0) {
        char search_path[basicpathlength + namenum + 5];
        strcpy(search_path, texts_dir);
        strcat(search_path, "*");

         WIN32_FIND_DATA findData;
         HANDLE hFind = FindFirstFile(search_path, &findData);

         if (!(hFind == INVALID_HANDLE_VALUE)) {
            printf("   Files in folder %s:\n", texts_dir);
            do {
                if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                printf("%s\n", findData.cFileName);
        }
    } while (FindNextFile(hFind, &findData));
         }
    }
    else if (strcmp(option, "info") == 0 || strcmp(option, "6") == 0) {
        printf("   Second Text on C created by Kruak\n You can edit max symbols and max file name length in program files\n You can use option number instead of option name\n You can edit file path length in program files\n");
    }
    else if (strcmp(option, "quit") == 0 || strcmp(option, "7") == 0) {
    exit(0);
    }
    } while (1);
    return 0;
}
