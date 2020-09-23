#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
* Generates a number of random lower case letterValues. * The letterValues will be stored in the given array. */
void generate_letterValues(int number, char *destination){
    char vowels[] = {'a', 'e', 'i', 'o', 'u'};
    int i;
    unsigned int rand_seed;
    printf("Number < 1000:\n");
    scanf("%d", &rand_seed);    // initialise the PRNG
    getchar();
    srandom(rand_seed);

    // Half of the letterValues should be vowels
    for (i=0;i<number/2;i++, destination++) *destination = vowels[random()%5];
    for (;i<number;i++, destination++) *destination = random()%26+'a';
}



/**
* Tries to read the file into the array.
* Each line has one value.
*
* Returns the number of lines read or -1 in case of file open error.
*/
int read_array_from_file(const char* filepath, int *array, int array_length){
    FILE *file;
    int i;

    if ((file = fopen(filepath, "r")) == NULL) return -1;
    for (i=0;i<array_length;i++){
        if (fscanf(file, "%d", &array[i]) == EOF) break;
    }
    return i;
}

/** Return value of letter if it exists in array
 * Converts Upper to Lower case letters
 * Returns -1 if letter not available
 */
int letterNumber(char *array, char letter,  const int *letters) {
    int valToReturn = -1;
    for (int i = 0; i < sizeof(array); ++i) {

        if (letter >= 65 && letter <= 90) {
            letter = letter + 32;
        }

        if (array[i]  == letter) {
            valToReturn = letters[array[i] - 97];
            array[i] = 0;
            break;
        }
    }
    return valToReturn;
}


int letterCounter(char letter, const char *list) {
    int counter = 0;

    for (int i = 0; i < sizeof(list); ++i) {

        if (list[i] == letter)
            counter++;

    }
    return counter;
}

int main(void) {

    char MyDeck[7];
    int letterValues[26];
    char word[7];
    int wordTotal = 0;
    int OverallTotal = 0;
    char exit = 0;
    char input = 0;
    int value = 0;
    char MyDeckCOPY[7];
    char listrOfWords[1000];
    int listPositioncounter = 0;

    generate_letterValues(7, MyDeck);
    read_array_from_file("/Users/daveirwin/Programming/CLionProjects/Assignment1/letter_values.dms", letterValues, 26);

    memcpy(MyDeckCOPY, MyDeck, sizeof(MyDeck)); // Used sothe original array of letters will be intact for when entering more than one word


//    for (int i = 0; i < 26 ; ++i) {
//        printf("%d ",letterValues[i]);
//    }


    printf("\nYour letterValues (and their count) are:\n");
    for (int i = 0; i < 7; ++i) {
        printf("%c --> %d\n", MyDeck[i], letterValues[MyDeck[i] - 97]);
    }

    do {

        // Stop reading when we get the new line
        printf("Input word: ");
        while (input != '\n') {
            input = getchar();
            if (input == '\n')
                break;

            value = letterNumber(MyDeckCOPY, input, letterValues);
            if (value != -1) {
                wordTotal = wordTotal + value;
                listrOfWords[listPositioncounter] = input;
                listPositioncounter++;



            } else {
                printf("Letter %c not available!\nNot enough letters to make that!\n", input);
                getchar();
                wordTotal = 0;
                break;
            }


        }
        if (value != -1) {
            OverallTotal = OverallTotal + wordTotal;
            printf("You Used: . Worth: %d. Current Total: %d\n", wordTotal, OverallTotal);

            listrOfWords[listPositioncounter] = '\n';
            listPositioncounter++;
        }

        printf("Try Again? (y/n)");

        exit = getchar();

        getchar();  //Used to handle letters in input stream like in Java

        input = 0;  //Getting rid of /n in input to stop while loop exiting prematurely

        memcpy(MyDeckCOPY, MyDeck, sizeof(MyDeck)); //Refilling letters in copy array so to be used again to make more words.

        wordTotal = 0;      //Re-initialise wordTotal to 0 as to stop accumulation of word counts.

    } while (exit != 'n');

    printf("\nTotal score: %d\n", OverallTotal);
    printf("\nYou provided the following words: \n%s\n", listrOfWords);
    printf("Letter Count:\n");
    for (int j = 0; j < sizeof(MyDeck); ++j) {
        int total = letterCounter(MyDeck[j], listrOfWords);
        printf("%c %d\n", MyDeck[j], total);
    }
}
