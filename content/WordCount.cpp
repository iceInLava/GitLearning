#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME_LENGTH 100
#define MAX_LINE_LENGTH 1000

// 统计字符数
int count_characters(FILE* fp) {
    int count = 0;
    char c;
    while ((c = fgetc(fp)) != EOF) {
        count++;
    }
    return count;
}

// 统计单词数
int count_words(FILE* fp) {
    int count = 0;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
        char* p = strtok(line, " ,\n\t"); // 按空格、逗号、换行符、制表符分割单词
        while (p != NULL) {
            count++;
            p = strtok(NULL, " ,\n\t");
        }
    }
    return count;
}

int main(int argc, char* argv[]) {
    char fpname[MAX_FILENAME_LENGTH] = "FxxkYou.txt"; // 默认文件名
    FILE* fp;
    int count;

    // 处理命令行参数
    if (argc == 3 && strcmp(argv[1], "-c") == 0) {
        // 统计字符数
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
        // 统计单词数
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
		fseek(fp, 0, SEEK_END); // 将文件指针移到文件末尾
    	long size = ftell(fp);  // 获取文件大小
    	rewind(fp);             // 将文件指针移到文件开头

    	char *content = (char *)malloc(size + 1); // 分配内存
    	fread(content, size, 1, fp);            // 读取文件内容
    	content[size] = '\0';                     // 添加字符串结尾符号

    	printf("%s\n", content);  // 输出文件内容
    	fclose(fp);
    	free(content);
	} 
    else {
        printf("Usage: WordCount -c/-w [input_fp_name]\n");
        return 1;
    }

    return 0;
}
