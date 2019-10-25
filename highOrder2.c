
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#define MAX 1024

// self-referential structure                       
struct listNode {                                      
   char word[80]; // each listNode contains a character 
   struct listNode *nextPtr; // pointer to next node
   struct listNode *firstPtr; 
   struct listNode *secondPtr;
   struct listNode *thirdPtr; 
   
}; 


typedef struct listNode ListNode; // synonym for struct listNode
typedef ListNode * ListNodePtr; // synonym for ListNode*

// prototypes
void insert(ListNodePtr *sPtr, char value[]);
int isEmpty(ListNodePtr sPtr);
void printList(ListNodePtr currentPtr);


int main(){
/*
        // DIR* FD;
         struct dirent **namelist;
         struct dirent **namelistSub;
         struct dirent* in_file;
         FILE    *entry_file;
          char words[MAXL];
         // char    buffer[BUFSIZ];
    
         int n, i, x, j ;

         n = scandir("./dataset", &namelist, NULL, alphasort); // . yerine /home/beyza/C-workspace/2025Projects gelebilir
         if (n < 0)
             perror("scandir");
         else {

                  char path[100] ="./dataset/"; 
                 printf("n is %d\n", n);
                 printf("%s\n", namelist[0]->d_name );
                 printf("%s\n", namelist[1]->d_name );
                 printf("%s\n", namelist[2]->d_name );
                 printf("%s\n", namelist[3]->d_name );
                 printf("%s\n", namelist[4]->d_name );
                                  
                 for( i = 2 ; i < n ; i++){
                  char onPath[100]  ;  
                  strcpy(onPath,path);
                  strcat(onPath , namelist[i]->d_name );
                  x = scandir(onPath, &namelistSub, NULL, alphasort);
                 // FD = opendir (onPath);
                    // in_file  = readdir(FD);
                  for(j = 2 ; j < x ; j++){

                    entry_file = fopen(namelistSub[j]->d_name, "r");
                    printf("I am in %s\n",namelistSub[j]->d_name );
                   }


                 }                 

         }*/


            ListNodePtr startPtr = NULL; // initially there are no nodes
           char item[80]; // char entered by user


            unsigned int choice; // user's choice
            scanf("%u", &choice);

   // loop while user does not choose 3
   while (choice != 3) { 

            
            printf("%s", "Enter a word: ");
            scanf("\n%s", item);
            insert(&startPtr, item); // insert item in list
            printList(startPtr);
            printf("%s", "? ");
            scanf("%u", &choice);

}




        
         return 1;
       }



  void insert(ListNodePtr *sPtr, char value[])
{ 
   ListNodePtr newPtr = malloc(sizeof(ListNode)); // create node

   if (newPtr != NULL) { // is space available
    // size_t destination_size = sizeof (array2);
     strncpy(newPtr->word, value, 80);
     newPtr->word[80 - 1] = '\0';

      //newPtr->word = value; // place value in node
      newPtr->nextPtr = NULL; // node does not link to another node

      ListNodePtr previousPtr = NULL;
      ListNodePtr currentPtr = *sPtr;

      // loop to find the correct location in the list       
      while (currentPtr != NULL && (int)value[0] > (int)currentPtr->word[0]) {
         previousPtr = currentPtr; // walk to ...               
         currentPtr = currentPtr->nextPtr; // ... next node 
      }                                          

      // insert new node at beginning of list
      if (previousPtr == NULL) { 
         newPtr->nextPtr = *sPtr;
         *sPtr = newPtr;
      } 
      else { // insert new node between previousPtr and currentPtr
         previousPtr->nextPtr = newPtr;
         newPtr->nextPtr = currentPtr;
      } 
   } 
   else {
      printf("%s not inserted. No memory available.\n", value);
   } 
}      
   



// return 1 if the list is empty, 0 otherwise
int isEmpty(ListNodePtr sPtr)
{ 
   return sPtr == NULL;
} 


void printList(ListNodePtr currentPtr)
{ 
   // if list is empty
   if (isEmpty(currentPtr)) {
      puts("List is empty.\n");
   } 
   else { 
      puts("The list is:");

      // while not the end of the list
      while (currentPtr != NULL) { 
        //puts("ın while");
         printf("%s --> ", currentPtr->word);
         currentPtr = currentPtr->nextPtr;   
      } 

      puts("NULL\n");
   } 
} 
