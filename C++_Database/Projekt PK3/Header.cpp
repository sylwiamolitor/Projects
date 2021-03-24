#include "Header.h"
#include "Obsluga_menu.h"


#include <iostream>
#include <fstream>


void podstawowe_dane_drukuj(class Eksponat_Muzealny *pH) 
{
	std::cout << "Nazwa eksponatu : " << pH->wypisz_nazwe() << std::endl;
	std::cout << "Rok powstania : " << pH->wypisz_rok() << std::endl;
	std::cout << "Autor : " << pH->wypisz_autora() << std::endl;
	std::cout << "Cena : " << pH->wypisz_cene() << std::endl;
}
Eksponat_Muzealny::~Eksponat_Muzealny()
{
}

const std::string & Eksponat_Muzealny::wypisz_nazwe() const
{
	return this->nazwa;
}

const std::string & Eksponat_Muzealny::wypisz_rok() const
{
	return this->rok_powstania;
}

const std::string & Eksponat_Muzealny::wypisz_autora() const
{
	return this->autor;
}

const std::string & Eksponat_Muzealny::wypisz_cene() const
{
	return this->cena;
}


const std::string & Dziela_sztuki::czy_obiekt_jest_przestrzenny() const
{
	return this->czy3d;
}

Dziela_sztuki::~Dziela_sztuki()
{
}

const std::string & Zwiazane_z_pismem::czy_oryginal_czy_kopia() const
{
	return this->oryginal_czy_kopia;
}

Zwiazane_z_pismem::~Zwiazane_z_pismem()
{
}

const std::string & Przedmioty_uzytkowe::jaka_wielkosc() const
{
	return this->wielkosc;
}

Przedmioty_uzytkowe::~Przedmioty_uzytkowe()
{
}

const std::string & Obrazy::ile_kolorow() const
{
	return this->liczba_kolorow;
}

const std::string & Rzezby::ile_elementow() const
{
	return this->liczba_elementow;
}


const std::string & Duze_przedmioty::jaka_nazwa_duzej_rzeczy() const
{
	return this->nazwa_duzej_rzeczy;
}

Duze_przedmioty::~Duze_przedmioty()
{
}

void Duze_przedmioty::wydrukuj_dane(Lista * pHead)
{
		auto *pH = pHead->pD;
		while (pH != nullptr)
		{
			podstawowe_dane_drukuj(pH);
			std::cout << "Wielkosc: " << pH->jaka_wielkosc() << std::endl;
			std::cout << "Nazwa du¿ej rzeczy: " << pH->jaka_nazwa_duzej_rzeczy() << std::endl;
			pH = pH->pNext;
		}
}

void Duze_przedmioty::dodaj_obiekt(Lista *& pHead, Eksponat_Muzealny * pDodany)
{
	auto pD = dynamic_cast<Duze_przedmioty*>(pDodany);
	auto *p = pHead->pD;
	while (p->pNext != nullptr)
		p = p->pNext;
	p->pNext = pD;


}

void Duze_przedmioty::usun_obiekt(Lista *& wsk2, Eksponat_Muzealny * pUsun)
{
	auto pU = dynamic_cast<Duze_przedmioty*>(pUsun);
	auto p = wsk2->pD;
	if (p->wypisz_nazwe() == pU->wypisz_nazwe() && p->wypisz_rok() == pU->wypisz_rok() && p->wypisz_autora() == pU->wypisz_autora() && p->wypisz_cene() == pU->wypisz_cene())//zmienic na funkcje getName itd
	{
		wsk2->pD = wsk2->pD->pNext;
		delete p;
		return;
	}
	while (p->pNext != nullptr) 
	{
		if (p->pNext->wypisz_nazwe() == pU->wypisz_nazwe() && p->pNext->wypisz_rok() == pU->wypisz_rok() && p->pNext->wypisz_autora() == pU->wypisz_autora() && p->pNext->wypisz_cene() == pU->wypisz_cene())
		{
			Duze_przedmioty *do_usuniecia = p->pNext;
			p->pNext = p->pNext->pNext;
			delete do_usuniecia;
			return;
		}
		p = p->pNext;

	}
}

const std::string & Male_przedmioty::jaka_nazwa_malej_rzeczy() const
{
	return this->nazwa_malej_rzeczy;
}

Male_przedmioty::~Male_przedmioty()
{
	
}

void Male_przedmioty::wydrukuj_dane(Lista * wsk2)
{
	auto *pH = wsk2->pM;
	while (pH != nullptr)
	{
		podstawowe_dane_drukuj(pH);
		std::cout << "Wielkosc: " << pH->jaka_wielkosc() << std::endl;
		std::cout << "Nazwa malej rzeczy: " << pH->jaka_nazwa_malej_rzeczy() << std::endl;
		pH = pH->pNext;
	}
}

void Male_przedmioty::dodaj_obiekt(Lista *& wsk2, Eksponat_Muzealny * pDodany)
{
	auto pD = dynamic_cast<Male_przedmioty*>(pDodany);
	auto *p = wsk2->pM;
	while (p->pNext != nullptr)
		p = p->pNext;
	p->pNext = pD;

}

void Male_przedmioty::usun_obiekt(Lista *& wsk2, Eksponat_Muzealny * pUsun)
{
	auto pU = dynamic_cast<Male_przedmioty*>(pUsun);
	auto p = wsk2->pM;
	if (p->wypisz_nazwe() == pU->wypisz_nazwe() && p->wypisz_rok() == pU->wypisz_rok() && p->wypisz_autora() == pU->wypisz_autora() && p->wypisz_cene() == pU->wypisz_cene())//zmienic na funkcje getName itd
	{
		wsk2->pM = wsk2->pM->pNext;
		delete p;
		return;
	}
	while (p->pNext != nullptr)
	{
		if (p->pNext->wypisz_nazwe() == pU->wypisz_nazwe() && p->pNext->wypisz_rok() == pU->wypisz_rok() && p->pNext->wypisz_autora() == pU->wypisz_autora() && p->pNext->wypisz_cene() == pU->wypisz_cene())
		{
			Male_przedmioty *do_usuniecia = p->pNext;
			p->pNext = p->pNext->pNext;
			delete do_usuniecia;
			return;
		}
		p = p->pNext;

	}
}
const std::string & Zabytkowe_rekopisy::jakie_nazwisko_odkrywcy() const
{
	return this->nazwisko_odkrywcy;
}

Zabytkowe_rekopisy::~Zabytkowe_rekopisy()
{
	

}

void Zabytkowe_rekopisy::wydrukuj_dane(Lista * wsk2)
{
	auto *pH = wsk2->pZ;
	while (pH != nullptr)
	{
		podstawowe_dane_drukuj(pH);
		std::cout << "Drukowane czy recznie?: " << pH->czy_oryginal_czy_kopia() << std::endl;
		std::cout << "Nazwisko odkrywcy: " << pH->jakie_nazwisko_odkrywcy() << std::endl;
		pH = pH->pNext;
	}
}

void Zabytkowe_rekopisy::dodaj_obiekt(Lista *& wsk2, Eksponat_Muzealny * pDodany)
{
	auto pD = dynamic_cast<Zabytkowe_rekopisy*>(pDodany);
	auto *p = wsk2->pZ;
	while (p->pNext != nullptr) 
		p = p->pNext;
	p->pNext = pD;

}

void Zabytkowe_rekopisy::usun_obiekt(Lista *& wsk2, Eksponat_Muzealny * pUsun)
{
	auto pU = dynamic_cast<Zabytkowe_rekopisy*>(pUsun);
	auto p = wsk2->pZ;
	if (p->wypisz_nazwe() == pU->wypisz_nazwe() && p->wypisz_rok() == pU->wypisz_rok() && p->wypisz_autora() == pU->wypisz_autora() && p->wypisz_cene() == pU->wypisz_cene())//zmienic na funkcje getName itd
	{
		wsk2->pZ = wsk2->pZ->pNext;
		delete p;
		return;
	}
	while (p->pNext != nullptr)
	{
		if (p->pNext->wypisz_nazwe() == pU->wypisz_nazwe() && p->pNext->wypisz_rok() == pU->wypisz_rok() && p->pNext->wypisz_autora() == pU->wypisz_autora() && p->pNext->wypisz_cene() == pU->wypisz_cene())
		{
			Zabytkowe_rekopisy *do_usuniecia = p->pNext;
			p->pNext = p->pNext->pNext;
			delete do_usuniecia;
			return;
		}
		p = p->pNext;

	}
}

const std::string & Starodruki::jaka_nazwa_drukarni() const
{
	return this->nazwa_drukarni;
}

Starodruki::~Starodruki()
{
	
}

void Starodruki::wydrukuj_dane(Lista * wsk2)
{
	auto *pH = wsk2->pS;
	while (pH != nullptr)
	{
		podstawowe_dane_drukuj(pH);
		std::cout << "Drukowane czy recznie?: " << pH->czy_oryginal_czy_kopia() << std::endl;
		std::cout << "Nazwa drukarni: " << pH->jaka_nazwa_drukarni() << std::endl;
		pH = pH->pNext;
	}
}

void Starodruki::dodaj_obiekt(Lista *& wsk2, Eksponat_Muzealny * pDodany)
{
	auto pD = dynamic_cast<Starodruki*>(pDodany);
	auto *p = wsk2->pS;
	while (p->pNext != nullptr) 
		p = p->pNext;
	p->pNext = pD;

}

void Starodruki::usun_obiekt(Lista *& wsk2, Eksponat_Muzealny * pUsun)
{
	auto pU = dynamic_cast<Starodruki*>(pUsun);
	auto p = wsk2->pS;
	if (p->wypisz_nazwe() == pU->wypisz_nazwe() && p->wypisz_rok() == pU->wypisz_rok() && p->wypisz_autora() == pU->wypisz_autora() && p->wypisz_cene() == pU->wypisz_cene())//zmienic na funkcje getName itd
	{
		wsk2->pS = wsk2->pS->pNext;
		delete p;
		return;
	}
	while (p->pNext != nullptr)
	{
		if (p->pNext->wypisz_nazwe() == pU->wypisz_nazwe() && p->pNext->wypisz_rok() == pU->wypisz_rok() && p->pNext->wypisz_autora() == pU->wypisz_autora() && p->pNext->wypisz_cene() == pU->wypisz_cene())
		{
			Starodruki *do_usuniecia = p->pNext;
			p->pNext = p->pNext->pNext;
			delete do_usuniecia;
			return;
		}
		p = p->pNext;

	}
}


Obrazy::~Obrazy()
{
	
}

void Obrazy::wydrukuj_dane(Lista * wsk2)
{
	auto *pH = wsk2->pO;
	while (pH != nullptr)
	{
		podstawowe_dane_drukuj(pH);
		std::cout << "Czy obiekt jest przestrzenny?: " << pH->czy_obiekt_jest_przestrzenny() << std::endl;
		std::cout << "Liczba kolorow: " << pH->ile_kolorow() << std::endl;
		pH = pH->pNext;
	}
}

void Obrazy::dodaj_obiekt(Lista *& wsk2, Eksponat_Muzealny * pDodany)
{
	auto pD = dynamic_cast<Obrazy*>(pDodany);
	auto *p = wsk2->pO;
	while (p->pNext != nullptr) 
		p = p->pNext;
	p->pNext = pD;
}

void Obrazy::usun_obiekt(Lista *& wsk2, Eksponat_Muzealny * pUsun)
{
	auto pU = dynamic_cast<Obrazy*>(pUsun);
	auto p = wsk2->pO;
	if (p->wypisz_nazwe() == pU->wypisz_nazwe() && p->wypisz_rok() == pU->wypisz_rok() && p->wypisz_autora() == pU->wypisz_autora() && p->wypisz_cene() == pU->wypisz_cene())//zmienic na funkcje getName itd
	{
		wsk2->pO = wsk2->pO->pNext;
		delete p;
		return;
	}
	while (p->pNext != nullptr)
	{
		if (p->pNext->wypisz_nazwe() == pU->wypisz_nazwe() && p->pNext->wypisz_rok() == pU->wypisz_rok() && p->pNext->wypisz_autora() == pU->wypisz_autora() && p->pNext->wypisz_cene() == pU->wypisz_cene())
		{
			Obrazy *do_usuniecia = p->pNext;
			p->pNext = p->pNext->pNext;
			delete do_usuniecia;
			return;
		}
		p = p->pNext;

	}
}

Rzezby::~Rzezby()
{

}

void Rzezby::wydrukuj_dane(Lista * wsk2)
{
	auto *pH = wsk2->pR;
	while (pH != nullptr)
	{
		podstawowe_dane_drukuj(pH);
		std::cout << "Czy obiekt jest przestrzenny?: " << pH->czy_obiekt_jest_przestrzenny() << std::endl;
		std::cout << "Liczba elementow: " << pH->ile_elementow() << std::endl;
		pH = pH->pNext;
	}
}

void Rzezby::dodaj_obiekt(Lista *& wsk2, Eksponat_Muzealny * pDodany)
{
	auto pD = dynamic_cast<Rzezby*>(pDodany);
	auto *p = wsk2->pR;
	while (p->pNext != nullptr)
		p = p->pNext;
	p->pNext = pD;
}

void Rzezby::usun_obiekt(Lista *& wsk2, Eksponat_Muzealny * pUsun)
{
	auto pU = dynamic_cast<Rzezby*>(pUsun);
	auto p = wsk2->pR;
	if (p->wypisz_nazwe() == pU->wypisz_nazwe() && p->wypisz_rok() == pU->wypisz_rok() && p->wypisz_autora() == pU->wypisz_autora() && p->wypisz_cene() == pU->wypisz_cene())//zmienic na funkcje getName itd
	{
		wsk2->pR = wsk2->pR->pNext;
		delete p;
		return;
	}
	while (p->pNext != nullptr)
	{
		if (p->pNext->wypisz_nazwe() == pU->wypisz_nazwe() && p->pNext->wypisz_rok() == pU->wypisz_rok() && p->pNext->wypisz_autora() == pU->wypisz_autora() && p->pNext->wypisz_cene() == pU->wypisz_cene())
		{
			Rzezby *do_usuniecia = p->pNext;
			p->pNext = p->pNext->pNext;
			delete do_usuniecia;
			return;
		}
		p = p->pNext;

	}
}
Eksponat_Muzealny::Eksponat_Muzealny(std::string nazwa, std::string rok_powstania, std::string autor, std::string cena)
{

	this->nazwa = nazwa;
	this->rok_powstania = rok_powstania;
	this->autor = autor;
	this->cena = cena;
}
