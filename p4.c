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

#define DELIM ' '
int MAXLINES=300; 
int MAXLEN=300; 
void process(char [], char attr[MAXLINES][MAXLEN] ); 
int get_state(int state, char []); 

int split_line( char orig[], char fields[MAXLINES][MAXLEN] );


void main()
{
	int cur; 
    int oldstate=1; // the state of the cursor when processing text
	int pstate=1; //the state of the program
	int tag=0; 

	char attr[MAXLINES][MAXLEN]; 

	char line[MAXLEN]; 
	int attr_index = 0; 

	while( fgets(line, MAXLEN, stdin) ) { 
		/* keep \n and add \0 to end of line */

		oldstate = pstate; 
		pstate = get_state(pstate, line); 

		if (oldstate != pstate) tag = 1; 
		
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
{ 
	char row[MAXLINES][MAXLEN];
	int columns; 
	columns = split_line(line, row); 
	printf("\n\t<tr>"); 
	for (int i = 0; i < columns; i++)
	{ 
		printf("\n\t\t<td %s> %s </td>", attr[i], row[i]); 
	} 

	printf("\n\t</tr>\n"); 
} 

int
split_line( char line[], char row[MAXLINES][MAXLEN] )
/*

*/
{
	int in_text=0; 
	int column_index = 0; 
	int cell_index =0; 

	for (int line_index=0; line_index < strlen(line)+1; line_index++)
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


