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

                                  +---------------+
+---------+                       |               |
|         +----noprocess---------->               |
| Init    +----attributes------+  |  No process   |
+--------++                    |  |  (print!)     |
         |                     |  |               |
         |         +-noprocess---->               |
         |         |           |  +---+-----------+
         |         |           |      |
        +v---------+---+       |      |
        |              |       |      |
        |  Process     <--/noprocess--+
        |  table text  |       |
        |  (similar    |       |
        |  last FSM)   |       |
        |              |       |
        +-+-^----------+       |
          | |                  |
          | |              +---v------------+
          | |              |                |
          | +-/attributes--+  Store         |
          |                |  attributes    |
          |                |  (build attr   |
          |                |  array)        |
          +----attributes-->                |
                           +----------------+

For part4, I'm going to assume properly formatted input, in that there 
won't be a line with multiple tags in it.  
If I encounter an <attributes> inside a noprocess block, I will print it. .
If I encounter a <noprocess> inside an attribute block, I will also print it. 
In other words, the attribute state can only be entered from the default state.
The noprocess state is greedy - this can be invoked from any state. 
*/

#define DELIM ' '
#define START 1 
#define PROCESS 2 
#define NOPROCESS 3 
#define ATTRIBUTE 4 
#define END 5 

int MAXLINES=300; 
int MAXLEN=300; 

int check_line_state(char line[MAXLEN]); 
int split_line(char line[MAXLEN], char splot_line[MAXLINES][MAXLEN]); 
int process_line(char line[MAXLEN], attr[MAXLINES][MAXLEN]); 
int store_attr(int attr_index, attr[MAXLINES][MAXLEN]); 

/*
main() 

Stores attributes, an array of strings 
Stores the current line, a string 
Stores the number of attributes 

Manages the transitions between the PROCESS, NOPROCESS, and ATTRIBUTE states
It calls check_line_state() after each line to look for state change tags 
Here's what we do in each state: 
NOPROCESS: print out the line as is 
ATTRIBUTE: As soon as we enter this state, each new line goes into the attr array
PROCESS: Send line by line of table text into process_line() to form rows and cells with attrs 

*/ 
int main()
{
	char attr[MAXLINES][MAXLEN]; 
	char table_lines[MAXLINES][MAXLEN]; 
	char line[MAXLEN]; 
	int attr_index = 0; 

    int state = START; 
    int prevstate = START; 
    
	while( fgets(line, MAXLEN, stdin) ) { 
		/* keep \n and add \0 to end of line */

        prevstate = state; 
		state = check_line_state(prevstate, line); 
        
        if (state==

		
	}
} 

int check_line_state(int curstate, char line[]) 
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


