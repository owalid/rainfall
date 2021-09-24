On peu voir dans le source que le user lit le fichier `/home/user/end/.pass`.
Si il a les bons droit la variable nommer `ret_open` est different de 0.

On rentre alors dans le deuxieme if qui lit et copie 66 charactere du fichier dans argv[0], il met alors un \0 au caractere numero atoi(argv[1]) de la string.

le deuxieme fread met les 65 autres caractere du fichier dans la variable rest.

il compare ensuite argv[0] et argv[1] si ils sont different il execute un shell.

Ici si on lui passe (argv[1]) une string vide. argv[0] sera alors egal a une string vide. En etudiant le strcmp il comparera alors "" et "" ce qui nous ferra entrer dans le else. Donc executer un shell.

commande: `./bonus3 ""`

