#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct dugum{
    char html_tag[100];
    struct dugum *next;  
};

typedef struct dugum yigin;


yigin *sta = NULL;
void add_to_stack(char tag[100]);
void delete_from_stack();
void print_stack();



int main(){
    yigin *temp = NULL;
    FILE* ptr = fopen("file.html", "r");
    if (ptr == NULL) {
        printf("no such file.");
        return 0;
    }
 
   
    char buf[100];
    int i;
    while (fscanf(ptr, "%s", buf) == 1){
        if(buf[0] == '<' && buf[1] != '/'){
            add_to_stack(buf);
            //print_stack();
        }
        else if (buf[0] == '<' && buf[1] == '/'){
            if(sta != NULL){
                i = 2;
                while(buf[i] != '>'){
                    if(buf[i] != sta -> html_tag[i-1]){
                        goto ben;
                    }
                    i++;
                }           
                delete_from_stack();
                //print_stack();
            }
            else{
                printf("\n Html dosyasindaki açilmayip  tüm taglar kapatilmaddi \n");
                return 0;
            }
            
        }
        ben:
    }

    if ( sta != NULL) {
        printf("\nHtml dosyasindaki açilan tüm taglar kapatilmadi\n");
    }else {
         printf("\nHtml dosyasindaki açilan tüm taglar kapatildi\n");
    }
    return 0;
}


void add_to_stack(char tag[100]){
    yigin *yeni_dugum = (yigin*)malloc(sizeof(yigin));
    strcpy(yeni_dugum -> html_tag, tag);
    if (sta == NULL){
        yeni_dugum -> next = NULL;
    }
    else {
        yeni_dugum -> next = sta;
    }
    sta = yeni_dugum;
}


void delete_from_stack(){
    if (sta != NULL){
        yigin *temp = sta;
        sta = sta -> next;
        free(temp);
    }
}

void print_stack(){
    if (sta != NULL){
        yigin *temp = sta;
        while (temp != NULL){
            printf("%s\t", temp -> html_tag);
            temp = temp -> next;
        }
    }
    else {
        printf("stack bos");
    }
    printf("\n");
}
