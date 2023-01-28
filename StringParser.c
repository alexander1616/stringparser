/**********************************************
*  String Parser                              *
*  Alexander Chan                             *
*  1/27/2023                                  *
**********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct SElement_t{
  char word[4];
  int wlen;
  struct SElement_t* next;
} SElement_t;

#define MAX_ELEMENT 8
SElement_t elementDict[MAX_ELEMENT];
SElement_t* head = NULL;
SElement_t* fhead = NULL;
int tcount = 0;

void printElementItem(SElement_t* p){
  char tempword[5];
  strncpy(tempword, p->word, 4);
  tempword[4] = 0; 
  printf("Word:[%-4s] len:[%d] next:[%p]\n", tempword, p->wlen, p->next);
};

void printElementArray(){
  SElement_t *p = &elementDict[0];
  for (int i = 0; i < MAX_ELEMENT; i++){
    printElementItem(p++);
  };
};

void printFreeLink(){
  SElement_t *q;
  printf("\nFree Link\n");
  for (q = fhead; q; q = q->next){
    printElementItem(q);
  };
};

void printElementLink(){
  SElement_t *q;
  printf("\nElement Link\n");
  for (q = head; q; q = q->next){
    printElementItem(q);
  };
};

SElement_t* allocElement(){
  SElement_t* p;
  p = fhead;
  if (p){
    fhead = fhead->next;
  }
  return p;
}

void freeElement(SElement_t* p){
  if (p){
    p->next = fhead;
    fhead = p;
  }
}

void toUpperWord(char* src, char* dst){
  char c;
  for(int i = 0; i < 4; i++){
    c = *src;
    if(islower(c)){
      c = toupper(c);
    }
    *dst = c;
    src ++;
    dst ++;
  };
};

int cmpElement(SElement_t* p1, SElement_t* p2){
  char tempp1[4];
  char tempp2[4];
  toUpperWord(p1->word, tempp1);
  toUpperWord(p2->word, tempp2);
  int value = strncmp(tempp1, tempp2, 4);
  if (value == 0){
    value = p1->wlen - p2->wlen;
  }
  return value;
}

int cmpXElement(SElement_t* p1, SElement_t* p2){
  int value = strncmp(p1->word, p2->word, 4);
  if (value == 0){
    value = p1->wlen - p2->wlen;
  }
  return value;
}

int acompare(const void* a, const void* b){
  SElement_t* *p1 = (SElement_t **) a;
  SElement_t* *p2 = (SElement_t **) b;
  return cmpXElement(*p1, *p2);
}

void sortElement(){
  SElement_t* eArray[MAX_ELEMENT];
  for (int i = 0; i < tcount; i++){
    eArray[i] = &elementDict[i];
  }
  qsort(eArray, tcount, sizeof(SElement_t *), acompare);

  head = 0;
  for (int i = tcount - 1; i >= 0; i--){
    eArray[i]->next = head;
    head = eArray[i];
  };
  printElementLink();
};

SElement_t* saveToken(char* s, int w){
  if (tcount >= MAX_ELEMENT){
    printf("No memory.\n");
    return 0;
  };
  SElement_t *p;
  p = &elementDict[tcount];
  strncpy(p->word, s, 4);
  p->wlen = w;
  p->next = head;
  head = p;
  tcount++;
  //printf("SaveToken: tcount[%d] word[%s] length[%d] next[%p]\n", tcount, p->word, p->wlen, p->next);
  return p;
};

SElement_t* findToken(char *s, int w){
  //printf("FindToken s:[%s], w:[%d]\n", s, w);
  for (int i=0; i < tcount; i++){
    if (!strncmp(s, elementDict[i].word, 4) && elementDict[i].wlen == w){
      return &elementDict[i];
    } 
  }
  return NULL;
};

int processToken(char* s){
  int w = strlen(s);
  SElement_t* test1 = findToken(s, w);
  if (test1 == 0){
    test1 = saveToken(s, w);
    if (test1 == 0){
      return -1;
    }
    test1->wlen = w;
  } else {
    printf("Found a duplicate [%s]\n", s);
  }
  return 0;
};

int allowedTable[256] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};

int fetchToken(FILE *fp, int (*func)(char *)){
  int x;
  char s[1000];
  int cur;
  int counter;
  int numToken;
  int state;

  counter = 0;
  numToken = 0;

  do{
    cur = fgetc(fp);    
    state = allowedTable[cur];
    if (state == 1 || cur == EOF){
      if (counter > 0){
        s[counter] = 0;
        numToken++;
        func(s);
        counter = 0;
      };
    } else {
      s[counter] = cur;
      counter++;
    };    
  } while (cur != '\n');
  sortElement();
  return numToken;
};

void readString(FILE *fp){
  int check;
  check = fetchToken(fp, processToken);
  if (check == -1){
    exit(1);
  };
};

void initRoutine(){
  head = NULL;
  fhead = NULL;
  tcount = 0;
  memset(elementDict, 0, sizeof(elementDict));
};

void createFreeElementList(){
  SElement_t * p;
  p = &elementDict[tcount];
  for (int i = tcount; i < MAX_ELEMENT; i++, p++){
    freeElement(p);
  }
  printFreeLink();
};

/******************************************
* Functions supported by Interactive Mode *
******************************************/
void cmdDeleteWord(char *s){
  int len = strlen(s);
  SElement_t temp;
  strncpy(temp.word, s, 4);
  temp.wlen = len;
  SElement_t * ip;
  ip = head;
  SElement_t * pp = 0;
  while (ip){
    int val = cmpXElement(&temp, ip);
    if (val == 0){
      if(!pp){
          head = ip->next;
        } else {
          pp->next = ip->next;
        };
        freeElement(ip);
        printf("Deleted: %s\n", s);
        return;
    } else if (val < 0){
      break;
    }
    pp = ip;
    ip = ip->next;
  }
  printf("Word not found: %s\n", s);
}

void cmdAddWord(char *s){
  int len = strlen(s);
  SElement_t temp;
  strncpy(temp.word, s, 4);
  temp.wlen = len;
  SElement_t * ip;
  ip = head;
  SElement_t * pp = 0;
  while (ip){
    int val = cmpXElement(&temp, ip);
    if (val == 0){
      printf("Word already in dictionary: %s\n", s);
      return;
    } else if (val < 0){
      SElement_t* xp = allocElement();
      if(!xp) {
        printf("Failed to add: %s, no memory.\n", s);
        return;
      }
      strncpy(xp->word, s, 4);
      xp->wlen = len;
      xp->next = ip;
      if(!pp) { 
          head = xp;
      } else {
        pp->next = xp;
      };
      printf("Word added: %s\n", s);
      return;
    }
    pp = ip;
    ip = ip->next;
  }
  SElement_t* xp = allocElement();
  if(!xp) {
    printf("Failed to add: %s, no memory.\n", s);
    return;
  }
  strncpy(xp->word, s, 4);
  xp->wlen = len;
  if (!pp){
    xp->next = head;
    head = xp;
  } else {
    pp->next = xp;
    xp->next = 0;
  }
  printf("Word added: %s\n", s);
}

void cmdSearchWord(char *s){
  int len = strlen(s);
  SElement_t temp;
  strncpy(temp.word, s, 4);
  temp.wlen = len;
  SElement_t * ip;
  ip = head;
  while (ip){
    int val = cmpElement(&temp, ip);
    if (val == 0){
      printf("Word in dictionary: %s ", s);
      printElementItem(ip);
      return;
    } 
    ip = ip->next;
  }
 printf("Word not found: %s\n", s);
}

void cmdxSearchWord(char *s){
  int len = strlen(s);
  SElement_t temp;
  strncpy(temp.word, s, 4);
  temp.wlen = len;
  SElement_t * ip;
  ip = head;
  while (ip){
    int val = cmpXElement(&temp, ip);
    if (val == 0){
      printf("Word in dictionary: %s ", s);
      printElementItem(ip);
      return;
    } 
    ip = ip->next;
  }
 printf("Word not found: %s\n", s);
}

/* Interactive Command Driver */
void interactiveMode(){
  char buff[256];
  char cmd[256];
  char param[256];
  int num;
  while(1){
    printf("\n");
    printf("========================================================\n");
    printf("Commands: quit          - exit program\n");
    printf("          print         - print dictionary\n");
    printf("          printfree     - print free list\n");
    printf("          add     word  - add word in dictionary\n");
    printf("          delete  word  - delete word from dictionary\n");
    printf("          search  word  - search word non case sensitive\n");
    printf("          xsearch word  - search word case sensitive\n");
    printf("Enter a command: \n");
    if (!fgets(buff, 255, stdin)){
      printf("Bye.\n");
      return;
    };
    buff[255] = 0;
    num = sscanf(buff, "%s%s", cmd, param);
    if (num == 0){
      continue;
    }
    if (num == 1){
      if (!strcmp(cmd, "quit")){
        printf("Bye.\n");
        return;
      }
      if (!strcmp(cmd, "print")){
        printElementLink();
        continue;
      }
      if (!strcmp(cmd, "printfree")) {
        printFreeLink();
        continue;
      }
    } else {
      if (!strcmp(cmd, "delete")) {
        cmdDeleteWord(param);
        continue;
      }
      if (!strcmp (cmd, "add")){
        cmdAddWord(param);
        continue;
      }
      if (!strcmp (cmd, "search")){
        cmdSearchWord(param);
        continue;
      }
      if (!strcmp (cmd, "xsearch")){
        cmdxSearchWord(param);
        continue;
      }
    }
  }
}

int main(int ac, char* av[]) {
  initRoutine();
  /**************************** 
  * Programmer Challenge: 3-5 *
  ****************************/
  printf("Enter a string : \n");
  readString(stdin);
  /****************************
  * Programmer Challenge: 6-9 *
  ****************************/
  createFreeElementList();
  interactiveMode();
  return 0;
}