#include	<stdio.h>
#include 	<string.h>

/*
Methodology: 
Read line by line using fgets() 
if state is noprocess, just print 
if state is attribute, store entire attribute into a row in my array 
if process, then print html tags and insert attribute for that column 
*/ 


/*
Program states: 
1. process block (default). Create html table. If attribute -> 2, if noprocess -> 3
2. in attribute block. Store attributes to attr. if /attribute -> 1
3. in noprocess block. print lines. if /noprocess -> 1

For part4, I'm going to assume properly formatted input, in that there 
won't be a line with multiple tags in it.  
If I encounter an <attributes> inside a noprocess block, I will print it. .
If I encounter a <noprocess> inside an attribute block, I will also print it. 
In other words, the attribute state can only be entered from the default state.
The noprocess state is greedy - this can be invoked from any state. 
*/

#define DELIM ' '
int MAXLINES=300; 
int MAXLEN=300; 
void process(char [], char attr[MAXLINES][MAXLEN] ); 
int get_state(int state, char []); 

int split_line( char orig[], char fields[MAXLINES][MAXLEN] );


void main()
{
	int cur; 
    int oldstate=1; // the state of the program before processing the current line
	int pstate=1; //the state of the program. 
	int tag=0; 

	char attr[MAXLINES][MAXLEN]; 

	char line[MAXLEN]; 
	int attr_index = 0; 

	while( fgets(line, MAXLEN, stdin) ) { 
		/* keep \n and add \0 to end of line */

		oldstate = pstate; 
		pstate = get_state(pstate, line); 

		if (oldstate != pstate) tag = 1; 
        // This means we encountered an html tag that changes the state of the program
        // We want to act on it, but not print or store it. 
		
		if (tag ==1) { 
		//do nothing when the line IS the tag 
		tag = 0;  
		} 
		
        else if (pstate ==2) // store attribute 
        { 
            strcpy(attr[attr_index], line); 
            attr[attr_index][strlen(line)-1] = '\0'; 
            attr_index++; 
        } 
		else if (pstate ==3) // no process
		{
			printf("%s", line); 
		} 
		else //default format table 
		{
			process(line, attr); 
		}
		
	}
} 

int get_state(int curstate, char line[]) 
{
	
	if ((curstate == 1) && (strstr(line, "<attributes>") ))  { 

		return 2; 
	} 
	if ((curstate == 2) && (strstr(line, "</attributes>") )) { 

		return 1; 
	} 
	if (strstr(line, "<noprocess>") ) { 

		return 3; 
	} 
	if (strstr(line, "</noprocess>") ) { 

		return 1; 
	} 
	return curstate; 
}


void process(char line[], char attr[MAXLINES][MAXLEN]) 
/*
Creates the table rows and columns by using split_lines() 
Adds attributes per column from the attributes array 
*/ 
{ 
	char row[MAXLINES][MAXLEN];
	int columns; 
	columns = split_line(line, row); 
	printf("\n\t<tr>"); 
    int i;  
	for (i = 0; i < columns; i++)
	{ 
		printf("\n\t\t<td %s> %s </td>", attr[i], row[i]); 
	} 

	printf("\n\t</tr>\n"); 
} 

int split_line( char line[], char row[MAXLINES][MAXLEN] )
/*
Splits lines of text that needs to be processed on space
Can be in two states: in text, or in white space. 
Stores results into an 2D array 
If in text, write characters to array
If in whitespace, move to the next index in the array to store the next word 
Returns the number of words 
*/
{
	int in_text=0; 
	int column_index = 0; 
	int cell_index =0; 
    int line_index; 
    
	for (line_index=0; line_index < strlen(line)+1; line_index++)
	{
		if ((line[line_index] == ' ') && (in_text ==1)) //hit a space 
		{ 			
			in_text = 0;
			row[column_index][cell_index] = '\0'; 
			cell_index = 0; 
			column_index++; 			
		} 
		else if (line[line_index] == '\0') //reached end of the line 
		{ 
			column_index++; //finished last column 
			row[column_index][cell_index] = line[line_index]; //copy trailing \0	

			return column_index; 
		} 
		else if ((line[line_index] != ' ') && (line[line_index] != '\n') ) //cell contents 
		{
			in_text = 1; 
			row[column_index][cell_index] = line[line_index]; 
			cell_index++; 
		}
	}


}


