#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct n
{
    char *x;
    int adet;
    struct n * sonraki;
} node;

node* ilkEleman = NULL;
node* iter = NULL;
node* sonEleman = NULL;
char* kelime = NULL;

void kelimeBul(FILE *dosya)
{
    fscanf(dosya,"%s",kelime);
    iter = ilkEleman;
    while(iter!=NULL)
    {
        if(strcmp(kelime,iter->x)==0 && !feof(dosya))
        {
            fscanf(dosya,"%s",kelime);
            iter = ilkEleman;
            continue;
        }
        iter = iter->sonraki;
    }
}

int kelimeSay(FILE *dosya,int say)
{
    char *tut = (char*)malloc(100*sizeof(char));
    while(!feof(dosya))
    {
        fscanf(dosya,"%s",tut);
        //upperToLower(tut);
        if((strcmp(kelime,tut)) == 0)
            say++;
    }
    return say;
}

void basaEkle(int say)
{
    node* ekle=(node*)malloc(sizeof(node));
    ekle->x = (char *)malloc(100*sizeof(char));

    strcpy(ekle->x,kelime);
    ekle->adet = say;
    ekle->sonraki = ilkEleman;
    ilkEleman = ekle;

    if(ilkEleman->sonraki == NULL)
        sonEleman = ilkEleman;
}

void sonaEkle(int say)
{
    node* ekle=(node*)malloc(sizeof(node));
    ekle->x = (char *)malloc(100*sizeof(char));

    strcpy(ekle->x,kelime);
    ekle->adet = say;
    ekle->sonraki = NULL;

    iter = sonEleman;
    iter->sonraki = ekle;
    sonEleman = iter->sonraki;
}

void arayaEkle(int say)
{
    node*ekle=(node*)malloc(sizeof(node));
    ekle->x = (char *)malloc(100*sizeof(char));

    strcpy(ekle->x,kelime);
    ekle->adet = say;

    iter = ilkEleman;
    while(iter->sonraki->adet > say)
        iter = iter->sonraki;

    node* onune;
    onune = iter->sonraki;
    iter->sonraki = ekle;
    ekle->sonraki = onune;
}

void ekle(int *say)
{
    if(ilkEleman==NULL || *say > ilkEleman->adet)
        basaEkle(*say);
    else if(*say <= sonEleman ->adet)
        sonaEkle(*say);
    else
        arayaEkle(*say);

    *say=1;
}

void yazdir()
{
    iter = ilkEleman;
    while(iter != NULL)
    {
        printf("%s -> %d\n",iter->x,iter->adet);
        iter = iter->sonraki;
    }
}

int donguKontrol()
{
    iter = ilkEleman;
    while(iter != NULL)
    {
        if(strcmp(kelime,iter->x) == 0)
            return -1;
        iter = iter->sonraki;
    }
    return 0;
}

void upperToLower(char *lower)
{
    for(int i=0;i<=strlen(lower);i++){
        if(*(lower+i)>=65&&*(lower+i)<=90)
            *(lower+i)=*(lower+i)+32;
    }
}

int main()
{
    FILE *dosya;
    kelime = (char*)malloc(100*sizeof(char));
    int say=1,kontrol=1;
    long int dosyaIsaretcisi=0;
    if((dosya=fopen("metin.txt","r"))!= NULL)
    {
        printf("DOSYA BULUNDU\n");
        while(kontrol)
        {
            kelimeBul(dosya);
            //upperToLower(kelime);
            dosyaIsaretcisi = ftell(dosya);
            if(feof(dosya))kontrol=donguKontrol();
            if(kontrol==-1)break;
            say = kelimeSay(dosya,say);
            ekle(&say);
            fseek(dosya,dosyaIsaretcisi,SEEK_SET);
        }
        yazdir();
    }
    fclose(dosya);
    return 0;
}
