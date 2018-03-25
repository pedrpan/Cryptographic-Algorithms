#include <stdlib.h>
#include <stdio.h>

int getkeylen(char s[], int x);
double getfreqsqred(char t[]);

main()
{
  int cyphersize, keylen, i=1;
  char *cypher = malloc(sizeof(char));

  while((cypher[i-1] = getchar()) != EOF)
    cypher = realloc(cypher, (++i)*sizeof(char));
  cypher[i-1]='\0', cyphersize = i-1;
  keylen = getkeylen(cypher, cyphersize);
  printf("keylen %d", keylen);
}

int getkeylen(char s[], int x){
  int t, j, best;
  char search[x];
  double currentfreq, bestfreq = 1000000;

  int k = 0;
  for (t=1; t <= x / 26; ++t){
      for (j=0 ; j*t <= x; ++j)
        search[j] = s[t * j];
      search[++j] = '\0';
      if ((currentfreq = getfreqsqred(search)) < bestfreq)
        bestfreq = currentfreq, best = t;
  }
  return best;
}

double getfreqsqred(char t[]){
  int chrcount[26];
  int j = 0;
  int i, k;
  double x = 0.0;

  for (k=0; k < 26; ++k)
    chrcount[k]=0;
  while (t[j] != '\0')
    if ((i = t[j++] - 'a') >= 0 && i <= 25)
      chrcount[i]+=1;
  for (k=0; k < 26; ++k)
    x += (chrcount[k] / j) * (chrcount[k] / j);
  return x;
}
