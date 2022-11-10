# Proiect PSO -> implementare aplicatie de tip port-scanner 
_Echipa: Banu Teodora & Prelipcean Marius_<br/> 
_Grupa: C113D_

## Introducere
Port scanning-ul reprezinta metoda prin care se poate determina ce porturi sunt deschise intr-o retea.
Porturile reprezinta puncte de legatura virtuale intre device-uri. Ele au rolul de a multiplexa o conexiune, adica mai multe schimburi de date pot avea loc simultan.
Treaba sta cam asa: <br/>![Port_multiplexing](http://www.comefunziona.net/img/fig4.jpg)<br/>
Putem spune ca ele au fost create pentru a asigura trafic preferential diferitor servicii/aplicatii de pe un end device.<br/>
Din schema de mai sus putem intelege ca serviciile, in functie de task-ul pe care trebuie sa-l indeplineasca, sunt dependente de un anumit tip de protocol pentru asigurarea conexiunii (TCP folosit, de exemplu, pentru o aplicatie de email si UDP folosit pentru o aplicatie de live streaming). Pe baza acestui fapt putem imparti porturile in [doua categorii](https://en.wikipedia.org/wiki/List_of_TCP_and_UDP_port_numbers).

## Cum va functiona aplicatia noastra?
Aplicatia va rula pe masinilie cu OS Linux. Aceasta va fi porni cu comanda:
```bash
./portScanner [option1, ..., optionN]
```
De asemenea planuim sa implementam urmatoarele optiuni:
```bash
--help <display invocation options>
--ports <ports to scan>
--ip <IP address to scan>
--file <file name containing IP addresses to scan>
--transport <TCP or UDP>
--ping <optiunea de a verfica daca host is alive before scanning>
```
a caror detalii se regasesc mai jos:
* **help**: afiseaza optiunile disponibile user-ului
* **ports**: by default, port scanner-ul va scana porturile [0-1024], dar prin intermediul acestei comenzi va scana doar porturile specificate in command line
* **ip**/**file**: aceste optiuni dau posibilitatea user-ului sa scaneze un IP anume sau o lista de IP-uri dintr-un fisier
* **transport**: by default, aplicatia va scana toate porturile TCP si UDP, insa ofera optiunea user-ului sa scaneze fie porturile TCP fie cele UDP
#### Network scanner
Prima componenta a aplicatiei noastre va fi un **network scanner**. Rolul acesteia este de a **verifica daca device-ul targetat de user se afla in retea sau nu**. Aceasta componenta se va construi in jurul protocolului **[ICMP](http://www.ping127001.com/pingpage.htm)**.<br/>
Pentru aceasta vom avea nevoie de: 
* structura predefinita [**structicmphdr**](https://docs.huihoo.com/doxygen/linux/kernel/3.7/structicmphdr.html)
```c++
#include <icmp.h>
```


#### Port scanner
todo...


## Ce vom utiliza?
Mediu de dezvoltare:
* Ubuntu vm
* Visual Studio Code


## Progres
#### 11/11/2022
Optiunea 
* ```--ip``` in tcp_connect.c
* ```--ports``` in tcp_all.c
*

