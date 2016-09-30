#include	<stdio.h>

/*
 * tt2ht1.c 
 *   purpose: creates html table from text table  
 *     input: text
 *    output: html table  
 *    errors: no error conditions
 *     usage: text > tt2ht1 > output 
 */

void space(int state); 

int main()
{
   
/*	
	1. Beginning of file: <table><tr>. If not EOF -> 2. If EOF -> 5 
	2. Create cells: <td> text until space, then </td>. -> 6 When encounter \n -> 4. When EOF -> 5
	Whitespace: Nothing until text -> 3 
	4. End of row: </tr> -> 2. 
	5. End of file: </tr> </table> 
*/

    int cur; 
    int state=1;

    while ( (cur = getchar()) != EOF) 
    { 
        if (state == 1) // beginning of table 
        {
			printf("<table>"); 
			state = 4; 
			
        } 
        else if (state == 2) // generating a row 
        { 
            
			if (cur == '\n') { // reached end of row 
				printf("NL");
				printf("</td>\n\t</tr>"); 
				state = 4; 
			} 
			else if (cur != ' ') {
				putchar(cur); 
			} 
			else if (cur == ' ') { // reached whitespace 
				printf("</td>"); 
				state = 3; 
			} 
			
        } 
        else if (state == 3)  // what to do while whitespace 
        {
			if (cur != ' ') { 
				printf("<td>"); 
				putchar(cur); 
				state = 2; 
			} 
        }
		else if (state == 4) // begin new row 
        {
			
			if (cur != ' ') { 
				state = 3; 
				printf("\n\t"); 
				printf("<tr>\n\t\t<td>"); 
				putchar(cur); 
			} 
        }
    }

	state =5 ;
	printf("\n");
	printf("</table>")  ;
}

void space(int state) { 
	if (state == 1) printf("\n"); 
	if (state == 2) printf("\n\t"); 
	if (state == 3) printf("\n\t"); 
	if (state == 6) printf("\n"); 
	if (state == 4) printf("\n\t"); 
	if (state == 5) printf("\n"); 
} 

