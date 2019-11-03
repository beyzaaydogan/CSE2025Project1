#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>


struct orderNode;

struct listNode {                                      
	char word[80];  
	struct listNode *nextPtr;
	struct orderNode *orderPtr;
}; 

typedef struct listNode ListNode; // synonym for struct listNode
typedef ListNode* ListNodePtr; // synonym for ListNode*

struct orderNode {
	ListNodePtr wordPtr;
	struct orderNode *nextPtr;
	struct orderNode *connectionPtr;
};

typedef struct orderNode OrderNode;
typedef OrderNode* OrderNodePtr;

struct connectionNode { 
	OrderNodePtr word1;
	OrderNodePtr word2;
	int orderDegree;
	struct connectionNode *nextPtr;
};

typedef struct connectionNode ConnectionNode;
typedef ConnectionNode * ConnectionNodePtr;

struct wordNode {
	char word[80];
	struct wordNode *nextWordNodePtr;
};

typedef struct wordNode WordNode;
typedef WordNode * WordNodePtr;




void insert(ListNodePtr *sPtr, char value[]);
int isEmpty(ListNodePtr sPtr);
void printMasterList(ListNodePtr currentPtr);
ConnectionNodePtr makeConnectionsOfOrders(ConnectionNodePtr headOfConnections, ListNodePtr word1, ListNodePtr word2, int orderDegree);
ConnectionNodePtr insertConnections(ConnectionNodePtr headOfConnection, ConnectionNodePtr connectionNode);
ListNodePtr putOrderNodeIntoListNode(ListNodePtr wordNode, OrderNodePtr orderNode);
void printConnections(ConnectionNodePtr headOfConnection, int orderDegree);
ListNodePtr getNodeFromMLL(ListNodePtr wordPtr, char wordInFile[]);
WordNodePtr createFileLinkedList(WordNodePtr headOfWordNodePtr, char path[]);
WordNodePtr insertWordNodeToFileLinkedList(WordNodePtr headOfWordNodePtr, WordNodePtr wordNode);
ConnectionNodePtr createFirstOrder(ListNodePtr headOfMLL, WordNodePtr headOfFLL, ConnectionNodePtr headOfConnections);
WordNodePtr clearFileLinkedList(WordNodePtr headOfFLL);

int main(){

	ListNodePtr headPtr = NULL; 
	ConnectionNodePtr headOfConnections = NULL;
	WordNodePtr headOfWordNodePtr = NULL;

	struct dirent **namelist;
	struct dirent **namelistSub;
	FILE *inputTxtFile;
	int numOfSubDirs, numOfSubFiles, j, i ;

    numOfSubDirs = scandir("./dataset", &namelist, NULL, alphasort); // . yerine /home/beyza/C-workspace/2025Projects gelebilir
    char path[100] ="./dataset/"; 

    if (numOfSubDirs < 0)
    	perror("scandir");

    else {

    	//printf(" Number of sub directories are %d\n", numOfSubDirs);
    	
    	for( i = 2 ; i < numOfSubDirs ; i++){
    		char dirPath[100], filePath[100];  
    		strcpy(dirPath, path);
    		strcat(dirPath , namelist[i]->d_name );
    		numOfSubFiles = scandir(dirPath, &namelistSub, NULL, alphasort);


    		for(j = 2 ; j < numOfSubFiles ; j++){

    		//	printf("\n\n\n\n\nI am in %s\n\n", namelistSub[j]->d_name );
    			strcpy(filePath, dirPath);
    			strcat(filePath, "/"); 
    			strcat(filePath, namelistSub[j]->d_name); 
    		//	printf("Filepath is --> %s\n\n\n\n", filePath );
    			inputTxtFile = fopen(filePath, "r"); 
    			if (inputTxtFile == NULL) { 
    				printf("Cannot open file \n"); 
    				exit(0); 
    			} 


    			char word[40];
    			while( fscanf(inputTxtFile,"%s", &word[0]) == 1 ){
					insert(&headPtr, word); // insert item in list
				}


				headOfWordNodePtr = createFileLinkedList(headOfWordNodePtr, filePath);	
			
				headOfConnections = createFirstOrder(headPtr, headOfWordNodePtr, headOfConnections);
			
			
				headOfWordNodePtr = clearFileLinkedList(headOfWordNodePtr);
			
				fclose(inputTxtFile); 

			}


		}
		printf("Master Linked List: ");                 
		printMasterList(headPtr);
		printf("\n");

	}
	printf("1 st -order term co-occurrence: " );
	printConnections(headOfConnections, 1);
	printf("\n");




	return 0;
}



void insert(ListNodePtr *sPtr, char value[]){ 

    ListNodePtr newPtr = (ListNodePtr)malloc(sizeof(ListNode)); // create node
    if (newPtr != NULL) { // is space available
    	strncpy(newPtr->word, value, 80);
    	newPtr->word[80 - 1] = '\0';
    	newPtr->nextPtr = NULL;	

    	ListNodePtr previousPtr = NULL;
    	ListNodePtr currentPtr = *sPtr;

    	while(currentPtr != NULL){

            if(strcmp(currentPtr->word, value) == 0){//checking if the word we want to instert exists
            	return;
            }
            currentPtr = currentPtr->nextPtr;
        }

        currentPtr = *sPtr;

        // loop to point to the  last(current) node in the list and its previous node       
        while (currentPtr != NULL) {

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



void printMasterList(ListNodePtr currentPtr){ 
   // if list is empty
	if (isEmpty(currentPtr)) {
		puts("List is empty.\n");
	} 
	else { 
		//puts("The list is:");

      // while not the end of the list
		while (currentPtr != NULL) { 
			printf("%s --> ", currentPtr->word);
			currentPtr = currentPtr->nextPtr;   
		} 

		puts("NULL\n");
	} 
} 




ConnectionNodePtr makeConnectionsOfOrders(ConnectionNodePtr headOfConnections, ListNodePtr word1, ListNodePtr word2, int orderDegree) {
	if(word1 != NULL && word2 != NULL){

		ConnectionNodePtr tmp = headOfConnections;
		while(tmp != NULL) {

			if((strcmp(tmp->word1->wordPtr->word, word1->word) == 0 && strcmp(tmp->word2->wordPtr->word, word2->word) == 0 && tmp->orderDegree == orderDegree) || 
				(strcmp(tmp->word1->wordPtr->word, word2->word) == 0 && strcmp(tmp->word2->wordPtr->word, word1->word) == 0 && tmp->orderDegree == orderDegree)) {

				return headOfConnections;
		}

		tmp = tmp->nextPtr; 
	}



	OrderNodePtr orderNode1 = (OrderNodePtr)malloc(sizeof(OrderNode)); 
	OrderNodePtr orderNode2 = (OrderNodePtr)malloc(sizeof(OrderNode)); 
	orderNode1->wordPtr = word1;
	orderNode2->wordPtr = word2;
	orderNode1->nextPtr = NULL;
	orderNode2->nextPtr = NULL;
	orderNode1->connectionPtr = orderNode2;
	orderNode2->connectionPtr = orderNode1;

	ConnectionNodePtr connectionNode = (ConnectionNodePtr)malloc(sizeof(ConnectionNode));
	connectionNode->word1 = orderNode1;
	connectionNode->word2 = orderNode2;
	connectionNode->nextPtr = NULL;
	connectionNode->orderDegree = orderDegree;

	headOfConnections = insertConnections(headOfConnections, connectionNode);
	
	word1 = putOrderNodeIntoListNode(word1, orderNode1);
	word2 = putOrderNodeIntoListNode(word2, orderNode2);

	
}
return headOfConnections;

}

ConnectionNodePtr insertConnections(ConnectionNodePtr headOfConnections, ConnectionNodePtr connectionNode) {
	if(headOfConnections == NULL) {
		headOfConnections = connectionNode;
		return headOfConnections;
	}
	
	ConnectionNodePtr tmp = headOfConnections;
	
	while(tmp->nextPtr != NULL) {
		tmp = tmp->nextPtr;
	}

	tmp->nextPtr = connectionNode;
	
	return headOfConnections;

}


ListNodePtr putOrderNodeIntoListNode(ListNodePtr wordNode, OrderNodePtr orderNode) {

	if(wordNode->orderPtr == NULL) {
		wordNode->orderPtr = orderNode;
		return wordNode;
	}
	OrderNodePtr tmp = wordNode->orderPtr;
	while(tmp->nextPtr != NULL){
		tmp = tmp->nextPtr;
	}
	tmp->nextPtr = orderNode;
	return wordNode;
}



void printConnections(ConnectionNodePtr headOfConnections, int orderDegree) {
	ConnectionNodePtr tmp = headOfConnections;
	
	while(tmp != NULL) {
		if(tmp->orderDegree == orderDegree) {
			printf("{%s,%s}, ", tmp->word1->wordPtr->word, tmp->word2->wordPtr->word);

		}
		tmp = tmp->nextPtr;

	}

}



ListNodePtr getNodeFromMLL(ListNodePtr headOfMLL, char wordInFile[] ) { 

	ListNodePtr tmp = headOfMLL;
	while(tmp != NULL) {
		if(strcmp(wordInFile, tmp -> word) == 0 ) {
            //printf(" \n Word in file is : %s", wordInFile);
			return tmp;
		}
		tmp = tmp -> nextPtr;
	}
	return NULL;
}



WordNodePtr createFileLinkedList(WordNodePtr headOfWordNodePtr, char path[]) {
	FILE *file;
	file = fopen(path, "r");
	char word[40];
	while( fscanf(file,"%s", &word[0]) == 1 ) {
		WordNodePtr newWordNode = (WordNodePtr)malloc(sizeof(WordNode));
		strcpy(newWordNode->word, word);
		newWordNode->nextWordNodePtr = NULL;
		headOfWordNodePtr = insertWordNodeToFileLinkedList(headOfWordNodePtr, newWordNode); 
	}
	fclose(file);
	return headOfWordNodePtr;
}



WordNodePtr insertWordNodeToFileLinkedList(WordNodePtr headOfWordNodePtr, WordNodePtr wordNode) {
	if(headOfWordNodePtr == NULL) {
		headOfWordNodePtr = wordNode;
		return headOfWordNodePtr;
	}
	WordNodePtr tmp = headOfWordNodePtr;
	while(tmp != NULL) {//check if the word exists
		if(strcmp(tmp->word, wordNode->word) == 0){
			return headOfWordNodePtr;
		}
		tmp = tmp->nextWordNodePtr;
	}

	tmp = headOfWordNodePtr;
	while(tmp->nextWordNodePtr != NULL ) {
		tmp = tmp->nextWordNodePtr;

	}
	tmp->nextWordNodePtr = wordNode;
	return headOfWordNodePtr;

}



ConnectionNodePtr createFirstOrder(ListNodePtr headOfMLL, WordNodePtr headOfFLL, ConnectionNodePtr headOfConnections) {
	WordNodePtr tmp1 = headOfFLL;

	while(tmp1 != NULL) {
		WordNodePtr tmp2 = tmp1->nextWordNodePtr;
		while(tmp2 != NULL) {

			ListNodePtr tmp1ListNode = getNodeFromMLL(headOfMLL, tmp1->word);
			ListNodePtr tmp2ListNode = getNodeFromMLL(headOfMLL, tmp2->word);

			headOfConnections = makeConnectionsOfOrders(headOfConnections, tmp1ListNode, tmp2ListNode, 1);
			
			tmp2 = tmp2->nextWordNodePtr;
		}
		tmp1 = tmp1->nextWordNodePtr;
	} 
	return headOfConnections;

}



WordNodePtr clearFileLinkedList(WordNodePtr headOfFLL) {
	WordNodePtr tmp = headOfFLL;

	while( tmp != NULL ) {
		headOfFLL = headOfFLL->nextWordNodePtr;
		free(tmp);

		tmp = headOfFLL;
	}
	return tmp;

}