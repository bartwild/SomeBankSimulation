W moim zadaniu wzorowałem się na wzorcu fabryki. Dzięki niemu mogę tworzyc nowe obiekty (kredyty) nie musząc od razu precyzowac jaka ma byc to klasa - program sam dokona decyzji na podstawie danych. Dodatkowo program działa rekursywnie tak jak się to odbywa we wzorcu komponentu - klasy kolejno wykonują zadane czynności, lecz klient może także sam sprawdzać potrzebne wartości (oczywiście w granicach tego, o ile takie sprawdzenie jest realne i ma sens).
Dziedziczenie odbywa się na zasadzie:
- Z ogólnego Banku dziedziczą jego oddziały odpowiedzialne za poszczególne kredyty.
- Z ogólnego kredytu dziedziczą poszczególne rodzaje kredytów.
- Przy wywoływaniu ogólnej metody zrobienia czegoś - wzięcie kredytu etc. wywoływana jest z poziomu Banku metoda jednego z oddziałów.
- Można wywoływać metody klas dziedziczących bezpośrednio, wskazując na klasę bazową.

Inteligentne wskaźniki:
- Ze względu na wielokrotne przekazywanie wskaźników zdecydowałem się na shared_ptr, które zapewniają mi taką możliwość.
- Zaimplementowałem przekazywanie aktualnego obiektu (this) za pomocą shared_ptr.
- Zaletą shared_ptr jest to że wiele wskaźników może wskazywać na ten sam obiekt, jednak jest usuwany dopiero po usunięciu ostatniego ze wskaźników.

W czym aktualna implementacja jest lepsza:
- Czytelniejsze metody klas i same klasy - widać od razu co się do czego odwołuje. Wszystko jest logiczniej poukładane i dziedziczy po odpowiednich ogólnych klasach, co pomaga w zrozumieniu problemu.
- Inteligentne wskaźniki pozwalają nam na działanie w programie bez konieczności używania delete[]
- Wzorzec fabryki daje nam przejrzystość kodu, o czym już mówiłem, ale także poprawia zdolność programu do dalszego rozwoju poprzez dziedziczenie na kolejne klasy.
- Bardziej przejrzyste testowanie kodu - możliwość odwołań do oddziałów, ale także działanie poprzez same dane wprowadzane do programu
