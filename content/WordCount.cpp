#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME_LENGTH 100
#define MAX_LINE_LENGTH 1000

// ͳ���ַ���
int count_characters(FILE* fp) {
    int count = 0;
    char c;
    while ((c = fgetc(fp)) != EOF) {
        count++;
    }
    return count;
}

// ͳ�Ƶ�����
int count_words(FILE* fp) {
    int count = 0;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
        char* p = strtok(line, " ,\n\t"); // ���ո񡢶��š����з����Ʊ���ָ��
        while (p != NULL) {
            count++;
            p = strtok(NULL, " ,\n\t");
        }
    }
    return count;
}

int main(int argc, char* argv[]) {
    char fpname[MAX_FILENAME_LENGTH] = "FxxkYou.txt"; // Ĭ���ļ���
    FILE* fp;
    int count;

    // ���������в���
    if (argc == 3 && strcmp(argv[1], "-c") == 0) {
        // ͳ���ַ���
        fp = fopen(argv[2], "r");
        if (fp == NULL) {
            printf("Cannot open file %s\n", argv[2]);
            return 1;
        }
        count = count_characters(fp);
        printf("Character count: %d\n", count);
        fclose(fp);
    }
    else if (argc == 3 && strcmp(argv[1], "-w") == 0) {
        // ͳ�Ƶ�����
        fp = fopen(argv[2], "r");
        if (fp == NULL) {
            printf("Cannot open file %s\n", argv[2]);
            return 1;
        }
        count = count_words(fp);
        printf("Word count: %d\n", count);
        fclose(fp);
    }else if(argc == 3 && strcmp(argv[1], "-all") == 0){
    	fp = fopen(argv[2], "r");
    	if (fp == NULL){
    		printf("Cannot open file %s\n", argv[2]);
    		return 1;
		}
		fseek(fp, 0, SEEK_END); // ���ļ�ָ���Ƶ��ļ�ĩβ
    	long size = ftell(fp);  // ��ȡ�ļ���С
    	rewind(fp);             // ���ļ�ָ���Ƶ��ļ���ͷ

    	char *content = (char *)malloc(size + 1); // �����ڴ�
    	fread(content, size, 1, fp);            // ��ȡ�ļ�����
    	content[size] = '\0';                     // ����ַ�����β����

    	printf("%s\n", content);  // ����ļ�����
    	fclose(fp);
    	free(content);
	} 
    else {
        printf("Usage: WordCount -c/-w [input_fp_name]\n");
        return 1;
    }

    return 0;
}
