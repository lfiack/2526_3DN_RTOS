# 3DN TD KiCAD
## Objectifs

Concevoir un projet simple sur KiCAD autour d'un STM32.

Liste des AAV :
1. Lister les composants nécessaires au STM32 pour fonctionner,
2. Concevoir un schéma propre, sans erreurs, lisible et maintenable,
3. Décrire les règles de placement des composants : Connecteurs, HMI, faciliter le routage,
4. Configurer les contraintes du logiciel en fonction des règles du fabricant (DFM pour Design for Manufacturability), 
5. Router un circuit en appliquant un ensemble de règles pour éviter les problèmes de CEM (Compatibilité Électro-Magnétique),
6. Générer les fichiers de fabrication.

## Création du projet

Deux logiciels à utiliser simultanément : 
* STM32CubeMX
* KiCAD

1. Lancez-les. 
2. Créez un dossier de travail qui contiendra les projets des deux logiciels. 
**Attention**, le dossier ne doit contenir ni espaces ni accents. 
2. **Dans STM32CubeMX**, créez un projet pour le MCU **STM32G031K8Tx**. Nommez-le à votre convenance, sans espace, sans accent.
3. Quels éléments sont nécessaires pour faire fonctionner le STM32 ?
4. **Dans KiCAD**, créez un projet. Nommez-le à votre convenance, sans espace, sans accent.
5. Configurez le cartouche.

## Configuration du STM32

De retour dans **STM32CubeMX**.

1. Activez le mode debug. _Lockez_ les pins correspondantes.

> SYS > Serial Wire

2. Repérez la pin reset (```NRST```) et _lockez_-la.
3. Activez l'**USART1**. 
Notez que pour certains périphériques les pins peuvent être déplacées :

> Ctrl + Clic gauche

Nommez les pins ```VCP_RX``` et ```VCP_TX``` respectivement sur ```PB7``` et ```PB6```.

4. Que signifie ```VCP``` ?

C'est tout ce que nous avons besoin pour faire démarrer un STM32. Ajoutons quelques périphériques, pour le sport:

5. Activez les channels **IN0** et **IN1** de l'**ADC1**.
6. Activez le **SPI1**. Pensez à activer le **Hardware NSS**, et expliquez ce que ça signifie.
7. Activez l'**I2C2**.
8. Activez les _channels_ 3 et 4 en mode **PWM Generation** de **TIM3**. Nommez-les LED1 et LED2.
9. Pourquoi utiliser une sortie de _timer_ pour une LED ?
10. Tentez de regrouper les pins au mieux et _lockez_-les.

## Tracé du schéma

Le logiciel dispose de beaucoup raccourcis claviers utiles. Commencez à les apprendre dès maintenant.

1. Ajoutez les composants principaux :
    * ```STM32G031K8Tx```, renommez-le en ```STM32G031K8T6```,
    * ```Conn_ST_STDC14```, choisissez la bonne empreinte,
    * ```MIC5504-3.3YM5```.
2. Quels sont leurs rôles ?
3. Ajoutez les **connecteurs** suivants de la librairie ```Connector_Generic```. Choisissez une empreinte de type ```JST-XH```. Renommez-les.
    * Un connecteur 4 broches pour l'**ADC**,
    * Un connecteur 4 broches pour l'**I2C**,
    * Un connecteur 6 broches pour le **SPI**.
4. Selon la _datasheet_ du ```MIC5504-3.3YM5```, quels composants doit-on ajouter ? Ajoutez-les. Tous les composants passifs seront de taille ```0603```.
5. Même question pour le ```STM32G031K8T6```.
6. En utilisant des _labels_ si nécessaire, connectez le connecteur de la **STLink** au **STM32**.
7. Connectez les **ADC**, l'**I2C** et le **SPI** aux connecteurs correspondants.
8. Pourquoi l'**I2C** a besoin de résistances de _pull-up_ ? Ajoutez-les. Configurez-les en _Do not populate_.
9. Ajoutez une LED témoin sur le ```+3V3``` et les deux LED de _status_ sur les sorties du _timer_.
10. Ajoutez 4 trous de fixation : ```MountingHole_3.2mm_M3_Pad_Via``` et reliez-les à la masse.
11. Indiquez les pins non-utilisées avec le ```No Connect Flag```.
12. Passez un peu de temps à organiser et à documenter votre schéma.
13. Vérifiez et corrigez les erreurs avec le ```Electrical Rules Checker```.

## Configuration de l'outil de routage

Même si ce n'est pas nécessaire dans cet exercice, vous allez concevoir un **PCB 4 couches**.
Les couches internes seront dédiées à la **masse** et aux **alimentations**.

Ce PCB ne sera pas fabriqué, mais ceux du TP le seront, alors prenez les bonnes habitudes.
Les PCB de TP seront fabriqués par la société [JLCPCB](https://jlcpcb.com/).

1. Sur le site de [JLCPCB](https://jlcpcb.com/), notez les capacités du fabricant en terme d'**isolation**, de **largeur de pistes** et de **taille de via**.
2. Reportez ces informations dans KiCAD (_Board Setup_). Configurez le PCB en 4 couches.
3. Pour des raisons de CEM, ce n'est pas toujours une bonne idée d'utiliser les pistes les plus fines possibles.
Ajoutez les _Pre-defined Sizes_ suivantes :
    * ```Track``` ```Width``` : **0.3mm**
    * ```Track``` ```Width``` : **0.4mm**
    * ```Track``` ```Width``` : **0.5mm**
    * ```Vias``` ```Diameter``` : **0.5mm** ; ```Hole``` : **0.3mm**
4. Configurez la ```Net Class``` ```Default``` à **0.3mm** avec les bonnes valeurs de _Clearance_ et de taille de _Via_.
5. Configurez la grille à 1mm. Vous allez passer votre temps à changer la taille de grille, c'est normal.
6. Configurez le cartouche.
7. ```Update PCB from Schematic```. Il ne devrait pas y en avoir d'erreurs, sinon il faudra les corriger dans le schéma.

## Placement des composants

1. Commencez par placer les trous de fixation selon un carré de **40mm** par **40mm**.
2. Tracez les ```Edge Cuts```.
3. Placez le **STM32** au milieu.
4. Placez les connecteurs sur les côtés.
5. Essayez au maximum de réduire les croisements dans le **chevelu** (_ratsnest_ en anglais).
6. Plus vous passerez de temps sur cette étape, moins vous passerez de temps sur le routage. 
N'hésitez pas à multiplier les allez-retours avec le schéma et **STM32CubeMX** pour réduire les croisements.
7. Allez voir la vue 3D.

## Routage

1. Tracez un _Filled Zone_ sur la couche **In1.Cu** connecté au signal ```GND```.
2. Tracez un _Filled Zone_ sur la couche **In2.Cu** connecté au signal ```+3V3```.
3. Sur la même couche **In2.Cu**, tracez un _Fill Zone_ de ```+5V``` pour relier le connecteur à l'entrée du **LDO**.
4. Reliez tous les ```+5V```, ```+3V3``` et ```GND``` aux différents plans à l'aide de vias.
5. Routez le reste des signaux.
6. Ajouter un plan de masse sur les couches **Top** et **Bottom**.
7. Retirez les antennes parasites. Ajoutez des _stitching vias_.
8. Vérifiez qu'il n'y ait pas d'erreurs dans _Design Rule Checker_.

## Finitions

1. Organisez proprement la sérigraphie.
2. Ajoutez toutes les informations qui vous semble nécessaire sur la sérigraphie.
3. Ajoutez un logo.
4. Vérifiez dans la vue 3D.
5. Revérifiez les DRC. On sait jamais.

## Fichiers de fabrication

1. Générez les fichers de fabrication GERBER ainsi que les fichiers de perçage.
2. Faites une simulation de commande sur le site [JLCPCB](https://jlcpcb.com/).
