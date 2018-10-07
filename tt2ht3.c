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
|         |                       |               |
| Init    |                       |  No process   |
+--------++                       |  (print!)     |
         |                        |               |
         |         +-noprocess---->               |
         |         |              +---+-----------+
         |         |                  |
      +--v---------+---+              |
      |                |              |
      |  Process       <--/noprocess--+
      |  table text    |
      |  (similar      |
      |  last FSM)     |
      |                |
      +-+-^--------+-^-+            +-----------------+
        | |        | |              |                 |
        | |        | +--/delim------+                 |
        | |        |                |  Get delimiter  |
        | |        |                |                 |
        | |        +-----delim------>                 |
        | |                         +-----------------+
        | |
        | |                +----------------+
        | |                |                |
        | +--+/attributes--+  Store         |
        |                  |  attributes    |
        |                  |  (build attr   |
        +-----+attributes-->  array)        |
                           |                |
                           +----------------+

*/

#define START 1 
#define PROCESS 2 
#define NOPROCESS 3 
#define ATTRIBUTE 4 
#define SETDELIM 5 

int MAXLINES=300; 
int MAXLEN=300; 

int check_line_state(int prevstate, char line[MAXLEN]); 
int split_line(char line[MAXLEN], char splot_line[MAXLINES][MAXLEN], int delim); 
int process_line(char line[MAXLEN], char attr[MAXLINES][MAXLEN], int delim); 
int store_attr(int attr_index, char attr[MAXLINES][MAXLEN], char line[MAXLEN]); 
int get_delim(char line[MAXLEN]);

/*
main() 

Stores attributes, an array of strings 
Stores the current line, a string 
Stores the number of attributes 
Sets the delim if found, otherwise use space or tab

Manages the transitions between the PROCESS, NOPROCESS, and ATTRIBUTE states
It calls check_line_state() after each line to look for state change tags 
Here's what we do in each state: 
NOPROCESS: print out the line as is 
ATTRIBUTE: As soon as we enter this state, each new line goes into the attr array
PROCESS: Send line by line of table text into process_line() to form rows and cells with attrs 
GETDELIM: Parses out the delim character from the delim tag 
*/ 
int main()
{
	char attr[MAXLINES][MAXLEN]; 
	//char table_lines[MAXLINES][MAXLEN]; 
	char line[MAXLEN]; 
	int attr_index = 0; 

    int state = START; 
    int prevstate = START; 
    int delim = ' '; 
    
	while( fgets(line, MAXLEN, stdin) ) { 
		/* keep \n and add \0 to end of line */

        prevstate = state; 
		state = check_line_state(prevstate, line); 
        
        if (state==SETDELIM) { 
            delim = get_delim(line); 
            state=PROCESS; 
        }
        else if (state!=prevstate) { 
            // do nothing! this is the state change line! 
        } 
        else if (state==NOPROCESS) {
            printf("%s", line); 
        } 
        else if (state==ATTRIBUTE) { 
            attr_index = store_attr(attr_index, attr, line); 
        } 
        else if (state==PROCESS) { 
            process_line(line, attr, delim); 
        } 
        else {
            return -1; //something went wrong?
        }
	}
    return 0;
} 


/*
store_attr()
Takes the current attr_index, the attr table, and text line
Stores the text as the next attr, increments the attr_index
returns the attr_index
*/
int store_attr(int attr_index, char attr[MAXLINES][MAXLEN], char line[MAXLEN]) 
{
    strncpy(attr[attr_index], line, MAXLEN); 
    attr[attr_index][strlen(attr[attr_index])-1] = '\0';
    attr_index++; 
    return attr_index; 
}


/*
check_line_state()
Takes the incoming line, checks if it is a line that can change the FSM state 
If so, return the new state.
Returns -1 if something goes wrong
*/
int check_line_state(int prevstate, char line[]) 
{
	
    if ((prevstate == START) || (prevstate == PROCESS))  { 
        if (strstr(line, "<noprocess>")) return NOPROCESS; 
        if (strstr(line, "<attributes>")) return ATTRIBUTE; 
        if (strstr(line, "<delim")) {
            return SETDELIM;
        } 
        return PROCESS; 
    } 
    if (prevstate == ATTRIBUTE)  { 
        if (strstr(line, "</attributes>")) return PROCESS; 
        return prevstate; // else do this by defaut  
    }
    if (prevstate == NOPROCESS)  { 
        if (strstr(line, "</noprocess>")) return PROCESS; 
        return prevstate; // else do this by defaut  
    }
    return -1; // something went wrong! 
    
}


/*
Creates the table rows and columns by using split_lines() 
Adds attributes per column from the attributes array 
*/ 
int process_line(char line[MAXLEN], char attr[MAXLINES][MAXLEN], int delim) 
{ 
	char row[MAXLINES][MAXLEN];
	int columns; 
	columns = split_line(line, row, delim); 
	printf("\t<tr>"); 
    int i;  
	for (i = 0; i < columns; i++)
	{ 
		printf("\n\t\t<td %s> %s </td>", attr[i], row[i]); 
	} 

	printf("\n\t</tr>\n"); 
    return 0;
} 


/*
Splits lines of text that needs to be processed on space
Can be in two states: in text, or in white space. 
Stores results into an 2D array 
If in text, write characters to array
If in whitespace, move to the next index in the array to store the next word 
Returns the number of words 
*/
int split_line( char line[MAXLEN], char splot_line[MAXLINES][MAXLEN], int delim )
{
	int in_text=0; 
	int column_index = 0; 
	int cell_index =0; 
    int line_index; 
    int this_char='\0'; 
    
	for (line_index=0; line_index < strlen(line); line_index++)
	{
        this_char = line[line_index];  
        // try to handle buffer overflow of cells
        if (cell_index > MAXLEN - 1) {
            splot_line[column_index][cell_index] = '\0';
            column_index++; // move onto the next column 
        } 
        // and overflow of the array as a whole 
        else if (column_index > MAXLINES -1) {
            return column_index; // we are going to run out of space 
        } 
		else if ((this_char == delim) && (in_text ==1)) //hit whitespace
		{ 			
			in_text = 0;
			splot_line[column_index][cell_index] = '\0'; 
			cell_index = 0; 
			column_index++; 			
		} 
		else if ((this_char == '\n') || (this_char == '\0')) //reached end of the line 
		{ 
			splot_line[column_index][cell_index] = '\0'; //copy trailing \0	
			column_index++; //finished last column 
			return column_index; 
		} 
		else if ((this_char != delim) && (this_char != '\n') ) //cell contents 
		{
			in_text = 1; 
			splot_line[column_index][cell_index] = this_char; 
			cell_index++; 
		}
	}
    return column_index; 
}


/*
get_delim()
Parses the line looking for the delim value. 
If it can find enough characters to be a valid delim tag,
then return that delim character. 
Otherwise, return space, the default delim.
*/
int get_delim(char line[MAXLEN]) 
{
    int value = ' ';
    char *afterequal;

    afterequal = strchr(line, '=');

    if (strlen(afterequal) > 3) { // make sure it's a valid tag length! 
        afterequal++;
        value = afterequal[0];
        
        return value;
    }
    else { 
        return ' '; //didn't find a suitable delimiter 
    }
}


/* 
I wrote this method to handle quoted delimiters. 
Why? I always get tripped up with different OS quotes. 
This will store the quote ascii character, 
look for the char between them, check that it's just one char, 
and then return that as the delimiter 
*/
int get_quoted_delim(char line[MAXLEN]) 
{
    int value = ' ';
    char *afterequal;
    char *after1stquote;
    char *after2ndquote;
    int quote = '\'';
    int delim_len = 1;

    afterequal = strchr(line, '=');
    quote = afterequal[1];
    printf("quote is :%c", quote); 
    after1stquote = strchr(afterequal, quote);
    printf("\nstring is: %s",after1stquote);

    if (strlen(after1stquote) > 2) {
        after1stquote++;
        value = after1stquote[0];
        after2ndquote = strchr(after1stquote, quote);
        delim_len = strlen(after1stquote) - strlen(after2ndquote);
        
        if (delim_len == 1) {
            printf("\n Found delim! %c", value);
            return value;
        } 
    }
    return ' '; //didn't find a suitable delimiter 
}
