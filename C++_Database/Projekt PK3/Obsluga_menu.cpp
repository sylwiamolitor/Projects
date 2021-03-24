#include "Header.h"
#include "Obsluga_menu.h"
#include "operacje_na_elementach.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream> 


void obsluga_menu(Lista *pHead)
{
	char obecna_akcja = '0';

	std::string nazwa;
	std::string rok;
	std::string autor;
	std::string cena;
	std::string zmienna1;
	std::string zmienna2;
	while (obecna_akcja != 'z')
	{
		std::cout << "Witaj w programie do obslugi bazy danych eksponatow!\n Wpisz litere \nw, aby wypisac baze danych,\nz aby zakonczyc i zapisac do pliku zrodlowego obecna baze danych\nd aby dodac nowy element\nu aby usunac element\n";
		switch (obecna_akcja)
		{
		case 'w':
			wypisz_baze(pHead);

			obecna_akcja = getchar();
		case 'z':
			break;
		case 'd': //dodajemy nowy element
			dodaj_lub_usun_element(pHead, nazwa, rok, autor, cena, zmienna1, zmienna2,1);
			break;
		case 'u': //nowy 
			dodaj_lub_usun_element(pHead, nazwa, rok, autor, cena, zmienna1, zmienna2,0);
			break; 


		}

		obecna_akcja = getchar();
		system("cls");
	}
}
void zapisz_do_pliku(Lista *pHead, std::string nazwa_pliku)
{		

	std::ofstream plikWyj(nazwa_pliku);
	if (plikWyj)
	{
		plikWyj.clear();
		if (pHead->pM)
		{
			auto pH = pHead->pM;
			plikWyj << "Male przedmioty" << std::endl;
			while (pH != nullptr)
			{
				plikWyj << pH->wypisz_nazwe() << "|" << pH->wypisz_rok() << "|" << pH->wypisz_autora() << "|" << pH->wypisz_cene() << "|" << pH->jaka_wielkosc() << "|" << pH->jaka_nazwa_malej_rzeczy() << "|" << std::endl;
				pH = pH->pNext;
			}

		}
		if (pHead->pD)
		{
			auto pH = pHead->pD;
			plikWyj << "Duze przedmioty" << std::endl;
			while (pH != nullptr)
			{
				plikWyj << pH->wypisz_nazwe() << "|" << pH->wypisz_rok() << "|" << pH->wypisz_autora() << "|" << pH->wypisz_cene() << "|" << pH->jaka_wielkosc() << "|" << pH->jaka_nazwa_duzej_rzeczy() << "|" << std::endl;
				pH = pH->pNext;
			}
		}
		if (pHead->pO)
		{
			auto pH = pHead->pO;
			plikWyj << "Obrazy" << std::endl;
			while (pH != nullptr)
			{
				plikWyj << pH->wypisz_nazwe() << "|" << pH->wypisz_rok() << "|" << pH->wypisz_autora() << "|" << pH->wypisz_cene() << "|" << pH->czy_obiekt_jest_przestrzenny() << "|" << pH->ile_kolorow() << "|" << std::endl;
				pH = pH->pNext;
			}

		}

		if (pHead->pR)
		{
			auto pH = pHead->pR;
			plikWyj << "Rzezby" << std::endl;
			while (pH != nullptr)
			{
				plikWyj << pH->wypisz_nazwe() << "|" << pH->wypisz_rok() << "|" << pH->wypisz_autora() << "|" << pH->wypisz_cene() << "|" << pH->czy_obiekt_jest_przestrzenny() << "|" << pH->ile_elementow() << "|" << std::endl;
				pH = pH->pNext;
			}

		}
		if (pHead->pS)
		{
			auto pH = pHead->pS;
			plikWyj << "Starodruki" << std::endl;
			while (pH != nullptr)
			{
				plikWyj << pH->wypisz_nazwe() << "|" << pH->wypisz_rok() << "|" << pH->wypisz_autora() << "|" << pH->wypisz_cene() << "|" << pH->czy_oryginal_czy_kopia() << "|" << pH->jaka_nazwa_drukarni() << "|" << std::endl;
				pH = pH->pNext;
			}

		}
		if (pHead->pZ)
		{
			auto pH = pHead->pZ;
			plikWyj << "Zabytkowe rekopisy" << std::endl;
			while (pH != nullptr)
			{
				plikWyj << pH->wypisz_nazwe() << "|" << pH->wypisz_rok() << "|" << pH->wypisz_autora() << "|" << pH->wypisz_cene() << "|" << pH->czy_oryginal_czy_kopia() << "|" << pH->jakie_nazwisko_odkrywcy() << "|" << std::endl;
				pH = pH->pNext;
			}

		}
		plikWyj.close();
	}

}


void wypisz_baze(Lista *pHead)
{
	std::cout << "Wypisuje baze:\n" << std::endl;
	if (pHead->pM != nullptr) /// TU BLAD POWINNO WYKRYWAC NULLPTR -naprawione na poczatku po prostu sztucznie ustawiam na nulltpr
	{
		std::cout << "\nMale przedmioty:\n" << std::endl;
		pHead->pM->wydrukuj_dane(pHead);
	}
	if (pHead->pD != nullptr)
	{
		std::cout << "\nDuze przedmioty:\n" << std::endl;
		pHead->pD->wydrukuj_dane(pHead);
	}
	if (pHead->pO != nullptr)
	{
		std::cout << "\nObrazy:\n" << std::endl;
		pHead->pO->wydrukuj_dane(pHead);
	}
	if (pHead->pR != nullptr)
	{
		std::cout << "\nRzezby:\n" << std::endl;
		pHead->pR->wydrukuj_dane(pHead);
	}
	if (pHead->pS != nullptr)
	{
		std::cout << "\nStarodruki:\n" << std::endl;
		pHead->pS->wydrukuj_dane(pHead);
	}
	if (pHead->pZ != nullptr)
	{
		std::cout << "\nZabytkowe rekopisy:\n" << std::endl;
		pHead->pZ->wydrukuj_dane(pHead);
	}
}

void wczytaj_podstawowe_dane(Lista *pHead, std::string &nazwa, std::string &rok_powstania, std::string &autor, std::string &cena)
{
	std::getline(std::cin, nazwa);
	std::cout << "Wpisz nazwe obiektu, ktory chcesz dodac/usunac" << std::endl;
	std::getline(std::cin, nazwa);
	std::cout << "Wpisz autora obiektu, ktory chcesz dodac/usunac" << std::endl;
	std::getline(std::cin, autor);
	std::cout << "Wpisz rok powstania obiektu, ktory chcesz dodac/usunac" << std::endl;
	std::getline(std::cin, rok_powstania);
	std::cout << "Wpisz cene obiektu, ktory chcesz dodac/usunac" << std::endl;
	std::getline(std::cin, cena);

}
void odczytaj_z_pliku(Lista *pHead, std::string nazwa_pliku)
{
	std::ifstream plikWej(nazwa_pliku);
	std::string znacznik = "|";
	if (plikWej)
	{
		std::string nazwa;
		std::string rok;
		std::string autor;
		std::string cena;
		std::string zmienna1;
		std::string zmienna2;
		std::string kategoria = "Male_przedmioty";
		while (!plikWej.eof()) //czytam do bazy
		{
			std::string linijka;
			std::getline(plikWej, linijka);
			std::size_t foundBeginning;
			std::string uciete;
			if (linijka == "Male przedmioty" || linijka == "Duze przedmioty" || linijka == "Obrazy" || linijka == "Rzezby" || linijka == "Starodruki" || linijka == "Zabytkowe rekopisy")
			{
				kategoria = linijka;
				std::getline(plikWej, linijka);
			}

			for (int i = 0; i < 6; i++)
			{
				foundBeginning = linijka.find(znacznik); 
				uciete = linijka.substr(0, foundBeginning);
				if (uciete == "") 
					break; 
				switch (i)
				{
				case 0:
				{
					nazwa = uciete;
					break;
				}
				case 1:
				{

					rok = uciete;
					break;
				}
				case 2:
				{
					autor = uciete;
					break;
				}
				case 3:
				{
					cena = uciete;
					break;
				}
				case 4:
				{
					zmienna1 = uciete;
					break;
				}
				case 5:
				{
					zmienna2 = uciete;
					break;
				}
				}
				linijka.erase(0, foundBeginning + znacznik.length());
			}
			if (uciete == "")
				continue;
			if (kategoria == "Male przedmioty")
			{
				Male_przedmioty *nowy = new Male_przedmioty(nazwa, rok, autor, cena, zmienna1, zmienna2);
				if (pHead->pM == nullptr)
					pHead->pM = nowy;
				else
					pHead->pM->dodaj_obiekt(pHead, nowy);
			}
			if (kategoria == "Duze przedmioty")
			{
				Duze_przedmioty *nowy = new Duze_przedmioty(nazwa, rok, autor, cena, zmienna1, zmienna2);
				if (pHead->pD == nullptr)
					pHead->pD = nowy;
				else
					pHead->pD->dodaj_obiekt(pHead, nowy);
			}
			if (kategoria == "Obrazy")
			{
				Obrazy *nowy = new Obrazy(nazwa, rok, autor, cena, zmienna1, zmienna2);
				if (pHead->pO == nullptr)
					pHead->pO = nowy;
				else
					pHead->pO->dodaj_obiekt(pHead, nowy);
			}
			if (kategoria == "Rzezby")
			{
				Rzezby *nowy = new Rzezby(nazwa, rok, autor, cena, zmienna1, zmienna2);
				if (pHead->pR == nullptr)
					pHead->pR = nowy;
				else
					pHead->pR->dodaj_obiekt(pHead, nowy);
			}
			if (kategoria == "Starodruki")
			{
				Starodruki *nowy = new Starodruki(nazwa, rok, autor, cena, zmienna1, zmienna2);
				if (pHead->pS == nullptr)
					pHead->pS = nowy;
				else
					pHead->pS->dodaj_obiekt(pHead, nowy);
			}
			if (kategoria == "Zabytkowe rekopisy")
			{
				Zabytkowe_rekopisy *nowy = new Zabytkowe_rekopisy(nazwa, rok, autor, cena, zmienna1, zmienna2);
				if (pHead->pZ == nullptr)
					pHead->pZ = nowy;
				else
					pHead->pZ->dodaj_obiekt(pHead, nowy);
			}
		}
	}
}
