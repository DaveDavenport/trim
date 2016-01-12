/**
 * trim
 *
 * MIT/X11 License
 * Copyright 2016 Qball Cow <qball@gmpclient.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS
 * OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

int main ( int argc, char **argv )
{
    int start = 1;
    int c;
    int count   = 0;
    int single  = 0;
    int tabsize = 4;

    for ( int ac = 1; ac < argc; ac++ ) {
        if ( strcmp ( argv[ac], "-s" ) == 0 ) {
            single = 1;
        }
        else if ( strcmp ( argv[ac], "-t" ) == 0 && ( ac + 1 ) < argc ) {
            ac++;
            tabsize = strtoul ( argv[ac], NULL, 10 );
        }
        else {
            printf ( "%s usage:\n", argv[0] );
            printf ( "\t%s [options]\n\n", argv[0] );
            printf ( "Read from stdin, strip leading and trailing whitespace and print to stdout.\n\n" );
            printf ( "Options:\n" );
            printf ( "\t-s: If multiple whitespace detected in the middle of the string, only print one space.\n" );
            printf ( "\t-t: Number of spaces in a tab. (default: 4)." );
            return EXIT_SUCCESS;
        }
    }

    if ( isatty ( fileno ( stdin ) ) ) {
        fprintf ( stderr, "Trim needs to take it input from a pipe or redirect, not a tty.\n" );
        return EXIT_FAILURE;
    }
    while ( ( c = getchar () ) != EOF ) {
        // Skip leading blanks.
        if ( start ) {
            if ( isblank ( c ) ) {
                continue;
            }
            putchar ( c );
            start = 0;
            continue;
        }
        // If we encounter blanks, count them for now.
        if ( c == ' ' ) {
            count++;
        }
        // For tabs we count 4 atm.
        else if ( c == '\t' ) {
            count += tabsize;
        }
        else{
            if ( count ) {
                for (; count > 0; count-- ) {
                    putchar ( ' ' );
                    if ( single ) {
                        count = 0;
                    }
                }
            }
            putchar ( c );
        }
    }
    return EXIT_SUCCESS;
}
