//Bu program windows visual studio gelistirme ortaminda yapilmistir.Farkli derleyicilerde hata verebilir.
//Taha Yuksel 140202028
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <fstream>
using namespace std;
struct okul { //okul bilgileri
	string okul_adi;
	string okul_turu;
	string okul_bolumu;
	int okul_baslangic;
	string okul_bitis;
	float okul_notOrtalamasi;
	struct okul *sonraki;
}; 
struct is { // is bilgileri
	string is_calistigi_yeradi;
	string is_adresi;
	string is_gorevi;
	float  is_tecrubesi;
	struct is *sonraki;
};
struct kisiler { // kisi bilgileri
	string isim;
	int yas;
	string yabanci_dil;
	string yasadigi_adres;
	string e_mail;
	string ehliyet;
	string telefon_no;
	kisiler *sag, *sol;
	int okul_sayisi;
	okul *okullar;
	int is_sayisi;
	is *isler;

}*agacKok = NULL, *gosterici=NULL;
int dosya_yaz(int gelen_sayi) //klavyeden bilgi alýnýp dosyaya yazýlmasý
{
		ofstream dosya;
		dosya.open("Kisiler.txt", ios::out | ios::app);
		string isim;
		int yas;
		string yabanci_dil;
		string yasadigi_adres;
		string e_mail;
		string ehliyet;   //Girilecek degerlerin tanýmlanmasi
		string telefon_no;
		int okul_sayisi;
		string okul_adi;
		string okul_turu;
		string okul_bolumu;
		unsigned int okul_baslangic;
		string okul_bitis;
		float okul_notOrtalamasi;

		int is_sayisi;
		string is_calistigi_yeradi;
		string is_adresi;
		string is_gorevi;
		float  is_tecrubesi;
		int sayac=0;
		
		cout << "\nIsim: ";
		cin.ignore();
		getline(cin, isim);
		dosya << isim << "\n";

		cout << "Adres: ";
		getline(cin, yasadigi_adres);
		dosya << yasadigi_adres << "\n";

		cout << "Telefon: ";
		getline(cin, telefon_no);
		dosya << telefon_no << "\n";          //dosyaya yazma islemleri

		cout << "Eposta: ";
		getline(cin, e_mail);
		dosya << e_mail << "\n";

		cout << "Dogum Tarihi: ";
		cin >> yas;
		dosya << yas << "\n";

		cout << "Bildiginiz yabanci diller(diller arasi ',' koyun): ";
		cin.ignore();
		getline(cin, yabanci_dil);
		dosya << yabanci_dil<<'\n';

		cout << "Sahip oldugunuz ehliyetler: ";
		getline(cin, ehliyet);
		dosya << ehliyet << '\n';

		cout << "Kac tane okul girmek istiyorsunuz: ";
		cin >> okul_sayisi;
		dosya << okul_sayisi << "\n";
		cout << endl;
		dosya << "\n";

		while (sayac < okul_sayisi)  // okul bilgilerinin yazilmasi
		{
			cout << "Okul Adi: ";
			cin.ignore();
			getline(cin, okul_adi);
			dosya << okul_adi << "\n";

			cout << "Okul Turu: ";
			getline(cin, okul_turu);
			dosya << okul_turu << "\n";

			cout << "Bolumu: ";
			getline(cin, okul_bolumu);
			dosya << okul_bolumu << "\n";

			cout << "Baslangic Tarihi: ";
			cin >> okul_baslangic;
			dosya << okul_baslangic << "\n";

			cout << "Bitis Tarihi(Bitmediyse 'Devam Ediyor' Yaz): ";
			cin.ignore();
			getline(cin, okul_bitis);
			dosya << okul_bitis << "\n";

			cout << "Not Ortalaman: ";
			cin >> okul_notOrtalamasi;
			dosya << okul_notOrtalamasi << "\n",

			sayac++;
			cout << endl;
			dosya << "\n";
		}
		sayac = 0;
		cout << "Kac yerde calistiniz: ";
		cin >> is_sayisi;
		dosya << is_sayisi << "\n";

		cout << endl;
		dosya << "\n";

		while (sayac < is_sayisi) // is bilgilerinin yazilmasi
		{
			cout << "Calistiginiz Yer Adi: ";
			cin.ignore();
			getline(cin, is_calistigi_yeradi);
			dosya << is_calistigi_yeradi << "\n";

			cout << "Is Adresi: ";
			getline(cin, is_adresi);
			dosya << is_adresi << "\n";

			cout << "Ordaki Gorevin: ";
			getline(cin, is_gorevi);
			dosya << is_gorevi << "\n";

			cout << "Tecrube Suren: ";
			cin >> is_tecrubesi;
			dosya << is_tecrubesi << "\n";

			sayac++;
			cout << endl;
			dosya << "\n";
		}

		dosya  <<"_______________________Kisi Kayitlari Girildi______________________\n";
		gelen_sayi++;
		return gelen_sayi;
}
int ekle(int gelen) //dosyadan okuma islemi yapýlýk agacdaki dugumlere bilgi girilmesi
{   
	ifstream dosya;
	int pozisyon; //foksiyon icerisindeki kullanilicak degiskenlerin tanimlanmasi
	string dummy;
	int sayac=0;
	dosya.open("kisiler.txt"); //dosya acilmasi
	int sayi=0,i=0;
	string yeniIsim;
	if (agacKok == NULL) // agac bossa
	{
		agacKok = new struct kisiler;
		getline(dosya, agacKok->isim);
		getline(dosya, agacKok->yasadigi_adres);
		getline(dosya, agacKok->telefon_no);
		getline(dosya, agacKok->e_mail);
		dosya >> agacKok->yas;
		dosya.ignore();
		getline(dosya, agacKok->yabanci_dil);
		getline(dosya, agacKok->ehliyet);
		dosya >> agacKok->okul_sayisi;
		okul *yeniokul;
		okul *geciciokul = nullptr; //Diger derleyicilerde hata verme durumunda 'nullptr' i NULL diye degistirin
		agacKok->okullar = NULL;
		while (sayac < agacKok->okul_sayisi) // okul bilgilerinin girilmesi
		{
			yeniokul = new okul;
			yeniokul->sonraki = NULL;
			if (agacKok->okullar == NULL)
			{
				agacKok->okullar = yeniokul;
			}
			else
			{
				geciciokul->sonraki = yeniokul;
			}
			dosya.ignore();
			dosya.ignore();
			getline(dosya, yeniokul->okul_adi);
			getline(dosya, yeniokul->okul_turu);
			getline(dosya, yeniokul->okul_bolumu);
			dosya >> yeniokul->okul_baslangic;
			dosya.ignore();
			getline(dosya, yeniokul->okul_bitis);
			dosya >> yeniokul->okul_notOrtalamasi;

			geciciokul = yeniokul;
			sayac++;
		}
		sayac = 0;
		dosya.ignore();
		dosya.ignore();
		dosya >> agacKok->is_sayisi;
		is *yeniIs;
		is *geciciIs = nullptr; //Diger derleyicilerde hata verme durumunda 'nullptr' i NULL diye degistirin
		agacKok->isler = NULL;
		while (sayac < agacKok->is_sayisi) // is bilgilerinin girilmesi
		{
			yeniIs = new is;
			yeniIs->sonraki = NULL;
			if (agacKok->isler == NULL)
			{
				agacKok->isler = yeniIs;
			}
			else
				geciciIs->sonraki = yeniIs;

			dosya.ignore();
			dosya.ignore();
			getline(dosya, yeniIs->is_calistigi_yeradi);
			getline(dosya, yeniIs->is_adresi);
			getline(dosya, yeniIs->is_gorevi);
			dosya >> yeniIs->is_tecrubesi;

			geciciIs = yeniIs;
			sayac++;
		}
		dosya.ignore();
		dosya.ignore();
		agacKok->sag = NULL;
		agacKok->sol = NULL;
		pozisyon = dosya.tellg(); //okudugumuz dosyadaki en son kaldigimiz indexi atama islemi
		return pozisyon; 
	}
	else // agac dolu ise
	{
		dosya.seekg(gelen,ios::beg); //en sonki galdigimiz indexe gore ayarlama
		getline(dosya, dummy);
		gosterici = agacKok;
		getline(dosya, yeniIsim);
		for (sayi = 0; sayi != -1; sayi++) // isimleri karsilastirma
		{
			if (yeniIsim[sayi] > gosterici->isim[sayi])
			{
				i = 1;
				break;
			}
			if (yeniIsim[sayi] < gosterici->isim[sayi])
			{
				i = 2;
				break;
			}
			if (yeniIsim[sayi] == gosterici->isim[sayi])
			{
				sayi++;
			}
		}
		while (true)
		{
			if ( i == 1) //en sonki isim daha buyukse
			{
				if (gosterici->sag == NULL) //agacin sagi bos mu
				{
					gosterici->sag = new  kisiler;  //bilgilerin sag tarafa girilmesi
					gosterici = gosterici->sag;
					gosterici->isim = yeniIsim;
					getline(dosya, gosterici->yasadigi_adres);
					getline(dosya, gosterici->telefon_no);
					getline(dosya, gosterici->e_mail);
					dosya >> gosterici->yas;
					dosya.ignore();
					getline(dosya, gosterici->yabanci_dil);
					getline(dosya, gosterici->ehliyet);
					dosya >> gosterici->okul_sayisi;
					okul *yeniokul;
					okul *geciciokul = nullptr; //Diger derleyicilerde hata verme durumunda 'nullptr' i NULL diye degistirin
					gosterici->okullar = NULL;
					while (sayac < gosterici->okul_sayisi) //okul bilgilerinin girilmesi
					{
						yeniokul = new okul;
						yeniokul->sonraki = NULL;
						if (gosterici->okullar == NULL)
						{
							gosterici->okullar = yeniokul;
						}
						else
						{
							geciciokul->sonraki = yeniokul;
						}
						dosya.ignore();
						dosya.ignore();
						getline(dosya, yeniokul->okul_adi);
						getline(dosya, yeniokul->okul_turu);
						getline(dosya, yeniokul->okul_bolumu);
						dosya >> yeniokul->okul_baslangic;
						dosya.ignore();
						getline(dosya, yeniokul->okul_bitis);
						dosya >> yeniokul->okul_notOrtalamasi;

						geciciokul = yeniokul;
						sayac++;
					}
					sayac = 0;
					dosya.ignore();
					dosya.ignore();
					dosya >> gosterici->is_sayisi;
					is *yeniIs;
					is *geciciIs = nullptr;
					gosterici->isler = NULL;
					while (sayac < gosterici->is_sayisi) //is bilgilerinin girilmesi
					{
						yeniIs = new is;
						yeniIs->sonraki = NULL;
						if (gosterici->isler == NULL)
						{
							gosterici->isler = yeniIs;
						}
						else
							geciciIs->sonraki = yeniIs;

						dosya.ignore();
						dosya.ignore();
						getline(dosya, yeniIs->is_calistigi_yeradi);
						getline(dosya, yeniIs->is_adresi);
						getline(dosya, yeniIs->is_gorevi);
						dosya >> yeniIs->is_tecrubesi;

						geciciIs = yeniIs;
						sayac++;
					}
					dosya.ignore();
					dosya.ignore();
					gosterici->sag = NULL;
					gosterici->sol = NULL;
					pozisyon = dosya.tellg(); //dosyadaki en sonki indexi atama
					return pozisyon;
				}
				else if(gosterici->sag!=NULL) //sag doluysa bir sonraki saga git
				{
					gosterici = gosterici->sag;
				}
			}
			else if(i == 2) //gelen isim bir oncekinden kucukse
			{
				if (gosterici->sol == NULL) //sol taraf bos mu
				{
					gosterici->sol = new  kisiler; //bilgilerin sol tarafa girilmesi
					gosterici = gosterici->sol;
					gosterici->isim = yeniIsim;
					getline(dosya, gosterici->yasadigi_adres);
					getline(dosya, gosterici->telefon_no);
					getline(dosya, gosterici->e_mail);
					dosya >> gosterici->yas;
					dosya.ignore();
					getline(dosya, gosterici->yabanci_dil);
					getline(dosya, gosterici->ehliyet);
					dosya >> gosterici->okul_sayisi;
					okul *yeniokul;
					okul *geciciokul = nullptr; //Diger derleyicilerde hata verme durumunda 'nullptr' i NULL diye degistirin
					gosterici->okullar = NULL;
					sayac = 0;
					while (sayac < gosterici->okul_sayisi) //okul bilgilerinin girilmesi
					{
						yeniokul = new okul;
						yeniokul->sonraki = NULL;
						if (gosterici->okullar == NULL)
						{
							gosterici->okullar = yeniokul;
						}
						else
						{
							geciciokul->sonraki = yeniokul;
						}
						dosya.ignore();
						dosya.ignore();
						getline(dosya, yeniokul->okul_adi);
						getline(dosya, yeniokul->okul_turu);
						getline(dosya, yeniokul->okul_bolumu);
						dosya >> yeniokul->okul_baslangic;
						dosya.ignore();
						getline(dosya, yeniokul->okul_bitis);
						dosya >> yeniokul->okul_notOrtalamasi;

						geciciokul = yeniokul;
						sayac++;
					}
					sayac = 0;
					dosya.ignore();
					dosya.ignore();
					dosya >> gosterici->is_sayisi;
					is *yeniIs;
					is *geciciIs = nullptr; //Diger derleyicilerde hata verme durumunda 'nullptr' i NULL diye degistirin
					gosterici->isler = NULL;
					while (sayac < gosterici->is_sayisi) //is bilgilerinin girilmesi
					{
						yeniIs = new is;
						yeniIs->sonraki = NULL;
						if (gosterici->isler == NULL)
						{
							gosterici->isler = yeniIs;
						}
						else
							geciciIs->sonraki = yeniIs;

						dosya.ignore();
						dosya.ignore();
						getline(dosya, yeniIs->is_calistigi_yeradi);
						getline(dosya, yeniIs->is_adresi);
						getline(dosya, yeniIs->is_gorevi);
						dosya >> yeniIs->is_tecrubesi;

						geciciIs = yeniIs;
						sayac++;
					}
					dosya.ignore();
					dosya.ignore();
					gosterici->sag = NULL;
					gosterici->sol = NULL;
					pozisyon = dosya.tellg(); //dosyadaki en sonki indexi atama
					return pozisyon;
				}
				else if(gosterici->sol!=NULL) //sol taraf dolu is bir sonrakine gec
				{
					gosterici = gosterici->sol;
				}
			}
		}
	}
}
void yazEkrana(struct kisiler *gelen) //listeleden gelen kisis ekrana yazdirma
{
	ofstream dosya;
	dosya.open("Listele.txt", ios::out | ios::app);
	cout << gelen->isim<<endl;
	dosya << gelen->isim << "\n";
}
void listele(kisiler *goster,int sayi)
{
	if (sayi == 1) { // inorder
		if (goster != NULL)
		{
			listele(goster->sol,1);
			yazEkrana(goster);
			listele(goster->sag,1);
		}
	}
	if (sayi == 2) { // preorder listeme
		if (goster != NULL)
		{
			yazEkrana(goster);
			listele(goster->sol,2);
			listele(goster->sag,2);
		}
	}
	if (sayi == 3) { // postorder listeleme
		if (goster != NULL)
		{
			listele(goster->sol,3);
			listele(goster->sag,3);
			yazEkrana(goster);
		}
	}
}
void bul(struct kisiler *gelenKisi,string aranan,int i=0) // kisilerin bilgilerini goruntuleme foksiyonu    
{
	int sayac = 0;
	if ( !gelenKisi->isim.compare(aranan) && i==0 ) // kullanicinin kendini goruntulemesi
	{
		cout << "\nIsim: " << gelenKisi->isim << endl; //kisi bilgilerinin goruntulenmesi
		cout << "Adres: " << gelenKisi->yasadigi_adres << endl;
		cout << "Telefon no: " << gelenKisi->telefon_no << endl;
		cout << "E-mail: " << gelenKisi->e_mail << endl;
		cout << "Dogum Tarihi: " << gelenKisi->yas << endl;
		cout << "Yabanci Dilleri: " << gelenKisi->yabanci_dil << "  dillerini biliyor. "<< endl;
		cout << "Sahip oldugu ehliyet(ler): " << gelenKisi->ehliyet << endl;
		cout << "\nOkudugu okullar:\n" << endl;
		okul *gosterici;
		gosterici = gelenKisi->okullar;
		while (sayac < gelenKisi->okul_sayisi)
		{
			cout << "Okul Adi:  " << gosterici->okul_adi << endl;
			cout << "Turu: " << gosterici->okul_turu << endl;
			cout << "Okul Bolumu: " << gosterici->okul_bolumu << endl;
			cout << "Okul Baslangic Tarihi: " << gosterici->okul_baslangic << endl;
			cout << "Okul Bitis Tarihi: " << gosterici->okul_bitis << endl;
			cout << "Okul Not Ortalamasi: " << gosterici->okul_notOrtalamasi << endl;
			sayac++;
			gosterici = gosterici->sonraki;
			cout << endl;
		}
		sayac = 0;
		cout << "\nCalistigi yerler:\n" << endl;
		is *goster;
		goster = gelenKisi->isler;
		while (sayac < gelenKisi->is_sayisi)
		{
			cout << "Calistigi isyeri: " << goster->is_calistigi_yeradi << endl;
			cout << "Is Adresi: " << goster->is_adresi << endl;
			cout << "Gorevi: " << goster->is_gorevi << endl;
			cout << "Tecrubesi: " << goster->is_tecrubesi << endl;
			sayac++;
			goster = goster->sonraki;
			cout << endl;
		}

		cout << "\nKisi Bilgileri Goruntulendi !" << endl; 
	}
	if (i == 1)  // tum kisileri goruntuleme
	{
		ofstream tum_bilgi; // dosya tanimlanmasi dosyaya yazilmasi
		tum_bilgi.open("Tum Bilgiler.txt", ios::out | ios::app);
		cout << "\nIsim: " << gelenKisi->isim << endl;
		tum_bilgi << "\nIsim: " << gelenKisi->isim << endl;

		cout << "Adres: " << gelenKisi->yasadigi_adres << endl;
		tum_bilgi << "\nIsim: " << gelenKisi->yasadigi_adres << endl;

		cout << "Telefon no: " << gelenKisi->telefon_no << endl;
		tum_bilgi << "Telefon no: " << gelenKisi->telefon_no << endl;

		cout << "E-mail: " << gelenKisi->e_mail << endl;
		tum_bilgi << "E-mail: " << gelenKisi->e_mail << endl;

		cout << "Dogum Tarihi: " << gelenKisi->yas << endl;
		tum_bilgi << "Dogum Tarihi: " << gelenKisi->yas << endl;

		cout << "Yabanci Dilleri: " << gelenKisi->yabanci_dil << "  dillerini biliyor. " << endl;
		tum_bilgi << "Yabanci Dilleri: " << gelenKisi->yabanci_dil << "  dillerini biliyor. " << endl;

		cout << "Sahip oldugu ehliyet(ler): " << gelenKisi->ehliyet << endl;
		tum_bilgi << "Sahip oldugu ehliyet(ler): " << gelenKisi->ehliyet << endl;

		cout << "\nOkudugu okullar:\n" << endl;
		tum_bilgi << "\nOkudugu okullar:\n" << endl;
		okul *gosterici;
		gosterici = gelenKisi->okullar;

		while (sayac < gelenKisi->okul_sayisi)
		{
			cout << "Okul Adi:  " << gosterici->okul_adi << endl;
			tum_bilgi << "Okul Adi:  " << gosterici->okul_adi << endl;

			cout << "Turu: " << gosterici->okul_turu << endl;
			tum_bilgi << "Turu: " << gosterici->okul_turu << endl;

			cout << "Okul Bolumu: " << gosterici->okul_bolumu << endl;
			tum_bilgi << "Okul Bolumu: " << gosterici->okul_bolumu << endl;

			cout << "Okul Baslangic Tarihi: " << gosterici->okul_baslangic << endl;
			tum_bilgi << "Okul Baslangic Tarihi: " << gosterici->okul_baslangic << endl;

			cout << "Okul Bitis Tarihi: " << gosterici->okul_bitis << endl;
			tum_bilgi << "Okul Bitis Tarihi: " << gosterici->okul_bitis << endl;

			cout << "Okul Not Ortalamasi: " << gosterici->okul_notOrtalamasi << endl;
			tum_bilgi << "Okul Not Ortalamasi: " << gosterici->okul_notOrtalamasi << endl;

			sayac++;
			gosterici = gosterici->sonraki;
			cout << endl;
			tum_bilgi << endl;
		}
		sayac = 0;
		cout << "\nCalistigi yerler:\n" << endl;
		tum_bilgi << "\nCalistigi yerler:\n" << endl;
		is *goster;
		goster = gelenKisi->isler;
		while (sayac < gelenKisi->is_sayisi)
		{
			cout << "Calistigi isyeri: " << goster->is_calistigi_yeradi << endl;
			tum_bilgi << "Calistigi isyeri: " << goster->is_calistigi_yeradi << endl;

			cout << "Is Adresi: " << goster->is_adresi << endl;
			tum_bilgi << "Is Adresi: " << goster->is_adresi << endl;

			cout << "Gorevi: " << goster->is_gorevi << endl;
			tum_bilgi << "Gorevi: " << goster->is_gorevi << endl;

			cout << "Tecrubesi: " << goster->is_tecrubesi << endl;
			tum_bilgi << "Tecrubesi: " << goster->is_tecrubesi << endl;
			sayac++;
			goster = goster->sonraki;
			cout << endl;
			tum_bilgi << endl;
		}
		cout << "\nKisi Bilgileri Goruntulendi !" << endl;
		tum_bilgi << "\n_______________Kisi Bilgileri Yazildi !________________ !" << endl;
	}
	if (i == 2 && !gelenKisi->isim.compare(aranan)) // is verenin kisi aramasi
	{
		ofstream Tek_bilgi; //dosya tanimlanmasi
		Tek_bilgi.open("Tek Kisinin Bilgisi.txt");
		cout << "\nIsim: " << gelenKisi->isim << endl;
		Tek_bilgi << "\nIsim: " << gelenKisi->isim << endl; //dosyaya yazilmasi

		cout << "Adres: " << gelenKisi->yasadigi_adres << endl;
		Tek_bilgi << "\nIsim: " << gelenKisi->yasadigi_adres << endl;

		cout << "Telefon no: " << gelenKisi->telefon_no << endl;
		Tek_bilgi << "Telefon no: " << gelenKisi->telefon_no << endl;

		cout << "E-mail: " << gelenKisi->e_mail << endl;
		Tek_bilgi << "E-mail: " << gelenKisi->e_mail << endl;

		cout << "Dogum Tarihi: " << gelenKisi->yas << endl;
		Tek_bilgi << "Dogum Tarihi: " << gelenKisi->yas << endl;

		cout << "Yabanci Dilleri: " << gelenKisi->yabanci_dil << "  dillerini biliyor. " << endl;
		Tek_bilgi << "Yabanci Dilleri: " << gelenKisi->yabanci_dil << "  dillerini biliyor. " << endl;

		cout << "Sahip oldugu ehliyet(ler): " << gelenKisi->ehliyet << endl;
		Tek_bilgi << "Sahip oldugu ehliyet(ler): " << gelenKisi->ehliyet << endl;

		cout << "\nOkudugu okullar:\n" << endl;
		Tek_bilgi << "\nOkudugu okullar:\n" << endl;
		okul *gosterici;
		gosterici = gelenKisi->okullar;
		while (sayac < gelenKisi->okul_sayisi)
		{
			cout << "Okul Adi:  " << gosterici->okul_adi << endl;
			Tek_bilgi << "Okul Adi:  " << gosterici->okul_adi << endl;

			cout << "Turu: " << gosterici->okul_turu << endl;
			Tek_bilgi << "Turu: " << gosterici->okul_turu << endl;

			cout << "Okul Bolumu: " << gosterici->okul_bolumu << endl;
			Tek_bilgi << "Okul Bolumu: " << gosterici->okul_bolumu << endl;

			cout << "Okul Baslangic Tarihi: " << gosterici->okul_baslangic << endl;
			Tek_bilgi << "Okul Baslangic Tarihi: " << gosterici->okul_baslangic << endl;

			cout << "Okul Bitis Tarihi: " << gosterici->okul_bitis << endl;
			Tek_bilgi << "Okul Bitis Tarihi: " << gosterici->okul_bitis << endl;

			cout << "Okul Not Ortalamasi: " << gosterici->okul_notOrtalamasi << endl;
			Tek_bilgi << "Okul Not Ortalamasi: " << gosterici->okul_notOrtalamasi << endl;

			sayac++;
			gosterici = gosterici->sonraki;
			cout << endl;
			Tek_bilgi << endl;
		}
		sayac = 0;
		cout << "\nCalistigi yerler:\n" << endl;
		Tek_bilgi << "\nCalistigi yerler:\n" << endl;
		is *goster;
		goster = gelenKisi->isler;
		while (sayac < gelenKisi->is_sayisi)
		{
			cout << "Calistigi isyeri: " << goster->is_calistigi_yeradi << endl;
			Tek_bilgi << "Calistigi isyeri: " << goster->is_calistigi_yeradi << endl;

			cout << "Is Adresi: " << goster->is_adresi << endl;
			Tek_bilgi << "Is Adresi: " << goster->is_adresi << endl;

			cout << "Gorevi: " << goster->is_gorevi << endl;
			Tek_bilgi << "Gorevi: " << goster->is_gorevi << endl;

			cout << "Tecrubesi: " << goster->is_tecrubesi << endl;
			Tek_bilgi << "Tecrubesi: " << goster->is_tecrubesi << endl;
			sayac++;
			goster = goster->sonraki;
			cout << endl;
		}

		cout << "\nKisi Bilgileri Goruntulendi !" << endl;
		Tek_bilgi << "\n_______________Kisi Bilgileri Yazildi !________________ !" << endl;
	}

}
void arama(kisiler *gelen,string aranan,int i=0) // kisilerin bilgilerini arama foksiyonu
{
	if (gelen != NULL) {
		arama(gelen->sol, aranan,i);
		bul(gelen, aranan,i);
		arama(gelen->sag, aranan,i);
	}
}
void duzelt(kisiler *gelenKisi, string aranan) // kisi bilgilerini guncelleme foksiyonu
{
	if (!gelenKisi->isim.compare(aranan))
	{
		cout << "\nBILGILERI GUNCELLE !" << endl;
		int sayac = 0;
		cout << "Adres: ";
		getline(cin, gelenKisi->yasadigi_adres);

		cout << "Telefon: ";
		getline(cin, gelenKisi->telefon_no);

		cout << "Eposta: ";
		getline(cin, gelenKisi->e_mail);

		cout << "Dogum Tarihi: ";
		cin >> gelenKisi->yas;

		cout << "Bildiginiz yabanci diller: ";
		cin.ignore();
		getline(cin, gelenKisi->yabanci_dil);

		cout << "Sahip oldugunuz ehliyetler: ";
		getline(cin, gelenKisi->ehliyet);

		cout << "Kac tane okul girmek istiyorsunuz: ";
		cin >> gelenKisi->okul_sayisi;

		cout << endl;

		okul *yeniokul;
		okul *geciciokul = nullptr; //Diger derleyicilerde hata verme durumunda 'nullptr' i NULL diye degistirin
		gelenKisi->okullar = NULL;
		while (sayac < agacKok->okul_sayisi)
		{
			yeniokul = new okul;
			yeniokul->sonraki = NULL;
			if (agacKok->okullar == NULL)
			{
				agacKok->okullar = yeniokul;
			}
			else
			{
				geciciokul->sonraki = yeniokul;
			}
			cout << "Okul Adi:";
			cin.ignore();
			getline(cin, yeniokul->okul_adi);
			cout << "Turu:";
			getline(cin, yeniokul->okul_turu);
			cout << "Bolumu:";
			getline(cin, yeniokul->okul_bolumu);
			cout << "Okul Baslangic:";
			cin >> yeniokul->okul_baslangic;
			cout << "Okul Bitis:";
			cin.ignore();
			getline(cin, yeniokul->okul_bitis);
			cout << "Not Ortalamasi:";
			cin >> yeniokul->okul_notOrtalamasi;

			geciciokul = yeniokul;
			sayac++;
			cout << endl;
		}
		sayac = 0;
		cout << "Kac yerde calistiniz: ";
		cin >> gelenKisi->is_sayisi;

		cout << endl;

		is *yeniIs;
		is *geciciIs = nullptr; //Diger derleyicilerde hata verme durumunda 'nullptr' i NULL diye degistirin
		gelenKisi->isler = NULL;
		while (sayac < agacKok->is_sayisi)
		{
			yeniIs = new is;
			yeniIs->sonraki = NULL;
			if (agacKok->isler == NULL)
			{
				agacKok->isler = yeniIs;
			}
			else
				geciciIs->sonraki = yeniIs;
			cout << "Calistiginiz Yer Adi: ";
			cin.ignore();
			getline(cin, yeniIs->is_calistigi_yeradi);
			cout << "Is Adresi: ";
			getline(cin, yeniIs->is_adresi);
			cout << "Goreviniz: ";
			getline(cin, yeniIs->is_gorevi);
			cout << "Tecrubeniz: ";
			cin >> yeniIs->is_tecrubesi;
			geciciIs = yeniIs;
			sayac++;
			cout << endl;
		}
		cout << "Kisi Bilgileri Guncellendi !" << endl;
	}
}
void guncelleme(kisiler *gelen, string aranan) //kisi bilgilerini guncellemek icin kisi arama foksiyonu
{
	if (gelen != NULL)
	{
		guncelleme(gelen->sol, aranan);
		duzelt(gelen, aranan);
		guncelleme(gelen->sag, aranan);
	}
}
void yok_et(kisiler *gelen,string yokEt)  // Dugum silme foksiyonu
{
	
	kisiler *gosterici, *p, *yo , *destroy ,*t ; //gerekli isaretcilerin tanimlanmasi
	if (gelen == NULL) // agac bos mu
	{
		cout << "Agac zaten Bos !" << endl;
		return;
	}
	gosterici = gelen;
	p = NULL;
	while (gosterici != NULL && gosterici->isim.compare(yokEt))
	{
		p = gosterici;
		if (yokEt[0] > gosterici->isim[0])
		{
			gosterici = gosterici->sag;
		}
		else
		{
			gosterici = gosterici->sol;
		}
	}
	if (gosterici == NULL)
	{
		cout << "\nAranan Bulanamadi " << endl;
		return;
	}
	if (gosterici->sag != NULL && gosterici->sol != NULL)
	{
		yo = gosterici->sol;
		t = gosterici;
		while(yo->sag != NULL)
		{
			t = yo;
			yo = yo->sag;
		}
		cout << gosterici->okul_sayisi << endl;
		cout << gosterici->is_sayisi << endl;
		cout << yo->okul_sayisi <<endl;
		int say = 0;
		gosterici->isim = yo->isim;
		gosterici->isim = yo->isim;
		gosterici->yas = yo->yas;
		gosterici->yabanci_dil = yo->yabanci_dil;
		gosterici->yasadigi_adres = yo->yasadigi_adres;
		gosterici->e_mail = yo->e_mail;
		gosterici->ehliyet = yo->ehliyet;
		gosterici->telefon_no = yo->telefon_no;
		gosterici->okul_sayisi = yo->okul_sayisi;
		while (say < gosterici->okul_sayisi)
		{
			gosterici->okullar->okul_adi = yo->okullar->okul_adi;
			gosterici->okullar->okul_baslangic = yo->okullar->okul_baslangic;
			gosterici->okullar->okul_bitis = yo->okullar->okul_bitis;
			gosterici->okullar->okul_bolumu = yo->okullar->okul_bolumu;
			gosterici->okullar->okul_turu = yo->okullar->okul_turu;
			gosterici->okullar = gosterici->okullar->sonraki;
			yo->okullar = yo->okullar->sonraki;
			say++;
		}
		say = 0;
		gosterici->is_sayisi = yo->is_sayisi;
		while (say < gosterici->is_sayisi)
		{
			gosterici->isler->is_adresi = yo->isler->is_adresi;
			gosterici->isler->is_calistigi_yeradi = yo->isler->is_calistigi_yeradi;
			gosterici->isler->is_gorevi = yo->isler->is_gorevi;
			gosterici->isler->is_tecrubesi = yo->isler->is_tecrubesi;
			gosterici->isler = gosterici->isler->sonraki;
			yo->isler = yo->isler->sonraki;
			say++;
		}

		gosterici = yo;
		p = t;
	}
	if (gosterici->sol != NULL)
	{
		destroy = gosterici->sol;
	}
	else
	{
		destroy = gosterici->sag;
	}

	if (gosterici == gelen)
	{
		agacKok = destroy;
	}
	else
	{
		if (gosterici == p->sol)
		{
			p->sol = destroy;
		}
		else
		{
			p->sag = destroy;
		}
	}
	free(gosterici);
	cout << "Kisi Yok Edildi By By" << endl;
}
void ozellik_arama(kisiler *gelenKisi,int i=0,float deneyim=0,int yas=0,string ehliyet="",int lisans=0,int ydil=0,int eng=0,int tecrube=0,int filtre=0)
{ //kisilerde ozellik bulunmasi
	if (i == 1) { // en az lisans mezunlari tek filtreleme
		ofstream enAz_lisans;
		enAz_lisans.open("Lisans.txt", ios::ios_base::app);
		string lisans = "lisans";
		string yuksek_lisans = "yuksek lisans";
		string doktora = "doktora";
		okul *gosterici;
		string dummy;
		gosterici = gelenKisi->okullar;
		int sayac = 0;
		while (sayac < gelenKisi->okul_sayisi) {
			dummy = gosterici->okul_turu;
			transform(dummy.begin(), dummy.end(), dummy.begin(), ::towlower);
			if (!dummy.compare(lisans))
			{
				cout << gelenKisi->isim << endl;
				enAz_lisans << gelenKisi->isim << endl;
				break;
			}
			else if (!dummy.compare(yuksek_lisans))
			{
				cout << gelenKisi->isim << endl;
				enAz_lisans << gelenKisi->isim << endl;
				break;
			}
			else if (!dummy.compare(doktora))
			{
				cout << gelenKisi->isim << endl;
				enAz_lisans << gelenKisi->isim << endl;
				break;
			}
			gosterici = gosterici->sonraki;
			sayac++;
		}
	}
	if (i == 2) // ingilizce bilenler tek filtreleme
	{
		ofstream eng_bilenler;
		eng_bilenler.open("Ingilizce Bilenler.txt", ios::ios_base::app);
		string ingilizce = "ingilizce";
		string dummy = gelenKisi->yabanci_dil;
		transform(dummy.begin(), dummy.end(), dummy.begin(), ::towlower);
		if (dummy.find(ingilizce) != string::npos)
		{
			cout << gelenKisi->isim << endl;
			eng_bilenler << gelenKisi->isim << endl;
		}
	}
	if (i == 3) // birden cok yabanci dil bilenler tek filtreleme
	{
		ofstream fazla_yabanciDil;
		int sayac = 0;
		fazla_yabanciDil.open("Birden Fazla Yabanci Dil Bilenler.txt", ios::ios_base::app);
		string dummy = gelenKisi->yabanci_dil;
		dummy[dummy.length()-1] = ',';
		int i;
		for (i = 0; i <= dummy.length()-1; i++)
		{
			if (dummy[i] == ',')
			{
				sayac++;
			}
		}
		if (sayac > 1)
		{
			cout << gelenKisi->isim << " " << sayac << " tane dil biliyor." << endl;
			fazla_yabanciDil << gelenKisi->isim << " " << sayac << " tane dil biliyor." << endl;
		}

	}
	if (i == 4) // Secilen deneyim suresine gore listeleme tek filtreleme
	{
		ofstream tecrube;
		tecrube.open("Girilen deneyim.txt", ios::ios_base::app);
		is *ptr;
		ptr = gelenKisi->isler;
		float toplam = 0;
		int say = 0;
		while (say < gelenKisi->is_sayisi)
		{
			toplam = toplam + ptr->is_tecrubesi;
			ptr = ptr->sonraki;
			say++;
		}

		if (toplam == deneyim)
		{
			tecrube << gelenKisi->isim << endl;
			cout << gelenKisi->isim << endl;
		}
	}
	if (i == 5) // deneyimsiz kisiler tek filtreleme
	{
		ofstream php;
		php.open("deneyimsiz.txt", ios::ios_base::app);
		if (gelenKisi->is_sayisi == 0)
		{
			cout << gelenKisi->isim << endl;

			php << gelenKisi->isim << endl;
		}
		
	}
	if (i == 6) // girilen yasa gore tek filtreleme
	{
		ofstream yil_hesabi;
		yil_hesabi.open("yasa gore.txt", ios::ios_base::app);
		int fark;
		fark = 2016 - gelenKisi->yas;
		if (yas > fark)
		{
			cout << gelenKisi->isim << endl;

			yil_hesabi << gelenKisi->isim << endl;
		}
	}
	if (i == 7) // girilen ehliyete gore tek filtreleme
	{
		ofstream son_samuray;
		son_samuray.open("ehliyet.txt", ios::ios_base::app);
		string dummy = gelenKisi->ehliyet;
		transform(ehliyet.begin(), ehliyet.end(), ehliyet.begin(), ::towlower);
		transform(dummy.begin(), dummy.end(), dummy.begin(), ::towlower);
		if (dummy.find(ehliyet) != string::npos)
		{
			cout << gelenKisi->isim << endl;
			son_samuray << gelenKisi->isim << endl;
		}

	}
	if (i == 8) // coklu filtreleme
	{
		ofstream filtre_cok;
		int say = 0,sayac=0,onemsiz=0;
		float toplam = 0;
		is *yeni;
		yeni = gelenKisi->isler;

		okul *ptr;
		string dummy;
		ptr = gelenKisi->okullar;

		filtre_cok.open("coklu listeleme.txt", ios::ios_base::app);
		if (tecrube == 1) //tecrube istenmis mi
		{
			if (deneyim == 0) // deneyimi yok sa
			{
				if (deneyim == gelenKisi->is_sayisi)
				{
					say++;
				}
			}
			else // deneyimi varsa
			{
				while (sayac < gelenKisi->is_sayisi)
				{
					toplam = toplam + yeni->is_tecrubesi;
					yeni = yeni->sonraki;
					sayac++;
				}
				if (toplam == deneyim)
				{
					say++;
				}
			}
		}
		sayac = 0;
		if (yas != 0) //yasa gore istenmis mi
		{
			onemsiz = 2016 - gelenKisi->yas;
			if (onemsiz < yas)
			{
				say++;
			}
		}
		if (ehliyet.compare("")) // ehliyet istenmis mi
		{
			string dummy = gelenKisi->ehliyet;
			transform(ehliyet.begin(), ehliyet.end(), ehliyet.begin(), ::towlower);
			transform(dummy.begin(), dummy.end(), dummy.begin(), ::towlower);
			if (dummy.find(ehliyet) != string::npos)
			{
				say++;
			}
		}
		if (lisans == 1) // lisanas mezunu istenmis mi
		{
			string lisans = "lisans";
			string yuksek_lisans = "yuksek lisans";
			string doktora = "doktora";
			string dummy;
			while (sayac < gelenKisi->okul_sayisi) {
				dummy = ptr->okul_turu;
				transform(dummy.begin(), dummy.end(), dummy.begin(), ::towlower);
				if (!dummy.compare(lisans))
				{
					say++;
					break;
				}
				else if (!dummy.compare(yuksek_lisans))
				{
					say++;
					break;
				}
				else if (!dummy.compare(doktora))
				{
					say++;
					break;
				}
				ptr = ptr->sonraki;
				sayac++;
			}
		}
		sayac = 0;
			if (ydil == 1) // yabanci dil istenmis mi
			{
				string dummy = gelenKisi->yabanci_dil;
				dummy[dummy.length() - 1] = ',';
				int i;
				for (i = 0; i <= dummy.length() - 1; i++)
				{
					if (dummy[i] == ',')
					{
						sayac++;
					}
				}
				if (sayac > 1)
				{
					say++;
				}
			}
			if (eng == 1) //ingilizce istenmis mi
			{
				string ingilizce = "ingilizce";
				string dummy = gelenKisi->yabanci_dil;
				transform(dummy.begin(), dummy.end(), dummy.begin(), ::towlower);
				if (dummy.find(ingilizce) != string::npos)
				{
					say++;
				}
			}
			if (say == filtre) //istedigi butun ozellikler bulundu mu
			{
				cout << gelenKisi->isim << endl;
				filtre_cok << gelenKisi->isim << endl;
			}
	}
}
void ozellik_bul(kisiler *gelen,int i=0,float deneyim_suresi=0,int year=0,string ehliyet="",int lisans=0,int ydil=0,int eng=0,int tecrube=0,int filtre=0)
{ // filtrelemek icin kisi arama
	if (gelen != NULL) {
		ozellik_bul(gelen->sol,i,deneyim_suresi,year,ehliyet,lisans,ydil,eng,tecrube,filtre);
		ozellik_arama(gelen,i,deneyim_suresi,year,ehliyet,lisans,ydil,eng,tecrube,filtre);
		ozellik_bul(gelen->sag,i,deneyim_suresi,year,ehliyet,lisans,ydil,eng,tecrube,filtre);
	}

}
int main()
{
	remove("Kisiler.txt");
	remove("Listele.txt");
	remove("Tek Kisinin Bilgisi.txt");
	remove("Tum Bilgiler.txt");
	remove("Lisans.txt");  //baslangicta dosya temizlenmesi
	remove("Ingilizce Bilenler.txt");
	remove("Birden Fazla Yabanci Dil Bilenler.txt");
	remove("Girilen deneyim.txt");
	remove("deneyimsiz.txt");
	remove("yasa gore.txt");
	remove("ehliyet.txt");
	remove("coklu listeleme.txt");
	int secenek, secim, secim2, pozisyon = 0, kisi_sayisi = 0, secenek2, dosyalanma,yas,coklu;
	float deneyim;
	string kontrol,kisi,ehliyet;  //foksiyondaki gerekli olan degisgenlerin tanimlanmasi
	while(true){
		cout << "1:Is basvurusu  icin"<<endl;
		cout << "2:Eleman aramak icin" << endl;
		cout << "Seceneklerden birini secin: ";
		cin >> secenek; // basvurumu mu,arama mý
		if ( secenek != 1 && secenek != 2 ) // secenek kontrol
		{
			cout << "\nYanlis giris yaptiniz !" << endl;
			system("PAUSE");
			exit(1);
		}
	
			if (secenek == 1) //basvuru ise
			{
				cout << "\n1:Sisteme kayit (kendi kisisel bilgilerini girme)" << endl;
				cout << "2:Sistemdeki bilgilerini goruntuleme" << endl;
				cout << "3:Sistemden cikma (bilgilerini silme)"<<endl;
				cout << "4:Sistemdeki bilgilerini guncelleme" << endl;
				cout << "Seceneklerden birini secin: ";
				cin >> secenek;
				switch (secenek)
				{
					case 1: //kisi ekle
					{
						
						kisi_sayisi = dosya_yaz(kisi_sayisi);
						pozisyon=ekle(pozisyon);
						break;
					}
					case 2: //kisi kendisini goruntulesin
					{
						cout << "\nIsminizi giriniz: ";
						cin.ignore();
						getline(cin, kisi);
						arama(agacKok, kisi);
						break;
					}
					case 3: // kisi sistemden ciksin
					{
						cout << "\nIsminizi giriniz: ";
						cin.ignore();
						getline(cin, kisi);
						yok_et(agacKok, kisi);
						break;
					}
					case 4: // kisi bilgilerini guncellesin
					{
						cout << "\nIsminizi giriniz: ";
						cin.ignore();
						getline(cin, kisi);
						guncelleme(agacKok, kisi);
						break;
					}
					default: //secenek kontrol
					{
						cout << "Yanlis giris yaptiniz !" << endl;
						break;
					}
				}
			}
			else if (secenek == 2) // arama secilmisse
			{
				cout << "\n1:Ikili arama agacindaki kisilerin adlarini duzeyleri ile birlikte Listeleme.Eleman sayisini yazdirma.";
				cout << "\n2:Ise basvuran tum adaylarin bilgilerini listeleme";
				cout << "\n3:Adindan kisi arama tum bilgilerini listeleme";
				cout << "\n4:En Az lisans mezunu olan kisilerin listelenmesi";
				cout << "\n5:Inglizce bilenlerin listelenmesi";
				cout << "\n6:Birden fazla yabanci dil bilenlerin listelenmesi";
				cout << "\n7:Gireceginiz deneyim suresine gore listeleme";
				cout << "\n8:Deneyimsiz kisileri listeleme";
				cout << "\n9:Girelen yas degerine gore listeleme";
				cout << "\n10:Girilen ehliyete gore listeleme";
				cout << "\n11:Coklu listleme";
				cout << "\nSeceneklerden birini secin: ";
				cin >> secenek2; // secenek alýnmasi
				switch (secenek2)
				{
				case 1: //listeleme
				{
					ofstream liste;
					liste.open("Listele.txt", ios::out | ios::app);
					liste << "Inorder Listeleme:" << endl;
					cout << "\nInorder Listeleme: " << endl;
					listele(agacKok, 1);
					liste << "\nPreorder Listeleme:" << endl;
					cout << "\nPreorder Listeleme: " << endl;
					listele(agacKok, 2);
					liste << "\nPostorder Listeleme:" << endl;
					cout << "\nPostorder Listeleme: " << endl;
					listele(agacKok, 3);
					liste << "\nDugum Sayisi: " << kisi_sayisi;
					cout << "\nDugum Sayisi: " << kisi_sayisi << endl;
					cout << "\nListelenme dosyalansin mi(1:Evet,2:Hayir)";
					cin >> dosyalanma; // dosyalanma icin onay
					liste.close();
					if (dosyalanma == 1)
					{

					}
					else if(dosyalanma == 2) 
					{
						remove("Listele.txt");
					}
					else //kontrol
					{
						cout << "\nYanlis giris yaptin !" << endl;
					}
					break;
				}
				case 2: { //agactaki kisilerin tum bilgilerini goruntuleme
					string dummy = " ";
					arama(agacKok, dummy, 1);
					cout << "\nListelenme dosyalansin mi(1:Evet,2:Hayir)";
					cin >> dosyalanma; // dosyalansin mi
					if (dosyalanma == 1)
					{

					}
					else if (dosyalanma == 2)
					{
						remove("Tum Bilgiler.txt");
					}
					else //kontrol
					{
						cout << "\nYanlis giris yaptin !" << endl;
					}
					break;
				}
				case 3: { //is veren kisi arama
					cout << "\nIsimi Girin: ";
					cin.ignore();
					getline(cin, kisi);
					arama(agacKok, kisi,2);
					cout << "\nListelenme dosyalansin mi(1:Evet,2:Hayir)";
					cin >> dosyalanma;
					if (dosyalanma == 1)
					{

					}
					else if (dosyalanma == 2)
					{
						remove("Tek Kisinin Bilgisi.txt");
					}
					else
					{
						cout << "\nYanlis giris yaptin !" << endl;
					}
					break;
				}
				case 4: {
					cout << "\nEn az Lisans Mezunlari Listesi\n"<<endl;
					ofstream Lisans;
					Lisans.open("Lisans.txt");
					Lisans << "En az lisans mezunlari listesine hos geldiniz !\n" << endl;
					ozellik_bul(agacKok,1);
					cout << "\nListelenme dosyalansin mi(1:Evet,2:Hayir)";
					Lisans.close();
					cin >> dosyalanma;
					if (dosyalanma == 1)
					{

					}
					else if (dosyalanma == 2)
					{
						remove("Lisans.txt");
					}
					else
					{
						cout << "\nYanlis giris yaptin !" << endl;
					}
					break;
				}
				case 5: // ingilizce bilenler
				{
					cout << "\nIngilizce Bilenlerin Listelenmesi\n" << endl;
					ofstream ingilizce;
					ingilizce.open("Ingilizce Bilenler.txt");
					ingilizce << "Inglizce Bilenlerin Listelenmesi " << endl;
					ozellik_bul(agacKok, 2);
					ingilizce.close();
					cout << "\nListelenme dosyalansin mi(1:Evet,2:Hayir)";
					cin >> dosyalanma;
					if (dosyalanma == 1)
					{

					}
					else if (dosyalanma == 2)
					{
						remove("Ingilizce Bilenler.txt");
					}
					else
					{
						cout << "\nYanlis giris yaptin !" << endl;
					}
					break;
				}
				case 6: // birden fazla dil bilenler
				{
					cout << "\nBirden fazla yabanci dil bilenlerin listelenmesi\n" << endl;
					ofstream cok_yabanci_dil;
					cok_yabanci_dil.open("Birden Fazla Yabanci Dil Bilenler.txt");
					cok_yabanci_dil << "Birden fazla yabanci dil bilenlerin listelenmesi\n" << endl;
					ozellik_bul(agacKok, 3);
					cout << "\nListelenme dosyalansin mi(1:Evet,2:Hayir)";
					cok_yabanci_dil.close();
					cin >> dosyalanma;
					if (dosyalanma == 1)
					{

					}
					else if (dosyalanma == 2)
					{
						remove("Birden Fazla Yabanci Dil Bilenler.txt");
					}
					else
					{
						cout << "\nYanlis giris yaptin !" << endl;
					}
					break;
				}
				case 7: //deneyime gore
				{
					ofstream klasor;
					klasor.open("Girilen deneyim.txt");
					klasor << "Girilen deneyim suresine gore listeleme:" << endl;
					cout << "\nDeneyim suresi girin: ";
					cin >> deneyim;
					if (deneyim < 0)
					{
						cout << "Yanlis giris yaptiniz !" << endl;
						break;
					}
					cout << "\nGirilen deneyim suresine gore listeleme:\n" << endl;
					ozellik_bul(agacKok, 4, deneyim);
					cout << "\nListelenme dosyalansin mi(1:Evet,2:Hayir)";
					klasor.close();
					cin >> dosyalanma;
					if (dosyalanma == 1)
					{

					}
					else if (dosyalanma == 2)
					{
						remove("Girilen deneyim.txt");
					}
					else
					{
						cout << "\nYanlis giris yaptin !" << endl;
					}
					break;
				}
				case 8: // deneyimsizler
				{
					ofstream sinir;
					sinir.open("deneyimsiz.txt");
					cout << "\nDeneyimsiz kisilerin listelenmesi:\n" << endl;
					sinir << "Deneyimsiz Kisiler:" << endl;

					ozellik_bul(agacKok, 5);

					sinir.close();
					cout << "\nListelenme dosyalansin mi(1:Evet,2:Hayir)";
					cin >> dosyalanma;
					if (dosyalanma == 1)
					{

					}
					else if (dosyalanma == 2)
					{
						remove("deneyimsiz.txt");
					}
					else
					{
						cout << "\nYanlis giris yaptin !" << endl;
					}
					break;
				}
				case 9: //yasa gore
				{
					cout << "\nYas girin:";
					cin >> yas;
					if (yas < 0)
					{
						cout << "\n Yanlis giris yaptiniz !" << endl;
						break;
					}
					ofstream happy_new_year;
					happy_new_year.open("yasa gore.txt");

					cout << "\nYasa gore listeleme:\n" << endl;
					happy_new_year << "Yasa gore listeleme:\n" << endl;
					ozellik_bul(agacKok,6, 0, yas);
					
					happy_new_year.close();
					cout << "\nListelenme dosyalansin mi(1:Evet,2:Hayir)";
					cin >> dosyalanma;
					if (dosyalanma == 1)
					{

					}
					else if (dosyalanma == 2)
					{
						remove("yasa gore.txt");
					}
					else
					{
						cout << "\nYanlis giris yaptin !" << endl;
					}
					break;
				}
				case 10: //ehliyete gore
				{
					cout << "\nAranacak ehliyeti girin:";
					cin.ignore();
					getline(cin, ehliyet);
					ofstream surucu;
					surucu.open("ehliyet.txt");
					cout << "Ehliyete gore listeleme:\n" << endl;
					surucu << "Ehliyete gore listeleme:" << endl;
					ozellik_bul(agacKok, 7, 0, 0, ehliyet);
					surucu.close();
					cout << "\nListelenme dosyalansin mi(1:Evet,2:Hayir)";
					cin >> dosyalanma;
					if (dosyalanma == 1)
					{

					}
					else if (dosyalanma == 2)
					{
						remove("ehliyet.txt");
					}
					else
					{
						cout << "\nYanlis giris yaptin !" << endl;
					}
					break;
				}
				case 11: // coklu filtre
				{
					int sayac;
					cout << "\nKac tane filtreleme kullanicaksin(min 2,max 6):";
					cin >> sayac;
					cout << "\n1:En Az lisans mezunu olan kisilerin listelenmesi";
					cout << "\n2:Inglizce bilenlerin listelenmesi";
					cout << "\n3:Birden fazla yabanci dil bilenlerin listelenmesi";
					cout << "\n4:Gireceginiz deneyim suresine gore listeleme";
					cout << "\n5:Girelen yas degerine gore listeleme";
					cout << "\n6:Girilen ehliyete gore listeleme";
					cout << "\nSeceneklerden birini secin:"<<endl;
					int say=0,ydil=0,eng=0,lisans=0,tecrube=0;
					deneyim = 0;
					yas = 0;
					ehliyet = "";
					if (sayac >= 2 && sayac < 7)
					{
						while (say < sayac) {

							cin >> coklu;
							if (coklu == 1)
							{
								lisans = 1;
							}
							if (coklu == 2)
							{
								eng = 1;
							}
							if (coklu == 3)
							{
								ydil = 1;
							}
							if (coklu == 4)
							{
								cout << "Deneyim suresi girin:";
								cin >> deneyim;
								tecrube = 1;
							}if (coklu == 5)
							{
								cout << "Yas Girin:";
								cin >> yas;
							}if (coklu == 6) {
								cout << "Ehliyet Girin:";
								cin >> ehliyet;
							}
							say++;
						}
						ofstream cokluListeleme;
						cokluListeleme.open("coklu listeleme.txt");
						cout << "\nSecilen kriterlere gore liste:\n" << endl;
						cokluListeleme << "Secilen kriterlere gore liste:" << endl;
						ozellik_bul(agacKok, 8, deneyim, yas, ehliyet, lisans, ydil, eng, tecrube,sayac);
						cokluListeleme.close();
						cout << "\nListelenme dosyalansin mi(1:Evet,2:Hayir)";
						cin >> dosyalanma;
						if (dosyalanma == 1)
						{

						}
						else if (dosyalanma == 2)
						{
							remove("coklu listeleme.txt");
						}
						else
						{
							cout << "\nYanlis giris yaptin !" << endl;
						}
						break;
					}
					else // kontorl
					{
						cout << "Yanlis giris yaptin !";
						break;
					}
				}
				default: { // kontrol
					cout << "Yanlis Giris Yaptiniz !";
					break;
				}

			 }
				
			}
			cout << "\nCikis etmek icin '1' e,Devam icin '2' ye basiniz"<< endl;
			cin >> kontrol;
			if (kontrol[0] == '1') // kontrol
			{
				break;
			}
			cout << endl;
	}

	system("PAUSE");
	return 0;
}