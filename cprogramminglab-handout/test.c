#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *s = "123456";
    
    for (int i = 0; s[i] != '\0'; i++) {
        printf("s[%d]: %c\n", i+1, s[i+1]);
    }
    char *copy = (char *)malloc(sizeof(char) * 6);
    strcpy(copy, s);
    for (int i = 0; s[i] != '\0'; i++) {
        printf("copy[%d]: %c\n", i+1, copy[i+1]);
    }
    return 0;
}