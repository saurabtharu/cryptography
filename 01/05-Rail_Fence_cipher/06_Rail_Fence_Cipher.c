#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int CeilValue(float num){
        if (num == (int)(num)){
                return num;
        }
        else if(num>=0){
                return (int)(num+1);
        }
        else{
                return (int)(num);
        }
}

void encrypt(char *plain,int depth, char *C) {
  int i;
  for(i=0;i<strlen(plain); i++){
    C[i] = plain[(i+(depth-1)*i)%(strlen(plain)-1)];
  }
  C[i-1] = plain[i-1];
  C[i] = '\0';
}
void decrypt(char *cipher,int depth, char *D) {
  int c = CeilValue(((float)strlen(cipher))/depth);  
  int i;
  for(i=0; i<strlen(cipher); ++i) {
    D[i] = cipher[(i + i *(c-1)) %(strlen(cipher)-1)]; 
  }
  D[i-1] = cipher[i-1];
  D[i] = '\0';
}
int main(int *argc, char **argv) {
  
  char P[100];    // plain text 
  char C[100];    // cipher text 
  char D[100];    // deciphered text
  printf("Enter ther plain text: ");
  fgets(P,100,stdin); 
  P[strcspn(P, "\n")]='\0';               // fgets use garera last ma `\n` character aauchha so teslai remove garna lai chai yo use gareko
                                        // Removing trailing newline character from fgets() input

  int depth;
  printf("Enter the depth: ");
  scanf("%d",&depth);
  
  /* ADJUSTING plain ACCORDING TO depth*/
  int temp = strlen(P)%depth; 
  char *adjustedPlain = malloc((strlen(P) + (depth - temp)) *sizeof(char*)); 
  if(temp!=0){
    int i;
    for(i=0;P[i]!='\0'; ++i)
      adjustedPlain[i] = P[i];
    for(int j=0; j<(depth - temp); ++j) {
      P[i+j] = 'x';
    }
  }

  /* ENCRYPTION */
  encrypt(P,depth,C);
  printf("The cipher text is: ");
  printf("%s\n",C);
  printf("================================================\n");
   /* DECRYPTION */
  printf("From above encrypted text: %s\n",C);
  decrypt(C,depth,D); 

  printf("The decipher text is: ");
  printf("%s\n",D);
}

