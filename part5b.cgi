#!/bin/sh
#
# cgi program to test tt2ht3
#
echo "Content-type: text/html"
echo ""
echo "<html><body><table>"
( echo "<delim value=;/>" ; grep "TR=1205;" sched ) | ./tt2ht3
echo "</table></body></html>"

