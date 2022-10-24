# Port-Scanner
# Proiect PSO -> implementare aplicatie de tip port-scanner

## Introducere
Port scanning-ul reprezinta metoda prin care se poate determina ce porturi sunt deschise intr-o retea.
Porturile reprezinta puncte de legatura virtuale intre device-uri. Ele au rolul de a multiplexa o conexiune, adica mai multe schimburi de date pot avea loc simultan.
Treaba sta cam asa: ![Port_multiplexing](http://www.comefunziona.net/img/fig4.jpg)<br/>
Putem spune ca ele au fost create pentru a asigura trafic preferential diferitor servicii/aplicatii de pe un end device.<br/>
Din schema de mai sus putem intelege ca serviciile, in functie de task-ul pe care trebuie sa-l indeplineasca, sunt dependente de un anumit tip de protocol pentru asigurarea conexiunii (TCP folosit de exemplu pentru o aplicatie de email si UDP folosit pentru o aplicatie de live streaming). Pe baza acestui fapt putem imparti porturile in [doua categorii](https://en.wikipedia.org/wiki/List_of_TCP_and_UDP_port_numbers)

Vom utiliza SFML pentru:
* partea de [networking](https://www.sfml-dev.org/documentation/2.5.1/group__network.php)
* partea de GUI?

implementare interfata grafica sau direct din consola? 

## Functionalitatea propriu-zisa:
* prima data se face ping catre un device pentru a testa daca exista sau nu in retea
* daca ping-ul a reusit => device-ul exista si poate fi adresat
* se prezinta mai multe optiuni
  *	full scan (toate porturile udp/tcp);
  *	check for specific port (da portul udp/tcp);
  *	check for most common ports (80,22,21,23,8008,8080,etc);

* aplicatia stie sa spuna ce servicii ruleaza pe acele porturi;
* aplicatia stie sa spuna daca tinta foloseste firewall;
* aplicatia stie sa faca quite mode scanning;	
* aplicatia stie ce tip de port este cel dat de user (stie daca portul dat este tcp sau udp, iar daca nu este hardcodat atunci invata);
