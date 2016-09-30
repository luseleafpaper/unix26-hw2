#include	<stdio.h>

/*





*/


/*
Methodology: 
array of strings for attributes 
read linput line by line using fgets() 
if noprocess, just print 
if attribute, store entire attribute into a row in my array 
if process, then do exactly what the previous code did 
*/ 


/*	
	1. Beginning of file: <table><tr>. If not EOF -> 2. If EOF -> 5 
	2. Create cells: <td> text until space, then </td>. -> 6 When encounter \n -> 4. When EOF -> 5
	3. In whitespace: Nothing until text -> 3 
	4. End of row: </tr> -> 2. 
	5. End of file: </tr> </table> 
*/

int process(int cur, int state); 

void main()
{
	int cur; 
    int state=1;
	while ( (cur = getchar()) != EOF) 
    {
		state = process(cur, state) ; 
	} 
	
} 



int process(int cur, int state)  
{
    if (state == 1) // beginning of table 
    {
		printf("<table>"); 
		if (cur != ' ') { 
			state = 2; 
			printf("\n\t"); 
			printf("<tr>\n\t\t<td>"); 
			putchar(cur); 
		} 
		
    } 
    else if (state == 2) // generating a row 
    { 
        
		if (cur == '\n') { // reached end of row 
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
			state = 2; 
			printf("\n\t"); 
			printf("<tr>\n\t\t<td>"); 
			putchar(cur); 
		} 
    }
    else {
		state =5 ;
		printf("\n");
		printf("</table>")  ;
	} 

	return state ;

}

