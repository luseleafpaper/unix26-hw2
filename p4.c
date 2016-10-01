#include	<stdio.h>
#include 	<string.h>

/*
Methodology: 
array of strings for attributes 
read lattr line by line using fgets() 
if noprocess, just print 
if attribute, store entire attribute into a row in my array 
if process, then do exactly what the previous code did 
*/ 


/*
Program states: 
1. process block (default). Create html table. If attribute -> 2, if noprocess -> 3
2. in attribute block. Store attributes to attr. if /attribute -> 1
3. in noprocess block. print lines. if /noprocess -> 1

For part4, I'm going to assume properly formatted input. 
If I encounter an <attributes> inside a noprocess block, I will print it. .
If I encounter a <noprocess> inside an attribute block, I will also print it. 
In other words, the attribute state can only be entered from the default state.
The noprocess state is greedy - this can be invoked from any state. 
*/
int MAXLINES=300; 
int MAXLEN=300; 
int process(int cur, int state); 
void load(char [MAXLINES][MAXLEN]); 
int get_state(int state, char []); 
void main()
{
	int cur; 
    int cstate=1; // the state of the cursor when processing text
	int pstate=1; //the state of the program

	char attr[MAXLINES][MAXLEN]; 

	char line[MAXLEN]; 
	int attr_index = 0 ; 

	strcpy(line, "here is some <attributes> and then some!"); 
	
	if ((pstate == 1) && (strstr(line, "<attributes>") ))  { 
		printf("1. state -> 2"); 
	} 


	while( fgets(line, MAXLEN, stdin) ) { 
		/* keep \n and add \0 to end of line */


		pstate = get_state(pstate, line); 
		printf("%d >>> %s", pstate, line) ; 
		
        if (pstate ==2) // store attribute 
        { 

            strcpy(attr[attr_index], line); 
            attr[attr_index][strlen(line)] = '\0'; 
            attr_index++; 
        } 
		else if (pstate ==3) // no process
		{
			//printf("%s", line); 
		} 
		else //default format table 
		{
			//printf("%s", line); 
		} 
	}
} 

int get_state(int curstate, char line[]) 
{
	
	if ((curstate == 1) && (strstr(line, "<attributes>") ))  { 

		return 2; 
	} 
	if ((curstate == 2) && (line == "</attribute>")) { 

		return 1; 
	} 
	if (strstr(line, "<noprocess>") ) { 

		return 3; 
	} 
	if (strstr(line, "</noprocess>") ) { 

		return 1; 
	} 
	return curstate; 
/*	if ((curstate == 1) && (line == "<noprocess>")){ 
		return 3; 
	} 
	if ((curstate == 3) && (line == "</noprocess>")) { 
		return 1; 
	} 
	*/
}
void load(char attr[MAXLINES][MAXLEN])
{
	
} 

/*	
	1. Beginning of file: <table><tr>. If not EOF -> 2. If EOF -> 5 
	2. Create cells: <td> text until space, then </td>. -> 6 When encounter \n -> 4. When EOF -> 5
	3. In whitespace: Nothing until text -> 3 
	4. End of row: </tr> -> 2. 
	5. End of file: </tr> </table> 
*/
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

