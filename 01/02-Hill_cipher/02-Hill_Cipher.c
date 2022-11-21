  /* 

17 17 5  
21 18 21
2 2 19

  */


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
void multiply(int matrixA[][3], int matrixB[][30], int resMatrix[][30], int row, int colB) {
    for(int i=0;i<row;i++) {
        for(int j=0;j<colB;j++) {
            resMatrix[i][j] = 0;
            for(int k=0;k<row;k++) {
                resMatrix[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
}
void GCD(int a,int b){
    int rem,quo;
    while(b>0){
        rem = a%b;
        quo = a/b;
        a = b;
        b=rem;
    }
}
int ExtendedEuclideanAglorithm(int a, int b, int* x, int* y)
{
	if (a == 0) {
		*x = 0;
		*y = 1;
		return b;
	}

	int x1, y1; // To store results of recursive call
	int gcd = ExtendedEuclideanAglorithm(b % a, a, &x1, &y1);

	*x = y1 - (b / a) * x1;
	*y = x1;

	return gcd;
}
int ExtendedEuclidean(int a,int b){
	int x, y;
	GCD(a, b);
	int g = ExtendedEuclideanAglorithm(a, b, &x, &y);
    if(x<0)
        x = b+x;
	return x;
}

int mod(int A) {
  A%=26;
  if(A<0) {
      A%=26;
      if (A<0) 
        A+=26;
  }
  return A;
}

void matrixMod26(int matrix[][30],int row,int col) {
  for(int i=0; i<row; i++) {
    for(int j=0; j<col; j++) {
      matrix[i][j] = mod(matrix[i][j]);
    }
  }
}


void inverseMatrix(int key[][3], int inv[][3]) {
	int C[3][3]; 
	int A[3][3]; 
	C[0][0] = key[1][1] * key[2][2] - key[2][1] * key[1][2];
	C[0][1] = -(key[1][0] * key[2][2] - key[2][0] * key[1][2]);
	C[0][2] = key[1][0] * key[2][1] - key[1][1] * key[2][0];
	C[1][0] = -(key[0][1] * key[2][2] - key[2][1] * key[0][2]);
	C[1][1] = key[0][0] * key[2][2] - key[2][0] * key[0][2];
	C[1][2] = -(key[0][0] * key[2][1] - key[2][0] * key[0][1]);
	C[2][0] = key[0][1] * key[1][2] - key[0][2] * key[1][1];
	C[2][1] = -(key[0][0] * key[1][2] - key[1][0] * key[0][2]);
	C[2][2] = key[0][0] * key[1][1] - key[1][0] * key[0][1];
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			A[i][j] = C[j][i];
		}
	}
	int det = key[0][0] * C[0][0] + key[0][1] * C[0][1] + key[0][2] * C[0][2];
	
	if (det == 0 || det % 2 == 0 || det % 13 == 0) {
		printf("The text cannot be encrypted. Take valid key.\n");
		exit(1);
	}
	int invs = ExtendedEuclidean(mod(det),26);                /* multiplicative inverse of the determinant  */

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			inv[i][j] = A[i][j] * invs;
		}
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (inv[i][j] >= 0) {
				inv[i][j] = inv[i][j] % 26;
			}
			else {
				for (int x = 0;; x++) {
					if (x * 26 + inv[i][j] > 0) {
						inv[i][j] = x * 26 + inv[i][j];
						break;
					}
				}
			}
		}
	}
}


void encrypt(int plain[][30],int key[][3],int C[][30],int row,int colP) {
  multiply(key,plain,C,row,colP);  
  matrixMod26(C,row,colP);  
}

void decrypt(int cipher[][30],int keyInverse[][3],int D[][30],int row,int colP) {
  multiply(keyInverse,cipher,D,row,colP);  
  matrixMod26(D,row,colP);

}
int main() {

  char P[100];              // plain text 
  int Pm[30][30];           // matrix representation of plain text
  char C[100];              // cipher text 
  int Cm[30][30];           // matrix representation of cipher text
  char D[100];              // deciphered text
  int Dm[30][30];           // matrix representation of deciphered text
  int K[3][3];              // key in matrix 
  
  printf("Enter ther plain text: ");
  fgets(P,100,stdin); 
  P[strcspn(P, "\n")]='\0';              
  toUpper(P,strlen(P));
 
  int row=3;
  printf("Enter the key : \n");
  for(int i=0; i<row;i++){
    for(int j=0; j<row;j++){
      scanf("%d",&K[i][j]);
    }
  }


  /* Representing plain text into matrix */
  int k=0;
  int col = CeilValue(((float)strlen(P))/row);
  int i,j;

  /* 

17 17 5  
21 18 21
2 2 19

  */
  char plainMatrix[30][30];
  char *alpha=alphabets();
  for(i=0; i<col; i++) {
    for(j=0; j<row; j++) {
        Pm[j][i]=indexOf(P[k],alpha); 
        plainMatrix[j][i] = P[k];
        if(P[k]=='\0'){
          plainMatrix[j][i] = 'X';
          Pm[j][i]=indexOf('X',alpha);
        }
        k++;
    }
  }
  
     /* matrix representation of plain text */ 
  printf("The matrix of plain text is : \n");
  for(int i=0; i<row; i++) {
    for(int j=0; j<col; j++) {
      printf("%4c",plainMatrix[i][j]);
    }
    printf("\n");
  } 

  printf("The matrix of indices of plain text is : \n");
  for(int i=0; i<row;i++) {
    for(int j=0; j<col; j++){
      printf("%4d",Pm[i][j]);
    }
    printf("\n");
  }
  printf("\n");


 /* ENCRYPTION  */
  printf("Encrypting.....\n");
  printf("==========================================\n");
  encrypt(Pm,K,Cm,row,col);
  printf("Matrix obtained after encryption: \n");
  for(int i=0; i<row; i++) {
    for(int j=0; j<col; j++) {
      printf("%4d",Cm[i][j]);
    }
    printf("\n");
  }

  printf("\nLetters from above matrix in matrix form:\n");
  for(int i=0; i<row; i++) {
    for(int j=0; j<col; j++) {
      printf("%4c",alpha[Cm[i][j]]);
    }
    printf("\n");
  }
  printf("\n\n");
  printf("\n");
  k=0;
  for(i=0; i<col; i++) {
    for(j=0; j<row; j++) {
      C[k] = alpha[Cm[j][i]];
      k++;
    }
  }
  C[k] = '\0';

  printf("The cipher text is: %s \n\n\n",C);

  printf("Decrypting......\n");
  printf("==========================================\n");
/* inverse of the key*/
  int inv[3][3];
  inverseMatrix(K,inv);
  
  printf("The inverse of key is: \n");
  for(int i=0; i<row; ++i) {
    for(int j=0; j<row; ++j) {
      printf("%4d",inv[i][j]);
    }
    printf("\n");
  }
  printf("\n\n");

/*DECRYPTION*/
  decrypt(Cm,inv,Dm,row,col);
  for(int i=0; i<row; i++) {
    for(int j=0; j<col; j++) {
      printf("%4d",Dm[i][j]);
    }
    printf("\n");
  }

  printf("\n\n");
  for(int i=0; i<row; i++) {
    for(int j=0; j<col; j++) {
      printf("%4c",alpha[Dm[i][j]]);
    }
    printf("\n");
  }
  printf("\n\n");
  k=0;
  for(i=0; i<col; i++) {
    for(j=0; j<row; j++) {
      D[k] = alpha[Dm[j][i]];
      k++;
    }
  }
  D[k] = '\0';
  printf("The deciphered text is %s\n",D);
}
  /* 

17 17 5  
21 18 21
2 2 19

  */
