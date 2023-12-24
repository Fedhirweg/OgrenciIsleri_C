#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Bolum // bolum bilgilerini iceren struct
{
	int bolumID;
	char bolumAd[30];
} bolum;

typedef struct ogr
{
	int numara;
	char tc[20], adSoyad[20], dTarihi[20], dYeri[20], cinsiyet, adres[30], tel[20], ePosta[30];
	int askerlikDurumu, BolumID, durum, ogrenciID;
} ogr;

void bolumListele();

void OgrenciEkle()
{
	system("cls");
	printf("Ogrenci Ekleme islemi... \n\n");
	ogr o1;

	FILE *numPtr = fopen("OgrenciNumaralari.dat", "a+b");
	int numara = 0;
	while (fread(&numara, sizeof(int), 1, numPtr))
	{
	}
	numara += 1;

	o1.ogrenciID = numara;
	fwrite(&numara, sizeof(int), 1, numPtr);
	fclose(numPtr);
    printf("Ad-Soyad         : ");
	scanf(" %[^\n]s", o1.adSoyad);
	printf("TC               : ");
	scanf(" %[^\n]s", o1.tc);
	printf("Dogum Tarihi     : ");
	scanf(" %[^\n]s", o1.dTarihi);
	printf("Dogum Yeri       : ");
	scanf(" %[^\n]s", o1.dYeri);
	printf("Cinsiyet         : ");
	scanf(" %[^\n]s", &o1.cinsiyet);
	printf("Adres            : ");
	scanf(" %[^\n]s", o1.adres);
	printf("Telefon          : ");
	scanf(" %[^\n]s", o1.tel);
	printf("Eposta           : ");
	scanf(" %[^\n]s", o1.ePosta);
	if (o1.cinsiyet == 'e' || o1.cinsiyet == 'E')
	{
		printf("Askerlik Durumu\n");
		printf("[Yapmadi (0), Yapti (1), Muaf(2)] ");
		scanf("%d", &o1.askerlikDurumu);
	}
	o1.askerlikDurumu = 3;
	fclose(numPtr);

	bolumListele();

	printf("Bolum Numarasi : ");
	scanf("%d", &o1.BolumID);
	o1.durum = 1;

	FILE *Ptr = fopen("Ogrenciler.dat", "a+b");

	fwrite(&o1, sizeof(ogr), 1, Ptr);
	fclose(Ptr);

	printf("%d Numarali ogrenci kaydi tamam \n", o1.numara);
}
void OgrenciSil()
{
}
void OgrenciListele()
{
     system("cls");
	printf("Ogrenci listesi \n\n");
	ogr o1;

	FILE *Ptr = fopen("Ogrenciler.dat", "rb");
	if (Ptr == NULL)
	{
       printf("Ogrenciler dosyasi acilmadi! \n");
	   return;
	}

	printf("%-20s%-30s\n", "Ogrenci--ID", "Ogrenci--ADI");
	while (fread(&o1, sizeof(ogr),1,Ptr))
	{
		printf("%-20d%-30s\n",o1.ogrenciID, o1.adSoyad);
	}
	fclose(Ptr);
}
void OgrenciBelgesi()
{
}
void OgrenciTranskript()
{
}
void OgrenciMezuniyet()
{
}
void OgrenciAra()
{
}

int OgrenciMenu()
{
	int secim;
	printf("\n\tOgrenci islemleri \n\n");
	printf("\n\t1- Ogrenci Ekle \n");
	printf("\n\t2- Ogrenci Sil \n");
	printf("\n\t3- Ogrenci Listele \n");
	printf("\n\t4- Ogrenci Belgesi \n");
	printf("\n\t5- Ogrenci Transkript  \n");
	printf("\n\t6- Ogrenci Ara  \n");
	printf("\n\t7- Ogrenci Mezuniyet \n");
	printf("\n\t0- Cikis \n");
	printf("\n\t- Seciminiz :  ");
	scanf("%d", &secim);
	system("cls");
	return secim;
}

void ogrenciIslemleri()
{
	int secim = OgrenciMenu();
	while (secim != 0)
	{
		switch (secim)
		{
		case 1:
			OgrenciEkle();
			break;
		case 2:
			OgrenciSil();
			break;
		case 3:
			OgrenciListele();
			break;
		case 4:
			OgrenciBelgesi();
			break;
		case 5:
			OgrenciTranskript();
			break;
		case 7:
			OgrenciMezuniyet();
			break;
		case 0:
			break;
		default:
			printf("Hatali secim yaptiniz ! \n");
		}
		secim = OgrenciMenu();
	}
	printf("Bolum islemlerinden cikis yaptiniz ... \n");
}
void ogretimGorevlisiIslemleri()
{
}
void dersIslemleri()
{
	system("cls");
	printf("\nDers islemleri");
}

void bolumEkle()
{
	system("cls");
	printf("Bolum Ekleme islemi... \n\n");
	bolum b1;
	printf("Bolum Adi : ");
	scanf(" %[^\n]s", b1.bolumAd);

	FILE *numPtr = fopen("bolumNumaralari.dat", "a+b");
	int numara = 0;
	while (fread(&numara, sizeof(int), 1, numPtr))
	{
	}
	numara += 1;
	b1.bolumID = numara;
	fwrite(&numara, sizeof(int), 1, numPtr);
	fclose(numPtr);

	FILE *Ptr = fopen("bolumler.dat", "a+b");
	fwrite(&b1, sizeof(bolum), 1, Ptr);
	fclose(Ptr);

	printf("%d Numarali Bolum Kaydi Tamam \n", numara);
}

void bolumListele()
{
	system("cls");
	printf("Bolumler listesi \n\n");
	bolum b1;

	FILE *Ptr = fopen("bolumler.dat", "rb");
	if (Ptr == NULL)
	{
		printf("Bolum dosyasi acilamadi! \n");
		return;
	}

	printf("%-20s%-30s\n", "BOLUM-ID", "BOLUM-ADI");
	while (fread(&b1, sizeof(bolum), 1, Ptr))
	{
		printf("%-20d%-30s\n", b1.bolumID, b1.bolumAd);
	}
	fclose(Ptr);
}

int bolumMenu()
{
	int secim;
	printf("\n\tBolum islemleri...\n\n");
	printf("\n\t1- Bolum Ekle \n");
	printf("\n\t2- Bolum listele \n");
	printf("\n\t0- Cikis \n");
	printf("\n\t1- Seciminiz :  ");
	scanf("%d", &secim);
	system("cls");
	return secim;
}

void bolumIslemleri()
{
	int secim = bolumMenu();
	while (secim != 0)
	{
		switch (secim)
		{
		case 1:
			bolumEkle();
			break;
		case 2:
			bolumListele();
			break;
		case 0:
			break;
		default:
			printf("Hatali secim yaptiniz ! \n");
		}
		secim = bolumMenu();
	}
	printf("Bolum islemlerinden cikis yaptiniz ... \n");
}
void notIslemleri()
{
}

int menu()
{
	int secim;
	printf("\n\tOGRENCI ISLERI OTOMASYONU\n\n");
	printf("\n\t1- OGRENCI ISLEMLERI \n");
	printf("\n\t2- OGRETIM GOREVLISI ISLEMLERI \n");
	printf("\n\t3- DERS ISLEMLERI \n");
	printf("\n\t4- BOLUM ISLEMLERI \n");
	printf("\n\t5- NOT ISLEMLERI \n");
	printf("\n\t0- PROGRAMI KAPAT \n");
	printf("\n\t1- Seciminiz :  ");
	scanf("%d", &secim);
	system("cls");
	return secim;
}

int main()
{
	printf("*************************************************\n");
	printf("\t\tHOSGELDINIZ\n");
	printf("*************************************************\n\n");
	int secim = menu();
	while (secim != 0)
	{
		switch (secim)
		{
		case 1:
			ogrenciIslemleri();
			break;
		case 2:
			ogretimGorevlisiIslemleri();
			break;
		case 3:
			dersIslemleri();
			break;
		case 4:
			bolumIslemleri();
			break;
		case 5:
			notIslemleri();
			break;
		case 0:
			break;
		default:
			printf("Hatali secim yaptiniz ! \n");
		}
		secim = menu();
	}
	printf("Programi kapattiniz... \n");

	return 0;
}
