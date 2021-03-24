.data 

dzielnikPiksela dd 255.0
dwa dd 2.0
zero dd 0.0
pol dd 0.50000
szesc dd 6.0
cztery dd 4.0
jeden dd 1.0
jednaTrzecia dd 0.3333333333333333
jednaSzosta dd 0.1666666666666667
dwieTrzecie dd 0.6666666666666667

.code

;Temat projektu : Desaturacja

;Krótki opis algorytmu : Algorytm zmniejsza saturacjê, czyli nasycenie bitmapy. 
;Odbywa siê to przez przeliczenie RGB na HSL, odjêcie podanej wartoœci S i powrót do RGB.
;Szczegó³owy opis algorytmu w raporcie.

;Datê wykonania projektu : 31.12.2020r.
;Semestr/Rok akademicki 5 semestr 2020/2021
;nazwisko autora Molitor Sylwia
;Aktualn¹ wersjê programu i historiê zmiany funkcjonalnoœci w kolejnych wersjach: wersja 1.0


MyProc1 proc
	pop r11						;od³o¿enie u¿ywanych rejestrów na stos
	pop r10
	push rax					
	push rbx
	push rcx
	push rsi
	push r8
	push r9


	xor rax, rax				;odpowiednik mov rax, 0 - wyzerowanie

	mov rsi, r9					;rsi licznik pêtli
	movups xmm15, xmm1			;desaturacja do xmm15
	mov rbx, r9					;adres poczatku do rbx
	Petla:
	cmp rsi, r8					;czy obecny piksel == koniec tablicy
	jge Koniec					;koniec

	cmp rsi, r11				;czy obecny piksel == szerokosc warunek dodania bufora
	jne Dodawanie
	add rsi, r10				;i += bufor

	Dodawanie:

	mov rbx, rsi				;indeks piksela do rbx
	
	



	mov al, byte ptr[rbx+rcx] ;bierzemy b
	CVTSI2SS  xmm2, eax
	mov al, byte ptr[rbx+rcx+1] ;bierzemy g
	CVTSI2SS  xmm1, eax
	mov al, byte ptr[rbx+rcx+2] ;bierzemy r
	CVTSI2SS  xmm0, eax

	;255 dzielnik
	movups xmm10, dzielnikPiksela 
	
	
	;dzielimy wszystkie piksele przez 255
	divss xmm2, xmm10
	divss xmm1, xmm10
	divss xmm0, xmm10

	;wybieramy wartoœæ maksymaln¹ i minimaln¹ z pikseli
	;max xmm3
	;min xmm4

	movups xmm3, xmm0 
	maxps xmm3, xmm1
	maxps xmm3, xmm2

	movups xmm4,xmm0
	minps xmm4, xmm1
	minps xmm4, xmm2

	;H - xmm5
	;S - xmm6
	;L - xmm7
	movups xmm7, xmm3 ; L=max
	addss xmm7, xmm4 ; L=min+max 
	divss xmm7, dwa ; L=(min+max)/2
	
	;mamy L

	comiss xmm3, xmm4 ; jesli max==min to H i S = 0
	jne NormalneHS	; w przeciwnym razie skok do obliczenia H i S
	movss xmm5, zero
	movss xmm6, zero
	jmp OdejmujemySaturacje ; skok do odejmowania saturacji

	
	NormalneHS:
	;delta - xmm8
	movups xmm8, xmm3
	subss xmm8, xmm4 ;delta = max - min;

	;jesli L>0.5
	movups xmm6, xmm8 ; S = delta
	subss xmm7, pol ; L -= 0.5
	comiss xmm7, zero ; jesli L>0.5 nie jest spelnione to nastepuje skok do MaleL
	jna MaleL 
	;w xmm9 umieszczamy mianownik: 2 - max - min
	movups xmm9, dwa
	subss xmm9, xmm4
	subss xmm9, xmm3
	divss xmm6, xmm9  ; S=delta/(2-max-min)
	jmp MamSaturacje
	MaleL:
	addss xmm4, xmm3 ; min = max+min
	divss xmm6, xmm4 ; S=delta/(max-min)
	;gotowe S
	MamSaturacje:
	addss xmm7, pol ;L+=0.5 aby przywrocic wartosc przed wyliczeniem S
	
	;wyliczamy H

	comiss xmm0, xmm3 ;jesli r==max
	jne Krok2	
	movups xmm5, xmm1
	subss xmm5, xmm2
	divss xmm5, xmm8 ; H = (g-b)/delta

	comiss xmm1, xmm2 ;jesli g>b 
	ja MamSaturacjeIOdcien
	addss xmm5, szesc
	jmp MamSaturacjeIOdcien

	Krok2:
	comiss xmm1, xmm3 ;g==max
	jne Krok3
	movups xmm5, xmm2
	subss xmm5, xmm0
	divss xmm5, xmm8
	addss xmm5, dwa ;H=(b-r)/delta

	jmp MamSaturacjeIOdcien
	Krok3:
					 ;b nie trzeba sprawdzaæ
	movups xmm5, xmm0
	subss xmm5, xmm1
	divss xmm5, xmm8
	addss xmm5, cztery ;H=(r-g)/delta

	MamSaturacjeIOdcien:
	divss xmm5, szesc ;H/=6
	;mamy H

	OdejmujemySaturacje:

	subss xmm6, xmm15 ;odjecie podanej wartosci S

	comiss xmm6, zero ;czy S<0, jesli tak to S=0
	ja PowrotDoRGB
	movss xmm6, zero 

	PowrotDoRGB:
	comiss xmm6, zero ;czy S=0, jesli nie skok do Przeliczanie, jesli tak to R = G = B = L
	jne Przeliczanie

	movss xmm0, xmm7
	movss xmm1, xmm7
	movss xmm2, xmm7 
	jmp Powrot
	
	
	Przeliczanie:

	comiss xmm7, pol ;jesli L<0.5 to skok do Lmniejsze
	jnae Lmniejsze 

	;l+s-ls
	movss xmm12, xmm7 ; q=L
	addss xmm12, xmm6 ; q=L+S
	movss xmm13, xmm7 ; l
	mulss xmm13, xmm6 ; l*s
	subss xmm12, xmm13 ; q = L+S - L*S
	jmp Dalej

	Lmniejsze:
	movss xmm12, xmm6
	addss xmm12, jeden
	mulss xmm12, xmm7 ;mamy q=L*(S+1) w xmm12

	Dalej:
	movss xmm14, xmm7
	mulss xmm14, dwa
	subss xmm14, xmm12 ;mamy p =2*L-q w xmm14

	movups xmm9, xmm15 ;wartosc desaturacji przeniesiona do xmm9, gdyz xmm15 wykorzystujemy w dalszych obliczeniach
	
	;wywolanie podfunkcji - wynik w xmm15
	;licznik skokow - xmm3

	movss xmm3, jeden ;w xmm3 1
	movss xmm13, xmm5
	addss xmm13, jednaTrzecia ; t= H+1/3

	jmp HSLdoRGB

	PowrotZPierwszejPodfunkcji:

	addss xmm3, jeden ;w xmm3 2
	movss xmm0, xmm15 ; r


	movss xmm13, xmm5 ;t=H
	jmp HSLdoRGB

	PowrotZDrugiejPodfunkcji:

	addss xmm3, jeden ;w xmm3 3
	movss xmm1, xmm15 ;g

	movss xmm13, xmm5
	subss xmm13, jednaTrzecia  ;t=H-1/3
	jmp HSLdoRGB

	PowrotZTrzeciejPodfunkcji:

	movss xmm2, xmm15 ;b

	movups xmm15, xmm9 ; powrot desaturacji do xmm15
	Powrot:
	;mno¿ymy przez 255
	mulss xmm2, xmm10
	mulss xmm1, xmm10
	mulss xmm0, xmm10

	;zapis

	CVTSS2SI eax,xmm2 ;B
	mov [rbx+rcx], al 

	CVTSS2SI eax,xmm1 ;G
	mov [rbx+rcx+1], al 


	CVTSS2SI eax,xmm0 ;R
	mov [rbx+rcx+2], al

	
;	i+=3
	inc rsi	
	inc rsi	
	inc rsi						;inkrementacja licznika pêtli wewnêtrznej

	jmp Petla					;wracamy do pêtli wewnêtrznej

Koniec:
	xor rax, rax
	pop r9
	pop r8
	pop rsi
	pop rcx
	pop rbx
	pop rax
	push r10
	push r11
ret



HSLdoRGB:

		comiss xmm13, zero	;jesli (t < 0)
		jna MniejNizZero		;jesli warunek spelniony to inkrementacja t o 1
		jmp CzyWiekszeOdJeden 

		MniejNizZero:
		addss xmm13, jeden ;t+=1

		CzyWiekszeOdJeden:
		comiss xmm13, jeden	;jesli (t> 1)
		ja WiekszeOdJeden ;jesli warunek spelniony to dekrementacja t o 1
		jmp Wyliczenie

		WiekszeOdJeden: 
		subss xmm13, jeden ;t-=1

		Wyliczenie:
		comiss xmm13, jednaSzosta ;jesli (t < 1.0 / 6.0)
		jae Wyliczenie2 ;jesli warunek niespelniony
		movss xmm15, xmm12 ; q
		subss xmm15, xmm14 ; q-p
		mulss xmm15, szesc ;(q-p)*6
		mulss xmm15, xmm13	;(q-p)*6*t
		addss xmm15, xmm14	;(q-p)*6*t + p
		jmp przygotowanieDoPowrotu	;return p + (q - p) * 6 * t;

		Wyliczenie2:
		comiss xmm13, pol  ;jesli (t < 1.0 / 2.0)
		jae Wyliczenie3 ;jesli warunek niespelniony
		movups xmm15, xmm12 ; q
		jmp przygotowanieDoPowrotu;return q

		Wyliczenie3:
		comiss xmm13, dwieTrzecie  ;jesli (t < 2.0 / 3.0)
		jae Wyliczenie4 ;jesli warunek niespelniony
		movss xmm11, xmm12 ;q
		subss xmm11, xmm14 ; q-p
		movss xmm15, dwieTrzecie ;2/3
		subss xmm15, xmm13 ;2/3 - t
		mulss xmm15, xmm11 ;(2/3 - t) * (q - p)
		mulss xmm15, szesc ;(2/3 - t) * (q - p) * 6
		addss xmm15, xmm14 ;(2/3 - t) * (q - p) * 6 + p 
		jmp przygotowanieDoPowrotu ;return p + (q - p) * (2.0 / 3.0 -t) * 6;

		Wyliczenie4:
		movss xmm15, xmm14 ;p
		jmp przygotowanieDoPowrotu ;return p


		przygotowanieDoPowrotu:
		comiss xmm3, jeden ;jesli to bylo wyliczenie r
		je PowrotZPierwszejPodfunkcji 

		comiss xmm3, dwa ;jesli to bylo wyliczenie g
		je PowrotZDrugiejPodfunkcji
		jmp PowrotZTrzeciejPodfunkcji ;jesli to bylo wyliczenie b


MyProc1 endp

end

