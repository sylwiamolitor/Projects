#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "pch.h"
#include <chrono>


/* Temat projektu : Desaturacja

 Krótki opis algorytmu : Algorytm zmniejsza saturacjê, czyli nasycenie bitmapy.
 Odbywa siê to przez przeliczenie RGB na HSL, odjêcie podanej wartoœci S i powrót do RGB.
 Szczegó³owy opis algorytmu w raporcie.
 Datê wykonania projektu : 31.12.2020r.
 Semestr / Rok akademicki 5 semestr 2020 / 2021
 nazwisko autora Molitor Sylwia
 Aktualn¹ wersjê programu i historiê zmiany funkcjonalnoœci w kolejnych wersjach : wersja 1.0
 */


extern "C"
{
	/*Funkcja wyliczaj¹ca R,G,B na podstawie float p, float q i float t, wyliczonych wczeœniej z H, S, L, zwraca wartoœæ typu float.*/
	float HSLdoRGB(float p, float q, float t)
	{
		//wartoœæ musi byæ w przedziale [0,1]
		if (t < 0)
			t += 1;
		if (t > 1)
			t -= 1;

		//w³aœciwe wyliczenie
		if (t < 1.0 / 6.0)
			return p + (q - p) * 6 * t;
		if (t < 1.0 / 2.0)
			return q;
		if (t < 2.0 / 3.0) 
			return p + (q - p) * (2.0 / 3.0 - t) * 6;

		return p;
	}

	/*Funkcja wywo³ywana z C#, w której nastêpuje przekszta³cenie bitmapy. Jest w niej wywo³ywana funkcja HSLdoRGB
	Przyjmuje BYTE* obraz - wskaŸnik na bitmapê lub jej fragment
	float wartoscDesaturacji - od 0 do 1, wartoœæ, o któr¹ zmniejszy siê saturacja
	int wielkosc - okreœla ostatni przetwarzany piksel (koñcowy)
	int poczatek - okreœla pierwsza przetwarzany piksel (pocz¹tkowy)
	int bufor - wyliczony bufor
	int szerokosc - szerokoœæ bitmapy*/

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

			//wybieramy wartoœæ maksymaln¹ i minimaln¹ z pikseli
			float Maksymalna = max(max(r, g), b);
			float Minimalna = min(min(r, g), b);


			//inicjujemy zmienne, na których bêdziemy liczyæ HSL
			float h = 0.0;
			float s = 0.0;
			float l = (Maksymalna + Minimalna) / 2.0; //wyliczamy œrednie œwiat³o bia³e




			if (Maksymalna == Minimalna)
			{
				h = s = 0.0; // jeœli maksymalna wartoœæ jest równa minimalnej to odcieñ i nasycenie s¹ równe 0
			}
			else
			{
				float delta = Maksymalna - Minimalna;
				//wyliczamy nasycenie
				if (l > 0.5)
					s = delta / (2.0 - Maksymalna - Minimalna);
				else
					s = delta / (Maksymalna + Minimalna);
				//wyliczamy odcieñ - w zale¿noœci od tego jaki kolor ma wartoœæ maksymaln¹(czerwony, zielony lub niebieski) stosujemy inny wzór
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

			//zmniejszamy saturacjê o podan¹ przez u¿ytkownika wartoœæ w przedziale [0-1]

			s -= wartoscDesaturacji;
			if (s < 0) //saturacja nie mo¿e byæ ujemna
				s = 0;

			if (s == 0)
			{
				r = g = b = l; // jeœli nasycenie jest równe 0, to r,g,b s¹ równe œredniemu œwiatle bia³emu
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

			//wracamy do w³aœciwego formatu zapisu [0-255] i zamieniamy piksele
			obraz[i] = round(b * 255);
			obraz[i + 1] = round(g * 255);
			obraz[i + 2] = round(r * 255);

		}
	}
	
}

