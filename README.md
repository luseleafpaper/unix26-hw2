# Part 1 

The three commands I picked here: 

* ps - reports a snapshot of current processes 
* arp - manipulates or displays the kernal's IPv4 network neighborhood cache. 
* lsmod - reformats the contents of /proc/modules, showing what kernel modules are currently loaded 

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

The only way to enter the attribute or noprocess block is from the default process block. 

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
if delim, parse and store delim

When splitting strings, split columns on any number of consecutive spaces, 
but split single-char delimited text on each delimiter. 

I wrote an extra method (not used) that would look for the delimiter within multiple OS style quotes. I'm not sure why I did other than I noticed that the assignment quotes were always different from my computer's, and had the assignment been to parse value=';' instead of value=;, I would need to handle those quotes. If I had to use this in production, I might provide a list of valid quotes from various OS's. Right now, it just expect some type of quote after the equal sign. 

I also did my best to implement some buffer overflow methods, for when cell data and row count is greater than the space allocated. 

# Commands to test scripts on the command line

cc -fno-stack-protector tt2ht1.c -o tt2ht1 -Wall
who | ./tt2ht1
ps | ./tt2ht1
arp | ./tt2ht1
lsmod | ./tt2ht1  
perl part3b.cgi 

cc -fno-stack-protector tt2ht2.c -o tt2ht2 -Wall
perl part4b.cgi

cc -fno-stack-protector tt2ht3.c -o tt2ht3 -Wall
perl part5b.cgi

