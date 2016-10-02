#include	<stdio.h>
#include 	<string.h>

/*
Methodology: 
Create a 2D array of strings for attributes 
read line by line using fgets() 
if noprocess, just print 
if attribute, store entire attribute into a row in my array 
if process, then do exactly what the previous code did 
if delim, store delim

When splitting strings, split columns on any number of consecutive spaces, 
but split single-char delimited text on each delimiter. 
*/ 


/*
Program states: 
1. process block (default). Create html table. If attribute -> 2, if noprocess -> 3
2. in attribute block. Store attributes to attr. if /attribute -> 1
3. in noprocess block. print lines. if /noprocess -> 1
4. in delimiter tag. Store the delimiter into DELIM 
*/
char DELIM =' ';
int MAXLINES=300; 
int MAXLEN=300; 
void process(char [], char attr[MAXLINES][MAXLEN] ); 
int get_state(int state, char []); 
char find_delim(char []); 
int split_line( char orig[], char fields[MAXLINES][MAXLEN], char DELIM );


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
		//printf("\nstate: %d, tag: %d, line: %s", pstate, tag, line); 
		oldstate = pstate; 
		pstate = get_state(pstate, line); 

		if (oldstate != pstate) tag = 1; 

		if (pstate ==4) //standalone tags go before the "do nothing if tag" block
		{
			DELIM = find_delim(line); 
			tag = 0; 
			pstate = oldstate; 
		}
		else if (tag ==1) { 
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

		curstate = 2; 
	} 
	if ((curstate == 2) && (strstr(line, "</attributes>") )) { 

		curstate = 1; 
	} 
	if (strstr(line, "<noprocess>") ) { 

		curstate = 3; 
	} 
	if (strstr(line, "</noprocess>") ) { 

		curstate = 1; 
	} 
	if ((strstr(line, "<delim value=") ))  { 
 		
		curstate = 4; 
	}
	return curstate; 
}

char find_delim(char line[]) 
/* 
In the <delim> tag, the delimiter is a char that follows the equal sign
*/ 
{ 
	int i ; 
	for (i = 0; i<strlen(line); i++)
	{ 
		if (line[i]=='=')
		{ 
			return line[i+1]; 
		} 
	} 
} 
void process(char line[], char attr[MAXLINES][MAXLEN]) 
{ 
	char row[MAXLINES][MAXLEN];
	int columns; 
	columns = split_line(line, row, DELIM); 

	printf("\n\t<tr>"); 
    int i;  
	for (i = 0; i < columns; i++)
	{ 
		printf("\n\t\t<td %s> %s </td>", attr[i], row[i]); 
	} 

	printf("\n\t</tr>\n"); 
} 

int
split_line( char line[], char row[MAXLINES][MAXLEN], char DELIM)
/*
If DELIM is a space, then we have the default space-delimited behavior. 
A block of spaces, no matter how long it is, is treated as one delimiter
If DELIM is not a space, then we have to treat each DELIM as a column separator
*/
{
	int in_text=0; 
	int column_index = 0; 
	int cell_index =0; 
    int line_index; 
    
	for (line_index=0; line_index < strlen(line)+1; line_index++)
	{
		if ((DELIM==' ') && (line[line_index] == ' ') && (in_text ==1)) //hit a space, create a new column 
		{ 			
			in_text = 0;
			row[column_index][cell_index] = '\0'; 
			cell_index = 0; 
			column_index++; 			
		} 
		else if (line[line_index] == DELIM && (in_text ==1)) // hit a delim, create a new cell 
		{ 		
			in_text = 0;
			row[column_index][cell_index] = '\0'; 
			cell_index = 0; 
			column_index++; 			
		}
		else if (line[line_index] == '\0') //reached end of the line 
		{ 
			column_index++; //finished last column 
			row[column_index][cell_index] = line[line_index]; //copy ending \0	

			return column_index; 
		} 
		else if ((line[line_index] != DELIM) && (line[line_index] != '\n') ) 
		//cell contents 
		{
			in_text = 1; 
			row[column_index][cell_index] = line[line_index]; 
			cell_index++; 
		}
		else {} // else do nothing. We are encountering spaces and in_text = 0 
	}


}


