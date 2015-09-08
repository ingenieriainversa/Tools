#!/usr/bin/python
 
"""
urlWordsCount.py v0.01
Copyleft - 2014  Javier Dominguez Gomez
Written by Javier Dominguez Gomez <jdg@member.fsf.org>
GnuPG Key: 6ECD1616
Madrid, Spain

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
 
Info:     This Python program list, sort and count all words in a URL. 
 
Usage:    python urlWordsCount.py http://www.gnu.org/
"""
 
import sys, re, string, urllib
# BeautifulSoup package is required.
from bs4 import BeautifulSoup
 
# The first command-line argument.
url = sys.argv[1]
 
# Get text plain from HTML code.
text = BeautifulSoup(urllib.urlopen(url)).get_text()
 
# Replace all ASCII punctuation characters from text to blank spaces, and initialize Array.
wordsArray = re.sub('[%s]' % re.escape(string.punctuation), ' ', text).split()
 
# Process sorted array elements 
n = 0
for i in sorted(set(wordsArray)):
    # Print array element if all characters in the string are alphabetic.
    if (i.isalpha() == True):
        n = n+1
        print n, i
