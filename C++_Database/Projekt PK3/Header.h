#pragma once
#ifndef _HEADER_H
#define _HEADER_H

//#include "Obsluga_menu.h"
#include <string>


struct Lista
{
	class Obrazy *pO;
	class Rzezby *pR;
	class Duze_przedmioty *pD;
	class Male_przedmioty *pM;
	class Zabytkowe_rekopisy *pZ;
	class Starodruki *pS;

};

class Eksponat_Muzealny
{
	std::string nazwa;
	std::string rok_powstania;
	std::string autor;
	std::string cena;

	public:
		Eksponat_Muzealny *pNext;
		const std::string &wypisz_nazwe() const;
		const std::string &wypisz_rok() const;
		const std::string &wypisz_autora() const;
		const std::string &wypisz_cene() const;
		Eksponat_Muzealny(std::string nazwa, std::string rok_powstania, std::string autor, std::string cena);
		~Eksponat_Muzealny(); 

		virtual void wydrukuj_dane(Lista *pHead) = 0;
		virtual void dodaj_obiekt(Lista *&pHead, class Eksponat_Muzealny *pDodany)=0; 
		virtual void usun_obiekt(Lista *&pHead, class Eksponat_Muzealny *pUsun)=0;
	
		
};

class Dziela_sztuki : public virtual Eksponat_Muzealny
{
	std::string czy3d; 
public:
	const std::string &czy_obiekt_jest_przestrzenny() const;
	
	Dziela_sztuki(std::string nazwa, std::string rok_powstania, std::string autor, std::string cena, std::string czy3d) : Eksponat_Muzealny(nazwa, rok_powstania, autor, cena), czy3d(czy3d) {};
	~Dziela_sztuki();

	virtual void wydrukuj_dane(Lista *pHead) = 0;
	virtual void dodaj_obiekt(Lista *&pHead, class Eksponat_Muzealny *pDodany) = 0;
	virtual void usun_obiekt(Lista *&pHead, class Eksponat_Muzealny *pUsun) = 0;


};

class Zwiazane_z_pismem : public virtual Eksponat_Muzealny
{	
	std::string oryginal_czy_kopia;
public:;
	const std::string &czy_oryginal_czy_kopia() const;
	
	Zwiazane_z_pismem(std::string nazwa, std::string rok_powstania, std::string autor, std::string cena, std::string oryginal_czy_kopia) : Eksponat_Muzealny(nazwa, rok_powstania, autor, cena), oryginal_czy_kopia(oryginal_czy_kopia) {};
	~Zwiazane_z_pismem();

	virtual void wydrukuj_dane(Lista *pHead) = 0;
	virtual void dodaj_obiekt(Lista *&pHead, class Eksponat_Muzealny *pDodany) = 0;
	virtual void usun_obiekt(Lista *&pHead, class Eksponat_Muzealny *pUsun) = 0;

};

class Przedmioty_uzytkowe : public virtual Eksponat_Muzealny
{
	std::string wielkosc;
public:

	const std::string &jaka_wielkosc() const;

	Przedmioty_uzytkowe(std::string nazwa, std::string rok_powstania, std::string autor, std::string cena, std::string wielkosc) : Eksponat_Muzealny(nazwa, rok_powstania, autor, cena), wielkosc(wielkosc) {};
	~Przedmioty_uzytkowe();
	
	virtual void wydrukuj_dane(Lista *pHead) = 0;
	virtual void dodaj_obiekt(Lista *&pHead, class Eksponat_Muzealny *pDodany) = 0;
	virtual void usun_obiekt(Lista *&pHead, class Eksponat_Muzealny *pUsun) = 0;

};


class Obrazy : public virtual Dziela_sztuki
{
	std::string liczba_kolorow;
public:
	const std::string &ile_kolorow() const;

	Obrazy(std::string nazwa, std::string rok_powstania, std::string autor, std::string cena, std::string czy3d, std::string liczba_kolorow) :Eksponat_Muzealny(nazwa, rok_powstania, autor, cena), Dziela_sztuki(nazwa, rok_powstania, autor, cena, czy3d), liczba_kolorow(liczba_kolorow) {};
	~Obrazy();

	void wydrukuj_dane(Lista *pHead);
	void dodaj_obiekt(Lista *&pHead, class Eksponat_Muzealny *pDodany);
	void usun_obiekt(Lista *&pHead, class Eksponat_Muzealny *pUsun);


	Obrazy *pNext;

};

class Rzezby : public virtual Dziela_sztuki
{
	std::string liczba_elementow;
public:
	const std::string &ile_elementow() const;

	Rzezby(std::string nazwa, std::string rok_powstania, std::string autor, std::string cena, std::string czy3d, std::string liczba_elementow) :Eksponat_Muzealny(nazwa, rok_powstania, autor, cena), Dziela_sztuki(nazwa, rok_powstania, autor, cena, czy3d), liczba_elementow(liczba_elementow) {};
	~Rzezby();

	void wydrukuj_dane(Lista *pHead);
	void dodaj_obiekt(Lista *&pHead, class Eksponat_Muzealny *pDodany);
	void usun_obiekt(Lista *&pHead, class Eksponat_Muzealny *pUsun);


	Rzezby *pNext;
};

class Duze_przedmioty : public virtual Przedmioty_uzytkowe
{
	std::string nazwa_duzej_rzeczy;
public:
	const std::string  &jaka_nazwa_duzej_rzeczy() const;

	Duze_przedmioty(std::string nazwa, std::string rok_powstania, std::string autor, std::string cena, std::string wielkosc, std::string nazwa_duzej_rzeczy) 
		:Eksponat_Muzealny(nazwa, rok_powstania, autor, cena), Przedmioty_uzytkowe(nazwa, rok_powstania, autor, cena, wielkosc), nazwa_duzej_rzeczy(nazwa_duzej_rzeczy)
	{};
	~Duze_przedmioty();

	void wydrukuj_dane(Lista *pHead);
	void dodaj_obiekt(Lista *&pHead, class Eksponat_Muzealny *pDodany);
	void usun_obiekt(Lista *&pHead, class Eksponat_Muzealny *pUsun);


	Duze_przedmioty *pNext;
};

class Male_przedmioty : public virtual Przedmioty_uzytkowe
{
	std::string nazwa_malej_rzeczy;
public:
	const std::string  &jaka_nazwa_malej_rzeczy() const;

	Male_przedmioty(std::string nazwa, std::string rok_powstania, std::string autor, std::string cena, std::string wielkosc, std::string nazwa_malej_rzeczy) : Eksponat_Muzealny(nazwa, rok_powstania, autor, cena), Przedmioty_uzytkowe(nazwa, rok_powstania, autor, cena, wielkosc), nazwa_malej_rzeczy(nazwa_malej_rzeczy) {};
	~Male_przedmioty();

	void wydrukuj_dane(Lista *pHead);
	void dodaj_obiekt(Lista *&pHead, class Eksponat_Muzealny *pDodany);
	void usun_obiekt(Lista *&pHead, class Eksponat_Muzealny *pUsun);


	Male_przedmioty *pNext;
};

class Zabytkowe_rekopisy : public virtual Zwiazane_z_pismem
{
	std::string nazwisko_odkrywcy;
public:
	const std::string  &jakie_nazwisko_odkrywcy() const;

	Zabytkowe_rekopisy(std::string nazwa, std::string rok_powstania, std::string autor, std::string cena, std::string oryginal_czy_kopia, std::string nazwisko_odkrywcy) : Eksponat_Muzealny(nazwa, rok_powstania, autor, cena), Zwiazane_z_pismem(nazwa, rok_powstania, autor, cena, oryginal_czy_kopia), nazwisko_odkrywcy(nazwisko_odkrywcy) {};
	~Zabytkowe_rekopisy();

	void wydrukuj_dane(Lista *pHead);
	void dodaj_obiekt(Lista *&pHead, class Eksponat_Muzealny *pDodany);
	void usun_obiekt(Lista *&pHead, class Eksponat_Muzealny *pUsun);


	Zabytkowe_rekopisy *pNext;
};

class Starodruki : public virtual Zwiazane_z_pismem
{
	std::string nazwa_drukarni;
public:
	const std::string  &jaka_nazwa_drukarni() const;

	Starodruki(std::string nazwa, std::string rok_powstania, std::string autor,
		std::string cena, std::string oryginal_czy_kopia, std::string nazwa_drukarni) : Eksponat_Muzealny(nazwa, rok_powstania, autor, cena),
		Zwiazane_z_pismem(nazwa, rok_powstania, autor, cena, oryginal_czy_kopia), nazwa_drukarni(nazwa_drukarni) 
	{
		
	};
	~Starodruki();

	void wydrukuj_dane(Lista *pHead);
	void dodaj_obiekt(Lista *&pHead, class Eksponat_Muzealny *pDodany);
	void usun_obiekt(Lista *&pHead, class Eksponat_Muzealny *pUsun);
	
	Starodruki *pNext;
	
};
#endif
