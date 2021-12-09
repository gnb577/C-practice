code   segment
assume   cs:code, ds:data

   mov   ax, data
   mov   ds, ax

   
   mov   bx, offset buffer   
   mov   ax, [bx]
   mov   si, 1
   mov   cx, 100
L1:
   cmp   al, 'z'
   ja   exit
   cmp   al, 'A'
   jb   exit
   cmp   al, 'Z'
   ja   PRINT

L2:   
   cmp   al, 'z'
   ja   exit
   cmp   al, 'A'
   jb   exit
   cmp   al, 'Z'
   jbe   PRINT2
   

PRINT:   
   
   sub   ax, 'a'-'A' 
   mov   dl, al
   mov   ah, 2   
   int   21h
   
   mov   ax, [bx+si]
   inc   si
   
   loop   L1

PRINT2:
   mov   dl, al
   mov   ah, 2
   int   21h   
   
   
   mov   ax, [bx+si]
   inc   si 
   
   loop   L1
exit:
   mov   ah, 4ch
   int   21h
code   ends


data   segment
buffer   db   'fdasfasdfasdfdasfasdfd'
data   ends
   end