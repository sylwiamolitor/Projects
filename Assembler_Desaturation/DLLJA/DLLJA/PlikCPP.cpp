#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "pch.h"
#include <chrono>


/* Temat projektu : Desaturacja

 Kr�tki opis algorytmu : Algorytm zmniejsza saturacj�, czyli nasycenie bitmapy.
 Odbywa si� to przez przeliczenie RGB na HSL, odj�cie podanej warto�ci S i powr�t do RGB.
 Szczeg�owy opis algorytmu w raporcie.
 Dat� wykonania projektu : 31.12.2020r.
 Semestr / Rok akademicki 5 semestr 2020 / 2021
 nazwisko autora Molitor Sylwia
 Aktualn� wersj� programu i histori� zmiany funkcjonalno�ci w kolejnych wersjach : wersja 1.0
 */


extern "C"
{
	/*Funkcja wyliczaj�ca R,G,B na podstawie float p, float q i float t, wyliczonych wcze�niej z H, S, L, zwraca warto�� typu float.*/
	float HSLdoRGB(float p, float q, float t)
	{
		//warto�� musi by� w przedziale [0,1]
		if (t < 0)
			t += 1;
		if (t > 1)
			t -= 1;

		//w�a�ciwe wyliczenie
		if (t < 1.0 / 6.0)
			return p + (q - p) * 6 * t;
		if (t < 1.0 / 2.0)
			return q;
		if (t < 2.0 / 3.0) 
			return p + (q - p) * (2.0 / 3.0 - t) * 6;

		return p;
	}

	/*Funkcja wywo�ywana z C#, w kt�rej nast�puje przekszta�cenie bitmapy. Jest w niej wywo�ywana funkcja HSLdoRGB
	Przyjmuje BYTE* obraz - wska�nik na bitmap� lub jej fragment
	float wartoscDesaturacji - od 0 do 1, warto��, o kt�r� zmniejszy si� saturacja
	int wielkosc - okre�la ostatni przetwarzany piksel (ko�cowy)
	int poczatek - okre�la pierwsza przetwarzany piksel (pocz�tkowy)
	int bufor - wyliczony bufor
	int szerokosc - szeroko�� bitmapy*/

	_declspec(dllexport) void wczytaj(BYTE* obraz, float wartoscDesaturacji, int wielkosc, int poczatek, int bufor, int szerokosc)
	{


		for (int i = poczatek; i < wielkosc; i += 3)
		{

			if (i == szerokosc)
			{
				//trafiono na koniec wiersza - przeskocz bufor
				i += bufor;
			}

			float b = obraz[i]; //czytamy piksel niebieski
			float g = obraz[i + 1]; //czytamy piksel zielony
			float r = obraz[i + 2]; //czytamy piksel czerwony

			//dzielimy wszystkie przez 255
			b /= 255.0;
			g /= 255.0;
			r /= 255.0;

			//wybieramy warto�� maksymaln� i minimaln� z pikseli
			float Maksymalna = max(max(r, g), b);
			float Minimalna = min(min(r, g), b);


			//inicjujemy zmienne, na kt�rych b�dziemy liczy� HSL
			float h = 0.0;
			float s = 0.0;
			float l = (Maksymalna + Minimalna) / 2.0; //wyliczamy �rednie �wiat�o bia�e




			if (Maksymalna == Minimalna)
			{
				h = s = 0.0; // je�li maksymalna warto�� jest r�wna minimalnej to odcie� i nasycenie s� r�wne 0
			}
			else
			{
				float delta = Maksymalna - Minimalna;
				//wyliczamy nasycenie
				if (l > 0.5)
					s = delta / (2.0 - Maksymalna - Minimalna);
				else
					s = delta / (Maksymalna + Minimalna);
				//wyliczamy odcie� - w zale�no�ci od tego jaki kolor ma warto�� maksymaln�(czerwony, zielony lub niebieski) stosujemy inny wz�r
				if (Maksymalna == r)
				{
					h = (g - b) / delta;
					if (g < b)
						h += 6.0;
				}
				else if (Maksymalna == g)
					h = (b - r) / delta + 2.0;
				else if (Maksymalna == b)
					h = (r - g) / delta + 4.0;
				h /= 6.0;
			}

			//zmniejszamy saturacj� o podan� przez u�ytkownika warto�� w przedziale [0-1]

			s -= wartoscDesaturacji;
			if (s < 0) //saturacja nie mo�e by� ujemna
				s = 0;

			if (s == 0)
			{
				r = g = b = l; // je�li nasycenie jest r�wne 0, to r,g,b s� r�wne �redniemu �wiatle bia�emu
			}
			else
			{
				//przeliczamy HSL na RGB
				float q;
				if (l < 0.5)
					q = l * (1.0 + s);
				else
					q = l + s - l * s;
				float p = 2.0 * l - q;
				r = HSLdoRGB(p, q, h + 1.0 / 3.0);
				g = HSLdoRGB(p, q, h);
				b = HSLdoRGB(p, q, h - 1.0 / 3.0);
			}

			//wracamy do w�a�ciwego formatu zapisu [0-255] i zamieniamy piksele
			obraz[i] = round(b * 255);
			obraz[i + 1] = round(g * 255);
			obraz[i + 2] = round(r * 255);

		}
	}
	
}

