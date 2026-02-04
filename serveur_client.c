#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "192.168.2.67"
#define PORT 8888

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char *message = "Donnees de la Ruche Fille en C";
    char buffer[1024] = {0};

    // 1. Création de la socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Erreur de création de la socket \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convertir l'adresse IP en format binaire
    if (inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr) <= 0) {
        printf("\n Adresse invalide ou non supportée \n");
        return -1;
    }

    // 2. Connexion au serveur
    printf("Tentative de connexion à la Mère (%s:%d)...\n", SERVER_IP, PORT);
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\n Connexion échouée. Vérifiez que le serveur est lancé.\n");
        return -1;
    }

    // 3. Envoi du message
    send(sock, message, strlen(message), 0);
    printf("Message envoyé : %s\n", message);

    // 4. Lecture de la réponse
    read(sock, buffer, 1024);
    printf("Réponse de la Mère : %s\n", buffer);

    // 5. Fermeture
    close(sock);
    return 0;
}
