/*****************************************************************************************
Prologue

UCSC Extension: Advanced C Programming

Instructor: Rajainder A. Yeldandi

Author: Kevin Geiszler

Assignment Number: 15, Hashing

Topics: Hashing

File Name: assignment15_KevinGeiszler.c

Date: 4/4/2017

Objective: This program reads records from an input file, creates a hash table, and places
		   them in the table accordingly.
		   
Comments:  This hash table uses a separate chaining method. The load factor is displayed
           after each number has been hashed in placed in a bucket. The records in the
           input file are randomly generated numbers between 100 and 1,000. These numbers
           were generated in an Excel file. When all elements have been hashed, a summary
           of the buckets is shown and the chains are displayed.

*****************************************************************************************/

//Preprocessor directives

#include <stdio.h>
#include <stdlib.h>

#define RECORD_SIZE 100
#define TABLE_SIZE 15

struct node
{
	int key, record;
	struct node *pNext;
};

typedef struct node NODE;

/****************************************************************************************/

//Function prototypes

int hashFunction(int record);
void insert(NODE *startPtr[], int key, int record);
void displayLinks(FILE *pOutFile, NODE *hashTable[]);
void displayBucketStats(FILE *pOutFile, NODE *hashTable[]);
void getUserInput(FILE *pOutFile, int *records, NODE *hashTable[]);

/****************************************************************************************/

//gcc -o a15 a15.c
//a15 a15infile.doc a15outfile.doc

//The main function

int main(int argc, char *argv[])
{
	NODE *hashTable[15];
	int records[RECORD_SIZE];
	FILE *pInFile, *pOutFile;
	
	//check command line arguments
	if (argc != 3)
	{
		printf("Error, need the following file usage: %s inputFile outputFile\n", argv[0]);
		exit(1);
	}
	
	//open input file
	if ((pInFile = fopen(argv[1], "r")) == NULL)
	{
		printf("Error opening input file (%s)\n", argv[1]);
		exit(1);
	}	
	
	//open output file
	if ((pOutFile = fopen(argv[2], "w")) == NULL)
	{
		printf("Error opening output file (%s)\n", argv[2]);
		exit(1);
	}
	
	rewind(pInFile);
	
	//set each bucket to NULL
	for (int i = 0; i < TABLE_SIZE; i++)
		hashTable[i] = NULL;
		
	for (int i = 0; i < RECORD_SIZE; i++)
		fscanf(pInFile, "%d", &records[i]);
		
	fclose(pInFile);

	getUserInput(pOutFile, records, hashTable);
	displayBucketStats(pOutFile, hashTable);
	displayLinks(pOutFile, hashTable);
	
	fclose(pOutFile);
	
	return 0;
}

/****************************************************************************************/

//The hash function

int hashFunction(int record)
{
	return record % TABLE_SIZE;
}

/****************************************************************************************/

//Insert a link into the hash table at the corresponding bucket

void insert(NODE *startPtr[], int key, int record)
{
	NODE *temp = *startPtr;
	NODE *newPtr = (NODE *) malloc(sizeof(NODE));
	
	if (newPtr == NULL)
	{
		printf("Error creating link in insert()\n");
		exit(1);
	}
	
	newPtr->key = key;
	newPtr->record = record;
	newPtr->pNext = NULL;
	
	if (*startPtr == NULL)
	{
		*startPtr = newPtr;
		return;
	}
	
	while (temp->pNext != NULL)
		temp = temp->pNext;
	
	temp->pNext = newPtr;
	
	return;
}

/****************************************************************************************/

//Display the hash table and its links

void displayLinks(FILE *pOutFile, NODE *hashTable[])
{
	NODE *temp = NULL;
	
	printf("The hash table and its links are as follows:\n\n");
	fprintf(pOutFile, "The hash table and its links are as follows:\n\n");
	
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		temp = hashTable[i];
		
		printf("Bucket %2d (Key %2d): ", i+1, i);
		fprintf(pOutFile, "Bucket %2d (Key %2d): ", i+1, i);
		
		while (temp != NULL)
		{
			printf("%d -> ", temp->record);
			fprintf(pOutFile, "%d -> ", temp->record);
			
			temp = temp->pNext;
		}
	
		printf("NULL\n");
		fprintf(pOutFile, "NULL\n");
	}
	
	printf("\nThe overall load factor is %.2lf\n\n", (double)RECORD_SIZE / TABLE_SIZE);
	fprintf(pOutFile, "\nThe overall load factor is %.2lf\n\n", (double)RECORD_SIZE / TABLE_SIZE);
}

/****************************************************************************************/

//Display the stats for each bucket

void displayBucketStats(FILE *pOutFile, NODE *hashTable[])
{
	int count = 0;
	NODE *temp = NULL;
	
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		temp = hashTable[i];
		count = 0;
		
		while (temp != NULL)
		{
			count++;
			temp = temp->pNext;
		}
		
		printf("Bucket %2d contains %2d links\n", i+1, count);
		fprintf(pOutFile, "Bucket %2d contains %2d links\n", i+1, count);
	}
	
	printf("\n");
	fprintf(pOutFile, "\n");
}

/****************************************************************************************/

//Get each record from the user, display the hash function result, indicate which bucket
//the record is being inserted into, and display the load factor.

void getUserInput(FILE *pOutFile, int *records, NODE *hashTable[])
{
	int myKey;
	
	for (int i = 0; i < RECORD_SIZE; i++)
	{
		printf("Reading record number %d: %d\n", i + 1, records[i]);
		fprintf(pOutFile, "Reading record number %d: %d\n", i + 1, records[i]);
		
		myKey = hashFunction(records[i]);
		printf("Hash function result: %d\n", myKey);
		fprintf(pOutFile, "Hash function result: %d\n", myKey);
		
		printf("Inserting %d into Bucket %d\n", records[i], myKey + 1);
		fprintf(pOutFile, "Inserting %d into Bucket %d\n", records[i], myKey + 1);
		
		printf("The load factor is now %.2lf\n\n", (double)(i + 1) / TABLE_SIZE);
		fprintf(pOutFile, "The load factor is now %.2lf\n\n", (double)(i + 1) / TABLE_SIZE);
		
		insert(&hashTable[myKey], myKey, records[i]);
	}
}

/****************************************************************************************/





















































