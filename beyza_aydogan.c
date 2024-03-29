// Beyza AYDOĞAN #150117030 
// Compiled with : gcc version 7.4.0 (Ubuntu 7.4.0-1ubuntu1~18.04.1) 
// Usage :  gcc beyza_aydogan.c -o beyza_aydogan -lm 


#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


struct orderNode;
struct connectionNode;

struct listNode {      // For Master Linked List                                
	char word[80];  
	struct listNode *nextPtr;
	struct orderNode *orderPtr;
}; 

typedef struct listNode ListNode; 
typedef ListNode* ListNodePtr; 

struct orderNode {	
	ListNodePtr wordPtr;
	struct orderNode *nextPtr;
	struct orderNode *connectionPtr;
	struct connectionNode *bond; 

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

struct frequencyNode {
	char word[80];
	int count;
	struct frequencyNode *nextFrequencyNodePtr;
};

typedef struct frequencyNode FrequencyNode;
typedef FrequencyNode * FrequencyNodePtr; 


ListNodePtr insertToMLL(ListNodePtr headPtr, char word[]);
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
ConnectionNodePtr createNthOrder(ListNodePtr headOfMLL, ConnectionNodePtr headOfConnections, int orderDegree); 
FrequencyNodePtr createFrequencyLinkedList(FrequencyNodePtr headOfFrequencyNodePtr, char path[]);
FrequencyNodePtr insertFrequencyNodeToFrequencyLinkedList(FrequencyNodePtr headOfFrequencyNodePtr, FrequencyNodePtr frequencyNode);
FrequencyNodePtr sortFrequencyNodes(FrequencyNodePtr headOfFrequencyNodePtr);

int main(){

	ListNodePtr headPtr = NULL; 
	ConnectionNodePtr headOfConnections = NULL;
	WordNodePtr headOfWordNodePtr = NULL;
	FrequencyNodePtr econHeadOfFrequencyNodePtr = NULL;
	FrequencyNodePtr healthHeadOfFrequencyNodePtr = NULL;
	FrequencyNodePtr magazinHeadOfFrequencyNodePtr = NULL;

	struct dirent **namelist;
	struct dirent **namelistSub;
	FILE *inputTxtFile;
	int numOfSubDirs, numOfSubFiles, j, i ;

  	numOfSubDirs = scandir("./dataset", &namelist, NULL, alphasort); 
    char path[30] ="./dataset/"; 

    if (numOfSubDirs < 0)
    	printf("%s\n","Wrong! dataset folder should be in the same directory with .c file. ");
 
    else {

    	
    	for( i = 2 ; i < numOfSubDirs ; i++) {
    		char dirPath[100] = {0};  
    		strcpy(dirPath, path);
    		strcat(dirPath , namelist[i]->d_name );
    		numOfSubFiles = scandir(dirPath, &namelistSub, NULL, alphasort);
  
    		for(j = 2 ; j < numOfSubFiles ; j++) {
    			char  filePath[100] = {0};
    			strcpy(filePath, dirPath);
    			strcat(filePath, "/"); 
    			strcat(filePath, namelistSub[j]->d_name); 
    			inputTxtFile = fopen(filePath, "r"); 
    			if (inputTxtFile == NULL) { 
    				printf("Cannot open file \n"); 
    				exit(0); 
    			} 
    	
    			char word[40];
    			while( fscanf(inputTxtFile,"%s", &word[0]) == 1 ) {
					headPtr = insertToMLL(headPtr, word); // insert item in list
				}
		
				fclose(inputTxtFile); 

				headOfWordNodePtr = createFileLinkedList(headOfWordNodePtr, filePath);	
				headOfConnections = createFirstOrder(headPtr, headOfWordNodePtr, headOfConnections);	
				headOfWordNodePtr = clearFileLinkedList(headOfWordNodePtr);
		
			}

		}

		/*printf("Master Linked List: ");                 
		printMasterList(headPtr);   //	To print Master Linked List
		printf("\n");*/


		printf("1 st-order term co-occurrence: " );
		printConnections(headOfConnections, 1);
		printf("\n");

		headOfConnections = createNthOrder(headPtr, headOfConnections, 2);
		printf("\n");
		printf("2 nd-order term co-occurrence: " );
		printConnections(headOfConnections, 2);
		printf("\n");

		headOfConnections = createNthOrder(headPtr, headOfConnections, 3);
		printf("\n");
		printf("3 rd-order term co-occurrence: " );
		printConnections(headOfConnections, 3);
		printf("\n");

		headOfConnections = createNthOrder(headPtr, headOfConnections, 4);
		printf("\n");
		printf("4 th-order term co-occurrence: " );
		printConnections(headOfConnections, 4);
		printf("\n");

		headOfConnections = createNthOrder(headPtr, headOfConnections, 5);
		printf("\n");
		printf("5 th-order term co-occurrence: " );
		printConnections(headOfConnections, 5);
		printf("\n");

		for(i = 2; i < numOfSubDirs; i++ ){
			if(strcmp(namelist[i]->d_name, "econ") == 0){
				econHeadOfFrequencyNodePtr = createFrequencyLinkedList(econHeadOfFrequencyNodePtr, "./dataset/econ");	
				econHeadOfFrequencyNodePtr = sortFrequencyNodes(econHeadOfFrequencyNodePtr);
			}
		}	
		for(i = 2; i < numOfSubDirs; i++ )
			if(strcmp(namelist[i]->d_name, "health") == 0){
				healthHeadOfFrequencyNodePtr = createFrequencyLinkedList(healthHeadOfFrequencyNodePtr, "./dataset/health");
				healthHeadOfFrequencyNodePtr = sortFrequencyNodes(healthHeadOfFrequencyNodePtr);
			}	
		for(i = 2; i < numOfSubDirs; i++ ){

			if(strcmp(namelist[i]->d_name, "magazin") == 0 ){
				magazinHeadOfFrequencyNodePtr = createFrequencyLinkedList(magazinHeadOfFrequencyNodePtr, "./dataset/magazin");
				magazinHeadOfFrequencyNodePtr = sortFrequencyNodes(magazinHeadOfFrequencyNodePtr);
			}
		}


		int k = 0;	
		printf("\nEcon   -  Health  -  Magazin\n");
		FrequencyNodePtr econTmp = econHeadOfFrequencyNodePtr;
		FrequencyNodePtr healthTmp = healthHeadOfFrequencyNodePtr ;
		FrequencyNodePtr magazinTmp = magazinHeadOfFrequencyNodePtr ;

		while(econTmp != NULL && healthTmp != NULL && magazinTmp != NULL && k != 5) {
			printf("%s %d    %s %d    %s %d\n", econTmp->word, econTmp->count, healthTmp->word, healthTmp->count,
			magazinTmp->word, magazinTmp->count);

			econTmp = econTmp->nextFrequencyNodePtr;
			healthTmp = healthTmp->nextFrequencyNodePtr;
			magazinTmp =  magazinTmp->nextFrequencyNodePtr;
			k++;
		}

		int m = 0;
		printf("\nEcon   -      Health  -    Magazin\n");
		econTmp = econHeadOfFrequencyNodePtr;
		healthTmp = healthHeadOfFrequencyNodePtr ;
		magazinTmp = magazinHeadOfFrequencyNodePtr ;

		while(econTmp != NULL && healthTmp != NULL && magazinTmp != NULL && m != 5) {
			double resultEcon = (econTmp->count)*log((double)3/econTmp->count);
			double resultHealth = (healthTmp->count)*log((double)2/healthTmp->count);
			double resultMagazin = (magazinTmp->count)*log((double)1/magazinTmp->count);
			printf("%s %.2f    %s %.2f    %s %.2f\n", econTmp->word, resultEcon , healthTmp->word, resultHealth,
			magazinTmp->word, resultMagazin);

			econTmp = econTmp->nextFrequencyNodePtr;
			healthTmp = healthTmp->nextFrequencyNodePtr;
			magazinTmp =  magazinTmp->nextFrequencyNodePtr;
			m++;
		}

	
	}

	return 0;
}



ListNodePtr insertToMLL(ListNodePtr headPtr, char word[]) { 

    ListNodePtr newPtr = (ListNodePtr)malloc(sizeof(ListNode)); 
     
    	strcpy(newPtr->word, word);
    	newPtr->orderPtr = NULL; 
    	newPtr->nextPtr = NULL;	

    	if(headPtr == NULL) {
    		headPtr = newPtr;
    		return headPtr;
    	}
    	
    	ListNodePtr currentPtr = headPtr;

    	while(currentPtr != NULL) {

            if(strcmp(currentPtr->word, word) == 0) {
            	return headPtr;
            }
            currentPtr = currentPtr->nextPtr;
        }

        currentPtr = headPtr;

        while(currentPtr->nextPtr != NULL) {
        	currentPtr = currentPtr->nextPtr;
        }
        currentPtr->nextPtr = newPtr;


        
    return headPtr; 

} 




void printMasterList(ListNodePtr currentPtr){ 	
		
		while (currentPtr != NULL) { 
			printf("%s --> ", currentPtr->word);
			currentPtr = currentPtr->nextPtr;   
		} 

		puts("NULL\n");
	 
} 




ConnectionNodePtr makeConnectionsOfOrders(ConnectionNodePtr headOfConnections, ListNodePtr word1, ListNodePtr word2, int orderDegree) {
	if(word1 != NULL && word2 != NULL){
		if(word1 == word2)//not to connect same two words
			return headOfConnections;

		ConnectionNodePtr tmp = headOfConnections;
		while(tmp != NULL) {

			if((strcmp(tmp->word1->wordPtr->word, word1->word) == 0 && strcmp(tmp->word2->wordPtr->word, word2->word) == 0 ) || 
				(strcmp(tmp->word1->wordPtr->word, word2->word) == 0 && strcmp(tmp->word2->wordPtr->word, word1->word) == 0 )) { 
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
	orderNode1->bond = connectionNode;
	orderNode2->bond = connectionNode;

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
            return tmp;
		}
		tmp = tmp -> nextPtr;
	}
	return NULL;
}



WordNodePtr createFileLinkedList(WordNodePtr headOfWordNodePtr, char path[]) {
	FILE *file;
	file = fopen(path, "r");
	if (file == NULL) { 
    		printf("Cannot open file for File Linked List \n"); 
    		return headOfWordNodePtr;
    	}
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
	return tmp = NULL;

}




ConnectionNodePtr createNthOrder(ListNodePtr headOfMLL, ConnectionNodePtr headOfConnections, int orderDegree) {

	ListNodePtr tmp = headOfMLL;

	while(tmp != NULL) {
		OrderNodePtr tmpOrderNode = tmp->orderPtr;
		while(tmpOrderNode != NULL) {
			if(tmpOrderNode->bond->orderDegree == (orderDegree-1)) {
				OrderNodePtr tmp2OrderNode = tmpOrderNode->connectionPtr->wordPtr->orderPtr;
				while(tmp2OrderNode != NULL) {
					if(tmp2OrderNode->bond->orderDegree == 1) {

						headOfConnections = makeConnectionsOfOrders(headOfConnections, tmp, tmp2OrderNode->connectionPtr->wordPtr, orderDegree);

					}
					tmp2OrderNode = tmp2OrderNode->nextPtr;

				}


			}
			tmpOrderNode = tmpOrderNode->nextPtr;
		}

		tmp = tmp->nextPtr;
	}

	return headOfConnections;
}




FrequencyNodePtr createFrequencyLinkedList(FrequencyNodePtr headOfFrequencyNodePtr, char path[]) {
	struct dirent **namelist;
	int i;
	int numOfSubFiles = scandir(path, &namelist, NULL, alphasort);
	FILE *file;
	for(i = 2; i < numOfSubFiles; i++) {
		char  filePath[100] = {0};
    	strcpy(filePath, path);
    	strcat(filePath, "/"); 
    	strcat(filePath, namelist[i]->d_name); 
    	file = fopen(filePath, "r"); 
    	if (file == NULL) { 
    		printf("Cannot open file for Frequency Linked List \n"); 
    		return headOfFrequencyNodePtr;
    	} 
		char word[40];
		while( fscanf(file,"%s", &word[0]) == 1 ) {
			FrequencyNodePtr newFrequencyNode = (FrequencyNodePtr)malloc(sizeof(FrequencyNode));
			strcpy(newFrequencyNode->word, word);
			newFrequencyNode->nextFrequencyNodePtr = NULL;
			newFrequencyNode->count = 0;
			headOfFrequencyNodePtr = insertFrequencyNodeToFrequencyLinkedList(headOfFrequencyNodePtr, newFrequencyNode); 
			}	
		fclose(file);
	}
	return headOfFrequencyNodePtr;
}



FrequencyNodePtr insertFrequencyNodeToFrequencyLinkedList(FrequencyNodePtr headOfFrequencyNodePtr, FrequencyNodePtr frequencyNode) {
	if(headOfFrequencyNodePtr == NULL) {
		frequencyNode->count = 1;
		headOfFrequencyNodePtr = frequencyNode;
		return headOfFrequencyNodePtr;
	}
	FrequencyNodePtr tmp = headOfFrequencyNodePtr;
	while(tmp != NULL) {
		if(strcmp(tmp->word, frequencyNode->word) == 0) {
			(tmp->count)++; 
			return headOfFrequencyNodePtr;
		}
		tmp = tmp->nextFrequencyNodePtr;
	}

	tmp = headOfFrequencyNodePtr;
	while(tmp->nextFrequencyNodePtr != NULL ) {
		tmp = tmp->nextFrequencyNodePtr;

	}
	frequencyNode->count = 1;
	tmp->nextFrequencyNodePtr = frequencyNode;
	return headOfFrequencyNodePtr;

}


FrequencyNodePtr sortFrequencyNodes(FrequencyNodePtr headOfFrequencyNodePtr) {
	
	int countTmp;
	
	if(headOfFrequencyNodePtr == NULL) {
		printf("headOfFrequencyNodePtr is null\n");
		return headOfFrequencyNodePtr;
	}
	if(headOfFrequencyNodePtr->nextFrequencyNodePtr == NULL ) {
		return headOfFrequencyNodePtr;
	}

	FrequencyNodePtr tmp1 = headOfFrequencyNodePtr;
	FrequencyNodePtr tmp2 = NULL;

	while(tmp1 != NULL) {

		tmp2 = tmp1->nextFrequencyNodePtr;

		while(tmp2 != NULL){

			if(tmp1->count < tmp2->count) {
				char wordTmp[80];
				
				countTmp = tmp1->count;
				tmp1->count = tmp2->count; 
				tmp2->count = countTmp;

				strcpy(wordTmp, tmp1->word);
				strcpy(tmp1->word, tmp2->word);
				strcpy(tmp2->word, wordTmp);
			}
			tmp2 = tmp2->nextFrequencyNodePtr; 
		}
		tmp1 = tmp1->nextFrequencyNodePtr;

	}

	return headOfFrequencyNodePtr;

}
