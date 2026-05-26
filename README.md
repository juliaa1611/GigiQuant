#GIGIQUANT - Manager de portofoliu

 DESCRIEREA PROIECTULUI:

 Acest proiect conține o serie de 4 task-uri și un bonus structurate sub forma unor interviuri pentru poziția de manager de portofoliu la compania fictivă „GigiQuant”. Scopul principal este utilizarea unor structuri de date clasice (liste, stive, cozi, arbori binari, grafuri) și dezvoltarea de algoritmi pentru a rezolva probleme concrete din domeniul financiar.

 Toate cerințele și detaliile de implementare sunt bazate pe documentul de referință ProiectPA_GigiQ.pdf.

 COMPONENETELE PROIECTULUI:

 Task 1: Sharpe Ratio
Descriere: Se evaluează performanța și profitabilitatea unui portofoliu raportată la riscul asumat.
 Implementare: Evoluția portofoliului este implementată prin liste simplu înlănțuite care stochează valorile și randamentele zilnice. Pe baza acestora, algoritmul calculează randamentul mediu și volatilitatea (deviația standard), afișând indicatorul Sharpe Ratio trunchiat la 3 zecimale.

 Task 3: Diversificarea Portofoliului
Descriere: Optimizează un portofoliu prin combinarea unor acțiuni volatile în oglindă pentru a obține o structură stabilă.
 Implementare: Mișcările zilnice ale prețurilor (creșteri sau scăderi) sunt stocate recursiv într-un arbore binar. Prin parcurgerea structurii generate, algoritmul identifică „opusul” sau oglinditul fiecărei acțiuni pentru a realiza diversificarea.

 Task 4: Lanțuri Markov
 Descriere: Se calculează șansele ca o acțiune să ajungă de la un anumit preț la un preț țintă după un număr de zile.
 Implementare: Prețurile sunt grupate în intervale fixe de dimensiune K, fiecare interval fiind un nod din graf. Programul parcurge graful zilnic pentru a calcula probabilitatea finală ca o acțiune să ajungă de la un preț de start la un preț țintă într-un interval de zile. Rezultatul este afișat ca o fracție ireductibilă.
 
 Bonus: Integrare API Financiar
 Descriere: Extinde funcționalitatea proiectului prin conectarea directă la o sursă de date externe în timp real.
 Implementare: Folosește biblioteca libcurl pentru a efectua cereri HTTP către API-ul Yahoo Finance și librăria cJSON pentru a procesa răspunsurile primite. Funcția principală (get_open_prices) extrage prețurile de deschidere ale unui simbol acționar (ex: AAPL) pentru a fi utilizate în calculele din task-ul 1.
