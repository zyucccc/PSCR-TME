# TME8

Plus ou moins compatible projet Eclipse CPP, car génère plusieurs executables.

Compatible autoconf/automake, exécuter cette séquence d'opérations
après le clone :

```
autoreconf -vfi
./configure 
make
```

Les fois suivantes simplement invoquer "make".

En principe sous eclipse en clic droit sur le projet on a l'option de réinvoquer autotools, et de lancer configure et make.