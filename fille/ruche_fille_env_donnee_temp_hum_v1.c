#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8888
#define SERVER_IP "192.168.2.67"

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    FILE *fp;

    while(1) {
        // Lecture du DHT22 via Python
        fp = popen("python3 -c \"import adafruit_dht; import board; d=adafruit_dht.DHT22(board.D13); print(f'{d.temperature:.1f},{d.humidity:.1f}')\" 2>/dev/null", "r");
        
        if (fp != NULL && fgets(buffer, sizeof(buffer), fp) != NULL) {
            pclose(fp);

            sock = socket(AF_INET, SOCK_STREAM, 0);
            serv_addr.sin_family = AF_INET;
            serv_addr.sin_port = htons(PORT);
            inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr);

            if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == 0) {
                send(sock, buffer, strlen(buffer), 0);
                printf("Données envoyées à la mère : %s", buffer);
            }
            close(sock);
        } else {
            if(fp) pclose(fp);
            printf("Erreur lecture capteur...\n");
        }
        sleep(10); 
    }
    return 0;
}
