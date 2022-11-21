
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int indexOf(char letter, char *alpha) {
  int index;
  for(int i = 0; i < 26; i++) {
    if(letter == alpha[i])
      return i;
  } 
}


void toUpper(char *text,int len) {
  for(int i = 0; i <len; ++i) {
    if(text[i] >='a' &&  text[i] <='z') {
      text[i] -=32;
    }
  } 
}
char* alphabets() {
  char *alpha = malloc(26*sizeof(char*));
  for(int i = 0, j=65; i<26, j<=90; ++i, ++j) {
    *(alpha + i) = j; 
  }
  return alpha;
}

void encrypt(char *plain,int key, char *C) {
  char *alpha = alphabets();
  for(int i=0; i<strlen(plain); ++i) {
    int index = indexOf(plain[i],alpha);
    index +=key;
    if(index > 25)
      index %=26;
    C[i] = alpha[index];
  }
}

void decrypt(char *cipher,int key, char *D) {
  char *alpha = alphabets();
  for(int i=0; i<strlen(cipher); ++i) {
    int index = indexOf(cipher[i],alpha);
    index -=key;
    if(index <0) {
      index %=26;
      if (index < 0) 
        index +=26;
    }
    D[i] = alpha[index];
  }
}
int main(int *argc, char **argv) {
  
  char P[100];    // plain text 
  char C[100];    // cipher text 
  char D[100];    // deciphered text
  printf("Enter ther plain text: ");
  fgets(P,100,stdin); 
  P[strcspn(P, "\n")]='\0';               // fgets use garera last ma `\n` character aauchha so teslai remove garna lai chai yo use gareko
                                        // Removing trailing newline character from fgets() input

  int len = strlen(P);
  toUpper(P,len);
  printf("The length of strin is %d\n",len);

  int K;
  printf("Enter the key: ");
  scanf("%d",&K);
  
  /* ENCRYPTION */
  encrypt(P,K,C);
  printf("The cipher text is: ");
  printf("%s\n",C);
  printf("================================================\n");
   /* DECRYPTION */
  printf("From above encrypted text: %s\n",C);
  decrypt(C,K,D); 
  
  printf("The decipher text is: ");
  printf("%s\n",D);
}

