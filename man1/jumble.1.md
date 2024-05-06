# jumble
Letter scrambler for finding words. Helpful for solving Jumble and related
word games.

# Command Line Options

* Check all possible permutations (current/default).
  + [no option]
* Do not return matches with additional letters (e.g:
  "racket" would return "trace" but not "shortcake").
  + `-m`/`--match-letters`
* Only return results with the same number of letters (e.g:
  "racket" would return "tacker" but not "trace").
  + `-n`/`--num-letters`
  + **NOTE**: The preceding two options may be combined to only return
    results with the same number of letters (e.g: "racket" would
    also return "tacker" but not "rackett").
    - `-m -n` / `--match-letters --num-letters`
* Only return results with _at least_ this many characters.
  + `-L <int>`/`--at-least=<int>`
* Only return results with _at most_ this many characters.
  + `-M <int>`/`--at-most=<int>`
  + **NOTE**: The preceding two options may be combined to bound the
          results, e.g:
    - `-M 6 -L 4` returns results between 4-6 characters long,
      inclusive.
    - `-L 6 -M 4` skips output words that are 5 characters long.
  + **NOTE**: The preceding two options are over-ridden by the `-n`/
          `--num-letters` option.
* Specify an alternate dictionary file.
  + `-D <path>`/`--dict=<path>`
* Show number of search results.
  + `-r`/`--results`
* Return error on no matches (file errors always return an
  error value).
  + `-e`/`--error`
* Show total number of iterations.
  + `-i`/`--iterations`
* Precede each output word with its iteration number.
  + `-v`/`--verbose`
* Show help message and exit.
  + `-h`/`--help`
* Show version information and exit.
  + `-V`/`--version`

## Future versions
Version 2: Support a configuration file and multiple dictionary files.
