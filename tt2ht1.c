#include	<stdio.h>

/*
 * tt2ht1.c 
 *   purpose: creates html table from text table  
 *     input: text
 *    output: html table  
 *    errors: no error conditions
 *     usage: text > tt2ht1 > output 
 */

#define BEFOREDATA 1 
#define INCELL 2 
#define BETWEENCELLS 3
#define BETWEENROWS 4 
#define AFTERDATA 5 

int start_table(int state); 
int start_row(int state);
int start_cell(int state);
int end_cell(int state); 
int end_row(int state); 
int end_table(int state); 

   
/*	
	1. Beginning of file: <table><tr>. If not EOF -> 2. If EOF -> 5 
	2. Create cells: <td> text until space, then in between cells -> 3. When encounter \n -> 4. When EOF -> 5
	3. In whitespace: Nothing until text -> 2 
	4. End of row: </tr> -> 2. 
	5. End of table data: </tr> </table> 
*/

int main()
{
    int cur; 
    int state=BEFOREDATA;

    while ( (cur = getchar()) != EOF) 
    { 
        if (state == BEFOREDATA) // beginning of table 
        {
			if ((cur != ' ') || (cur !='\t')) { 
				state = start_table(state); 
				putchar(cur); 
			} 
			
        } 
        else if (state == INCELL) { // generating a row 
			if (cur == '\n') { // reached end of row 
				state = end_row(state); 
			} 
			else if ((cur != ' ') && (cur != '\t')) { // print out the contents of a cell! 
				putchar(cur); 
			} 
			else if ((cur == ' ')  || (cur != '\t')) { // reached whitespace 
				state = end_cell(state); 
			} 
			
        } 
        else if (state == BETWEENCELLS) { // what to do while whitespace 
			if ((cur != ' ') && (cur != '\t')) { 
                state = start_cell(state); 
				putchar(cur); 
			} 
        }
		else if (state == BETWEENROWS) { // begin new row 
			if ((cur != ' ') && (cur != '\t')) { 
                state = start_row(state); 
				putchar(cur); 
			} 
        }
    }

	if (state != BEFOREDATA) { 
        state = end_table(state);
    }
    return 0; 
}

int start_table(int state) { 
    printf("<table>"); 
    printf("\n\t"); 
    printf("<tr>\n\t\t<td>");
    return INCELL; 
} 

int start_row(int state) { 
    printf("\n\t<tr>");
    return start_cell(state); 
} 

int start_cell(int state) { 
    printf("\n\t\t<td>");
    return INCELL;
} 

int end_cell(int state) { 
    printf("</td>"); 
    return BETWEENCELLS;
} 

int end_row(int state) { 
    printf("</td>\n\t</tr>"); 
    return BETWEENROWS; 
} 

int end_table(int state) {
    printf("\n<table>\n"); 
    return AFTERDATA; 
}
