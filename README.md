# Port-Scanner
## Proiect PSO -> implementare aplicatie de tip port-scanner

### Introducere
Port scanning-ul reprezinta metoda prin care se poate determina ce porturi sunt deschise intr-o retea.
Porturile reprezinta puncte de legatura virtuale intre device-uri. Ele au rolul de a multiplexa o conexiune, adica mai multe schimburi de date pot avea loc simultan.
Treaba sta cam asa: ![Port_multiplexing](http://www.comefunziona.net/img/fig4.jpg)

Vom utiliza [SFML](https://www.sfml-dev.org/documentation/2.5.1/group__network.php) pentru:
* partea de networking
* partea de GUI?

implementare interfata grafica sau direct din consola? 

## functionalitatea propriu-zisa:
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
