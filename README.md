# Ristrutturazione in corso
Abbiamo decisamente bisogno di API più elegante, puntiamo all'OOP.

#Installazione
Clonare questa repo dentro la vostra cartella libraries per Arduino IDE.

### API essenziale
Per ora trascuriamo il magnetometro, serviranno:
- inizializzatore, che legga le impostazioni scritte sul chip e le salvi
	internamente (fondoscala/sensitività, calibrazione ... )
- scrittura impostazioni
- calibrazione stazionaria (ACC, GIR, ACC+GIR)
- calibrazione manuale (ACC, GIR)
- Verifica connessione
- lettura dati (ACC, GIR, ACC+GIR) nei formati: int grezzi, float in scala

### License
This library derives from Kris Winer's [code](https://github.com/kriswiner/MPU-9250)
which was licensed as Beerware.
