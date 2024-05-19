#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_KULLANICILAR 100
#define KULLANICI_ADI_UZUNLUK 20
#define SIFRE_UZUNLUK 20

typedef struct Kullanici
{
	char kullaniciAdi[KULLANICI_ADI_UZUNLUK];
	char sifre[SIFRE_UZUNLUK];
} Kullanici;

typedef struct Bolum
{
	int bolumNO;
	char bolumAd[30];
	int durum; // 1 ise aktif, 0 ise silinmiş
} bolum;

typedef struct Kisi // Öğrenci ve öğretim görevlisi yapısı tanımlanmaktadır.
{
	int numara;
	char adSoyad[20], tc[20], dTarih[20], dYeri[20], cinsiyet, tel[20], ePosta[30], adres[30];
	int bolumNO;
	int durum; // 1 ise aktif, 0 ise silinmiş, 2 ise mezun
} ogr;

typedef struct Ders // Ders yapısı tanımlanmaktadır.
{
	int dersID;
	int bolumNO;
	int kredi;
	char dersAd[30];
	int ogrGorNO;
	int	durum;

} ders;

typedef struct Notlar // Notlar yapısı tanımlanmaktadır.
{
	int notID;
	int dersID;
	int bolumNO;

	int ogrGorNO;
	int ogrenciNO;
	float puan;
	int durum;
} notlar;

int kullaniciAdiVarMi(const Kullanici *kullanicilar, const int kullaniciSayisi, const char *kullaniciAdi)
{
	for (int i = 0; i < kullaniciSayisi; i++)
	{
		if (strcmp(kullanicilar[i].kullaniciAdi, kullaniciAdi) == 0)
		{
			return 1; // Kullanici adi var
		}
	}
	return 0; // Kullanici adi yok
}

void kullaniciKayit(Kullanici *kullanicilar, int *kullaniciSayisi)
{
	if (*kullaniciSayisi >= MAX_KULLANICILAR)
	{
		printf("Maksimum kullanici sayisina ulasildi.\n");
		return;
	}

	Kullanici yeniKullanici;

	system("cls");
	printf("\n\tKULLANICI KAYIT ISLEMI ...\n\n\n");
	printf("\tKullanici Adi: ");
	scanf("%s", yeniKullanici.kullaniciAdi);

	if (kullaniciAdiVarMi(kullanicilar, *kullaniciSayisi, yeniKullanici.kullaniciAdi))
	{
		system("cls");
		printf("Bu kullanici adi zaten var. Baska bir kullanici adi seciniz.\n");
		return;
	}
	printf("\tSifre: ");
	scanf("%s", yeniKullanici.sifre);

	kullanicilar[*kullaniciSayisi] = yeniKullanici;
	(*kullaniciSayisi)++;

	// Kullaniciyi dosyaya yaz
	FILE *kullaniciDosyasi = fopen("./data/kullanici.dat", "ab");
	FILE *sifreDosyasi = fopen("./data/sifre.dat", "ab");

	system("cls");
	if (kullaniciDosyasi != NULL && sifreDosyasi != NULL)
	{
		fwrite(&yeniKullanici, sizeof(Kullanici), 1, kullaniciDosyasi);
		fwrite(&yeniKullanici, sizeof(Kullanici), 1, sifreDosyasi);

		fclose(kullaniciDosyasi);
		fclose(sifreDosyasi);

		printf("Kullanici kaydedildi.\n");
	}
	else
	{
		printf("Dosya acma hatasi.\n");
	}
}

int kullaniciGiris(const Kullanici *kullanicilar, int kullaniciSayisi)
{
	char kullaniciAdi[KULLANICI_ADI_UZUNLUK];
	char sifre[SIFRE_UZUNLUK];
	system("cls");
	printf("\n\tGIRIS YAPMA ISLEMI ...\n\n\n");

	printf("\tKullanici Adi: ");
	scanf("%s", kullaniciAdi);

	printf("\tSifre: ");
	scanf("%s", sifre);

	for (int i = 0; i < kullaniciSayisi; i++)
	{
		if (strcmp(kullanicilar[i].kullaniciAdi, kullaniciAdi) == 0 && strcmp(kullanicilar[i].sifre, sifre) == 0)
		{
			return i; // Giris basarili
		}
	}

	return -1; // Giris basarisiz
}

void kullaniciBilgileriniOku(Kullanici *kullanicilar, int *kullaniciSayisi)
{
	FILE *kullaniciDosyasi = fopen("./data/kullanici.dat", "rb");
	FILE *sifreDosyasi = fopen("./data/sifre.dat", "rb");

	if (kullaniciDosyasi != NULL && sifreDosyasi != NULL)
	{
		while (fread(&kullanicilar[*kullaniciSayisi], sizeof(Kullanici), 1, kullaniciDosyasi) == 1)
		{
			fread(&kullanicilar[*kullaniciSayisi], sizeof(Kullanici), 1, sifreDosyasi);
			(*kullaniciSayisi)++;
		}

		fclose(kullaniciDosyasi);
		fclose(sifreDosyasi);
	}
}

void dataKlasoru() // Data klasörü oluşturma fonksiyonu.
{
	const char *folderPath = "data";

	if (CreateDirectory(folderPath, NULL) || ERROR_ALREADY_EXISTS == GetLastError())
	{
	}
	else
	{
		printf("Dizin hatasÄ±: %s\n", folderPath);
	}
}

void bolumEkle()
{
	system("cls");
	printf("Bolum ekleme islemi... \n\n");
	bolum b1;
	printf("Bolum Adi : ");
	scanf(" %[^\n]s", b1.bolumAd);

	FILE *numPtr = fopen("./data/bolumNumaralari.dat", "a+b"); // Bolüm NO tutmak için oluşturulan dosya
	int numara = 0;
	while (fread(&numara, sizeof(int), 1, numPtr))
	{
	}
	numara += 1;
	b1.bolumNO = numara;
	b1.durum = 1;
	fwrite(&numara, sizeof(int), 1, numPtr);
	fclose(numPtr);

	FILE *ptr = fopen("./data/bolumler.dat", "a+b");
	fwrite(&b1, sizeof(bolum), 1, ptr);
	fclose(ptr);

	printf("%d numarali bolum kaydi tamam \n", numara);
}

void bolumListele()
{
	system("cls");
	printf("Bolumler listesi \n\n");
	bolum b1;

	FILE *Ptr = fopen("./data/bolumler.dat", "rb");
	if (Ptr == NULL)
	{
		printf("Bolum dosyasi acilamadi! \n");
		return;
	}

	printf("%-20s%-30s\n", "BOLUM-NO", "BOLUM-ADI");
	while (fread(&b1, sizeof(bolum), 1, Ptr))
	{
		if (b1.durum == 1){
			printf("%-20d%-30s\n", b1.bolumNO, b1.bolumAd);
		}
	}
	fclose(Ptr);
}

void bolumSil()
{
	system("cls");
	printf("Bolum silme islemi... \n\n");

	bolum b1;
	int numara, sayac = 0, sonuc = 0;

	FILE *ptr = fopen("./data/bolumler.dat", "r+b");
	bolumListele();
	printf("Silinecek Bolum Numarasi : ");
	scanf("%d", &numara);
	while (fread(&b1, sizeof(bolum), 1, ptr) == 1)
	{
		if (numara == b1.bolumNO && b1.durum == 1)
		{
			sonuc = 1;
			break;
		}
		sayac++;
	}
	if (sonuc == 0)
		printf("%d numarali bolum bulunamadi \n", numara);
	else
	{
		rewind(ptr);
		fseek(ptr, (sayac) * sizeof(bolum), 0);
		b1.durum = 0;
		fwrite(&b1, sizeof(bolum), 1, ptr);
		printf("%d numarali bolum kaydi silindi \n", numara);
	}
	fclose(ptr);
}

int bolumMenu()
{
	int secim;
	printf("\n\tBolum islemleri...\n\n");
	printf("\n\t1- Bolum Ekle \n");
	printf("\n\t2- Bolum Listele \n");
	printf("\n\t3- Bolum Sil \n");
	printf("\n\t0- Cikis \n");
	printf("\n\t   Seciminiz :  ");
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
		case 3:
			bolumListele();
			bolumSil();
			break;
		default:
			printf("Hatali secim yaptiniz ! \n");
		}
		secim = bolumMenu();
	}
	printf("bolum islemlerinden cikis yaptiniz ... \n");
}

void ogrEkle() // Sisteme öğrenci ekleme fonksiyonu.
{
	system("cls");
	printf("Ogrenci ekleme islemi... \n\n");

	ogr k;

	FILE *numPtr = fopen("./data/ogrenciNumaralari.dat", "a+b"); // Arka planda numara üretir
	int numara = 0;
	while (fread(&numara, sizeof(int), 1, numPtr))
	{
	}
	numara += 1;

	k.numara = numara;
	fwrite(&numara, sizeof(int), 1, numPtr);
	fclose(numPtr);
	printf("Ad-Soyad       : ");
	scanf(" %[^\n]s", k.adSoyad);
	printf("TC             : "); // Öğrencinin bilgileri alındı.
	scanf(" %[^\n]s", k.tc);
	printf("Dogum Tarih    : ");
	scanf(" %[^\n]s", k.dTarih);
	printf("Dogum Yeri     : ");
	scanf(" %[^\n]s", k.dYeri);
	printf("Cinsiyet       : ");
	scanf(" %[^\n]s", &k.cinsiyet);
	printf("Telefon        : ");
	scanf(" %[^\n]s", k.tel);
	printf("E-Posta        : ");
	scanf(" %[^\n]s", k.ePosta);
	printf("Adres          : ");
	scanf(" %[^\n]s", k.adres);
	fclose(numPtr);

	bolumListele();

	printf("Bolum Numarasi : ");
	scanf("%d", &k.bolumNO);
	k.durum = 1;

	FILE *ptr = fopen("./data/ogrenciler.dat", "a+b");
	fwrite(&k, sizeof(ogr), 1, ptr); // Oluşturulan numarayı kaydettik ve kapattık.
	fclose(ptr);

	printf("%d numarali ogrenci kaydi tamam \n", k.numara);
}

void ogrSil()
{
	system("cls");
	printf("Ogrenci silme islemi... \n\n");

	ogr k;
	int numara, sayac = 0, sonuc = 0;

	FILE *ptr = fopen("./data/ogrenciler.dat", "r+b"); // Okuma ve yazma formatın pointer oluşturduk.

	printf("Numara : ");
	scanf("%d", &numara);
	while (fread(&k, sizeof(ogr), 1, ptr) == 1)
	{
		if (numara == k.numara && k.durum == 1)
		{
			sonuc = 1;
			break;
		}
		sayac++;
	}
	if (sonuc == 0)
		printf("%d numarali aktif ogrenci bulunamadi \n", numara);
	else
	{
		rewind(ptr);
		fseek(ptr, (sayac) * sizeof(ogr), 0);
		k.durum = 0; // Durum 0 ise öğrencinin kaydı silinmiştir ve ya dondurulmuştur.
		fwrite(&k, sizeof(ogr), 1, ptr);
		printf("%d numarali ogrenci kaydi silindi \n", numara);
	}

	fclose(ptr);
}

void ogrBul()
{
	system("cls");
	printf("Ogrenci arama islemi... \n\n");

	ogr k;
	int numara, sayac = 0, sonuc = 0;

	FILE *ptr = fopen("./data/ogrenciler.dat", "r+b");

	printf("Numara : "); // Aranıcak olan öğrencinin numarasını sorgulama.
	scanf("%d", &numara);
	while (fread(&k, sizeof(ogr), 1, ptr) == 1)
	{
		if (numara == k.numara)
		{
			sonuc = 1;
			break;
		}
		sayac++;
	}
	if (sonuc == 0)
		printf("%d numarali ogrenci bulunamadi \n", numara);
	else
	{

		printf("%d numarali ogrenci bilgileri \n", numara); // Öğrencinin kayıtlı bilgileri burada gösterilir.
		printf("TC          : %s \n", k.tc);
		printf("Ad-Soyad    : %s \n", k.adSoyad);
		printf("Bolumu      : %d \n", k.bolumNO);
		printf("Durumu      : %d \n", k.durum);
		printf("Adres       : %s \n", k.adres);
		printf("Telefon     : %s \n", k.tel);
	}
	fclose(ptr);
}

void ogrListele()
{
	system("cls");
	printf("Ogrenci listele islemi... \n\n");

	ogr k;
	FILE *ptr = fopen("./data/ogrenciler.dat", "r+b");

	bolumListele();
	int bolumNo, sayac = 0;
	printf("Bolum No : ");
	scanf("%d", &bolumNo);
	system("cls");
	printf("%-20s%-20s%-30s\n", "NUMARA", "TC", "AD-SOYAD"); // Öğrencinin bilgileri alındı.
	while (fread(&k, sizeof(ogr), 1, ptr) == 1)
	{
		if (bolumNo == k.bolumNO && k.durum == 1)
		{
			printf("%-20d%-20s%-30s \n", k.numara, k.tc, k.adSoyad); // Hangi bölümün öğrencisi ise onu listeliyoruz.
			sayac++;
		}
	}
	fclose(ptr);
	printf("\nBolumdeki toplam ogrenci sayisi : %d \n", sayac);
}

void ogrBelgesi()
{
	system("cls");
	printf("Ogrenci belgesi islemleri... \n\n");

	ogr k;
	int numara, sayac = 0, sonuc = 0;

	FILE *ptr = fopen("./data/ogrenciler.dat", "r+b");

	printf("Numara : ");
	scanf("%d", &numara);
	while (fread(&k, sizeof(ogr), 1, ptr) == 1)
	{
		if (numara == k.numara)
		{
			sonuc = 1;
			break;
		}
		sayac++;
	}
	if (sonuc == 0)
		printf("%d numarali ogrenci bulunamadi \n", numara);
	else
	{
		if (k.durum == 0) // Öğrencinin aktif mi yoksa mezun bir öğrenci mi olduğunu gösterilmiştir.
		{
			printf("%d numarali ogrencin kaydi SILINMISTIR . bilgileri asagidadir. \n", numara);
			printf("TC          : %s \n", k.tc);
			printf("Ad-Soyad    : %s \n", k.adSoyad);
			printf("Dogum tarihi: %s \n", k.dTarih);
			printf("Bolumu      : %d \n", k.bolumNO);
			printf("Durumu      : %d \n", k.durum);
			printf("Adres       : %s \n", k.adres);
			printf("Telefon     : %s \n", k.tel);
		}

		else if (k.durum == 1) // Durum Eğer 1 ise aktif kayıtlı öğrencidir.
		{
			printf("%d numarali ogrenci AKTIF kayitli ogrencidir . bilgileri asagidadir. \n", numara);
			printf("TC          : %s \n", k.tc);
			printf("Ad-Soyad    : %s \n", k.adSoyad);
			printf("Dogum tarihi: %s \n", k.dTarih);
			printf("Bolumu      : %d \n", k.bolumNO);
			printf("Durumu      : %d \n", k.durum);
			printf("Adres       : %s \n", k.adres);
			printf("Telefon     : %s \n", k.tel);
		}
		else if (k.durum == 2)
		{
			printf("%d numarali ogrenci Fakultemizden MEZUN olmustur . bilgileri asagidadir. \n", numara);
			printf("TC          : %s \n", k.tc);
			printf("Ad-Soyad    : %s \n", k.adSoyad);
			printf("Dogum tarihi: %s \n", k.dTarih);
			printf("Bolumu      : %d \n", k.bolumNO);
			printf("Durumu      : %d \n", k.durum);
			printf("Adres       : %s \n", k.adres);
			printf("Telefon     : %s \n", k.tel);
		}
	}
	fclose(ptr);
}
void ogrTranskript()
{
	system("cls");
	printf("Ogrenci transkript islemleri... \n\n");

	ogr k;
	int numara, sayac = 0, sonuc = 0;

	FILE *ptr = fopen("./data/ogrenciler.dat", "r+b");

	printf("Numara : ");
	scanf("%d", &numara);
	while (fread(&k, sizeof(ogr), 1, ptr) == 1)
	{
		if (numara == k.numara)
		{
			sonuc = 1;
			break;
		}
		sayac++;
	}
	if (sonuc == 0)
		printf("%d numarali ogrenci bulunamadi \n", numara);
	else
	{
		printf("%d numarali ogrenci BILGILERI \n\n", numara);
		printf("TC          : %s \n", k.tc);
		printf("Ad-Soyad    : %s \n", k.adSoyad);
		printf("Bolumu      : %d \n", k.bolumNO);
		printf("Durumu      : %d \n", k.durum);
		printf("Adres       : %s \n", k.adres);
		printf("Telefon     : %s \n", k.tel);

		printf("NOT BILGILERI \n\n\n");

		notlar n1;

		FILE *file = fopen("./data/notlar.dat", "r+b");
		printf("%-20s%-20s%-20s\n", "DERS-NO", "OGRENCI-NO", "PUAN");
		while (fread(&n1, sizeof(notlar), 1, file))
		{

			if (numara == n1.ogrenciNO)
				printf("%-20d%-20d%.2f\n", n1.dersID, n1.ogrenciNO, n1.puan);
		}
		fclose(file);
	}
}
void ogrMezun()
{
	system("cls");
	printf("Ogrenci mezuniyet islemi... \n\n");

	ogr k;
	int numara, sonuc = 0, sayac = 0;

	FILE *ptr = fopen("./data/ogrenciler.dat", "r+b");

	printf("Numara : "); // Yine numara sorgulama yapolmıştır.
	scanf("%d", &numara);
	while (fread(&k, sizeof(ogr), 1, ptr) == 1)
	{
		if (numara == k.numara)
		{
			sonuc = 1; // Öğrencinin durumu 0 ise silinmiştir 1 ise aktiftir.
			break;
		}
		sayac++;
	}
	if (sonuc == 0)
		printf("%d numarali ogrenci bulunamadi \n", numara);
	else
	{
		rewind(ptr); // gösterilen akışda ki aktif dosya konumunu en başa alır.
		fseek(ptr, (sayac) * sizeof(ogr), 0);
		k.durum = 2;
		fwrite(&k, sizeof(ogr), 1, ptr);
		printf("%d numarali %s isimli ogrencinin mezuniyet islemi tamamlandi... \n", numara, k.adSoyad);
	}
	fclose(ptr);
}

int ogrMenu()
{
	int secim;
	printf("\n\tOgrenci islemleri... \n\n");
	printf("\n\t1- Ogrenci Ekle  \n");
	printf("\n\t2- Ogrenci Sil  \n");
	printf("\n\t3- Ogrenci Ara  \n");
	printf("\n\t4- Ogrenci Listele  \n");
	printf("\n\t5- Ogrenci Belgesi  \n");
	printf("\n\t6- Ogrenci Transkript  \n");
	printf("\n\t7- Ogrenci Mezuniyet  \n");
	printf("\n\t0- Cikis \n");
	printf("\n\t   Seciminiz   :  ");
	scanf("%d", &secim);
	system("cls");
	return secim;
}

void ogrIslemleri()
{
	int secim = ogrMenu();
	while (secim != 0)
	{
		switch (secim)
		{
		case 1:
			ogrEkle();
			break;
		case 2:
			ogrSil();
			break;
		case 3:
			ogrBul();
			break;
		case 4:
			ogrListele();
			break;
		case 5:
			ogrBelgesi();
			break;
		case 6:
			ogrTranskript();
			break;
		case 7:
			ogrMezun();
			break;
		default:
			printf("Hatali secim yaptiniz ! \n");
		}
		secim = ogrMenu();
	}
	printf("Ogrenci islemlerinden cikis yaptiniz ... \n");
}
void ogrGorEkle()
{
	system("cls");
	printf("Ogretim gorevlisi ekleme islemi... \n\n");

	ogr k;

	FILE *numPtr = fopen("./data/ogretimGorevlisiNumaralari.dat", "a+b");
	int numara = 0;
	while (fread(&numara, sizeof(int), 1, numPtr))
	{
	}
	numara += 1;

	k.numara = numara;
	fwrite(&numara, sizeof(int), 1, numPtr);
	fclose(numPtr);
	printf("Ad-Soyad       : ");
	scanf(" %[^\n]s", k.adSoyad);
	printf("TC             : ");
	scanf(" %[^\n]s", k.tc);
	printf("Dogum Tarih    : ");
	scanf(" %[^\n]s", k.dTarih);
	printf("Dogum Yeri     : ");
	scanf(" %[^\n]s", k.dYeri);
	printf("Cinsiyet       : ");
	scanf(" %[^\n]s", &k.cinsiyet);
	printf("Telefon        : ");
	scanf(" %[^\n]s", k.tel);
	printf("E-Posta        : ");
	scanf(" %[^\n]s", k.ePosta);
	printf("Adres          : ");
	scanf(" %[^\n]s", k.adres);
	fclose(numPtr);

	bolumListele();

	printf("Bolum Numarasi : ");
	scanf("%d", &k.bolumNO);
	k.durum = 1;

	FILE *ptr = fopen("./data/ogretimGorevlileri.dat", "a+b");
	fwrite(&k, sizeof(ogr), 1, ptr);
	fclose(ptr);

	printf("%d numarali ogretim gorevlisi kaydi tamam \n", k.numara);
}

void ogrGorSil()
{
	system("cls");
	printf("Ogretim gorevlisi silme islemi... \n\n");

	ogr k;
	int numara, sayac = 0, sonuc = 0;

	FILE *ptr = fopen("./data/ogretimGorevlileri.dat", "r+b");

	printf("Numara : ");
	scanf("%d", &numara);
	while (fread(&k, sizeof(ogr), 1, ptr) == 1)
	{
		if (numara == k.numara && k.durum == 1)
		{
			sonuc = 1;
			break;
		}
		sayac++;
	}
	if (sonuc == 0)
		printf("%d numarali ogretim gorevlisi bulunamadi \n", numara);
	else
	{
		rewind(ptr);
		fseek(ptr, (sayac) * sizeof(ogr), 0);
		k.durum = 0;
		fwrite(&k, sizeof(ogr), 1, ptr);
		printf("%d numarali ogretim gorevlisinin kaydi silindi \n", numara);
	}
	fclose(ptr);
}

void ogrGorBul()
{
	system("cls");
	printf("Ogretim gorevlisi arama islemi... \n\n");

	ogr k;
	int numara, sayac = 0, sonuc = 0;

	FILE *ptr = fopen("./data/ogretimGorevlileri.dat", "r+b");

	printf("Numara : ");
	scanf("%d", &numara);
	while (fread(&k, sizeof(ogr), 1, ptr) == 1)
	{
		if (numara == k.numara)
		{
			sonuc = 1;
			break;
		}
		sayac++;
	}
	if (sonuc == 0)
		printf("%d numarali ogretim gorevlisi bulunamadi \n", numara);
	else
	{

		printf("%d numarali ogretim gorevlisi bilgileri \n", numara);
		printf("TC          : %s \n", k.tc);
		printf("Ad-Soyad    : %s \n", k.adSoyad);

		printf("Bolumu      : %d \n", k.bolumNO);
		printf("Durum       : %d \n", k.durum);
		printf("Adres       : %s \n", k.adres);
		printf("Telefon     : %s \n", k.tel);
	}

	fclose(ptr);
}

void ogrGorListele()
{
	system("cls");
	printf("Ogretim gorevlisi listele islemi... \n\n");

	ogr k;
	bolum b;
	FILE *ptr = fopen("./data/ogretimGorevlileri.dat", "r+b");
	FILE *bolumPtr = fopen("./data/bolumler.dat", "r+b");
	int sayac = 0;

	printf("%-20s%-20s%-30s%-30s\n", "NUMARA", "TC", "AD-SOYAD", "BOLUM ADI");
	while (fread(&k, sizeof(ogr), 1, ptr) == 1)
	{
		rewind(bolumPtr); // dosya pointerını başa alır.
		while (fread(&b, sizeof(bolum), 1, bolumPtr) == 1) // Bolum bilgileri alınmaktadır.
		{
			if (b.bolumNO == k.bolumNO) // Eğer bolumNO eşit ise bolumAd bilgileri alınmaktadır.
			{
				printf("%-20d%-20s%-30s%-30s\n", k.numara, k.tc, k.adSoyad, b.bolumAd);
				break; // Eğer eşit ise döngüden çıkılmaktadır.
			}
		}
		sayac++;
	}
	fclose(ptr);
	fclose(bolumPtr);
	printf("\nToplam ogretim gorevlisi sayisi : %d \n", sayac);
}

int ogrGorMenu()
{
	int secim;
	printf("\n\tOgretim gorevlisi islemleri... \n\n");
	printf("\n\t1- Ogretim Gorevlisi Ekle  \n");
	printf("\n\t2- Ogretim Gorevlisi Sil  \n");
	printf("\n\t3- Ogretim Gorevlisi Ara  \n");
	printf("\n\t4- Ogretim Gorevlisi Listele  \n");

	printf("\n\t0- Cikis \n");
	printf("\n\t   Seciminiz   :  ");
	scanf("%d", &secim);
	system("cls");
	return secim;
}

void ogrGorIslemleri()
{
	int secim = ogrGorMenu();
	while (secim != 0)
	{
		switch (secim)
		{
		case 1:
			ogrGorEkle();
			break;
		case 2:
			ogrGorSil();
			break;
		case 3:
			ogrGorBul();
			break;
		case 4:
			ogrGorListele();
			break;
		default:
			printf("Hatali secim yaptiniz ! \n");
		}
		secim = ogrGorMenu();
	}
	printf("Ogretim gorevlisi islemlerinden cikis yaptiniz ... \n");
}

void dersEkle() // Sisteme ders ekleme fonksiyonu
{
	system("cls");
	printf("Ders ekleme islemi... \n\n");
	ders d1;

	printf("Ders Adi : ");
	scanf(" %[^\n]s", d1.dersAd);
	printf("AKTS : ");
	scanf(" %d", &d1.kredi);

	bolumListele();
	printf("Bolum Numarasi : ");
	scanf(" %d", &d1.bolumNO);

	ogrGorListele();

	printf("Ogretim gorevlisi numarasi : ");
	scanf(" %d", &d1.ogrGorNO);

	FILE *numPtr = fopen("./data/dersNumaralari.dat", "a+b"); // Dersler ekleme ve okuma modunda açılmaktadır.
	int numara = 0;
	while (fread(&numara, sizeof(int), 1, numPtr))
	{
	}
	numara += 1;
	d1.dersID = numara;
	d1.durum = 1;
	fwrite(&numara, sizeof(int), 1, numPtr);
	fclose(numPtr);

	FILE *ptr = fopen("./data/dersler.dat", "a+b");
	fwrite(&d1, sizeof(ders), 1, ptr); // Eklenen ders bilgileri dosyaya yazılmaktadır.
	fclose(ptr);
	printf("%d numarali ders kaydi tamam \n", numara);
}

void dersListele()
{
	system("cls");
	printf("Ders listesi ... \n\n");

	ders d1;
	ogr ogrGor;

	FILE *dersPtr = fopen("./data/dersler.dat", "r+b");
	FILE *ogrGorPtr = fopen("./data/ogretimGorevlileri.dat", "r+b");

	printf("%-20s%-20s%-30s%-20s%-30s\n", "BOLUM-NO", "DERS-NO", "DERS-ADI", "Ogr.NO", "Ogr.ADI");

	while (fread(&d1, sizeof(ders), 1, dersPtr))
	{
		// Check if the course is active
		if (d1.durum == 1) {
			char ogrGorAdi[20] = "Bilinmiyor"; // Default value if no match is found

			// Reset the file pointer to the beginning of the file
			rewind(ogrGorPtr);

			// Search for the instructor in the instructors file
			while (fread(&ogrGor, sizeof(ogr), 1, ogrGorPtr))
			{
				if (ogrGor.numara == d1.ogrGorNO)
				{
					strcpy(ogrGorAdi, ogrGor.adSoyad);
					break;
				}
			}

			printf("%-20d%-20d%-30s%-20d%-30s\n", d1.bolumNO, d1.dersID, d1.dersAd, d1.ogrGorNO, ogrGorAdi);
		}
	}

	fclose(dersPtr);
	fclose(ogrGorPtr);
}

void dersSil()
{
	system("cls");
	printf("Ders silme islemi... \n\n");

	dersListele();
	ders d1;
	int numara, sayac = 0, sonuc = 0;

	FILE *ptr = fopen("./data/dersler.dat", "r+b");

	printf("Silinecek ders numarasi : ");
	scanf("%d", &numara);
	while (fread(&d1, sizeof(ders), 1, ptr) == 1)
	{
		if (numara == d1.dersID && d1.durum == 1)
		{
			sonuc = 1;
			break;
		}
		sayac++;
	}
	if (sonuc == 0)
		printf("%d numarali ders bulunamadi \n", numara);
	else
	{
		rewind(ptr);
		fseek(ptr, (sayac) * sizeof(ders), 0);
		d1.durum = 0;
		fwrite(&d1, sizeof(ders), 1, ptr);
		printf("%d numarali ders kaydi silindi \n", numara);
	}
	fclose(ptr);
}

int dersMenu()
{
	int secim;
	printf("\n\tDers islemleri... \n\n");
	printf("\n\t1- Ders Ekle  \n");
	printf("\n\t2- Ders Listele \n");
	printf("\n\t3- Ders Sil \n");
	printf("\n\t0- Cikis \n");
	printf("\n\t   Seciminiz   :  ");
	scanf("%d", &secim);
	system("cls");
	return secim;
}

void dersIslemleri()
{
	int secim = dersMenu(); // Yukarıda ki ders menüsü islemi çağırılmıştır.
	while (secim != 0)
	{
		switch (secim)
		{
		case 1:
			dersEkle();
			break;
		case 2:
			dersListele();
			break;
		case 3:
			dersSil();
			break;
		default:
			printf("Hatali secim yaptiniz ! \n");
		}
		secim = dersMenu();
	}
	printf("Ders islemlerinden cikis yaptiniz ... \n");
}

void notEkle()
{
	system("cls");
	printf("Not ekleme islemi... \n\n");
	notlar n1;

	printf("Ogrenci Numarasi : ");
	scanf(" %d", &n1.ogrenciNO);
	dersListele();
	printf("Ders Numarasi : ");
	scanf(" %d", &n1.dersID);

	bolumListele();
	printf("Bolum Numarasi : ");
	scanf(" %d", &n1.bolumNO);

	ogrGorListele();
	printf("Ogretim gorevlisi numarasi : ");
	scanf(" %d", &n1.ogrGorNO);

	printf("Puani : ");
	scanf(" %f", &n1.puan);

	FILE *numPtr = fopen("./data/notNumaralari.dat", "a+b");
	int numara = 0;
	while (fread(&numara, sizeof(int), 1, numPtr))
	{
	}
	numara += 1;
	n1.notID = numara;
	fwrite(&numara, sizeof(int), 1, numPtr);
	fclose(numPtr);

	n1.durum = 1;

	FILE *ptr = fopen("./data/notlar.dat", "a+b");
	fwrite(&n1, sizeof(notlar), 1, ptr);
	fclose(ptr);
	printf("%d numarali not kaydi tamam \n", numara);
}

void notListele()
{
	system("cls");
	printf("Not listesi ... \n\n");

	notlar n1;
	ders d1;
	ogr o1;
	bolum b1;

	FILE *notPtr = fopen("./data/notlar.dat", "r+b");
	FILE *dersPtr = fopen("./data/dersler.dat", "r+b");
	FILE *ogrPtr = fopen("./data/ogrenciler.dat", "r+b");
	FILE *bolumPtr = fopen("./data/bolumler.dat", "r+b");

	printf("%-20s%-30s%-20s%-30s%-20s%-30s\n", "NOT-ID", "DERS-ADI", "OGRENCI-NO", "OGRENCI-ADI", "PUAN", "BOLUM-ADI");

	while (fread(&n1, sizeof(notlar), 1, notPtr))
	{
		if (n1.durum == 1) {
			rewind(dersPtr);
			while (fread(&d1, sizeof(ders), 1, dersPtr)) {
				if (d1.dersID == n1.dersID && d1.durum == 1) {
					rewind(ogrPtr);
					while (fread(&o1, sizeof(ogr), 1, ogrPtr)) {
						if (o1.numara == n1.ogrenciNO && o1.durum == 1) {
							rewind(bolumPtr);
							while (fread(&b1, sizeof(bolum), 1, bolumPtr)) {
								if (b1.bolumNO == n1.bolumNO && b1.durum == 1) {
									printf("%-20d%-30s%-20d%-30s%-20.2f%-30s\n", n1.notID, d1.dersAd, n1.ogrenciNO, o1.adSoyad, n1.puan, b1.bolumAd);
									break;
								}
							}
							break;
						}
					}
					break;
				}
			}
		}
	}

	fclose(notPtr);
	fclose(dersPtr);
	fclose(ogrPtr);
	fclose(bolumPtr);
}

void notSil()
{
	system("cls");
	printf("Not silme islemi... \n\n");

	notlar n1;
	int numara, sayac = 0, sonuc = 0;

	FILE *ptr = fopen("./data/notlar.dat", "r+b");

	notListele();
	printf("Numara : ");
	scanf("%d", &numara);
	while (fread(&n1, sizeof(notlar), 1, ptr) == 1)
	{
		if (numara == n1.notID)
		{
			sonuc = 1;
			break;
		}
		sayac++;
	}
	if (sonuc == 0)
		printf("%d numarali not bulunamadi \n", numara);
	else
	{
		rewind(ptr);
		fseek(ptr, (sayac) * sizeof(notlar), 0);
		n1.durum = 0;
		fwrite(&n1, sizeof(notlar), 1, ptr);
		printf("%d numarali not kaydi silindi \n", numara);
	}
	fclose(ptr);
}

int notMenu()
{
	int secim;
	printf("\n\tNot islemleri... \n\n");
	printf("\n\t1- Not Ekle  \n");
	printf("\n\t2- Not Listele \n");
	printf("\n\t3- Not Sil \n");
	printf("\n\t0- Cikis \n");
	printf("\n\t   Seciminiz   :  ");
	scanf("%d", &secim);
	system("cls");
	return secim;
}

void notIslemleri()
{
	int secim = notMenu();
	while (secim != 0)
	{
		switch (secim)
		{
		case 1:
			notEkle();
			break;
		case 2:
			notListele();
			break;
		case 3:
			notSil();
			break;
		default:
			printf("Hatali secim yaptiniz ! \n");
		}
		secim = notMenu();
	}
	printf("Not islemlerinden cikis yaptiniz ... \n");
}

int menu()
{
	int secim;
	printf("\n\tOGRENCI ISLERI OTOMASYONU\n\n");
	printf("\n\t1- OGRENCI ISLEMLERI \n");
	printf("\n\t2- OGRETIM GOREVLISI ISLEMLERI \n");
	printf("\n\t3- DERS ISLEMLERI \n");
	printf("\n\t4- NOT ISLEMLERI \n");
	printf("\n\t5- BOLUM ISLEMLERI \n");

	printf("\n\t6- OTURUMU KAPAT \n");
	printf("\n\t0- PROGRAMI KAPAT \n");
	printf("\n\t   Seciminiz   :  ");
	scanf("%d", &secim);
	system("cls");
	return secim;
}

void menuEkrani()
{
	int secim = menu();
	while (secim != 6)
	{
		switch (secim)
		{
		case 1:
			ogrIslemleri();
			break;
		case 2:
			ogrGorIslemleri();
			break;
		case 3:
			dersIslemleri();
			break;
		case 4:
			notIslemleri();
			break;
		case 5:
			bolumIslemleri();
			break;
		case 0:
			printf("Program sonlandiriliyor... \n");
			exit(0);
		default:
			printf("Hatali secim yaptiniz ! \n");
		}
		secim = menu();
	}
}

int main()
{
	dataKlasoru();

	Kullanici kullanicilar[MAX_KULLANICILAR];
	int kullaniciSayisi = 0;
	int secim;

	kullaniciBilgileriniOku(kullanicilar, &kullaniciSayisi);

	do
	{
		printf("\n\n\t\t*********************************************\n");
		printf("\t\t*                                           *\n");
		printf("\t\t*                                           *\n");
		printf("\t\t*         OGRENCI ISLERI OTOMASYONU         *\n");
		printf("\t\t*                                           *\n");
		printf("\t\t*                                           *\n");
		printf("\t\t*              \t1. KAYIT OL                 *\n");
		printf("\t\t*              \t2. GIRIS YAP                *\n");
		printf("\t\t*              \t0. CIKIS                    *\n");
		printf("\t\t*                                           *\n");
		printf("\t\t*********************************************\n");
		printf("\n\t\tSeciminiz:    ");
		scanf("%d", &secim);

		switch (secim)
		{
		case 1:
			kullaniciKayit(kullanicilar, &kullaniciSayisi);
			break;
		case 2:
		{
			int userindex = kullaniciGiris(kullanicilar, kullaniciSayisi);
			if (userindex != -1)
			{
				system("cls");
				printf("Giris basarili!\n");
				printf("                                     \n");
				printf("        ******************************************\n");
				printf("        *                                        *\n");
				printf("        *      Hosgeldin, %-20.20s   *\n", kullanicilar[userindex].kullaniciAdi);
				printf("        *                                        *\n");
				printf("        ******************************************\n");
				menuEkrani();
			}
			else
			{
				system("cls");
				printf("Giris basarisiz. Kullanici adi veya sifre hatali.\n");
			}
			break;
		}
		case 0:
			printf("Cikis yapiliyor...\n");
			break;
		default:
			system("cls");
			printf("Gecersiz secim. Lutfen tekrar deneyin.\n");
		}
	} while (secim != 0);

	printf("Programi kapattiniz... \n");

	return 0;
}