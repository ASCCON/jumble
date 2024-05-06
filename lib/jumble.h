/**
 * @file   jumble.h
 * @author Walter.Davies <walter.davies@MacBook-Pro.local>
 * @date   Wed Nov 21 19:14:18 2018
 *
 * @brief  Header file for jumble.c.
 *
 * This is about the most inefficient implementation possible;
 * partly to just get a POC running and partly to see how much
 * better we can make it!
 */
///@file jumble.h

/**
 * All the libraries that are fit to print.
 * Note non-standard github.com:likle/cargs.git
 */
#include <cargs.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>

/**
 * Define this as the DStat header file. For when only the most verbose
 * will do.
 */
#ifndef JUMBLE_H
#define JUMBLE_H
#endif

/**
 * Enables the `DT_` entries in sys/dirent.h.
 */
#define _BSD_SOURCE

/**
 * For some reason, we can figure out the system-specific, but not the generic,
 * MAXPATHLEN.
 */
#define MAXPATHLEN __DARWIN_MAXPATHLEN

/**
 * Set up debug printing.
 */
#define Dprint(fmt, ...)                                                \
    do { if (DEBUG) fprintf(stderr, "<DEBUG> %s:%d:%s(): " fmt "\n",    \
                            __FILE__, __LINE__, __func__, __VA_ARGS__); } \
    while (0)

#ifdef DEBUG
#define DEBUG 1
#else
#define DEBUG 0
#endif

// Placeholder until we figure out somthing better.
int MATCHES = 0;

/**
 * Default location for global dictionary file.
 */
#define dictionary "/usr/share/dict/words";

/**
 * Global variable declarations which may be over-ridden by CLI options.
 */
struct sel_opts_s {
    char *dict;  ///< Path to alternate dictionary file.
    int  least;  ///< Minimum number of letters in results.
    int  most;   ///< Maximum number of letters in results.
    bool err;    ///< Return error condition on no matches.
    bool its;    ///< Include total number of iterations in output.
    bool mat;    ///< Match only letters from input in results.
    bool num;    ///< Match only number of letters from input in results.
    bool vrb;    ///< Precede each output word with iteration index.
    char *FOPTS; ///< Placeholder for file handling options.
    FILE *DICT;  ///< File handle for dictionary path.
};
