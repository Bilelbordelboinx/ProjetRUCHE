#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    printf("--- Système de surveillance Ruche (GPIO 13) ---\n");
    printf("Lecture en cours...\n\n");

    while (1) {
        // On appelle Python juste pour la lecture du capteur (très fiable)
        // et on récupère le résultat dans notre programme C
        system("python3 -c \"import adafruit_dht; import board; d=adafruit_dht.DHT22(board.D13); print(f'Temp: {d.temperature}C | Hum: {d.humidity}%')\" 2>/dev/null");
        
        // Le DHT22 est lent : on attend 3 secondes
        sleep(3);
    }
    return 0;
}
