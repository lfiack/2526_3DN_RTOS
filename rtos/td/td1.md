# RTDS TD1

tache 0, j = 0, x = 1

Creation de la tache 0

tache 1, j = 0, x = 2

Creation de la tache 1

tache 2, j = 0, x = 3

Creation de la tache 2

tache 3, j = 0, x = 4

Creation de la tache 3

> Dans init, la ligne ```vTaskDelete(NULL);``` détruit la tâche en cours (init)
> Toutes les tâches sont bloquées

tache 3, j = 1, x = 5

tache 2, j = 1, x = 6

tache 1, j = 1, x = 7

tache 0, j = 1, x = 8

2. codeTache n'est pas réentrante, car x est global
