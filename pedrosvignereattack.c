#include <stdlib.h>
#include <stdio.h>
#define ALPSIZE 26

int getkeylen(char s[], int x);
double getfreq(char t[]);
void getkey(char a[], char b[], int c, int d);
int properform(char s[]);

main()
{
  int cyphersize, keylen, i=1;
  char *cypher = malloc(1);

  while((cypher[i-1] = getchar()) != EOF)
    cypher = realloc(cypher, ++i);
  cypher[i-1]='\0';
  printf("The cypher is \n");
  printf(cypher);
  cyphersize = properform(cypher);
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
  char searchkey[x+1];
  char search[x+1];
  double currentfreq, bestfreq = 1000000;

  for (t=1; t <= x / (ALPSIZE); ++t){
    getkey(searchkey, s, t, x);
    for (j=0 ; j < x; ++j)
      search[j] = (((s[j] - 'a')+(searchkey[j % t] - 'a')) % ALPSIZE) +'a';
    search[++j] = '\0';
    if ((currentfreq = getfreq(search)) < bestfreq)
      bestfreq = currentfreq, best = t;
  printf("\n when t = %d the freq is %lf", t, currentfreq);
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
      chrcount[ t[j++] - 'a']+=1;
  for (k=0; k < ALPSIZE; ++k)
    x += (chrcount[k] / j) * (chrcount[k] / j);
  x -= 0.065497;
  return x>0 ? x : -x ;
}

double getfreqtwo(char t[]){
  double chrcount[ALPSIZE];
  int j = 0;
  int i, k;
  double y = 0.0;
  double x[26];
  x[0] =0.08167;
  x[1] =0.01492;
  x[2] =0.02782;
  x[3] =0.04253;
  x[4] =0.12702;
  x[5] =0.02228;
  x[6] =0.02015;
  x[7] =0.06094;
  x[8] =0.06966;
  x[9] =0.00153;
  x[10] =0.00772;
  x[11] =0.04025;
  x[12] =0.02406;
  x[13] =0.06749;
  x[14] =0.07507;
  x[15] =0.01929;
  x[16] =0.00095;
  x[17] =0.05987;
  x[18] =0.06327;
  x[19] =0.09056;
  x[20] =0.02758;
  x[21] =0.00978;
  x[22] =0.02360;
  x[23] =0.00150;
  x[24] =0.01974;
  x[25] =0.00074;

  for (k=0; k < ALPSIZE; ++k)
    chrcount[k]=0;

  while (t[j] != '\0')
    if ((i = t[j++] - 'a') >= 0 && i <= ALPSIZE - 1)
      chrcount[i]+=1;
  for (k=0; k < ALPSIZE; ++k)
    y += (chrcount[k] / j) * x[k];
  y -= 0.065497;
  return y>0 ? y : -y ;
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
      if ((currentfreq = getfreqtwo(search)) < bestfreq)
        bestfreq = currentfreq, best = k;
    }
    a[i] = 'a' + best;
  }
  a[i]='\0';
}


int properform(char s[]){
  int c, j = 0, i = 0;

  while (s[i]!='\0')
    if ((c = s[i++] - 'a') >= 0 && c <= ALPSIZE-1)
      s[j++]=s[i-1];
  s[j] = '\0';
  return j;
}
