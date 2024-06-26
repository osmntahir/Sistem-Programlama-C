#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./Libfdr/include/fields.h"
#include "./Libfdr/include/jrb.h"
#include "./Libfdr/include/jval.h"

#define MAX_ARGUMENTS 50

// Çift yönlü bağlı list düğüm yapısı
typedef struct DllNode {
    char data; // Veri
    struct DllNode *prev; // Önceki düğüm
    struct DllNode *next; // Sonraki düğüm
} DllNode;

// Çift yönlü bağlı list yapısı
typedef struct {
    DllNode *head; // Başlangıç düğümü
    DllNode *tail; // Son düğüm
    int size; // Liste boyutu
} Dllist;

// Yeni bir çift yönlü bağlı liste oluşturma
Dllist *create_dllist() {
    Dllist *list = (Dllist *)malloc(sizeof(Dllist));
    if (list == NULL) {
        fprintf(stderr, "Bellek tahsisi yapilamadi.\n");
        exit(EXIT_FAILURE);
    }
    DllNode *head = (DllNode *)malloc(sizeof(DllNode));
    if (head == NULL) {
        fprintf(stderr, "Bellek tahsisi yapilamadi.\n");
        exit(EXIT_FAILURE);
    }
    DllNode *HeadPrev = (DllNode *)malloc(sizeof(DllNode));
    if (HeadPrev == NULL) {
        fprintf(stderr, "Bellek tahsisi yapilamadi.\n");
        exit(EXIT_FAILURE);
    }

    list->head = head;
    list->head->prev = HeadPrev;
    list->tail = NULL;
    list->size = 0;
    return list;
}

// Çift yönlü bağlı listeden düğüm silme
void dllist_remove_node(Dllist *list, DllNode *node) {
    if (node == NULL || list->head == NULL) return;

    if (node->prev != NULL) {
        node->prev->next = node->next;
    } else {
        list->head = node->next;
    }

    if (node->next != NULL) {
        node->next->prev = node->prev;
    } else {
        list->tail = node->prev;
    }

    free(node);
    list->size--;
}

// Bütün çift yönlü bağlı list düğümlerini silme
void clear_dllist(Dllist *list) {
    DllNode *current = list->head;
    while (current != NULL) {
        DllNode *next = current->next;
        free(current);
        current = next;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}
void dllist_insert(Dllist *list, DllNode *cursorNODE, char data) {
    // Yeni bir düğüm oluştur
    DllNode *newNode = (DllNode *)malloc(sizeof(DllNode));
    if (newNode == NULL) {
        fprintf(stderr, "Bellek tahsisi yapilamadi.\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;

    if (list->head == NULL) {
        // Liste boşsa, yeni düğümü başlangıç düğümü olarak ayarla
        list->head = newNode;
        list->tail = newNode;
    } else if (cursorNODE == NULL) {
        // İmleç düğümü boşsa, yeni düğümü listenin sonuna ekle
        list->tail->next = newNode;
        newNode->prev = list->tail;
        list->tail = newNode;
    } else if (cursorNODE->next == NULL) {
        // İmleç düğümü son düğümse, yeni düğümü sonrasına ekle
        cursorNODE->next = newNode;
        newNode->prev = cursorNODE;
        list->tail = newNode;
    } else {
        // İmleç düğümü ortadaysa, yeni düğümü araya ekleyin
        newNode->next = cursorNODE->next;
        newNode->prev = cursorNODE;
        cursorNODE->next->prev = newNode;
        cursorNODE->next = newNode;
    }

    // Yeni düğüm eklendiği için liste boyutunu artır
    list->size++;
}



DllNode *cursorNode = NULL; // İmleç düğümü
// Yaz fonksiyonu
void yaz(char *args[], Dllist *list, int arg_count) {
    for (int i = 0; i < arg_count; i += 2) { // Her iki argüman için
        int count = atoi(args[i]); // Sayıyı al
        char *ch = args[i + 1]; // Karakter dizisini al

        for (int m = 0; m < count; m++) {
            char *ptr = ch; // Karakter dizisinin başlangıç adresini sakla
            while (*ptr) { // Karakter dizisinin sonuna kadar git
                if (*ptr == '\\') {
                    ptr++; // '\\' karakterinden sonraki karaktere geç
                    if (*ptr == 'b') {
                        dllist_insert(list, cursorNode, ' '); // '\b' karakterini liste
                    } else if (*ptr == 'n') {
                        dllist_insert(list, cursorNode, '\n'); // '\n' karakterini liste
                    } else if (*ptr == 't') {
                        dllist_insert(list, cursorNode, '\t'); // '\t' karakterini liste
                    } else {
                        dllist_insert(list, cursorNode, '\\'); // '\\' karakterini liste
                    }
                } else {
                    dllist_insert(list, cursorNode, *ptr); // Karakteri liste
                }
                ptr++; // Bir sonraki karaktere geç
            }
            // Cursor düğümünü bir sonrakine geçir
            if (cursorNode != NULL && cursorNode->next != NULL) {
                cursorNode = cursorNode->next;
            }
        }
    }
}
void sil(char *args[], Dllist *list, int arg_count) {
    for (int i = 0; i < arg_count; i += 2) { // Her iki argüman için
        int count = atoi(args[i]); // Sayıyı al
        char searchChar = args[i + 1][0]; // Karakteri al

        DllNode *current = list->tail;
        while (current != NULL && count > 0) {
            if (current->data == searchChar) { // Aranan karakter bulundu mu?
                DllNode *temp = current;
                current = current->prev; // Bir önceki düğüme geç
                dllist_remove_node(list, temp); // Düğümü listeden çıkar
                count--; // Bir karakter silindi
            } else {
                current = current->prev; // Bir önceki düğüme geç
            }
            cursorNode = current; // İmleci güncelle
           
        }
        if (count > 0)
        {
            cursorNode = list->head;
        }
        
    }
}
void dosyaya_yaz(Dllist *list, FILE *outputFile) {
    if (outputFile == NULL) {
        fprintf(stderr, "Dosya isaretcisi gecerli degil.\n");
        return; // Dosya işaretçisi geçerli değilse işlem yapmayı durdur
    }

    printf("\n -- Dosyaya yaziliyor... \n");
    
    DllNode *current = list->head;
    while (current != NULL) { // Liste üzerinde gezin
        if(current->data != '\0')
       fprintf(outputFile, "%c", current->data); // Karakteri dosyaya yaz
        current = current->next; // Bir sonraki düğüme geç
    }

    fflush(outputFile); // Dosyayı boşalt ve kapat
}

// Sonagit fonksiyonu
void sonagit(Dllist *list) {
    cursorNode = list->tail; // İmleci son düğüme taşı
   
}

// Dur fonksiyonu
void dur() {
    printf("\n -- Program sonlandirildi. \n");
    exit(EXIT_SUCCESS); // Programı sonlandır
}

int main() {
    
    FILE *outputFile = fopen("cikis.dat", "w+");
    if (outputFile == NULL) {
        fprintf(stderr, "Cikis dosyasi acilirken bir hata olustu.\n");
        exit(EXIT_FAILURE);
    }

    Dllist *list = create_dllist(); // Yeni bir çift yönlü bağlı liste oluştur
    cursorNode = list->head; // İmleci başlangıç düğümüne taşı
    IS is = new_inputstruct("giris.dat");
    if (is == NULL) {
        fprintf(stderr, "Giris dosyasi acilirken bir hata olustu.\n");
        exit(EXIT_FAILURE);
    }
   
    // İşlem giriş dosyasından komutları okuma ve işleme
    while (get_line(is) >= 0) {
        char *command = is->fields[0];
        char *args[MAX_ARGUMENTS];
        int arg_count = is->NF - 1; // Komutun ardından gelen argüman sayısı

        // Komutun ardından gelen argümanları args dizisine kopyala
        for (int i = 0; i < arg_count; i++) {
            args[i] = is->fields[i + 1];
        }
        
        // Komutlara göre işlemleri yap
        if (strcmp(command, "yaz:") == 0) {
            yaz(args, list, arg_count);
        } else if (strcmp(command, "sil:") == 0) {
            sil(args, list, arg_count);
        } else if (strcmp(command, "sonagit:") == 0) {
            sonagit(list);
        } else if (strcmp(command, "dur:") == 0) {
             dosyaya_yaz(list, outputFile); // Çift yönlü bağlı listeyi dosyaya yaz
            dur();
        } else if (strcmp(command, "") == 0) {
            continue;
        } else {
            fprintf(stderr, "Hatali komut: %s\n", command);
        }
    }
   
    jettison_inputstruct(is);
    fclose(outputFile);
    clear_dllist(list); // Bağlı listeyi temizle
    free(list); // Liste yapısını serbest bırak

    return 0;
}
