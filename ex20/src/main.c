#include<stdio.h>
#include<stdbool.h>
#include<string.h>

/*
Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

An input string is valid if:

    Open brackets must be closed by the same type of brackets.
    Open brackets must be closed in the correct order.
    Every close bracket has a corresponding open bracket of the same type.
*/


bool validation(char *s);

int main(){

char s[]="()[]{}";

/////////////////////////

    if (validation(s) == true) {
        printf("\n true");

    } else {
        printf("\n false");
    }

/////////////////////////

 return 0;   
}

bool validation(char *s) {
    int size = strlen(s);

    for (int i = 0; i < size; i++) {

        if (s[i] == '(' || s[i] == '[' || s[i] == '{') {

            for (int j = size - 1; j > i; j--) {

                if (s[j] == ')' && s[i] == '(') {
                    s[j] = ' ';
                    s[i] = ' ';
                    break;

                } else if (s[j] == ']' && s[i] == '[') {
                    s[j] = ' ';
                    s[i] = ' ';
                    break;

                } else if (s[j] == '}' && s[i] == '{') {
                    s[j] = ' ';
                    s[i] = ' ';
                    break;
                }
            }
        }
    }

    for (int i = 0; i < size; i++) {

        if (s[i] == '(' || s[i] == '[' || s[i] == '{' || s[i] == ')' || s[i] == ']' || s[i] == '}') {
            return false;
        }
    }

    return true;
}
