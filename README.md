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
#### Network scanner
Prima componenta a aplicatiei noastre va fi un **network scanner**. Rolul acesteia este de a **verifica daca device-ul targetat de user se afla in retea sau nu**. Aceasta componenta se va construi in jurul protocolului **[ICMP](http://www.ping127001.com/pingpage.htm)**.<br/>
<br/>
#### Port scanner
In mare, **port scanner-ul se bazeaza pe trimiterea de requests catre porturile unui device din retea si interpretarea reaspunsurilor generate**. **In functie de tipul de serviciu** care ruleaza pe un anumit port si **constructia mesajului de request difera**. Daca acest fapt nu este luat in considerare, nu avem garantia ca raspunsul generat este reliable si poate fi interpretat gresit (de exemplu, daca formatul pentru un http request nu este respectat si este trimis catre portul 80, exista posibilitatea ca acesta sa nu raspunda request-ului nostru si poate fi interpretat fie drept port inchis, fie drept firewall in place). De aceea vom implementa un **["dictionar al porturilor"](https://en.wikipedia.org/wiki/List_of_TCP_and_UDP_port_numbers)** la nivelul aplicatiei noastre. Totusi, ne dorim sa implementam si o **componenta de invatare** in cadrul aplicatiei noastre, adica, atunci cand nu stie cum sa construiasca un request pentru un anume port, va folosi metoda **trial and error** si va invata **ce serviciu ruleaza pe acel port**.<br/> 

## Ce vom utiliza?
Vom utiliza [SFML](https://www.sfml-dev.org/index.php) pentru:
* partea de [networking](https://www.sfml-dev.org/documentation/2.5.1/group__network.php)
* partea de [GUI](https://www.sfml-dev.org/documentation/2.5.1/group__graphics.php)?
implementare interfata grafica sau direct din consola? 

## Functionalitati:
* prima data se face ping catre un device pentru a testa daca exista sau nu in retea (Network scanning);
* daca ping-ul a reusit => device-ul exista si poate fi adresat;
```c++
//Linux side
//TODO Win side with icmpapi.h?
#include <iostream>

using namespace std;

int main() {
    int x = system("ping -c1 -s1 8.8.8.8  > /dev/null 2>&1");
    
    if (x == 0) {
        cout << "success";
    } 
    else {
        cout << "failed";
    }

    return 0;
}
```
* se prezinta mai multe optiuni
  *	full scan (toate porturile udp/tcp);
  *	check for specific port (da portul udp/tcp);
  *	check for most common ports (80,22,21,23,8008,8080,etc);<br/> 
* aplicatia stie sa spuna ce servicii ruleaza pe acele porturi;
* aplicatia stie sa spuna daca tinta foloseste firewall;
* aplicatia stie sa faca quite mode scanning;	
* aplicatia stie ce tip de port este cel dat de user (stie daca portul dat este tcp sau udp, iar daca nu este hardcodat atunci invata);

## Surse:
* https://github.com/davidgatti/How-to-Understand-Sockets-Using-IoT
* https://github.com/davidgatti/How-to-Deconstruct-Ping-with-C-and-NodeJS
* http://www.codeproject.com/KB/IP/winping.aspx
* http://tangentsoft.net/wskfaq/examples/rawping.html
* https://learn.microsoft.com/fr-fr/windows/win32/api/icmpapi/nf-icmpapi-icmpsendecho?redirectedfrom=MSDN
* https://commschamp.github.io/comms_protocols_cpp/
* https://www.sfml-dev.org/tutorials/2.5/network-http.php
* ...
