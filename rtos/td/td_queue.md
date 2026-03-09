t1: alive
t1: created Queue
t1: S msg00
t1: S msg01
t1: S msg02
t1: S msg03

> Le fait d'écrire msg03 dans la queue bloque la tâche 1

t2: alive

> t2 lit dans la queue, vide un slot, ce qui débloque la tâche 1
> t1 re-remplis immédiatement la queue

t1: S msg04

> t1 rebloque

t2: R msg00

> t2 débloque d1
> t1 écrit le dernier message

t1 out
t2: R msg01
t2: R msg02
t2: R msg03
t2: R msg04
