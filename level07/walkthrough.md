# Level 07

- Dans le code un faille est visible quand on essaye met des argument trop long:
```
strcpy(i1->name, argv[1]);
printf("addr: %p\n", i2->name);
strcpy(i2->name, argv[2]);
# on rajoute un printf dans le code et on compile
```
- en le lancant on voit que le premiere argument overwrite l'addresse de i2->name se qui fait qu'on peut ecrire n'importe ou dans la memoire
```
./a.out AAAABBBBCCCCDDDDEEEEFFFF 1111122223333
addr: 0x46464646 # ascii for FFFF
Segmentation fault
```
