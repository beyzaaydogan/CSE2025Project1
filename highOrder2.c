
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <unistd.h>
#include <errno.h>


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
void insertTofirstOrder(ListNodePtr *sPtr, char value[]);


int main(){

        ListNodePtr startPtr = NULL; // initially there are no nodes
        struct dirent **namelist;
        struct dirent **namelistSub;
        FILE    *inputTxtFile;
        int numOfSubDirs, numOfSubFiles, j, i ;

        numOfSubDirs = scandir("./dataset", &namelist, NULL, alphasort); // . yerine /home/beyza/C-workspace/2025Projects gelebilir
         
        if (numOfSubDirs < 0)
            perror("scandir");
         
        else {

            char path[100] ="./dataset/"; 
            printf("number of sub directories are %d\n", numOfSubDirs);
            printf("%s\n", namelist[0]->d_name );
            printf("%s\n", namelist[1]->d_name );
            printf("%s\n", namelist[2]->d_name );
            printf("%s\n", namelist[3]->d_name );
            printf("%s\n", namelist[4]->d_name );
                                  
              for( i = 2 ; i < numOfSubDirs ; i++){
                  char dirPath[100], filePath[100];  
                  strcpy(dirPath, path);
                  strcat(dirPath , namelist[i]->d_name );
                  numOfSubFiles = scandir(dirPath, &namelistSub, NULL, alphasort);
                 

                  for(j = 2 ; j < numOfSubFiles ; j++){

                    
                      printf("\n\n\n\n\nI am in %s\n\n",namelistSub[j]->d_name );
                      strcpy(filePath, dirPath);
                      strcat(filePath, "/"); 
                      strcat(filePath, namelistSub[j]->d_name); 
                      printf("Filepath is --> %s\n\n\n\n", filePath );
                      inputTxtFile = fopen(filePath, "r");
                      if (inputTxtFile == NULL) { 
                          printf("Cannot open file \n"); 
                          exit(0); 
                      } 
                     

                      int count = 0;
                     
                      char word[40];
                      while( fscanf(inputTxtFile,"%s", &word[0]) == 1 ){
                        //puts("word is ----> ");
                        //puts(word);
                        insert(&startPtr, word); // insert item in list
                        printList(startPtr);
                        ++count;
                        }
                     
                      printf("\nThis file has %d words in it.", count);
                    
                      fclose(inputTxtFile); 

                   }


                 }                 

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

      while(currentPtr != NULL){
        if(strcmp(currentPtr->word, value) == 0){
           return;
        }
        currentPtr = currentPtr->nextPtr;
      }

      currentPtr = *sPtr;

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
   




  void insertTofirstOrder(ListNodePtr *sPtr, char value[]){ 
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
int isEmpty(ListNodePtr sPtr){ 
   return sPtr == NULL;
} 


void printList(ListNodePtr currentPtr){ 
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
