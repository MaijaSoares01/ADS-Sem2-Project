#define bool int
#define false 0
#define true (!false)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct book {
	char *bookId;//[9];
	char *bookTitle;//[40];
	char *bookAuthor;//[40];
	int yearPub;
	bool loanedOut;
	int timesLoaned;
	float rate;
	char *review;
    struct book *next;
};

struct book *head = NULL;
struct book *current = NULL;

//display the list
void printList() {                  
   struct book *print = head;
	int i = 0;
   //start from the beginning
   while(print != NULL) {
    	printf("\nBook %d:\n", i+1);
		printf("ID: %s\n", print->bookId);
		printf("Title: %s\n", print->bookTitle);
		printf("Author: %s\n", print->bookAuthor);
		printf("Year of Publication: %d\n", print->yearPub);
		printf("Currently Loaned out: %s\n", print->loanedOut ? "true" : "false");
		printf("Times Loaned out: %d\n", print->timesLoaned);
		printf("Rate: %1.1f stars\n", print->rate);
		printf("Last Review: %s\n", print->review);
		i++;
        print = print->next;
   }
}

//insert link at the first location
void insertFirst(char* bookId, char* bookTitle, char* bookAuthor, int yearPub, bool loanedOut, int timesLoaned, float rate, char* review) {
   //create a link
	    struct book *link = (struct book*) malloc(sizeof(struct book));
        link->bookId =(char*)malloc(sizeof(char)*(strlen(bookId) + 1));
        link->bookTitle = (char*)malloc(sizeof(char)*(strlen(bookTitle) + 1));
        link->review = (char*)malloc(sizeof(char)*(strlen(review) + 1));
        strcpy(link->bookId,bookId);
        strcpy(link->bookTitle,bookTitle);
        link->bookAuthor = bookAuthor;
        link->yearPub = yearPub;
        link->loanedOut = loanedOut;
        link->timesLoaned = timesLoaned;
        link->rate = rate;
        strcpy(link->review ,review);
	
   //point it to old first node
   link->next = head;
	
   //point first to new first node
   head = link;
}

//delete first item
struct book* deleteFirst() {
   //save reference to first link
   struct book *tempLink = head;
   //mark next to first link as first 
   head = head->next;
   //return the deleted link
   return tempLink;
}

//is list empty
bool isEmpty() {
   return head == NULL;
}

int length() {
   int length = 0;
   struct book *current;
	
   for(current = head; current != NULL; current = current->next) {
      length++;
   }
	
   return length;
}

//find a link with given key
struct book* find(char* bookId) {

   //start from the first link
   struct book* current = head;

   //if list is empty
   if(head == NULL) {
      return NULL;
   }

   //navigate through list
   while(current->bookId != bookId) {
	
      //if it is last node
      if(current->next == NULL) {
         return NULL;
      } else {
         //go to next link
         current = current->next;
      }
   }      
	
   //if data found, return the current Link
   return current;
}
void sort() {

   int i, j, k;
   char *tempBookId;
   char *tempBookTitle;
   char *tempBookAuthor;
   int tempYearPub;
   bool tempLoanedOut;
   int tempTimesLoaned;
   float tempRate;
   char *tempReview;
   
   struct book *current;
   struct book *next;
	
   int size = length();
   k = size ;
	
   for ( i = 0 ; i < size - 1 ; i++, k-- ) {
      current = head;
      next = head->next;
		
      for ( j = 1 ; j < k ; j++ ) {   

         if ( current->bookId > next->bookId ) {
            tempBookId = current->bookId;
            current->bookId = next->bookId;
            next->bookId = tempBookId;

            tempBookTitle = current->bookTitle;
            current->bookTitle = next->bookTitle;
            next->bookTitle = tempBookTitle;
            
            tempBookAuthor = current->bookAuthor;
            current->bookAuthor = next->bookAuthor;
            next->bookAuthor = tempBookAuthor;
            
            tempYearPub = current->yearPub;
            current->yearPub = next->yearPub;
            next->yearPub = tempYearPub;
            
            tempLoanedOut = current->loanedOut;
            current->loanedOut = next->loanedOut;
            next->loanedOut = tempLoanedOut;
            
            tempTimesLoaned = current->timesLoaned;
            current->timesLoaned = next->timesLoaned;
            next->timesLoaned = tempTimesLoaned;
            
            tempRate = current->rate;
            current->rate = next->rate;
            next->rate = tempRate;
            
            tempReview = current->review;
            current->review = next->review;
            next->review = tempReview;
         }
			
         current = current->next;
         next = next->next;
      }
   }   
}
//delete a link with given key
struct book* del(char* bookId) {

   //start from the first link
   struct book* current = head;
   struct book* previous = NULL;
	
   //if list is empty
   if(head == NULL) {
      return NULL;
   }

   //navigate through list
   while(current->bookId != bookId) {

      //if it is last node
      if(current->next == NULL) {
         return NULL;
      } else {
         //store reference to current link
         previous = current;
         //move to next link
         current = current->next;
      }
   }

   //found a match, update the link
   if(current == head) {
      //change first to point to next link
      head = head->next;
   } else {
      //bypass the current link
      previous->next = current->next;
   }    
   return current;
}



void main() {
   insertFirst("12345","Lord of the Flies","William Golding",1800,true,200,5,"Excelent read");
   insertFirst("24575","Catch-22","Joseph Heller",1800,false,180,4,"Thrilling");
   insertFirst("37687","David Copperfield","Charles Dickens",1800,false,150,4.5,"A bit slow but great");
   insertFirst("49090","The Great Gatsby","F-Scott Fitzgerald",1800,true,300,4.8,"Classic, must read");
   insertFirst("52345","Ulysses","James Joyce",1800,false,100,5,"Amazing!");
   insertFirst("63211","The Call of the Wild","Jack London",1800,true,50,3,"Exciting read!"); 

   printf("Original List: "); 	
   //print list
   printList();
	int r=0;
   while(!isEmpty()) {            
      struct book *temp = deleteFirst();
      printf("\nDeleted value:");
        printf("\nBook %d:\n", r+1);
		printf("ID: %s\n", temp->bookId);
		printf("Title: %s\n", temp->bookTitle);
		printf("Author: %s\n", temp->bookAuthor);
		printf("Year of Publication: %d\n", temp->yearPub);
		printf("Currently Loaned out: %s\n", temp->loanedOut ? "true" : "false");
		printf("Times Loaned out: %d\n", temp->timesLoaned);
		printf("Rate: %1.1f stars\n", temp->rate);
		printf("Last Review: %s\n", temp->review);
		r++;
   }  
	
   printf("\nList after deleting all items: ");
   printList();
   insertFirst("12345","Lord of the Flies","William Golding",1800,true,200,5,"Excelent read");
   insertFirst("24575","Catch-22","Joseph Heller",1800,false,180,4,"Thrilling");
   insertFirst("37687","David Copperfield","Charles Dickens",1800,false,150,4.5,"A bit slow but great");
   insertFirst("49090","The Great Gatsby","F-Scott Fitzgerald",1800,true,300,4.8,"Classic, must read");
   insertFirst("52345","Ulysses","James Joyce",1800,false,100,5,"Amazing!");
   insertFirst("63211","The Call of the Wild","Jack London",1800,true,50,3,"Exciting read!"); 
   
   printf("\nRestored List: ");
   printList();
   printf("\n");  

   struct book *foundLink = find("12345");
	
   if(foundLink != NULL) {
      printf("Element found: ");
        printf("\nBook:\n");
		printf("ID: %s\n", foundLink->bookId);
		printf("Title: %s\n", foundLink->bookTitle);
		printf("Author: %s\n", foundLink->bookAuthor);
		printf("Year of Publication: %d\n", foundLink->yearPub);
		printf("Currently Loaned out: %s\n", foundLink->loanedOut ? "true" : "false");
		printf("Times Loaned out: %d\n", foundLink->timesLoaned);
		printf("Rate: %1.1f stars\n", foundLink->rate);
		printf("Last Review: %s\n", foundLink->review);
        printf("\n");  
   } else {
      printf("Element not found.");
   }

   del("12345");
   printf("List after deleting an item: ");
   printList();
   printf("\n");
   foundLink = find("12345");
	
   if(foundLink != NULL) {
      printf("Element found: ");
      printf("\nBook:\n");
	  printf("ID: %s\n", foundLink->bookId);
	  printf("Title: %s\n", foundLink->bookTitle);
	  printf("Author: %s\n", foundLink->bookAuthor);
	  printf("Year of Publication: %d\n", foundLink->yearPub);
	  printf("Currently Loaned out: %s\n", foundLink->loanedOut ? "true" : "false");
	  printf("Times Loaned out: %d\n", foundLink->timesLoaned);
	  printf("Rate: %1.1f stars\n", foundLink->rate);
	  printf("Last Review: %s\n", foundLink->review);
      printf("\n");
   } else {
      printf("Element not found.");
   }
   printf("\n");
   sort();
	
   printf("List after sorting the data: ");
   printList();
}
