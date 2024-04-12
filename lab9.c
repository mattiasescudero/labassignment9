#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order; 
	struct RecordType *next;
};

// Fill out this structure, should be a node for a Linked List
struct HashType
{
	struct RecordType *head;
};

// Compute the hash function
int hash(int x)
{
	return x % 23;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
	int i;
	struct RecordType *current;

	for (i=0;i<hashSz;++i)
	{
		printf("Index %d -> ", i);
		current = pHashArray[i].head;
		while (current != NULL)
		{
			printf("\t%d %c %d\n", current->id, current->name, current->order);
			current = current->next;
		}
	}
	printf("\n");
}

int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;
	int hashSz = 23;

	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);
	// Your hash implementation

	struct HashType hashTable[hashSz];
	for (int i = 0; i < hashSz; ++i)
	{
		hashTable[i].head = NULL;
	}

	for (int i = 0; i < recordSz; ++i)
	{
		int index = hash(pRecords[i].id);
		if (hashTable[index].head == NULL)
		{
			hashTable[index].head = &pRecords[i];
		}
		else
		{
			struct RecordType *current = hashTable[index].head;
			while (current->next != NULL)
			{
				current = current->next;
			}
			current->next = &pRecords[i];
		}
	}

	displayRecordsInHash(hashTable, hashSz);

	free(pRecords);

	return 0;
}