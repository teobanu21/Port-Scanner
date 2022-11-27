# Proiect PSO -> aplicatie de tip port-scanner 
_Echipa: Banu Teodora & Prelipcean Marius_<br/> 
_Grupa: C113D_

## Introducere
Port scanning-ul reprezinta metoda prin care se poate determina ce porturi sunt deschise intr-o retea.
Porturile reprezinta puncte de legatura virtuale intre device-uri. Ele au rolul de a multiplexa o conexiune, adica mai multe schimburi de date pot avea loc simultan.
Treaba sta cam asa: <br/>![Port_multiplexing](http://www.comefunziona.net/img/fig4.jpg)<br/>
Putem spune ca ele au fost create pentru a asigura trafic preferential diferitor servicii/aplicatii de pe un end device.<br/>
Din schema de mai sus putem intelege ca serviciile, in functie de task-ul pe care trebuie sa-l indeplineasca, sunt dependente de un anumit tip de protocol pentru asigurarea conexiunii (TCP folosit, de exemplu, pentru o aplicatie de email si UDP folosit pentru o aplicatie de live streaming). Pe baza acestui fapt putem imparti porturile in [doua categorii](https://en.wikipedia.org/wiki/List_of_TCP_and_UDP_port_numbers).

## Cum va functiona aplicatia noastra?
Aplicatia va rula pe masinilie cu OS Linux.
Pentru a crea executabilul, rulati urmatoarele instructiuni:
```bash 
make clean
```
```bash
make nscan
```
Pentru a rula executabilul, rulati:
```bash
./nscan [option1, ..., optionN]
```
Mai multe detalii in ceea ce priveste utilizarea aplicatiei noastre mai jos:
```bash
--help <display invocation options>
--port <port to scan>
--scan <IP address to scan>
--file <file name containing IP addresses to scan>
--ping <check if host is alive before scanning>
```
* **help**: afiseaza optiunile disponibile user-ului
* **port**: by default, port scanner-ul va scana porturile [0-1024], dar prin intermediul acestei comenzi va scana doar porturile specificate in command line
* **scan**/**file**: aceste optiuni dau posibilitatea user-ului sa scaneze un IP anume sau o lista de IP-uri dintr-un fisier
* **ping**: verifica daca host is alive

Pentru a regasi aceste indrumari si in terminal se va utiliza una dintre urmatoarele comenzi:
```bash
./nscan
```
sau
```bash
./nscan --help
```

## Ce vom utiliza?
Mediu de dezvoltare:
* Ubuntu vm
* Visual Studio Code

## Surse
#### socket()
* https://linux.die.net/man/3/socket
* https://stackoverflow.com/questions/64256922/in-socket-programming-using-c-language-how-to-set-time-limit-on-server-for-acce
* 

#### struct sockaddr_in, struct in_addr
* https://www.gta.ufrj.br/ensino/eel878/sockets/sockaddr_inman.html

#### gethostbyaddr + netdb.h
* https://www.ibm.com/docs/en/ztpf/1.1.0.15?topic=apis-gethostbyaddr-get-host-information-ip-address
* http://www.qnx.com/developers/docs/qnxcar2/index.jsp?topic=%2Fcom.qnx.doc.neutrino.lib_ref%2Ftopic%2Fh%2Fhostent.html

#### inet_aton()
* https://www.ibm.com/docs/en/zos/2.5.0?topic=lf-inet-aton-convert-internet-address-format-from-text-binary

#### arpa/inet.h
* https://pubs.opengroup.org/onlinepubs/7908799/xns/arpainet.h.html




## Progres
#### 27/11/2022
Optiuni functionale: 
```bash
./nscan
```
```bash
./nscan --help
```
```bash
./nscan --ip 8.8.8.8 #or any other IP address
```
```bash
./nscan --port 53 8.8.8.8 #or any other port or IP address
```
```bash
./nscan --port 53 dns.google #or any other port or domain name
```
```bash
./nscan --file example.txt #or any other file
```
```bash
./nscan --ping 8.8.4.4 #or any other IP
```
```bash
./nscan --ping dns.google #or any other domain name
```

#### todo:
* Improve multithread part
* Add supported file extentions for ```--file``` option
* Make connect non blocking for tcp_all func
* Resolve todo's...