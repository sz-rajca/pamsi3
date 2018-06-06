# Gra w kółko i krzyżyk
Do implementacji gry został wykorzystany algorytm Minimax. Gra, dla zadanego przez użytkownika rozmiaru planszy, symuluje przeciwnika dla gracza.

Algorytm ma funkcję oceniającą aktualną wartość stanu gry. Gracz min chce stan zminimalizować, a gracz max zmaksymalizować. Funkcja oceniająca oblicza drzewo wszystkich możliwych stanów w grze do pewnej głębokości. Ocena rozpoczyna się od stanów końcowych, symulując optymalne wybory dla obu graczy. Dzięki temu gracz min zawsze wybiera ruch, który prowadzi do zmniejszenia wartości końcowej, a gracz max – do zwiększenia.

Dla gry na planszy 3 x 3, algorytm nigdy nie przegrał. W przypadku planszy 4 x 4, poprzez użycie małej głębokości dla funkcji oceniającej spowodowane małą mocą obliczeniową, algorytm jedynie broni się przed porażką.
