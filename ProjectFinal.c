#include <stdio.h>

#define MAX_LINES 100
#define MAX_LENGTH 256
#define MAX_INPUTS 50
#define MADLIB1 "madlib1.txt"
#define MADLIB2 "madlib2.txt"

// Prototypes
void loadMadlibFile(const char *filename, char story[MAX_LINES][MAX_LENGTH], int *lineCount);
void getUserInput(char type, char inputs[][MAX_LENGTH], int *count);
void replacePlaceholders(char story[][MAX_LENGTH], int lineCount, char adjectives[][MAX_LENGTH], char nouns[][MAX_LENGTH], char verbs[][MAX_LENGTH], int adjCount, int nounCount, int verbCount);
void printStory(char story[MAX_LINES][MAX_LENGTH], int lineCount);
void copyString(char *dest, const char *src);

// Main
int main() {
	char story[MAX_LINES][MAX_LENGTH];
	char adjectives[MAX_INPUTS][MAX_LENGTH];
	char nouns[MAX_INPUTS][MAX_LENGTH];
	char verbs[MAX_INPUTS][MAX_LENGTH];
	const char *files[] = {MADLIB1, MADLIB2};
    
	int lineCount = 0;
	int adjCount = 0;
	int nounCount = 0;
	int verbCount = 0;
	int choice;
    
	printf("Which madlibs file do you want to use?\n");
	for(int i = 0; i < 2; i++) {
    	printf("%d: %s\n", i + 1, files[i]);
	}
	printf("Enter your choice (1 or 2): ");
	scanf(" %d", &choice);
    
	if (choice < 1 || choice > 2) {
    	printf("Error! Invalid\n");
    	return 0;
	}
    
	FILE *fl;
	fl = fopen(files[choice - 1], "r");
    
	if(fl == NULL) {
    	printf("Error, file did not open\n");
    	return 0;
	}
    
	int count = 0;
	while (fgets(story[count], MAX_LENGTH, fl) && count < MAX_LINES) {
    	int ben = 0;
    	while (story[count][ben] != '\0' && story[count][ben] != '\n') {
        	ben++;
    	}
    	story[count][ben] = '\0';
    	count++;
	}
	fclose(fl);
	lineCount = count;
    
	for (int i = 0; i < lineCount; i++) {
    	if (story[i][0] == 'A') {
        	getUserInput('A', adjectives, &adjCount);
	} else if (story[i][0] == 'N') {
    	getUserInput('N', nouns, &nounCount);
	} else if (story[i][0] == 'V') {
    	getUserInput('V', verbs, &verbCount);
    	}
	}
    
replacePlaceholders(story, lineCount, adjectives, nouns, verbs, adjCount, nounCount, verbCount);
 
	return 0;
}

// Functions start here

void loadMadlibFile(const char *filename, char story[][MAX_LENGTH], int *lineCount) {
	FILE *fl;
	fl = fopen(filename, "r");
    
	if (fl == NULL) {
    	printf("Error opening file\n");
    	return;
	}
    
	int count = 0;
	while (fgets(story[count], MAX_LENGTH, fl) && count < MAX_LINES) {
    	int ben = 0;
    	while (story[count][ben] != '\0' && story[count][ben] != '\n') {
        	ben++;
    	}
    	story[count][ben] = '\0';
    	count++;
	}
	fclose(fl);
	*lineCount = count;
}

void getUserInput(char type, char inputs[][MAX_LENGTH], int *count) { 

	if (type == 'A') {
    	printf("Enter an adjective: ");
    	scanf("%c", inputs[*count]);
	} else if (type == 'N') {
    	printf("Enter a noun: ");
    
	} else if (type == 'V') {
    	printf("Enter a verb: ");
    	
	}
	scanf("%s", inputs[*count]);
    
	int ben = 0;
	while (inputs[*count][ben] != '\0' && inputs[*count][ben] != '\n') {
    	ben++;
	}
	inputs[*count][ben] = '\0';
	(*count)++;
}

void replacePlaceholders(char story[][MAX_LENGTH], int lineCount, char adjectives[][MAX_LENGTH], char nouns[][MAX_LENGTH], char verbs[][MAX_LENGTH], int adjCount, int nounCount, int verbCount) {
	int adjIndex = 0;
	int nounIndex = 0;
	int verbIndex = 0;

	char finalStory[MAX_LINES * MAX_LENGTH] = "";
	int finalStoryIndex = 0;

	for (int i = 0; i < lineCount; i++) {
    	int j = 0;

    	if (story[i][0] == 'A' && adjIndex < adjCount) {
        	char *word = adjectives[adjIndex++];
            	for (int k = 0; word[k] != '\0'; k++) {
                	finalStory[finalStoryIndex++] = word[k];
            	}
    	}
    	else if (story[i][0] == 'N' && nounIndex < nounCount) {
        	char *word = nouns[nounIndex++];
            	for (int k = 0; word[k] != '\0'; k++) {
                	finalStory[finalStoryIndex++] = word[k];
            	}
    	}
    	else if (story[i][0] == 'V' && verbIndex < verbCount) {
        	char *word = verbs[verbIndex++];
            	for (int k = 0; word[k] != '\0'; k++) {
                	finalStory[finalStoryIndex++] = word[k];
            	}
    	}
    	else {
        	while (story[i][j] != '\0') {
            	finalStory[finalStoryIndex++] = story[i][j++];
        	}
    	}

	finalStory[finalStoryIndex++] = ' ';
	}

	finalStory[finalStoryIndex] = '\0';

	printf("\nFinal Story:\n%s\n", finalStory);
}

void printStory(char story[][MAX_LENGTH], int lineCount) {
	for (int i = 0; i < lineCount; i++) {
    	printf("%s\n", story[i]);
	}
}

void copyString(char *dest, const char *src) {
	while (*src != '\0') {
    	*dest = *src;
    	dest++;
    	src++;
	}
	*dest = '\0';
}

