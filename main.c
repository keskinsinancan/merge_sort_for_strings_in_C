#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct List{
    char dest[20];//hedef
    char clock[20];//hareket saati
}List;

//fonksiyon tanýmlarý
void mergeSortByCities(List *, int, int);
void mergeSortByClocks(List *, int, int);
void mergeByCities(List *, int, int, int);
void mergeByClocks(List *, int, int, int);
void printArray(List *, int);

int main()
{
    //okunacak dosya için pointer ayarlandý
    FILE *f=NULL;
    f = fopen("seferler.txt", "r");
    if(!f)
        {
        printf("Dosya acilamadi");
        return -1;
    }

    //seger saatlerini almak için geçici deðiþkenler
    char city[20];
    char time[5];

    //Sefer listesinde kac tane otobüs bulunduðu okundu
    List *L;
    int numOfLines=0;
    while(!feof(f))
        {
            fscanf(f,"%s",city);
            numOfLines++;
        }
    numOfLines++;
    numOfLines=numOfLines/2;

    //liste için yer ayrýldý
    L=(struct List *)malloc(numOfLines*sizeof(struct List));
    if(!L)
    {
        printf("yer ayrilamadý\n");
        return -1;
    }
    //dosya pointerý baþa sarýldý
    rewind(f);

    int i=0;

    //dosyadaki bilgiler liste dizisine alýndý
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
    printArray(L, numOfLines);//sefer listesinin sýrasýz hali yazdýrýldý
    printf("\n------------------");

    mergeSortByCities(L, 0, numOfLines );//seferler þehirlere göre sýraya konuldu
   // printf("LISTENIN SEHIRLERE GORE SIRALI HALI\n");
    printArray(L, numOfLines);//sehirlere göre sýralý liste ekrana yazdýrýldý
    printf("\n------------------");

    mergeSortByClocks(L, 0, numOfLines);//seferler hareket saaatlerine göre sýralandý
   // printf("LISTENIN SEHIRLERE VE SAATLERE GORE SIRALI HALI\n");
    printArray(L, numOfLines);//hareket saatleri ve sehirlere gore sýralý listeler ekrana yazdýrýldu

    fclose(f);//dosya kapatýldý
    free(L);//ayrýlan yer boþaltýldý
    return 0;
}

void mergeSortByCities(List *arr, int l, int r)//þehirlere göre sýralama yapan fonksiyon
{
    if (l < r)
    {
        int m = l+(r-l)/2;

        mergeSortByCities(arr, l, m);
        mergeSortByCities(arr, m+1, r);

        mergeByCities(arr, l, m, r);
    }
}

void mergeSortByClocks(List *arr, int l, int r)//sefer saatlerine göre sýralama yapan fonksiyon
{
    if(l < r)
    {
        int m = l+(r-l)/2;

        mergeSortByClocks(arr, l, m);
        mergeSortByClocks(arr, m+1, r);

        mergeByClocks(arr, l, m, r);
    }
}

void mergeByCities(List *arr, int l, int m, int r)//sehirlere göre sýralama için kullanýlan birleþtirme iþlemini yapan fonksiyon
{
    //yerel deðiþken tanýmlarý
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    List *LL;//sýralama iþleminde geçici olarak kullanýlacak olan diziler
    List *RR;

    /* create temp arrays */
    LL=(struct List *)malloc(n1*sizeof(struct List));

    if(!LL)
    {
        printf("yer ayrilamadý\n");
    }
    RR=(struct List *)malloc(n2*sizeof(struct List));

    if(!RR)
    {
        printf("yer ayrilamadý\n");
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
        ret = strcmp(LL[i].dest, RR[j].dest);//þehirlere göre kýyaslama yapýlýr
        if( ret < 0)
        {
            //kücük olan þehir önce kopyalanýr
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
    //gecici dizilerde kalan elemanlar kopyalanýr
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
        printf("yer ayrilamadý\n");
    }

    RR=(struct List *)malloc(n2*sizeof(struct List));

    if(!RR)
    {
        printf("yer ayrilamadý\n");
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
void printArray(List *L, int size)//diziyi ekrana yazdýrmak için kullanýlan fonksiyon
    {
        int i = 0;

        for(i=0;i<size;i++){
            printf("\n %d=> %s %s",i+1 , L[i].dest, L[i].clock);
        }
    }



