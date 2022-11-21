#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char* alphabets() {
  char *alpha = malloc(26*sizeof(char*));
  for(int i = 0, j=65; i<26, j<=90; ++i, ++j) {
    *(alpha + i) = j; 
  }
  return alpha;
}
void toUpper(char *text,int len) {
  for(int i = 0; i <len; ++i) {
    if(text[i] >='a' &&  text[i] <='z') {
      text[i] -=32;
    }
  } 
}

int indexOf(char letter, char *alpha) {
  int index;
  for(int i = 0; i < 26; i++) {
    if(letter == alpha[i])
      return i;
  } 
}

void encrypt(char *plain,char *key,char *C) {
  int indexP, indexK, index;
  char *alpha=alphabets();
  for(int i=0,j=0;i<strlen(plain),j<strlen(plain); ++i,++j) {
    indexP = indexOf(plain[i],alpha);
    indexK = indexOf(key[j],alpha);
    index = indexP + indexK;
    if (index > 25) 
        index %=26;
    C[i] = alpha[index];
  } 
}

void decrypt(char *cipher, char *key, char *D) {
  int indexP, indexK, index;
  char *alpha=alphabets();
  for(int i=0; i<strlen(cipher); ++i) {
    index = indexOf(cipher[i],alpha);
    indexK = indexOf(key[i],alpha);
    indexP = index - indexK; 
    if(indexP <0) {
      indexP %=26;
      if (indexP < 0) 
        indexP +=26;
    }
    D[i] = alpha[indexP];
  }
}
int main() {

  char P[100];    // plain text 
  char Key[100];
  char C[100];    // cipher text 
  char D[100];    // deciphered text

  printf("Enter ther plain text: ");
  fgets(P,100,stdin); 
  P[strcspn(P, "\n")]='\0';              
  toUpper(P,strlen(P));


  printf("Enter the key: ");
  fgets(Key,100,stdin); 
  Key[strcspn(Key, "\n")]='\0';              
  toUpper(Key,strlen(Key));
  
  char *K = malloc(strlen(P)*sizeof(char*));
  for(int i=0; P[i]!='\0'; ++i) {
    K[i] = Key[i%strlen(Key)];
  }

  /* ENCRYPTION */
  encrypt(P,K,C);
  printf("\n\nThe cipher text is: ");
  printf("%s\n",C);


  printf("================================================\n");
   /* DECRYPTION */
  decrypt(C,K,D);
  printf("From above encrypted text: %s\n",C);
  printf("The deciphered text is: ");
  printf("%s\n",D);
}
