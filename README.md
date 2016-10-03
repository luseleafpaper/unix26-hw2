# Part 1 

The three commands I picked here: 

* netstat - shows network routes, interfaces, and connections 
* df - shows disk usage 
* free - shows memory usage 

#Part 2 

My manual html is in who.html, which uses whostyle.css. 

#Part 3 

The relevant files for part 3 are: 

* part3b.cgi - this file gets output from various unix commands, as well as the output from trainsched, and passes it to tt2ht1 for html conversion. 
* tt2ht1.c - this program creates an html table from a text table. 
* tt2ht1 - the compiled command 

#Part 4 

The relevant files for part 3 are: 

* part4b.cgi - This file combines part4b.top and who.output as inputs for the table converter. 
* part4b.top - This text file contains some XML tags that the table converter uses. 
* tt2ht2.c - this program is the table converter. It creates an html table from a text table, and can be configured using tags in the xml 
* tt2ht2 - the compiled command 

Methodology: 
Read line by line using fgets() 
if state is noprocess, just print 
if state is attribute, store entire attribute into a row in a 2D array 
if process, then print html tags and insert attribute for that column 

Here's what I decided to with the nested attribute or noprocess tags. If there is EVER a noprocess tag, I never process the text in that block. In other words, if there is an attributes tag inside a noprocess block, I will print it. 

This means that a true attribute block can only be access from outside a noprocess state. 

#Part 5

The relevant files for part 3 are: 

* part5b.cgi - This file combines part4b.top and who.output as inputs for the table converter. 
* tt2ht3.c - this program is the table converter. It creates an html table from a text table, and can be configured using tags in the xml. It'll also check for a delimiter tag in the xml. 
* tt2ht3 - the compiled command 

Methodology: 
Create a 2D array of strings for attributes 
read line by line using fgets() 
if noprocess, just print 
if attribute, store entire attribute into a row in my array 
if process, then do exactly what the previous code did 
if delim, store delim

When splitting strings, split columns on any number of consecutive spaces, 
but split single-char delimited text on each delimiter. 

Something that I realized was that if the delim tag appears after the text table, only subsequent text tables will use that delimiter. I can change that behavior by reading in the entire document before splitting lines.  

Also, I did not have enough time to implement protection for overflow. If I were to do so, I would break any text-copying activity as soon as the number of characters exceeded my max. 


# Commands to test scripts on the command line
/sbin/route | ./tt2ht1
ls -l | ./tt2ht1
./tt2ht1 < /etc/fstab
(cd /home/l/i/lib113/lectures/lect04/5_Code/cgi; ./trainsched 1205) | ./tt2ht1


echo "Content-type: text/html"
echo ""
( cat part4b.top ; cat ~lib113/hw/tt2ht/who.output ) | ./tt2ht2
echo "</table></body></html>"


echo "Content-type: text/html"
echo ""
echo "<html><body><table>"
( echo "<delim value=;/>" ; grep "TR=1205;" sched ) | ./tt2ht3
echo "</table>"


