Dana jest tabela długości dróg łączących bezpośrednio miasta A...H. Drogi są nieskierowane i można nimi przemieszczać się w obu kierunkach. Z tego względu tablica jest wypełniona niesymetrycznie. Jeżeli jest podana długość drogi od miasta M1 do miasta M2, to znaczy, że taka sama jest długość drogi z miasta M2 do M1, gdzie M1 i M2 należą do A...H. Puste miejsce w prawej, górnej części tablicy oznacza brak bezpośredniego połączenia między daną parą miast (i konieczność jeżdżenia poprzez inne miasta).
 
 
 
 
 B
C
 
 
 
 D
E
 
 
F
 
 
G
 
 
H
 
A
12
20
8
 
  
5
 
 
B
--
29
66
69
28
 
C
--
 
74
 
 
D
--
6
44
 
20
 
28
 
E
--
65
 
74
 
2
 
F
--
 
  
 
 
G
 
 
 
 
 
 
--
 
20
 
 W węzłach F, C i D znajdują się dostawcy; dysponujący towarem w ilości odpowiednio: 50, 40 i 20. Zapotrzebowanie odbiorców wynosi B - 40, E - 35; G - 20; H - 10 i A - 5. Koszt przewiezienia jednostki towaru jest proporcjonalny do odległości, na jaką towar jest przewożony. Należy przewieźć towar od dostawców do odbiorców przy jak najniższym łącznym koszcie przewozu. Uwaga, można założyć, że przepustowość dróg jest dostatecznie duża, żeby można traktować ją jako nieograniczoną.
1. Narysować sieć przepływową modelującą dany problem, określając wszystkie parametry każdego z jej elementów.
2. Dla każdej pary dostawca odbiorca wyznaczyć najkrótszą drogę przesyłania towaru.
3. Sformułować zadanie transportowe w postaci tabelarycznej (obejmujące tylko dostawców i odbiorców)
4. Sformułować równoważne zadanie programowania liniowego.
5. Wyznaczyć możliwie dobre początkowe rozwiązanie dopuszczalne zadania transportowego i obliczyć odpowiadający mu koszt przewozu.
6. Sformułować zadanie programowania liniowego modelujące dany problem przewiezienia towaru w sieci, gdy oprócz kosztów przewozu proporcjonalnych do ilości towaru i odległości (przyjąć, że długości odcinków są podane w kilometrach a jednostkowy koszt przewozu jest równy 10 zł/km) należy uwzględnić stały koszt posługiwania się poszczególnymi odcinkami dróg pomiędzy miastami, niezależny od ilości towaru (koszt ten ponosi się wówczas, gdy danym odcinkiem transportuje się jakąkolwiek ilość towaru większa od zera), równy długości odcinka pomnożonej przez 300 zł.
