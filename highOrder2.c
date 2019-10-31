
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
//#include <locale.h>


struct firstOrderNode;     

struct listNode {                                      
    char word[80];  
    struct listNode *nextPtr; 
    struct firstOrderNode *firstPtr; 
    struct listNode *secondPtr;
    struct listNode *thirdPtr; 
   
}; 

struct firstOrderNode {
    struct firstOrderNode *nextPtr;
    struct listNode *firstOrderPtr;
};


typedef struct listNode ListNode; // synonym for struct listNode
typedef ListNode * ListNodePtr; // synonym for ListNode*

typedef struct firstOrderNode FirstOrderNode; // synonym for struct firstOrderNode 
typedef FirstOrderNode * FirstOrderNodePtr; // synonym for FirstOrderNode *



void insert(ListNodePtr *sPtr, char value[]);
int isEmpty(ListNodePtr sPtr);
void printMasterList(ListNodePtr currentPtr);
void createFirstOrder(ListNodePtr *sPtr, FILE *file);
ListNodePtr searchInFile(ListNodePtr wordPtr, char wordInFile[]);

int main(){
       // setlocale(LC_CTYPE, "tr_TR.UTF-8");
        ListNodePtr startPtr = NULL; // initially there are no nodes
        struct dirent **namelist;
        struct dirent **namelistSub;
        FILE *inputTxtFile;
        int numOfSubDirs, numOfSubFiles, j, i ;

        numOfSubDirs = scandir("./dataset", &namelist, NULL, alphasort); // . yerine /home/beyza/C-workspace/2025Projects gelebilir
        char path[100] ="./dataset/"; 
         
        if (numOfSubDirs < 0)
            perror("scandir");
         
        else {

            printf(" Number of sub directories are %d\n", numOfSubDirs);
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
                      inputTxtFile = fopen(filePath, "r"); //ccs=UTF-8");
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
                        ++count;
                        }
                     
                      printf("\nThis file has %d words in it.", count);
                    
                      fclose(inputTxtFile); 

                   }


                 }                 
                        printMasterList(startPtr);

         }














         for( i = 2 ; i < numOfSubDirs ; i++){
                  char dirPath[100], filePath[100];  
                  strcpy(dirPath, path);
                  strcat(dirPath , namelist[i]->d_name );
                  numOfSubFiles = scandir(dirPath, &namelistSub, NULL, alphasort);
                 

                  for(j = 2 ; j < numOfSubFiles ; j++){

                    
                      strcpy(filePath, dirPath);
                      strcat(filePath, "/"); 
                      strcat(filePath, namelistSub[j]->d_name); 
                      inputTxtFile = fopen(filePath, "r"); //ccs=UTF-8");
                      if (inputTxtFile == NULL) { 
                          printf("Cannot open file \n"); 
                          exit(0); 
                      } 
                      
                      createFirstOrder(&startPtr, inputTxtFile);

                      fclose(inputTxtFile); 

                   }
                 
                 }                 
                       
          // printf("startPtr is %s\n",startPtr->word);
          // printf("firstOrderPtr is %s\n", startPtr->firstPtr->firstOrderPtr->word);



        
         return 1;
       }




  void insert(ListNodePtr *sPtr, char value[]){

      ListNodePtr newPtr = malloc(sizeof(ListNode)); // create node

      if (newPtr != NULL) { // is space available
            //size_t destination_size = sizeof (array2);
            strncpy(newPtr->word, value, 80);
            newPtr->word[80 - 1] = '\0';

            //newPtr->word = value; // place value in node
            newPtr->nextPtr = NULL; // node does not link to another node

            ListNodePtr previousPtr = NULL;
            ListNodePtr currentPtr = *sPtr;

            while(currentPtr != NULL){
                
                if(strcmp(currentPtr->word, value) == 0){//checking if the word we want to instert exists
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
   




  void createFirstOrder(ListNodePtr *sPtr, FILE *file){ 
      
      char word[40];
      fscanf(file, "%s", &word[0]);
      ListNodePtr wordInTxt = searchInFile(*sPtr, word);
      FirstOrderNodePtr tmp = malloc(sizeof(FirstOrderNode));
      fscanf(file, "%s", &word[0]);
      tmp->firstOrderPtr = searchInFile(*sPtr, word);
      //tmp->nextPtr = NULL;
      wordInTxt->firstPtr = tmp;
      
      while( fscanf(file,"%s", &word[0]) == 1 && wordInTxt->firstPtr != NULL){
        FirstOrderNodePtr tmp = malloc(sizeof(FirstOrderNode));
        tmp->firstOrderPtr = searchInFile(*sPtr, word);
        wordInTxt->firstPtr= tmp;
        wordInTxt->firstPtr = wordInTxt->firstPtr->nextPtr;
        
      }

      printf("%s\n", );

}      
   









// return 1 if the list is empty, 0 otherwise
int isEmpty(ListNodePtr sPtr){ 
   return sPtr == NULL;
} 



void printMasterList(ListNodePtr currentPtr){ 
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


void printFirstOrder(ListNodePtr wPtr){

    if (isEmpty(currentPtr)) {
      puts("List is empty.\n");
    } 
    else { 
      while(wPtr->firstPtr != NULL){
       // printf("{%s}\n", );
      }



}





ListNodePtr searchInFile(ListNodePtr wordPtr, char wordInFile[] ){//(File * file, ListNodePtr wordPtr){// burada verdiğimiz kelimenin Master LinkedListteki yerini buluyoruz. 

      while(wordPtr != NULL){
        if(strcmp(wordInFile, wordPtr->word) == 0 ){
          printf(" \n Word in file is : %s", wordInFile);
          return wordPtr;
        }else{
          wordPtr = wordPtr->nextPtr;
        }
    


     }

}