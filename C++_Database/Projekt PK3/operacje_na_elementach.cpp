
#include "operacje_na_elementach.h"
#include "Header.h"
#include "Obsluga_menu.h"

#include <iostream>
#include <fstream>

void dodaj_lub_usun_element(Lista *pHead, std::string nazwa, std::string rok, std::string autor, std::string cena, std::string zmienna1, std::string zmienna2, bool dodaj_czy_usun)
{
	Male_przedmioty *dodajM;
	Duze_przedmioty *dodajD;
	Obrazy *dodajO;
	Rzezby *dodajR;
	Starodruki *dodajS;
	Zabytkowe_rekopisy *dodajZ;

	char obecna_akcja = getchar();
	std::cout << "Wpisz typ obiektu, ktory chcesz dodac/usunac: \n1 Male przedmioty \n2 Duze przedmioty \n3 Obrazy \n4 Rzezby \n5 Starodruki \n6 Zabytkowe rekopisy" << std::endl;
	obecna_akcja = getchar();
	wczytaj_podstawowe_dane(pHead, nazwa, rok, autor, cena);
	switch (obecna_akcja)
	{	
	case '1':
		std::cout << "Wpisz wielkosc malego przedmiotu:" << std::endl;
		std::getline(std::cin, zmienna1);
		std::cout << "Wpisz nazwe malego przedmiotu:" << std::endl;
		std::getline(std::cin, zmienna2);
		dodajM = new Male_przedmioty(nazwa, autor, rok, cena, zmienna1, zmienna2); 
		if (dodaj_czy_usun == 1)
		{
			if (pHead->pM == nullptr) 
				pHead->pM = dodajM; 
			else
				pHead->pM->dodaj_obiekt(pHead, dodajM);
		}
		else
		{	if (pHead->pM)
				pHead->pM->usun_obiekt(pHead, dodajM);
		}
		break;
	case '2':
		std::cout << "Wpisz wielkosc duzego przedmiotu:" << std::endl;
		std::getline(std::cin, zmienna1);
		std::cout << "Wpisz nazwe duzego przedmiotu:" << std::endl;
		std::getline(std::cin, zmienna2);
		dodajD = new Duze_przedmioty(nazwa, autor, rok, cena, zmienna1, zmienna2);
		if (dodaj_czy_usun == 1)
		{
			if (pHead->pD == nullptr)
				pHead->pD = dodajD;
			else
				pHead->pD->dodaj_obiekt(pHead, dodajD);
		}
		else
		{
			if (pHead->pD)
				pHead->pD->usun_obiekt(pHead, dodajD);
		}
		break;
	case '3':
		std::cout << "Wpisz, czy obiekt jest przestrzenny:" << std::endl;
		std::getline(std::cin, zmienna1);
		std::cout << "Wpisz liczbe kolorow:" << std::endl;
		std::getline(std::cin, zmienna2);
		dodajO = new Obrazy(nazwa, autor, rok, cena, zmienna1, zmienna2);
		if (dodaj_czy_usun == 1)
		{

			if (pHead->pO == nullptr) 
				pHead->pO = dodajO;
			else
				pHead->pO->dodaj_obiekt(pHead, dodajO);
		}
		else
		{
			if (pHead->pO)
				pHead->pO->usun_obiekt(pHead, dodajO);
		}

		break;
	case '4':
		std::cout << "Wpisz, czy obiekt jest przestrzenny:" << std::endl;
		std::getline(std::cin, zmienna1);
		std::cout << "Wpisz liczbe elementow:" << std::endl;
		std::getline(std::cin, zmienna2);
		dodajR = new Rzezby(nazwa, autor, rok, cena, zmienna1, zmienna2);
		if (dodaj_czy_usun == 1)
		{
			if (pHead->pR == nullptr) 
				pHead->pR = dodajR;
			else
				pHead->pR->dodaj_obiekt(pHead, dodajR);
		}
		else
		{
			if (pHead->pR)
				pHead->pR->usun_obiekt(pHead, dodajR);
		}
		break;
	case '5':
		std::cout << "Wpisz, czy rekopis jest oryginalem, czy kopia:" << std::endl;
		std::getline(std::cin, zmienna1);
		std::cout << "Wpisz nazwisko odkrywcy:" << std::endl;
		std::getline(std::cin, zmienna2);
		dodajS = new Starodruki(nazwa, autor, rok, cena, zmienna1, zmienna2); 
		if (dodaj_czy_usun == 1)
		{
			if (pHead->pS == nullptr) 
				pHead->pS = dodajS;
			else
				pHead->pS->dodaj_obiekt(pHead, dodajS);
		}
		else
		{
			if (pHead->pS)
				pHead->pS->usun_obiekt(pHead, dodajS);
		}
		break;
	case '6':
		std::cout << "Wpisz, czy rekopis jest oryginalem, czy kopia:" << std::endl;
		std::getline(std::cin, zmienna1);
		std::cout << "Wpisz nazwisko odkrywcy:" << std::endl;
		std::getline(std::cin, zmienna2);
		dodajZ = new Zabytkowe_rekopisy(nazwa, autor, rok, cena, zmienna1, zmienna2);
		if (dodaj_czy_usun == 1)
		{
			if (pHead->pZ == nullptr) 
				pHead->pZ = dodajZ;
			else
				pHead->pZ->dodaj_obiekt(pHead, dodajZ);
		
		}
		else
		{
			if (pHead->pZ)
				pHead->pZ->usun_obiekt(pHead, dodajZ);
		}

		break;

		break; 

	}

}