# RELAZIONE VOLTMETRO & OHMETRO

Salve a tutti, oggi relazionerò un dispositivo in grado di misurare la differenza di potenziale e la resistenza dei resistori. Cominciamo subito!

### Componenti necessari:
1. Arduino UNO R4 MINIMA
2. 3 Resistori di resistenza:
   1. 3 x 10Kohm
   2. 1Kohm
   3. 2Kohm
   4. 250ohm
3. 4 connettori femmina a banana.
4. Scatola di derivazione 150x110mm
5. 1 millefori
6. Display lcd 16x2 1602A
7. 2 pulsanti
8. 1 saldatore
9. Stagno 0.8mm
10. Spellacavi(facoltativa)

## COMINCIAMO AD ASSEMBLARE TUTTO(voltmetro):
Cominciamo subito con il voltmetro, quindi prendiamo due resistori di resistenza 10Kohm e 2Kohm, il motivo di questi valori è il seguente:
arduino è una scheda opera a 5V ciò significa che la massima tensione che possono tollerare i pin di arduino è di 5V, ma dato che il nostro voltmetro deve arrivare a massimo 30V, dovremmo occuparci di due calcoli:
```
Vmax = 30V
R1 = 10Kohm
R2 = ?

VR2 = R2 * I =>
VR2 = R2 * 30V/10Kohm+R2
5V/30V/R1+R2 = R2
(10Kohm+R2)/6 = R2
10Kohm+R2 = 6R2
10Kohm + R2 = 6R2
5R2 = 10Kohm
R2 = 2Kohm
```
Bene, adesso sappiamo i valori del nostro partitore, adesso vediamo cosa in che situazione siamo messi:

![PartitoreResistivo](https://www.learningaboutelectronics.com/immagini/Partitore-di-tensione.png)


Vin sarà la tensione del nostro dispositivo che stiamo misurando, per trovarla occorre prima trovare Vout.
Per trovare Vout basterà collegare il punto di serie tra i due resistori ad uno dei pin analogici di arduino e attraverso la seguente proporzione:

```
A0 : 16383 = Vout : 5V
```
Quindi:
```
Vout = (A0*5V)/16383
```
Adesso serviranno una serie di calcoli per trovare Vin, ecco i calcoli:
```
Affermiamo che:
VR2 = Vout
VR2 = R2 * I
VR2 = R2 * Vin/R1+R2
Vin = (VR2*(R1+R2))/R2 
```
Adesso che abbiamo Vin possiamo dedicarci alla parte del circuito, per questo progetto ho usato una millefori. Iniziamo subito col inserire sulla millefori i due resistori subito dopo accendiamo il saldatore ed appena ha raggiunto la temperatura ottimale, cominciamo a depositare dello stagno sulla punta e cominciamo a riscaldare la piastra dove si trova il terminale del primo resistore appena lo stagno si comincierà a depositare piano piano, poggiamo delicatamente un pò di stagno sulla piastra così da aver coperto tutta la piastra di stagno, stessa procedura la si esegue anche sull'ultimo terminale a differenza che sta volta dovremmo unire anche il primo terminale del secondo resistore, quindi uniremo due piastre, così da averle messe in serie. Infine saldiamo l'ultimo terminale del secondo resistore. Adesso il circuito è quais pronto, ma mancano i due puntali da saldare, per questo progetto ho usato dei plug a banana femmina, così da non usare i jumper come puntali, ma ho la possibilità di usare svariati puntali:

![Plug](https://res.cloudinary.com/rsc/image/upload/bo_1.5px_solid_white,b_auto,c_pad,dpr_2,f_auto,h_399,q_auto,w_710/c_pad,h_399,w_710/F7632935-01?pgw=1)

Prima di saldare sulla millefori, saldiamo un cavo in questo plug e la parte opposta del cavo la saldiamo nella piastra dove abbiamo saldato il primo terminale del primo resistore, identica cosa facciamo con un altro plug che però andrà saldato nell'ultimo terminale del secondo resistore. Adesso saldiamo un cavo nel punto di serie dei due resistori e lo colleghiamo al pin analogico di arduino A0. Adesso tutto è pronto per il voltmetro, adesso dedichiamoci alla parte software, come mostra il codice allegato in codesto reposistory la seguente funzione:
```C
void voltmetro(){
  float r1 = 10000.0;
  float r2 = 2000.0;
  float vout = (analogRead(A0)*5.0)/16383.0;
  float vin = (vout*(r1+r2))/r2;
  lcd.print("Volt: ");
  lcd.print(vin);
  lcd.print("V");
  delay(250);
}
```
Come si vede dal codice, ho applicato le due formule che in precedenza abbiamo trovato e usato un tempo di 250ms a misura.
Adesso ci dedicheremo all'ohmetro.

## COMINCIAMO AD ASSEMBLARE IL TUTTO(ohmetro):

Per l'ohmetro il circuito cambia, perchè dovremmo usare un partitore resistivo con i seguenti dati:
1. Vin: 5V
2. R2: 1Kohm

Quindi prima di mettere mano sul circuito, facciamo due calcoli:
```
VR2 = R2 *I
VR2 = R2 * Vin/R1+R2
VR2/Vin/R1+R2 = R2
(VR2 * (R1+R2))/Vin = R2
(VR2 * (R1+R2)) = (R2 * Vin)
(R1+R2) = (R2 * Vin)/VR2
R1 = ((R2 * Vin)/VR2)- R2
```
Adesso che sappiamo il calcolo che dobbiamo fare mostriamo graficamente la nostra situazione:

