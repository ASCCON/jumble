/**
 * @file   jumble.c
 * @author Walter.Davies <walter.davies@MacBook-Pro.local>
 * @date   Wed Nov 21 19:14:18 2018
 *
 * @brief  C program to print all permutations with duplicates allowed.
 *
 * This is about the most inefficient implementation possible;
 * partly to just get a POC running and partly to see how much
 * better we can make it!
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define dictionary "/usr/share/dict/words"

int MATCHES = 0;

/**
 * fileSearch: Reads file name \cfname and searches for string \cstr
 *
 * @param fname pointer to char filename string
 * @param str pointer to char
 *
 * @return -1 ferror, 0 no match, 1 match
 */
int fileSearch(char *fname, char *str) {
    FILE *fp;
    //int   line_num    = 1;
    int   retval      = 0;
    char  temp[512];

    if ( (fp = fopen(fname, "r")) == NULL ) {
        return -1;
    }

    while (fgets(temp, 512, fp) != NULL) {
        if ((strstr(temp, str)) != NULL) {
            //printf("A match found on line: %d\n", line_num);
            printf("%s", temp);
            MATCHES++;
            retval = 1;
        }
        //line_num++;
    }

    // Close the file if still open
    if (fp) { fclose(fp); }

    return retval;
}

/**
 * swap: Flip the inputs
 *
 * @param x First pointer to char becomes second
 * @param y Second pointer to char becomes first
 */
void swap(char *x, char *y) {
    char temp;
    temp = *x;
    *x   = *y;
    *y   = temp;
}

/**
 * permute: Function to print permutations of string
 *
 * @param a Pointer to char string
 * @param l Integer starting index of the string
 * @param r Integer ending index of the string
 */
void permute(char *a, int l, int r) {
    int i;
    if ( l == r )
        // printf("%s\n", a);
        fileSearch(dictionary, a);
    else {
        for ( i = l; i <= r; i++ ) {
            swap((a + l), (a + i));
            permute(a, l + 1, r);
            swap((a + l), (a + i));  // backtrack
        }
    }
}

/**
 * main: Driver program to test above functions
 *
 * @param argc Integer argument count
 * @param argv Pointer to char argument vector
 *
 * @return Calls exit(1) on error or 0 otherwise
 */
int main(int argc, char *argv[]) {
    // Add CLI options checking.
    if (argc != 2) {
        printf("usage: %s %s\n", argv[0], "<word>");
        exit(1);
    }

    char *str = argv[1];
    // generate list of permutations
    // e.g char str[] = "aspirin";
    int n = strlen(str);
    permute(str, 0, n - 1);

    // check permutations against dictionary
    // ideally, slurp dictionary into memory

    // count number of matches and exit on absolute value of (num - 1)
    if ( MATCHES == 0 ) {
        printf("Sorry, couldn't find a match.\n");
        exit(1);
    } else {
        printf("%d matches found.\n", MATCHES);
        exit(0);
    }
}
