#include	<stdio.h>

/*
 * tt2ht1.c 
 *   purpose: filter data and prints out strings 
 *     input: text
 *    output: text of only the strings, including escaped quotes 
 *    errors: no error conditions
 *     usage: extract_strings < input > output
 */

int main()
{
    /* Three states this machine can be in: 
     * 1: not in any quotes: 
     *      Start here or enter from state 2 
     *      Don't print 
     *      Exit to state 2 when ' 
     * 2: in double quotes:
     *      Enter when ' from state 1 
     *      Print 
     *      Exit to state 1 when ' 
     * 3: in escaped double quotes: 
     *      Enter when \" from state 2 
     *      Print 
     *      Exit to state 2 when \"
     * In order to detect states 1 and 2, check if current char is '
     * In order to detect state 3, check if current char is '
     * and if the PREVIOUS char was \.    
     * Oh, and if end of file is reached, terminate. 
     */ 

    int cur; 
    int prev; 
    int state=1; 
    while ( (cur = getchar()) != EOF) 
    { 
        if ((cur == '"') && (state == 1)) 
        {
            state = 2;
            printf("\n");
        } 
        else if ((cur == '"') && (prev == '\\') && (state == 2))
        { 
            state = 3; 
        }
        else if ((cur == '"') && (prev == '\\') && (state == 3))
        { 
            state = 2; 
        } 
        else if((cur == '"') && (state == 2)) 
        {
            state = 1; 
            putchar(cur);
        }

        if ((state==2) || (state==3))
        { 
            putchar(cur); 
        } 
        prev = cur;
    } 
}

