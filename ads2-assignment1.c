/** Name: Maija Soares 
*   Student Number: C19478224
*   Module: ADS
*/
//Definitions
#define bool int
#define false 0
#define true (!false)

//Libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

//Max Amount of books
#define MAX 10
 

struct book {//What information does each book have
	char bookId[9];//a unique 9 character id
	char bookTitle[40];//title of the book
	char bookAuthor[40];//author of book
	int yearPub;//year of publication
	bool loanedOut;//is it currently being loaned out (true or false)
	char customerName[40];//customer currently loaning out the book
	int timesLoaned;//amount of times book is loaned out
	float rate;//last rating of the book
	char review[30];//last review of the book
	char language[20];//language book is in
	char specifics[20];//specific version of book
};
//Stucture template for one node
struct LinearNode {
     struct book *element;//used to access elements values
	struct LinearNode *next;//used to access next elements values 
};
struct LinearNode *head = NULL;//front of the list is null
struct LinearNode *current = NULL;//current is null
//Function prototypes
void inputABook();//adding books to front of the list
void saveToFile(FILE *);//saves values to a .dat file
void getFromFile(FILE *);//read .dat file
void displayBooks();//displays all books information
void deleteBook(char*);//delete a specific book
bool isEmpty();//is list empty(true or false)
bool linearSearch(char*);//checks if id exists in the list
bool UniqueSearch(char*);//looks through list to check if id is unique
void LoanOutBook(char*);//after giving an id, loans out that book
void ReturnBook(char*);//after giving an id, if book is currently loaned out, it can be returned
void Popular();//Displays least and most popular
void FindLanguage(char*);//search for books in a specific language
void FindSpecifics(char*);//search for books with a specific version

// Global Variables
struct LinearNode *list = NULL; //front of list

struct LinearNode *last = NULL; //pointer to last node in list

int main()
{
	FILE *fp;//File object
	int i;//int i to add a book until Max is achieved
    char delay;//delay
	if ((fp = fopen("books.dat", "rb")) == NULL) {//books.dat is empty
	//file DOES NOT exist so get user to input books
	     for (i=0; i< MAX; i++){//for loop to add max books
         printf("Book %d\n",i+1);//Book 1, Book 2, ......
		 	inputABook();//add a book
		 	printf("\n\n");//add spacing
		}
		printf("\n\n\n\n\n\n\n\n\n");//add spacing before menu
	}//end if
	else{ //file DOES exist
		getFromFile(fp);//get books.dat file
	}
	int I;//int to take in menu response
    do//do while loop
    {
    	char bookId[9] = {0};//bookId string 
		int response=0;//int response
		char temp[20]={0};//temparary string
		char language[20]={0};//language string
		char specifics[20]={0};//specific string
		printf("--Menu--\n");//menu displayed!
    	printf("1. Add a new book to the library\n");
		printf("2. Allow customer to take out a book\n");
		printf("3. Allow customer to return a book\n");
		printf("4. Delete an old book from stock\n");
		printf("5. View all books\n");
		printf("6. View a specific book\n");
		printf("7. View details of most popular and least popular books\n");
		printf("8. Search for Specific types of books\n");
		printf("9. Exit the system\n");
        printf("Enter your choice: \n");
        scanf("%d",&I);//take in menue response
        if(I>9 || I<1){//if I is greater than 9 or less than 1 
        printf("ERROR-PLEASE ENTER A VALID MENU INPUT\n");//an error occurs
		}else{//else..
        switch(I)//if I equals...
	        {
	            case 1://if I equals...1
	            inputABook();//add a book to the list
	            printf("\n\n\n\n\n\n");//add spacing before menu
	            break;
	            case 2://if I equals...2
	            printf("Enter a book ID eg xxxx-xxxx - that you would like to loan out\n");//ask for a book id to loan out
			    scanf("%s",&bookId);//take in bookid
	            LoanOutBook(bookId);//call loan out book method
	            printf("\n\n\n\n\n\n");//add spacing
	            break;
	            case 3://if I equals...3
	            printf("Enter the books ID eg xxxx-xxxx - that you are returning\n");//ask for book id to return
			    scanf("%s",&bookId);//take in bookid
	            ReturnBook(bookId);//call return book method
	            printf("\n\n\n\n\n\n");//add spacing
	            break;
	            case 4://if I equals...4
	            printf("Enter a book ID eg xxxx-xxxx - will delete the book only if it is before 2010\n");//ask for book id to delete only if the year of publish is before 2010
			    scanf("%s",&bookId);//take in bookid
				deleteBook(bookId);//delete a book method called
				printf("\n\n\n\n\n\n");//add spacing
	            break;
	            case 5://if I equals...5
	            displayBooks();//call display books method
	            printf("\n\n\n\n\n\n");//add spaing
	            break;
	            case 6://if I equals...6
	            printf("Enter a book ID eg xxxx-xxxx\n");//asks for book id
			    scanf("%s",&bookId);//take in book id
				linearSearch(bookId);//call linear search method
				printf("\n\n\n\n\n\n");//add spacing
	            break;
	            case 7://if I equals...7
	            Popular();//call popular method
	            printf("\n\n\n\n\n\n");//add spacing
	            break;
	            case 8://if I equals...8
	            printf("Would you like to search for a specific version[1] or a book in a specific language[2]? \n");//asks if user wants to search for language or version
    			scanf("%d",&response);//take in response 
    			bool res=true;//boolean res is equal to true
	            if (response==1){//if response equals 1
	            	do{//do while loop
	            	printf("Would you like to see books in an audio version[1], a braille version[2] or a hardcover version[3]?\n");//select which version to search for
	            	scanf("%d",&response);//take in response 
	            	if (response == 1){//if response = 1
					strcpy(specifics , "Audio version");//string specifics = Audio version
					FindSpecifics(specifics);//call method find specifics
					}else if(response==2){//if response = 2
						strcpy(specifics , "Braille version");//string specifics = Braille version
						FindSpecifics(specifics);//call method find specifics
					}else if(response==3){//if response = 3
						strcpy(specifics , "Hardcover version");//string specifics = Hardcover version
						FindSpecifics(specifics);//call method find specifics
					}else{//else..
						res = false;//bool res = false
						printf("ERROR-PLEASE ENTER A VALID RESPONSE 1,2 OR 3");//error has occurred
					}
				}while(res==false);//keep looping if res equals false
				}else if(response==2){//if response equals 2
					printf("What language would you like to search for?\n");//asks for what language to search for
					scanf("%c",&temp);//temp statement to clear buffer
    				scanf("%[^\n]",language);//take in language
    				FindLanguage(language);//call find language method  				
				}else{//else...
					printf("You did not hit a valid option so you will be returned to the menu\n");//error occurred and will return to menu
				}
				printf("\n\n\n\n\n\n");//add spacing
	            break;
	            case 9://if I equals...9
	        	printf("Thank you!\n");//end message
	        	saveToFile(fp);//save file and book information
	            break;
	            default:
	            printf("ERROR HAS OCCURRED\n");//an error has occurred
	        }
    	}
    }while(I != 9);//keep looping while I doesnt equal 9
}

void saveToFile(FILE *fp){//write and save file method
	fp = fopen("books.dat", "wb");//books.dat file
	int i=0;//int i equals 0 
		while (current!=NULL) {//while loop... loop while current does not equal null
        fwrite(&current->element->bookId, sizeof(struct book), 1, fp);//write bookid for current
		fwrite(&current->element->bookTitle, sizeof(struct book), 1, fp);//write bookTitle for current
		fwrite(&current->element->bookAuthor, sizeof(struct book), 1, fp);//write bookAuthor for current
		fwrite(&current->element->yearPub, sizeof(struct book), 1, fp);//write yearPub for current
		fwrite(&current->element->loanedOut, sizeof(struct book), 1, fp);//write loanedOut for current
		fwrite(&current->element->customerName, sizeof(struct book), 1, fp);//write customerName for current
		fwrite(&current->element->timesLoaned, sizeof(struct book), 1, fp);//write timesLoaned for current
		fwrite(&current->element->rate, sizeof(struct book), 1, fp);//write rate for current
		fwrite(&current->element->review, sizeof(struct book), 1, fp);//write review for current
		fwrite(&current->element->language, sizeof(struct book), 1, fp);//write language for current
		fwrite(&current->element->specifics, sizeof(struct book), 1, fp);//write specifics for current
		current=current->next;//current now equals current next
        i++;//add one to i
    	}
		printf("%d many items were saved\n",i );//shows how many items were saved
	fclose(fp);//close file
}

	void getFromFile(FILE *fp){//get from and read file method
		int i = 0;//int i equals 0
	    char c;//character c
	    struct LinearNode *temp = current;//temparary struct equals current
		printf("Retriving books from file...\n");//prints retrieving books
		while (current!=NULL ) {//while current does not equal null loop
		fread(&temp->element->bookId, sizeof(struct book), 1, fp);//read bookId for current
		fread(&temp->element->bookTitle, sizeof(struct book), 1, fp);//read bookTitle for current
		fread(&temp->element->bookAuthor, sizeof(struct book), 1, fp);//read bookAuthor for current
		fread(&temp->element->yearPub, sizeof(struct book), 1, fp);//read yearPub for current
		fread(&temp->element->loanedOut, sizeof(struct book), 1, fp);//read loanedOut for current
		fread(&temp->element->customerName, sizeof(struct book), 1, fp);//read customerName for current
		fread(&temp->element->timesLoaned, sizeof(struct book), 1, fp);//read timesLoaned for current
		fread(&temp->element->rate, sizeof(struct book), 1, fp);//read rate for current
		fread(&temp->element->review, sizeof(struct book), 1, fp);//read review for current
		fread(&temp->element->language, sizeof(struct book), 1, fp);//read language for current
		fread(&temp->element->specifics, sizeof(struct book), 1, fp);//read specifics for current
		temp=temp->next;//temporary equals temporary next
	}
		fclose(fp);//close file
	}

void inputABook(){	
		struct LinearNode *aNode;//linearnode struct
		struct book *anElement;//book struct
		char bookId[9] = {0};//bookid
		char bookTitle[40] = {0};//book title
		char bookAuthor[40] = {0};//book author
		int yearPub=0;//year of publications
		bool loanedOut = false;//loaned out
		char customerName[40] = {0};//customer name
		int timesLoaned = 0;//loaned out times
		float rate = 0;//last rating
		char review[30] = {0};//last review
		char language[20] = {0};//language
		char specifics[20] = {0};//specifics
		int response;//int response
		strcpy(review , "no review yet...");//review equals "no review yet.."
		strcpy(customerName , "no customers have loaned out...");//customer name equals "no customers have loaned out..."
		char temp;//temporary character
		bool validID = true;//boolean validID
		 //create space for new book element
        anElement = (struct book *)malloc(sizeof(struct book));
		// create space for new node
		aNode = (struct LinearNode *)malloc(sizeof(struct LinearNode));
		do{
			validID = true;//validID equals true
			printf("Enter a unique book ID eg xxxx-xxxx\n");//ask for bookid
    		scanf("%s",bookId);//take in bookid
    	    int c = 0;//int c equals 0
    	    while (bookId[c] != '\0'){//this while loop gets the length of bookid
    		c++;
    		}
    	    int length = c;//length equals c
    	    if(length == 9) {//if length equals 9
    	    	int i;//int i
	        for(i=0; i < length; i++) {//goes up to 9
    	    	if (i==4){//if i equals 4
    	    		char dash = bookId[i];//get character at index 4 of bookid
    	    		if (dash != '-'){//if this character is not a dash
    	    			validID=false;//it is not a validID
    	    			printf("ERROR-You have not inputted a '-' at character %d\n",i+1);//error message
					}
				}else{//if i doesnt equal 4
					bool digit = isdigit(bookId[i]); //check if bookid is a digit at character i
			         if(digit==false) {//if not then..
			            validID=false;//it is not valid
		    	    	printf("ERROR-You did not input a digit at character %d\n",i+1);//error message
			         }
				}
	      	}
	      		if(validID==true){//if validID equals true
			      	bool unique = UniqueSearch(bookId);//call unique search method to check if bookid is unique
		    	    if(unique==false){//if it is not unique
						validID=false;//it is not valid
					}else{//else..
						validID=true;//it is valid
					}
					if (validID==false){//if ValidID equals false
					printf("ERROR~BOOKID IS NOT UNIQUE\n");//error message
					}
			 	}
	    	}else{//else
	    		validID=false;//it is not valid
	    		printf("ERROR-You have inputted a bookID that is not 9 characters long\n");//error message
			}
		}while(validID == false);//keep looping if validId equals false
		bool validYR = false;//boolean validYR equals false
		do{//do while loop
			printf("Enter the year of publication(must be after 2008):\n");//asks for year of publication
			scanf("%d", &yearPub);//take in year of publication
			if (yearPub>2008){//if year of publication if after 2008 
				validYR = true;//it is valid
			}else{//else..
				printf("ERROR~NONVALID YEAR OF PUBLISH INPUTTED\n");//error message
				validYR = false;//it is not valid
			}
		}while(validYR == false);//keep looping if validYr equals false
		printf("Enter the title:\n");//ask for book title
		scanf("%c",&temp); // temp statement to clear buffer
    	scanf("%[^\n]",bookTitle);//take in book title
		printf("Enter the authors name:\n");//ask for book author
		scanf("%c",&temp); // temp statement to clear buffer
    	scanf("%[^\n]",bookAuthor);//take in book author
		printf("What language is this book in?:\n");//ask for language of book
		scanf("%c",&temp); // temp statement to clear buffer
    	scanf("%[^\n]",language);//take in language
    	bool valid=true;//bool valid equals true
    	do {//do while loop
    	printf("Is the book you're looking for an audio version[1], a braille version[2] or a hardcover version[3]:\n");
		scanf("%d",&response);//take in response 
		if (response == 1){//if response equals 1
			strcpy(specifics , "Audio version");//specifics equals "Audio version"
		}else if(response == 2){//if response equals 1
			strcpy(specifics , "Braille version");//specifics equals "Braille version"
		}else if(response == 3){//if response equals 1
			strcpy(specifics , "Hardcover version");//specifics equals "Hardcover version"
		}else{//else
			valid = false;//valid equals false
			printf("ERROR-PLEASE ENTER A VALID RESPONSE 1,2 OR 3\n");//error message
		}
		}while(valid==false);//keep looping if valid equals false
		
         //add information to book node
         strcpy(anElement->bookTitle , bookTitle);//add bookTitle to book node
         strcpy(anElement->bookId , bookId);//add bookId to book node
         strcpy(anElement->bookAuthor , bookAuthor);//add bookAuthor to book node
         anElement->yearPub = yearPub;//add yearPub to book node
         anElement->loanedOut = loanedOut;//add loanedOut to book node
         strcpy(anElement->customerName , customerName);//add customerName to book node
         anElement->timesLoaned = timesLoaned;//add timesLoaned to book node
         anElement->rate = rate;//add rate to book node
         strcpy(anElement->review , review);//add review to book node
         strcpy(anElement->language , language);//add language to book node
         strcpy(anElement->specifics , specifics);//add specifics to book node
         
         //add data part to the node
		if (aNode == NULL)//if aNode is null
			printf("Error - no space for the new book\n");//there isnt any space
		else { // add book part to the node
		 	aNode->next = NULL;//anode next equals null
		 	aNode->element = anElement;//anode element equals an element
			//add node to front of the list
			if (isEmpty())  //if list is empty
			{
				list = aNode;//front is anode
				last = aNode;//last is anode
		    }
			else {//or...
				aNode->next = list;//anode next is equal to front
				list = aNode;//front is equal to anode
			} //end else
		}//end else
} //end inputABook
 			

void displayBooks(){//display books method
	struct LinearNode *current;//linear node current
	int i = 0;//int i equals 0
	if (isEmpty())//if the list is empty 
		printf("Error - there are no books in the list\n");//error message
	else {//else...
			current = list;//current equals list
			while (current != NULL) {//while current does not equal null
			printf("Book %d:\n", i+1);//print out book values
			printf("ID: %s\n", current->element->bookId);
			printf("Title: %s\n", current->element->bookTitle);
			printf("Author: %s\n", current->element->bookAuthor);
			printf("Year of Publication: %d\n", current->element->yearPub);
			printf("Currently Loaned out: %s\n", current->element->loanedOut ? "true" : "false");
			printf("Customer name currently loaning book: %s\n", current->element->customerName);
			printf("Times Loaned out: %d\n", current->element->timesLoaned);
			printf("Last Rating: %1.1f stars\n", current->element->rate);
			printf("Last Review: %s\n", current->element->review);
			printf("Language: %s\n", current->element->language);
			printf("Version: %s\n", current->element->specifics);
			printf("\n\n");//add spacing
			i++;//add one to i
			current=current->next;//current equals current next
			} //end while
    }//end else
} //end displayBooks

bool linearSearch(char* target){//linear search method
	struct LinearNode *current;//linear node current
	bool found=false;//bool found equals false
	int i = 0;//int i equals 0
	if (isEmpty())//if list is empty
		printf("Error - there are no books in the list\n");//error message
 	else {//else
			current = list;//current equals list
			while (current != NULL) {//while current does not equal null
			if (strcmp(current->element->bookId, target)==0){//if target equals the current book id
					found=true;//found equals true
					printf("Book %d:\n", i+1);//print out book values
					printf("ID: %s\n", current->element->bookId);
					printf("Title: %s\n", current->element->bookTitle);
					printf("Author: %s\n", current->element->bookAuthor);
					printf("Year of Publication: %d\n", current->element->yearPub);
					printf("Currently Loaned out: %s\n", current->element->loanedOut ? "true" : "false");
					printf("Customer name currently loaning book: %s\n", current->element->customerName);
					printf("Times Loaned out: %d\n", current->element->timesLoaned);
					printf("Last Rating: %1.1f stars\n", current->element->rate);
					printf("Last Review: %s\n", current->element->review);
					printf("Language: %s\n", current->element->language);
					 printf("Version: %s\n", current->element->specifics);
			}
			i++;//add one to i
			current=current->next;//current equals current next
			} //end while
    }//end else
    return found;//return bool found
}

void FindSpecifics(char* target){//find specific method
	struct LinearNode *current;//linear node current
	bool found=false;//bool found equals false
	int i = 0;//int i equals 0
	if (isEmpty())//if list is empty
		printf("Error - there are no books in the list\n");//error message
 	else {//else...
			current = list;//current equals list
			while (current != NULL) {//while current does not equal null
			if (strcmp(current->element->specifics, target)==0){//if target equals the current specific
					printf("We found a book in a %s\n\n",current->element->specifics);//say we found their book
					found=true;//found equals true
					printf("Book %d:\n", i+1);//print book values
					printf("ID: %s\n", current->element->bookId);
					printf("Title: %s\n", current->element->bookTitle);
					printf("Author: %s\n", current->element->bookAuthor);
					printf("Year of Publication: %d\n", current->element->yearPub);
					printf("Currently Loaned out: %s\n", current->element->loanedOut ? "true" : "false");
					printf("Customer name currently loaning book: %s\n", current->element->customerName);
					printf("Times Loaned out: %d\n", current->element->timesLoaned);
					printf("Last Rating: %1.1f stars\n", current->element->rate);
					printf("Last Review: %s\n", current->element->review);
					printf("Language: %s\n", current->element->language);
					 printf("Version: %s\n", current->element->specifics);
			}
			i++;//add 1 to i
			current=current->next;//current equals current next
			} //end while
			if(found==false){//if found equals false
				printf("Sorry we could not find books in a %s\n\n",target);//message saying book could not be found 
			}
    }//end else
}

void FindLanguage(char* target){//find a language book method
	struct LinearNode *current;//linear node current
	bool found=false;//bool found equals false
	int i = 0;//int i equals 0
	if (isEmpty())//if list is empty
		printf("Error - there are no books in the list\n");//error message
 	else {//else..
			current = list;//current equals list
			while (current != NULL) {//while current does not equal null
			if (strcmp(current->element->language, target)==0){//if target equals the current language
					printf("We found a book in %s\n\n",current->element->language);//say we found their book
					found=true;//found equals true
					printf("Book %d:\n", i+1);//print book values
					printf("ID: %s\n", current->element->bookId);
					printf("Title: %s\n", current->element->bookTitle);
					printf("Author: %s\n", current->element->bookAuthor);
					printf("Year of Publication: %d\n", current->element->yearPub);
					printf("Currently Loaned out: %s\n", current->element->loanedOut ? "true" : "false");
					printf("Customer name currently loaning book: %s\n", current->element->customerName);
					printf("Times Loaned out: %d\n", current->element->timesLoaned);
					printf("Last Rating: %1.1f stars\n", current->element->rate);
					printf("Last Review: %s\n", current->element->review);
					printf("Language: %s\n", current->element->language);
					 printf("Version: %s\n", current->element->specifics);
			}
			i++;//add 1 to i
			current=current->next;//current equals current next
			} //end while
			if(found==false){//if found equals false
				printf("Sorry we could not find a book in %s\n\n",target);//message saying book could not be found 
			}
    }//end else
}

bool UniqueSearch(char* target){//unique search method     
	struct LinearNode *current;//linear node current
	bool unique=true;//bool unique equals true
	int i = 0;//int i equals 0
			current = list;//current equals list
			while (current != NULL) {//while current does not equal null
			if (strcmp(current->element->bookId, target)==0){//if target equals the current bookid
					unique=false;//unique equals false
					printf("its not unique");//bookid is not unique
			}
			i++;//i plus 1
			current=current->next;//current equals current next
			} //end while
    return unique;//return unique
}


void deleteBook(char* target){//delete book method
   //start from the first link
   struct LinearNode* current = head;
   struct LinearNode* previous = NULL;
   //if list is empty
   if(isEmpty()) {//if list is empty
      return ;//stops method
   }
			current = previous = list;//current equals previous and list
			bool over = false;//bool over equals false
			bool notFound = true;//notFound equals true
			int i = 0;//int i equals 0
			while (over!=true && current != NULL) {//while over doesnt equal true and current doesnt equal null
				if (strcmp(current->element->bookId, target)==0){//if target equals the current bookid
					if(current->element->yearPub<2010){//if current year is less than 2010
						printf("We found your book!\n");//print out we have found their book
						notFound = false;//not found equals false
						if (current == list) {//if current equals list
							list = list->next;//list = list next
							free(current);//free up current
						} //end else
						else {
								previous->next= current->next;//previous next equals current next 
								free(current);//free up current
						} //end else
						printf("Book with value %s has been deleted\n", target);//print out that book has been deleted
						over = true;//over is equal to true
						return;//return to stop method
					}
					else{//else...
						printf("We found your book!\n");//print out we found the book but!
						printf("However we can only delete books before 2010\n");//say we can only delete books before 2010
						notFound = true;//notFound equals true
						over = true;//over equals true
						return;//return to stop method
					}	
				}
				i++;//i plus one
						current=current->next;//current equals current next
			} //end while
			if (notFound==true){//if notFound equals true
				printf("ERROR - sorry your book could not be found or is older than 2010: %s\n", target);//error message
			}
		//}//end else
}// end deleteBook

bool isEmpty(){//is empty method
	if (list == NULL)//if list equals null
		return true;//return true
	else//or
		return false;//return false
}

void LoanOutBook(char* target){//loan out book method
	struct LinearNode *current;//linear node current
	bool found=false;//bool found equals false
	int i = 0;//int i equals 0
	if (isEmpty())//if list is empty
		printf("Error - there are no books in the list\n");//error message
 	else {
			current = list;//current equals list
			while (current != NULL) {//while current doesnt equal null
			if (strcmp(current->element->bookId, target)==0){//if target equals the current bookid
					found=true;//found equals true
					if(found==true){//if found equals true
    					printf("We found your book!\n");//print out we found the book
    					if(current->element->loanedOut==true){//if current element loanedOut equals true
							printf("But sadly its currently loaned out :(\n");//print out that book is currently being loaned out
						}else{//else...
							printf("And its currently available!\n\n");//print out that book is currently not being loaned out
							printf("Book %d:\n", i+1);//print of book values
							printf("ID: %s\n", current->element->bookId);
							printf("Title: %s\n", current->element->bookTitle);
							printf("Author: %s\n", current->element->bookAuthor);
							printf("Year of Publication: %d\n", current->element->yearPub);
							printf("Currently Loaned out: %s\n", current->element->loanedOut ? "true" : "false");
							printf("Customer name currently loaning book: %s\n", current->element->customerName);
							printf("Times Loaned out: %d\n", current->element->timesLoaned);
							printf("Last Rating: %1.1f stars\n", current->element->rate);
							printf("Last Review: %s\n", current->element->review);
							printf("Language: %s\n", current->element->language);
							printf("Version: %s\n", current->element->specifics);
							char temp[40] = {0};//string temporary
							char customerName[40] = {0};//string customername
							printf("Lets loan it out to you!\n");//let the user loan out
							printf("Whats your name? eg Alan\n");//ask for customer name
					    	scanf("%c",&temp); // temp statement to clear buffer
					    	scanf("%[^\n]",customerName);//take in name
					    	printf("Thank you! Here's your book. Please return it when you're done reading it! :)\n");//say they now have the book
					    	bool loanedOut = true;//loanedOut now equals true
					    	int timesLoaned = current->element->timesLoaned + 1;//timeLoaned now is plus 1
					        current->element->loanedOut = loanedOut;//edit node
					        current->element->timesLoaned = timesLoaned;//edit node
					        strcpy(current->element->customerName , customerName);//edit node
						}
					}		
				}
					i++;//add 1 to i
					current=current->next;//current equals current next
			} //end while
    }//end else
}

void ReturnBook(char* target){//return book method
	struct LinearNode *current;//linear node current
	bool found=false;//bool found equals false
	int i = 0;//int i equals 0
			current = list;//current equals list
			while (current != NULL) {//while current doesnt equal null
			if (strcmp(current->element->bookId, target)==0){//if target equals the current bookid
					found=true;//found equals true
					if(found==true){//if found equals true
    					printf("We found your book!\n");//print out we found the book
    					if(current->element->loanedOut==false){//if current element loanedOut equals false
							printf("But for some reason this book is current in our stock\n");//error message
						}else{
							printf("Thank you for returning it!\n\n");//message
							printf("Book %d:\n", i+1);//print of book values
							printf("ID: %s\n", current->element->bookId);
							printf("Title: %s\n", current->element->bookTitle);
							printf("Author: %s\n", current->element->bookAuthor);
							printf("Year of Publication: %d\n", current->element->yearPub);
							printf("Currently Loaned out: %s\n", current->element->loanedOut ? "true" : "false");
							printf("Customer name currently loaning book: %s\n", current->element->customerName);
							printf("Times Loaned out: %d\n", current->element->timesLoaned);
							printf("Last Rating: %1.1f stars\n", current->element->rate);
							printf("Last Review: %s\n", current->element->review);
							char temp[40] = {0};//temp sting
							char review[40] = {0};//review string
							float rate = 0;//float string
							char customerName[40] = {""};//customername string
							printf("Before returning it could you leave a review and rating?\n");//ask for rating and review
							printf("What is your review of the book?\n");//ask for review
							scanf("%c",&temp); // temp statement to clear buffer
					    	scanf("%[^\n]",review);//take in review
					    	printf("What is your rating of the book?(0-5)eg 3.5\n");//ask for rating
					    	scanf("%f",&rate);//takes in rate
					    	bool loanedOut = false;//loanedOut equals false
					        current->element->rate = rate;//current element equals rate
					        strcpy(current->element->review , review);//current element equals review
					        strcpy(current->element->customerName , customerName);//current element equals customerName
						}
					}		
				}
					i++;//i plus one
					current=current->next;//current equals current next
			} //end while
}
void Popular(){//popular method
	struct LinearNode *current;//linear node current
	int maxTimesLoaned;//int maxTimesLoaned
	int minTimesLoaned;//int minTimesLoaned
	float maxRating;//float maxRating
	float minRatig;//float minRatig
	char bookId[9] = {0};//bookId string
	char bookTitle[40] = {0};//bookTitle string
	char bookAuthor[40] = {0};//bookAuthor string
	int yearPub=0;//yearPub equals 0
	bool loanedOut = false;//loanedOut equals false
	char customerName[40] = {0};//customerName string
	int timesLoaned = 0;//timesLoaned equals 0
	float rate = 0;//rate equals 0
	char review[30] = {0};//review string
	int i = 0;//int i equals 0
	if (isEmpty())//if list is empty
		printf("Error - there are no books in the list\n");//error message
 	else {
 			//TIMESLOANED
 			struct LinearNode *temp = current;//Linearnode temp equals current
 			minTimesLoaned = list->element->timesLoaned;//minTimesLoaned equals list->element->timesLoaned
 			strcpy(bookId , list->element->bookId);//bookId equals list->element->bookId
			strcpy(bookTitle , list->element->bookTitle);//bookTitle equals list->element->bookTitle
			strcpy(bookAuthor , list->element->bookAuthor);//bookAuthor equals list->element->bookAuthor
			loanedOut = list->element->loanedOut;//loanedOut equals list->element->loanedOut
			strcpy(customerName , list->element->customerName);//customerName equals list->element->customerName
			rate = list->element->rate;//rate equals list->element->rate
			strcpy(review , list->element->review);//review equals list->element->review
			while(temp != NULL){//while temp does not equal null
             //If current node's data is smaller than min  
             //Then, replace value of min with current node's data  
             if(minTimesLoaned > temp->element->timesLoaned){//minTimesLoaned is greater than temp->element->timesLoaned
                 minTimesLoaned = temp->element->timesLoaned;//minTimesLoaned equals list->element->timesLoaned
				 strcpy(bookId , temp->element->bookId);//bookId equals temp->element->bookId
				 strcpy(bookTitle , temp->element->bookTitle);//bookTitle equals temp->element->bookTitle
				 strcpy(bookAuthor , temp->element->bookAuthor);//bookAuthor equals temp->element->bookAuthor
				 loanedOut = temp->element->loanedOut;//loanedOut equals temp->element->loanedOut
				 strcpy(customerName , temp->element->customerName);//customerName equals temp->element->customerName
				 rate = temp->element->rate;//rate equals temp->element->rate
				 strcpy(review , temp->element->review);//review equals temp->element->review
             }  
             temp= temp->next;  
        	 }          
        	 printf("Book with minimum loan in the list: %d\n", minTimesLoaned);//Print out book values
        	 printf("ID: %s\n", bookId);
			 printf("Title: %s\n", bookTitle);
			 printf("Author: %s\n", bookAuthor);
			 printf("Currently Loaned out: %s\n", loanedOut ? "true" : "false");
			 printf("Customer name currently loaning book: %s\n", customerName);
			 printf("Last Rating: %1.1f stars\n", rate);
			 printf("Last Review: %s\n", review);
    		 struct LinearNode *temp2 = current;
			 maxTimesLoaned = list->element->timesLoaned;
			 strcpy(bookId , list->element->bookId);
			 strcpy(bookTitle , list->element->bookTitle);
			 strcpy(bookAuthor , list->element->bookAuthor);
			 loanedOut = list->element->loanedOut;
			 strcpy(customerName , list->element->customerName);
			 rate = list->element->rate;
			 strcpy(review , list->element->review);
			 while(temp2 != NULL){  
             //If current node's data is smaller than min  
             //Then, replace value of min with current node's data  
             if(maxTimesLoaned > temp2->element->timesLoaned) {  
                 minTimesLoaned = temp2->element->timesLoaned;
				 strcpy(bookId , temp2->element->bookId);
				 strcpy(bookTitle , temp2->element->bookTitle);
				 strcpy(bookAuthor , temp2->element->bookAuthor);
				 loanedOut = temp2->element->loanedOut;
				 strcpy(customerName , temp2->element->customerName);
				 rate = temp2->element->rate;
				 strcpy(review , temp2->element->review);
             }  
             temp2= temp2->next;  
        	 }          
        	 printf("Book with maximum loan in the list: %d\n", maxTimesLoaned);//Print out book values
        	 printf("ID: %s\n", bookId);
			 printf("Title: %s\n", bookTitle);
			 printf("Author: %s\n", bookAuthor);
			 printf("Currently Loaned out: %s\n", loanedOut ? "true" : "false");
			 printf("Customer name currently loaning book: %s\n", customerName);
			 printf("Last Rating: %1.1f stars\n", rate);
			 printf("Last Review: %s\n", review);
			 //RATINGS
			 struct LinearNode *temp3 = current;
			 minRatig = list->element->rate;
			 strcpy(bookId , list->element->bookId);
			 strcpy(bookTitle , list->element->bookTitle);
			 strcpy(bookAuthor , list->element->bookAuthor);
			 loanedOut = list->element->loanedOut;
			 strcpy(customerName , list->element->customerName);
			 timesLoaned = list->element->timesLoaned;
			 strcpy(review , list->element->review);
			while(temp3 != NULL){  
             //If current node's data is smaller than min  
             //Then, replace value of min with current node's data  
             if(minRatig > temp3->element->rate) {  
                 minRatig = temp3->element->rate;
				 strcpy(bookId , temp3->element->bookId);
				 strcpy(bookTitle , temp3->element->bookTitle);
				 strcpy(bookAuthor , temp3->element->bookAuthor);
				 loanedOut = temp3->element->loanedOut;
				 strcpy(customerName , temp3->element->customerName);
				 timesLoaned = temp3->element->timesLoaned;
				 strcpy(review , temp3->element->review);
             }  
             temp3= temp3->next;  
        	 }          
        	 printf("Book with lowest rating in the list: %1.1f\n", minRatig);//Print out book values
        	 printf("ID: %s\n", bookId);
			 printf("Title: %s\n", bookTitle);
			 printf("Author: %s\n", bookAuthor);
			 printf("Currently Loaned out: %s\n", loanedOut ? "true" : "false");
			 printf("Customer name currently loaning book: %s\n", customerName);
			 printf("Times Loaned out: %d\n", current->element->timesLoaned);
			 printf("Last Review: %s\n", review);
    		 struct LinearNode *temp4 = current;
			 maxRating = list->element->rate;
			 strcpy(bookId , list->element->bookId);
			 strcpy(bookTitle , list->element->bookTitle);
			 strcpy(bookAuthor , list->element->bookAuthor);
			 loanedOut = list->element->loanedOut;
			 strcpy(customerName , list->element->customerName);
			 timesLoaned = list->element->timesLoaned;
			 strcpy(review , list->element->review);
			 while(temp4 != NULL){  
             //If current node's data is smaller than min  
             //Then, replace value of min with current node's data  
             if(maxRating > temp4->element->rate) {  
                 maxRating = temp4->element->rate;
				 strcpy(bookId , temp4->element->bookId);
				 strcpy(bookTitle , temp4->element->bookTitle);
				 strcpy(bookAuthor , temp4->element->bookAuthor);
				 loanedOut = temp4->element->loanedOut;
				 strcpy(customerName , temp4->element->customerName);
				 timesLoaned = temp4->element->timesLoaned;
				 strcpy(review , temp4->element->review);
             }  
             temp4= temp4->next;  
        	 }          
        	 printf("Book with lowest rating in the list: %1.1f\n", maxRating);//Print out book values
        	 printf("ID: %s\n", bookId);
			 printf("Title: %s\n", bookTitle);
			 printf("Author: %s\n", bookAuthor);
			 printf("Currently Loaned out: %s\n", loanedOut ? "true" : "false");
			 printf("Customer name currently loaning book: %s\n", customerName);
			 printf("Times Loaned out: %d\n", current->element->timesLoaned);
			 printf("Last Review: %s\n", review);
			 }  
}

