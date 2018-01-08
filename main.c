#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct List{
    char dest[20];//hedef
    char clock[20];//hareket saati
}List;

//fonksiyon tan�mlar�
void mergeSortByCities(List *, int, int);
void mergeSortByClocks(List *, int, int);
void mergeByCities(List *, int, int, int);
void mergeByClocks(List *, int, int, int);
void printArray(List *, int);

int main()
{
    //okunacak dosya i�in pointer ayarland�
    FILE *f=NULL;
    f = fopen("seferler.txt", "r");
    if(!f)
        {
        printf("Dosya acilamadi");
        return -1;
    }

    //seger saatlerini almak i�in ge�ici de�i�kenler
    char city[20];
    char time[5];

    //Sefer listesinde kac tane otob�s bulundu�u okundu
    List *L;
    int numOfLines=0;
    while(!feof(f))
        {
            fscanf(f,"%s",city);
            numOfLines++;
        }
    numOfLines++;
    numOfLines=numOfLines/2;

    //liste i�in yer ayr�ld�
    L=(struct List *)malloc(numOfLines*sizeof(struct List));
    if(!L)
    {
        printf("yer ayrilamad�\n");
        return -1;
    }
    //dosya pointer� ba�a sar�ld�
    rewind(f);

    int i=0;

    //dosyadaki bilgiler liste dizisine al�nd�
    while(!feof(f))
        {
            fscanf(f,"%s",city);
            strcpy(L[i].dest, city);

            fscanf(f,"%s",time);
            strcpy(L[i].clock,time);

            i++;
        }
    i=0;

   // printf("LISTENIN SIRASIZ HALI\n");
    printArray(L, numOfLines);//sefer listesinin s�ras�z hali yazd�r�ld�
    printf("\n------------------");

    mergeSortByCities(L, 0, numOfLines );//seferler �ehirlere g�re s�raya konuldu
   // printf("LISTENIN SEHIRLERE GORE SIRALI HALI\n");
    printArray(L, numOfLines);//sehirlere g�re s�ral� liste ekrana yazd�r�ld�
    printf("\n------------------");

    mergeSortByClocks(L, 0, numOfLines);//seferler hareket saaatlerine g�re s�raland�
   // printf("LISTENIN SEHIRLERE VE SAATLERE GORE SIRALI HALI\n");
    printArray(L, numOfLines);//hareket saatleri ve sehirlere gore s�ral� listeler ekrana yazd�r�ldu

    fclose(f);//dosya kapat�ld�
    free(L);//ayr�lan yer bo�alt�ld�
    return 0;
}

void mergeSortByCities(List *arr, int l, int r)//�ehirlere g�re s�ralama yapan fonksiyon
{
    if (l < r)
    {
        int m = l+(r-l)/2;

        mergeSortByCities(arr, l, m);
        mergeSortByCities(arr, m+1, r);

        mergeByCities(arr, l, m, r);
    }
}

void mergeSortByClocks(List *arr, int l, int r)//sefer saatlerine g�re s�ralama yapan fonksiyon
{
    if(l < r)
    {
        int m = l+(r-l)/2;

        mergeSortByClocks(arr, l, m);
        mergeSortByClocks(arr, m+1, r);

        mergeByClocks(arr, l, m, r);
    }
}

void mergeByCities(List *arr, int l, int m, int r)//sehirlere g�re s�ralama i�in kullan�lan birle�tirme i�lemini yapan fonksiyon
{
    //yerel de�i�ken tan�mlar�
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    List *LL;//s�ralama i�leminde ge�ici olarak kullan�lacak olan diziler
    List *RR;

    /* create temp arrays */
    LL=(struct List *)malloc(n1*sizeof(struct List));

    if(!LL)
    {
        printf("yer ayrilamad�\n");
    }
    RR=(struct List *)malloc(n2*sizeof(struct List));

    if(!RR)
    {
        printf("yer ayrilamad�\n");
    }

    //fill temporary arrays
    for(i=0;i<n1;i++)
    {
        strcpy(LL[i].dest, arr[l+i].dest);
        strcpy(LL[i].clock, arr[l+i].clock);
    }

    for(j=0; j<n2;j++)
    {
        strcpy(RR[j].dest,arr[m+1+j].dest);
        strcpy(RR[j].clock, arr[m+1+j].clock);
    }

    i = 0;
    j = 0;
    k = l;

    int ret = 0;

    while(i < n1 && j < n2)
    {
        ret = strcmp(LL[i].dest, RR[j].dest);//�ehirlere g�re k�yaslama yap�l�r
        if( ret < 0)
        {
            //k�c�k olan �ehir �nce kopyalan�r
            strcpy(arr[k].dest, LL[i].dest);
            strcpy(arr[k].clock, LL[i].clock);
            i++;
        }
        else
        {
            strcpy(arr[k].dest, RR[j].dest);
            strcpy(arr[k].clock, RR[j].clock);
            j++;
        }
        k++;
    }

    //Copy the remaining elements
    //gecici dizilerde kalan elemanlar kopyalan�r
    while(i < n1)
    {
        strcpy(arr[k].dest, LL[i].dest);
        strcpy(arr[k].clock, LL[i].clock);
        i++;
        k++;
    }

    while(j < n2)
    {
        strcpy(arr[k].dest, RR[j].dest);
        strcpy(arr[k].clock, RR[j].clock);
        j++;
        k++;
    }
}



void mergeByClocks(List *arr, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    List *LL;
    List *RR;

    /* create temp arrays */
    LL=(struct List *)malloc(n1*sizeof(struct List));

    if(!LL)
    {
        printf("yer ayrilamad�\n");
    }

    RR=(struct List *)malloc(n2*sizeof(struct List));

    if(!RR)
    {
        printf("yer ayrilamad�\n");
    }

    //fill temporary arrays
    for(i=0;i<n1;i++)
    {
        strcpy(LL[i].dest, arr[l+i].dest);
        strcpy(LL[i].clock, arr[l+i].clock);
    }

    for(j=0; j<n2;j++)
    {
        strcpy(RR[j].dest,arr[m+1+j].dest);
        strcpy(RR[j].clock, arr[m+1+j].clock);
    }

    i = 0;
    j = 0;
    k = l;

    int ret = 0;
    int res = 0;

    while(i < n1 && j < n2)
    {
        ret = strcmp(LL[i].dest, RR[j].dest);

        if( ret == 0)
        {
            res = strcmp(LL[i].clock, RR[j].clock);
            if(res > 0)
                {
                    strcpy(arr[k].dest, RR[j].dest);
                    strcpy(arr[k].clock, RR[j].clock);
                    j++;
                }
                else
                {
                    strcpy(arr[k].dest, LL[i].dest);
                    strcpy(arr[k].clock, LL[i].clock);
                    i++;
                }
        }
        else
        {
            strcpy(arr[k].dest, LL[i].dest);
            strcpy(arr[k].clock, LL[i].clock);
            i++;
        }
        k++;
    }

    while(i < n1)
    {
        strcpy(arr[k].dest, LL[i].dest);
        strcpy(arr[k].clock, LL[i].clock);
        i++;
        k++;
    }

    while(j < n2)
    {
        strcpy(arr[k].dest, RR[j].dest);
        strcpy(arr[k].clock, RR[j].clock);
        j++;
        k++;
    }
}
void printArray(List *L, int size)//diziyi ekrana yazd�rmak i�in kullan�lan fonksiyon
    {
        int i = 0;

        for(i=0;i<size;i++){
            printf("\n %d=> %s %s",i+1 , L[i].dest, L[i].clock);
        }
    }



