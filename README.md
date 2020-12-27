## Networking
Jest to API dla całej reszty programu izolujące część sieciową. Odpowiada za logikę wysyłania i odbierania paczek arpingu z użyciem wielowątkowości. Na razie mamy szkielet programu, TODO jest jego przetestowanie.
## Usage
Dla uruchomienia testu przykładowego:
1. Uzupełnić makra PREFIX (podsieć lokalna, w której będzie szukana maszyna o podanym MACu) i MAC w ``` test/test_ip_getter_manual.cpp ```.
2. ```cd networking/```
3. ```make arping```
4. ```make test```
5. ```../test/test_ip_getter_manual.x```
