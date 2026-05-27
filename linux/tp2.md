# TP2 : Accès à la LED

L'objectif de ce TP est de se familiariser avec l'accès à des registres depuis Linux. D'abord en mode utilisateur, puis en mode noyau.

## Code User space

Une seule LED est directement connectée au HPS. Elle possède son propre driver, disponible dans le dossier suivant : 

```
/sys/class/leds/hps_led0
```

### Accès à la LED à l'aide de son driver

On peut allumer la LED grâce à la ligne suivante :
```bash
echo "1" > /sys/class/leds/hps_led0/brightness
```

1. Écrivez un code C permettant d'ouvrir le fichier ```/sys/class/leds/hps_led0/brightness``` et d'utiliser la fonction ```write()``` pour faire clignoter la LED.

### Accès à la LED par son adresse

Dans cette partie, vous allez écrire un code C permettant de faire clignoter la LED en remappant la mémoire avec ```mmap()```.

Vous devrez trouver l'adresse du GPIO sur lequel la LED est branchée. 
1. Commencez par chercher dans le device-tree : 

```
linux-socfpga/arch/arm/boot/dts/intel/socfpga/socfpga_cyclone5_de0_nano_soc.dts
```

2. Quel est le nom du port sur lequel la LED est branchée ?

3. Vous ne connaissez pas la synthaxe d'un fichier ```.dts```, mais vous pouvez deviner sur quel pin de ce port la led est branché. Quelle est votre proposition ?

4. Les adresse des ports sont définies dans un autre device-tree :

```
linux-socfpga/arch/arm/boot/dts/intel/socfpga/socfpga.dtsi
```

Comment le fichier ```socfpga.dtsi``` est-il inclu dans ```socfpga_cyclone5_de0_nano_soc.dts``` ?

5. Quelle est l'adresse du port utilisée par la LED ?

6. Écrivez un code C permettant de faire clignoter la LED en remappant la mémoire avec ```mmap()```.

7. Testez, montrez à l'enseignant.

## Module

Pour pouvoir crosscompiler le module, dans le dossier ```emb``` :

```bash
export CROSS_COMPILE=$PWD/arm-gnu-toolchain-15.2.rel1-x86_64-arm-none-linux-gnueabihf/bin/arm-none-linux-gnueabihf-
export ARCH=arm
```

### Test de la chaine de compilation

Vous allez commencer par reprendre l'exemple du module simple vu en cours.

1. Modifiez le fichier ```Makefile``` pour utiliser les sources du noyau ```linux-socfpga```. Il faudra y ajouter la ligne suivante : 

```Makefile
CFLAGS_MODULE=-fno-pic
```

2. Compilez le module

3. Copiez le fichier ```.ko``` sur la carte

4. Testez.

### Accès à la LED

1. Modifiez le code du module précédent pour allumer la LED au chargement du module,

2. Et l'éteindre au déchargement du module.

Vous aurez besoin d'utiliser la fonction suivante :

```C
void *ioremap(unsigned long phys_addr, unsigned long size);
```

3. Quels includes sont nécessaires pour la fonction ```ioremap``` ?

4. Testez, montrez à l'enseignant.

### Ajout d'un timer

1. Ajoutez un timer software pour faire clignoter la LED à intervalle régulier.

> **Attention** certaines fonctions présentées en cours sont obsolètes. Faites vos propres recherches.

2. Pensez à supprimer le timer au déchargement du module, sinon vous risqueriez de faire planter le noyau. 
Si ça c'est produit, redémarrez simplement la carte.

3. Testez, montrez à l'enseignant.

### Modification de la période

1. Avec les fonctions de procfs, ajoutez un fichier permettant de configurer la période de clignotement de la LED.

2. Configurez un paramètre pour permettre à l'utilisateur de choisir le nom du fichier.

3. Programmez la fonction ```write``` permettant à l'utilisateur de de changer la période.
Vous aurez besoin de la fonction ```kstrtol``` pour convertir une chaine de caractères en un entier.

4. Écrivez le code de la fonction ```read``` pour pouvoir relire la période en cours.
Vous pouvez utiliser la fonction ```scnprintf``` pour créer une chaine de caractère à partir d'un entier.

5. Testez, montrez à l'enseignant.