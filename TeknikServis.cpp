#include <iomanip> 
#include <cstring> 
#include <stdlib.h>
#include <conio.h>
#include <stdio.h> 
#include <fstream>                  
#include <iostream>

using namespace std;

struct Urun
{char urun_no[80];
char model[80];
char ariza[80];
char garanti;
};
Urun urun;

void Ekle();
void Listele();
void Ara();
void Silme();
void Duzenle();

int main()
{
	setlocale(LC_ALL,"Turkish");
char secim;

do
{system("cls");
cout << "|-------Hosgeldiniz------|" << endl ;
cout << "|     Secim Yapiniz      |" << endl ;
cout << "|   1- Ürün Ekleme       |" << endl ;
cout << "|   2- Ürün Listeleme    |" << endl ;
cout << "|   3- Ürün Arama        |" << endl ;
cout << "|   4- Ürün Silme        |" << endl ;
cout << "|   5- Ürün Düzenleme    |" << endl ;
cout << "|------------------------|" << endl ;
cout<<"Yapmak Ýstediðiniz Ýþlemi Giriniz: ";
secim=getche();
	
switch(secim)
{  
    case '1':
    { Ekle();
   	break;
    }	
    case '2':
    { Listele();
   	break;
    }	
    case '3':
    { Ara();
   	break;
    }	
    case '4':
    { Silme();
   	break;
    }	
    case '5':
    { Duzenle();
   	break;
    }	
}
	
	
cout<<"\nAna Menüye Dönmek Ýçin (A/a)'ya Basýnýz."<<endl;
secim=getche();	
}while(secim=='A'||secim=='a');	

	system("pause");
	return 0;
}

void Ekle()
{
ofstream yaz("urunbilgileri.dat",ios::binary| ios::app);
int i=0;
char secim;
    do
    {
    cout<<"\nÜrün No Giriniz: "<<endl;
    cin>>urun.urun_no;
    cout<<"Ürün  Modelini Giriniz: "<<endl;
    cin>>urun.model;
    cout<<"Ürün Arýzasýný Giriniz: "<<endl;
    cin>>urun.ariza;
    cout<<"Ürünün Garanti Durumunu Giriniz (v/y): "<<endl;
    urun.garanti=getche();
    
    yaz.write((char*)&urun,sizeof(urun));
    i++;
    cout<<"\nBaþka Ürün Eklemek Ýster Misiniz? (e/h)"<<endl;
    secim=getche();
    cout<<endl;
    }while(secim=='e'||secim=='E');

cout<<endl;
cout<<i<<" ADET ÜRÜN EKLENDÝ."<<endl;
}

void Listele()
{
ifstream oku("urunbilgileri.dat",ios::binary|ios::app);
oku.seekg(0,ios::end);
int kayits=oku.tellg()/sizeof(urun);

cout<<endl;
cout<<kayits<<" Adet Kayýt Bulunmaktadýr."<<endl;
cout<<endl;
if(kayits>0)
{   for(int i=0;i<kayits;i++)
   {
   oku.seekg(i*sizeof(urun));
   oku.read((char*)&urun,sizeof(urun));
   
   cout<<i+1<<". ÜRÜNÜN BÝLGÝLERÝ"<<endl;
   cout<<"Ürün No: "<<urun.urun_no<<endl;
   cout<<"Ürün Modeli: "<<urun.model<<endl;
   cout<<"Ürün Arýzasý: "<<urun.ariza<<endl;
   if(urun.garanti=='v'||urun.garanti=='V')
   cout<<"Ürün Garantisi VAR."<<endl;
   else if(urun.garanti=='y'||urun.garanti=='Y')
   cout<<"Ürün Garantisi YOK."<<endl;
   cout<<"---------------------"<<endl;
   }
}

oku.close();
}

void Ara()
{ifstream oku("urunbilgileri.dat",ios::binary|ios::app);
oku.seekg(0,ios::end);
int kayits=oku.tellg()/sizeof(urun);
char no[80];
cout<<"\nBulmak Ýstediðiniz Ürünün Numarasýný Giriniz.";
cin>>no;

 if(kayits>0)
 {
  for(int i=0;i<kayits;i++)
  {
	oku.seekg(i*sizeof(urun));
    oku.read((char*)&urun,sizeof(urun));
    
    if(strcmp(urun.urun_no,no)==0)
    {cout<<"\n-------Bulunan Ürünün Bilgileri------"<<endl;
    cout<<"Ürün Numarasý: "<<urun.urun_no<<endl;
    cout<<"Ürün Modeli: "<<urun.model<<endl;
    cout<<"Ürün Arýzasý: "<<urun.ariza<<endl;
    if(urun.garanti=='v'||urun.garanti=='V')
    cout<<"Ürün Garantisi VAR."<<endl;
    else if(urun.garanti=='y'||urun.garanti=='Y')
    cout<<"Ürün Garantisi YOK."<<endl;
	}
  }
 }
 else 
 cout<<"Eklenmiþ Kayýt Bulunmamaktadýr."<<endl;
 
 oku.close();
}

void Silme()
{
ifstream oku("urunbilgileri.dat",ios::binary|ios::app);
oku.seekg(0,ios::end);
int kayits=oku.tellg()/sizeof(urun);
char no[80];

cout<<"\nSilmek Ýstediðiniz Ürünün Numarasýný Giriniz.";
cin>>no;

for(int i=0;i<kayits;i++)
{oku.seekg(i*sizeof(urun));
oku.read((char*)&urun,sizeof(urun));

    if(strcmp(urun.urun_no,no)==0)
    {
    }
    else
    {Urun y_urun;
    ofstream y_yaz("yedek.dat",ios::binary|ios::app);
    
    strcpy(y_urun.urun_no,urun.urun_no);
    strcpy(y_urun.model,urun.model);
    strcpy(y_urun.ariza,urun.ariza);
    y_urun.garanti=urun.garanti;
    
    y_yaz.write((char*)&urun,sizeof(urun));
    y_yaz.close();
    }
}
oku.close();
remove("urunbilgileri.dat");
rename("yedek.dat","urunbilgileri.dat");
cout<<no<<" Nolu Ürün Silindi."<<endl;
}

void Duzenle()
{ifstream oku("urunbilgileri.dat",ios::binary|ios::app);
oku.seekg(0,ios::end);
int kayits=oku.tellg()/sizeof(urun);
char no[80];

cout<<"\nDüzenlemek Ýstediðiniz Ürünün Numarasýný Giriniz.";
cin>>no;

    for(int i=0;i<kayits;i++)
    {oku.seekg(i*sizeof(urun));
    oku.read((char*)&urun,sizeof(urun));
    
      if(strcmp(urun.urun_no,no)==0)
      { ofstream y_yaz ("yedek.dat",ios::binary|ios::app);
      cout<<endl;
	  cout<<"Ürün Numarasý Giriniz."<<endl;
      cin>>urun.urun_no;
      cout<<"Ürün Modelini Giriniz."<<endl;
      cin>>urun.model;
      cout<<"Ürün Arýzasýný Giriniz."<<endl;
      cin>>urun.ariza;
      cout<<"Ürün Garanti Durumunu Giriniz."<<endl;
      urun.garanti=getche();
      
      y_yaz.write((char*)&urun,sizeof(urun));
      y_yaz.close();
	  }
	  
	  else
	  { Urun y_urun;
	  ofstream y_yaz ("yedek.dat",ios::binary|ios::app);
	  
	  strcpy(y_urun.urun_no,urun.urun_no);
	  strcpy(y_urun.model,urun.model);
	  strcpy(y_urun.ariza,urun.ariza);
	  y_urun.garanti=urun.garanti;
	  
	  y_yaz.write((char*)&urun,sizeof(urun));
	  y_yaz.close();
	  }
    
	}
	oku.close();
	
	remove("urunbilgileri.dat");
	rename("yedek.dat","urunbilgileri.dat");
	
	cout<<"\nKayýt Düzeltildi."<<endl;	
}













