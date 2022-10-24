# Port-Scanner
# Proiect PSO -> implementare aplicatie de tip port-scanner 

Vom utiliza SFML

implementare interfata grafica sau direct din consola? 

# functionalitatea propriu-zisa:
-prima data se face ping catre un device pentru a testa daca exista sau nu in retea
-daca ping-ul a reusit => device-ul exista si poate fi adresat
-se prezinta mai multe optiuni
	-full scan (toate porturile udp/tcp);
	-check for specific port (da portul udp/tcp);
	-check for most common ports (80,22,21,23,8008,8080,etc);

-aplicatia stie sa spuna ce servicii ruleaza pe acele porturi;
-aplicatia stie sa spuna daca tinta foloseste firewall;
-aplicatia stie sa faca quite mode scanning;	
-aplicatia stie ce tip de port este cel dat de user (stie daca portul dat este tcp sau udp, iar daca nu este hardcodat atunci invata);
