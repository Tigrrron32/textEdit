#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string.h>

using namespace std;

void showTextFile(const char* FileName) {
    FILE* F = fopen(FileName, "rt");
    if (!F) {
        cout << "ERROR: File not found!: " << FileName << endl;
        return;
    }

    puts(FileName);
    char S[20000];
    while (fgets(S, sizeof(S), F)) {
        cout << S;
    }
    fclose(F);
}

int strLen(const char* S) {
    int count = 0;
    while (*S++) {
        count++;
    }
    return count;
}

bool isSeparator(char C) {
    return 0 <= C && C <= 32;
}

int getWordsCount(const char* s) {
    int count = 0;
    int len = strLen(s);
    for (int i = 0; i < len; i++) {
        if (!isSeparator(s[i]) && isSeparator(s[i + 1])) {
            count++;
        }
    }
    return count;
}

int getWordPosition(const char* s, int numOfWord) {
    int count = 0;
    int len = strLen(s);
    char prev = ' ';
    for (int i = 0; i < len; i++) {
        if (isSeparator(prev) && !isSeparator(s[i])) {
            if (count == numOfWord) {
                return i;
            }
            count++;
        }
        prev = s[i];
    }
    return -1;
}

//int getWordPosition(char* s, int numOfWord) {
//    int count = 0;
//    int len = strLen(s);
//    char S[20000] = " ";
//    strcat(S, s);
//    for (int i = 1; i < len; i++) {
//        if (isSeparator(S[i-1]) && !isSeparator(S[i])) {
//            if (count == numOfWord) {
//                return i - 1;
//            }
//            count++;
//        }
//    }
//    return -1;
//}

int getWordLength(const char* S, int numOfWord) {
    int pos = getWordPosition(S, numOfWord);
    if (pos == -1) return 0;

    int n = strLen(S);
    int count = 0;
    for (int i = pos; i < n; i++) {
        if (!isSeparator(S[i])) {
            count++;
        }
        else {
            break;
        }
    }
    return count;
}

void getWord(const char* S, int numOfWord, char* word) {
    word[0] = 0;
    int pos = getWordPosition(S, numOfWord);
    if (pos == -1) return;
    int len = getWordLength(S, numOfWord);
    for (int i = 0; i < len; i++) {
        word[i] = S[pos + i];
    }
    word[len] = 0;
}

int main(int argc, char* argv[])
{
    system("chcp 1251>>nul");
    setlocale(LC_ALL, "UKR");

    char FileName[300];
    strcpy(FileName, argv[1]);
    int width = atoi(argv[2]);// ширина колонки яку ми робимо
    int indent = atoi(argv[3]);//показує скільки пропусків в першому рядку абзаца
    showTextFile(FileName);
    
    FILE* F = fopen(FileName, "rt");
    if (!F) {
        cout << "ERROR: File not found!: " << FileName << endl;
        return 1;
    }

    FILE* G = fopen("result.txt", "wt");
    if (!G) {
        cout << "ERROR: Cannot create file!: " << "result.txt" << endl;
        fclose(F);
        return 2;
    }

    char s[20000];
    while (fgets(s, sizeof(s), F)) {
        /*int N = strLen(s);
        cout << "N= " << N << endl;*/
        int n = getWordsCount(s);
        cout << "n= " << n << endl;
       
        char resultLine[300] = "";
        for (int i = 0; i < indent; i++) {
            resultLine[i] = ' ';
        }
        resultLine[indent] = 0;

        int Len = indent;
        for (int i = 0; i < n; i++) {
            char word[300];
            getWord(s, i, word);
            //cout << i << ". " << word << endl;
            int len = strLen(word);
            if (i>0) len++;

            if (Len + len <= width) {
                if (i>0) strcat(resultLine, " ");
                strcat(resultLine, word);
                Len += len;
            }
            else {
                strcat(resultLine, "\n");
                fputs(resultLine, G);
                cout << resultLine;
                resultLine[0] = 0;
                strcat(resultLine, word);
                Len = len;
            }
        }
        fputs(resultLine, G);
        cout << "----------" << endl;
    }
    fclose(F);
    fclose(G);


    return 0;
}
