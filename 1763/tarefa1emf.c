#include<stdio.h>

/////////////////////////////////////////////

/*

1763
A string s is nice if, for every letter of the alphabet that s contains, it appears both in uppercase and lowercase. 
For example, "abABB" is nice because 'A' and 'a' appear, and 'B' and 'b' appear. However, "abA" is not because 'b' appears, but 'B' does not.

Given a string s, return the longest substring of s that is nice. If there are multiple, return the substring of the earliest occurrence. 
If there are none, return an empty string. 
*/

/////////////////////////////////////////////

void longestNiceSubstring(char s[20]);

int main() {

  char s[20] = "aAaaAaba";

  printf("bonjour\n");

  longestNiceSubstring(s);

  return 0;
}

/////////////////////////////////////////////

void longestNiceSubstring(char s[20]) {
  char temp[20];
int j = 0;

for (int i = 0; i < 20; i++) {

   // Find the A/a

    if (s[i] == 'a' || s[i] == 'A' || s[i] == 'b' || s[i] == 'B') {
      for (int j = 0; j < 20; j++) {

      // loop the A/a

        if (s[j + 1] == 'A' || s[j + 1] == 'a' || s[j + 1] == 'B' || s[j + 1] == 'b') {
          temp[j] = s[j];
            } else {
           break;
      }
    }
  }
}

char asw[20];

  for (int i = 0; i < 20; i++) {
    asw[i] = temp[i];
}

printf("%s \n", asw);

}