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

/**
 * Import everything else in <jumble.h>.
 */
#include "lib/jumble.h"
#include "lib/version.h"

/**
 * CArgs library struct with options and documentation.
 */
static struct cag_option options[] = {
    {.identifier = 'D',
     .access_letters = "D",
     .access_name = "dict",
     .value_name = "DICTIONARY",
     .description = "Use a different dictionary file from the default."},

    {.identifier = 'L',
     .access_letters = "L",
     .access_name = "at-least",
     .value_name = "LEAST",
     .description = "Only returns results with AT LEAST <num> letters. May be combined with the -M option to inside- or outside-bound the result set."},

    {.identifier = 'M',
     .access_letters = "M",
     .access_name = "at-most",
     .value_name = "MOST",
     .description = "Only returns results with AT MOST <num> letters. May be combined with the -L option to inside- or outside-bound the result set."},

    {.identifier = 'V',
     .access_letters = "V",
     .access_name = "version",
     .value_name = NULL,
     .description = "Print version information and exit."},

    {.identifier = 'e',
     .access_letters = "e",
     .access_name = "error",
     .value_name = NULL,
     .description = "Return a non-zero exit status if no words are found. Normally, only file access or command-line problems return a non-zero exit status."},

    {.identifier = 'h',
     .access_letters = "h",
     .access_name = "help",
     .value_name = NULL,
     .description = "Prints this help message."},

    {.identifier = 'i',
     .access_letters = "i",
     .access_name = "iterations",
     .value_name = NULL,
     .description = "Show the total number of iterations on output. See also the -v option."},

    {.identifier = 'm',
     .access_letters = "m",
     .access_name = "match-letters",
     .value_name = NULL,
     .description = "Only return results with the letters of the input string. May be combined with the -n option to limit the result set to the same letters and same number of letters as the input string."},

    {.identifier = 'n',
     .access_letters = "n",
     .access_name = "num-letters",
     .value_name = NULL,
     .description = "Only return results with the letters of the input string. May be combined with the -m option to limit the result set to the same letters and same number of letters as the input string."},

    {.identifier = 'v',
     .access_letters = "v",
     .access_name = "verbose",
     .value_name = NULL,
     .description = "Precede each output word with its iteration index. See also the -i option."}};


/**
 * Initialise the various CLI options.
 */
struct sel_opts_s opt = {
    // Default values for sel_opts{}.
    .dict = "dictionary",
    .least = 0, .most = 0,
    .err = false, .its = false, .mat = false, .num = false, .vrb = false,
    .FOPTS =  "r", // O_RDONLY
};

/**
 * fileSearch: Reads file name \cfname and searches for string \cstr
 *
 * @param str pointer to char
 *
 * @return -1 ferror, 0 no match, 1 match
 */
int fileSearch(char *str) {
    FILE *fp;
    //int   line_num    = 1;
    int   retval      = 0;
    char  temp[512];

    if ( (fp = fopen(opt.dict, opt.FOPTS)) == NULL ) {
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
        fileSearch(a);
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
    /// Initialise, read, and set the various user options.
    //int param_index = 0;
    cag_option_context context;

    cag_option_init(&context, options, CAG_ARRAY_SIZE(options), argc, argv);

    while (cag_option_fetch(&context)) {
        switch (cag_option_get_identifier(&context)) {
        case 'D':
            if ( cag_option_get_value(&context) ) {
                opt.dict = (char *)cag_option_get_value(&context);
                opt.DICT = fopen(opt.dict, opt.FOPTS);
                if ( ! opt.DICT ) {
                    Dprint("*opt.dict: %i", opt.DICT->_file);
                    errno = ENOENT;
                    perror("Specified dictionary file not found.");
                    exit(EXIT_FAILURE);
                }
            } else {
                errno = EINVAL;
                perror("Must specify path to alternate dictionary file.");
                exit(EXIT_FAILURE);
            }
            break;
        case 'L':
            if ( cag_option_get_value(&context) ) {
                if ( atoi(cag_option_get_value(&context)) > 0 ) {
                    opt.least = atoi(cag_option_get_value(&context));
                } else {
                    errno = EINVAL;
                    perror("Least number must be an integer greater than 0.");
                    exit(EXIT_FAILURE);
                }
            } else {
                errno = EINVAL;
                perror("Must specify Least number.");
                exit(EXIT_FAILURE);
            }
            break;
        case 'M':
            if ( cag_option_get_value(&context) ) {
                if ( atoi(cag_option_get_value(&context)) > 0 ) {
                    opt.most = atoi(cag_option_get_value(&context));
                } else {
                    errno = EINVAL;
                    perror("Most number must be an integer greater than 0.");
                    exit(EXIT_FAILURE);
                }
            } else {
                errno = EINVAL;
                perror("Must specify Most number.");
                exit(EXIT_FAILURE);
            }
            break;
        case 'V':
            printf("%s %s\n", PROGNAME, VERSION);
            printf("Git commit ID: %s\n", COMMIT);
            printf("%s\n", AUTHOR);
            printf("%s\n", DATE);
            printf("%s\n", ELLIE);
            exit(EXIT_SUCCESS);
            break;
        case 'e':
            opt.err = true;
            break;
        case 'h':
            printf("Usage: dstat [OPTION]... DIRECTORY...\n");
            printf("Quickly gathers and reports the numbers of various file ");
            printf("types under a\ndirectory or filesystem.\n\n");
            cag_option_print(options, CAG_ARRAY_SIZE(options), stdout);
            exit(EXIT_SUCCESS);
        case 'i':
            opt.its = true;
            break;
        case 'v':
            opt.vrb = true;
        case '?':
            cag_option_print_error(&context, stdout);
            exit(EXIT_FAILURE);
        }
    }
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
