## Networking
Jest to API dla całej reszty programu izolujące część sieciową. Odpowiada za logikę wysyłania i odbierania paczek arpingu z użyciem wielowątkowości. Na razie mamy szkielet programu, TODO jest jego przetestowanie.
## Usage
Dla uruchomienia testu przykładowego:
1. Uzupełnić stałe PREFIX (podsieć lokalna, w której będzie szukana maszyna o podanym MACu) i MAC w ``` networking/config.h ``` (ewentualnie też iface).
2. ```cd networking/```
3. ```make arping; make test_with_arping``` w wersji programu, używającego **arping** dla wysyłania i przechwytywania pakietów
4. ```make libcrafter; make test_with_crafter``` w wersji programu, używającego **libcrafter** dla wysyłania i przechwytywania pakietów
5. ```../test/test_ip_getter_manual.x```
