#include <stdlib.h>
#include <stdio.h>
#define ALPSIZE 26

int getkeylen(char s[], int x);
double getfreq(char t[]);
void getkey(char a[], char b[], int c, int d);
int lowercaseform(char s[]);

main()
{
  int cyphersize, keylen, i=1;
  char *cypher = malloc(1);

  while((cypher[i-1] = getchar()) != EOF)
    cypher = realloc(cypher, ++i);
  cypher[i-1]='\0';
  printf("The cypher is \n");
  printf(cypher);
  cyphersize = lowercaseform(cypher);
  printf("\nThe cypher in proper form is \n");
  printf(cypher);
  keylen = getkeylen(cypher, cyphersize);
  char key[keylen + 1];
  getkey(key, cypher, keylen, cyphersize);
  printf("\nThe key length is %d\n", keylen);
  printf("The key is \n");
  printf(key);
  printf("\nand the encrypted message is \n");
  int p;
  for (p=0; cypher[p]!='\0'; ++p)
    printf("%c", (((cypher[p] - 'a')+(key[p % keylen] - 'a')) % ALPSIZE) +'a'  );
}

int getkeylen(char s[], int x){
  int t, j, best;
  char search[x];
  double currentfreq, bestfreq = 1000000;

  int k = 0;
  for (t=1; t <= x / ALPSIZE; ++t){
    for (j=0 ; j*t <= x; ++j)
      search[j] = s[t * j];
    search[++j] = '\0';
    if ((currentfreq = getfreq(search)) < bestfreq)
      bestfreq = currentfreq, best = t;
  }
  return best;
}

double getfreq(char t[]){
  double chrcount[ALPSIZE];
  int j = 0;
  int i, k;
  double x = 0.0;

  for (k=0; k < ALPSIZE; ++k)
    chrcount[k]=0;

  while (t[j] != '\0')
    if ((i = t[j++] - 'a') >= 0 && i <= ALPSIZE - 1)
      chrcount[i]+=1;
  for (k=0; k < ALPSIZE; ++k)
    x += (chrcount[k] / j) * (chrcount[k] / j);
  x -= 0.065497;
  return x>0 ? x : -x ;
}

void getkey(char a[], char b[], int c, int d){
  int i, j, k, l, m, x, best;
  char buff[d / c + 1];
  char search[d / c + 2];
  double currentfreq, bestfreq;

  for (i=0; i < c; ++i){
    m=0, best = -1;
    bestfreq = 1000000;
    for (j=0; i + j * c <= d ; ++j)
      if ((x = b[i + j * c] - 'a') <= ALPSIZE - 1 && x >= 0)
        buff[m++] = b[i + j * c];
    buff[m]='\0';
    for (k=0; k<ALPSIZE; ++k){
      for (l=0; l<m; ++l)
        search[l] = (((buff[l] - 'a') + k) % ALPSIZE) + 'a';
      search[++l]='\0';
      if ((currentfreq = getfreq(search)) < bestfreq)
        bestfreq = currentfreq, best = k;
    }
    a[i] = 'a' + best;
  }
  a[i]='\0';
}


int lowercaseform(char s[]){
  int c, j = 0, i = 0;

  while (s[i]!='\0')
    if ((c = s[i++] - 'a') >= 0 && c <= ALPSIZE-1)
      s[j++]=s[i-1];
  s[j] = '\0';
  return j;
}
