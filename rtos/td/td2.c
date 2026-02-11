/* Exercice 1 */
void task1(void * p) {
    for(;;) {
        process1();     // dure 4ms
        vTaskDelay(4);  // Delay 4ms
    }
}

void task2(void * p) {
    for(;;) {
        process2();     // dure 2ms
        vTaskDelay(8);  // Delay 8ms
    }
}

/* Exercice 3 */
SemaphoreHandle_t sem1; // Équivalent à une variable initialiée à ZÉRO
SemaphoreHandle_t sem2;

// priorité >= 3
void taskSync(void * ) {
    // Débloquer tache 1 toutes les 8ms
    // Débloquer tache 2 toutes les 10ms
    // xSemaphoreGive(sem1) toutes les 8ms
    // xSemaphoreGive(sem2) toutes les 10ms
    int i = 0;
    for(;;)
    {
        if (i % 8 == 0) // On rentre dans le if tous les multiples de 8
        {
            xSemaphoreGive(sem1);
        }
        if (i % 10 == 0)
        {
            xSemaphoreGive(sem2);
        }

        i++;
        vTaskDelay(1);
    }
}

// priorité 1
void task1(void * p) {
    for(;;) {
        // Bloquer
        // Débloquer toutes les 8ms
        xSemaphoreTake(sem1, portMAX_DELAY);

        process1();     // dure 4ms
    }
}

// priorité 2
void task2(void * p) {
    for(;;) {
        // Bloquer
        // Débloquer toutes les 10ms
        xSemaphoreTake(sem2, portMAX_DELAY);
        process2();     // dure 2ms

    }
}

/* Exercice 7 */
SemaphoreHandle_t sem1;     // Équivalent à une variable initialiée à ZÉRO
SemaphoreHandle_t sem2;
SemaphoreHandle_t mutex;    // Par défaut, initialisé à UN

// priorité >= 3
void taskSync(void * ) {
    // Débloquer tache 1 toutes les 8ms
    // Débloquer tache 2 toutes les 10ms
    // xSemaphoreGive(sem1) toutes les 8ms
    // xSemaphoreGive(sem2) toutes les 10ms
    int i = 0;
    for(;;)
    {
        if (i % 8 == 0) // On rentre dans le if tous les multiples de 8
        {
            xSemaphoreGive(sem1);
        }
        if (i % 10 == 0)
        {
            xSemaphoreGive(sem2);
        }

        i++;
        vTaskDelay(1);
    }
}

// priorité 1
void task1(void * p) {
    for(;;) {
        // Bloquer
        // Débloquer toutes les 8ms
        xSemaphoreTake(sem1, portMAX_DELAY);

        xSemaphoreTake(mutex, portMAX_DELAY);
        process1();     // dure 4ms
        xSemaphoreGive(mutex)
    }
}

// priorité 2
void task2(void * p) {
    for(;;) {
        // Bloquer
        // Débloquer toutes les 10ms
        xSemaphoreTake(sem2, portMAX_DELAY);

        xSemaphoreTake(mutex, portMAX_DELAY);
        process2();     // dure 2ms
        xSemaphoreGive(mutex)
    }
}
