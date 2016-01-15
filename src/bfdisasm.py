import sys
import re

from pprint import PrettyPrinter

pp = PrettyPrinter (indent = 2)

debug_chars = {}
with open ('debug.txt', 'r') as d:
    for l in d:
        st = l.split (':')
        if len (st) == 2:
            debug_chars[st[1].strip ()] = st[0].strip ()

pp.pprint (debug_chars)

#sys.exit (0)


with open ('disasm', 'r') as d:
    data = d.read ()
    #print (patt.findall (data))
    for t in debug_chars:
        #data = data.replace ("%s:" % t, "\n%s\n  %s:" % (debug_chars[t], t))
        data = re.sub (r'( +' + t + '+:)',"\n%s\n\\1" % debug_chars[t], data)
    print (data)

    
