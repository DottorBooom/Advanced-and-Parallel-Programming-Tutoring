from collections import defaultdict


class Polynomial:

    def __init__(self, coeffs):
        # devo definire un polinomio in base al grado. In particolare, coeff è un dizionario

        if coeffs != {}:
            # Capire il grado in base al massimo numero della chiave
            self.degree = max([x for x in coeffs.keys()])
            self.mindeg = min([x for x in coeffs.keys()])

        # salva il dict di coefficienti
        self. coeffs = coeffs

    def __getitem__(self, k):
        # la funzione deve ritornare un elemento in base alla chiave

        #   C * x ^ k

        # L'elemento è presente?
        if k in self.coeffs.keys(): # la chiave esiste
            return self.coeffs[k] # ritorno il valore corrispondente al k coefficiente.
        else:
            # se non c'è il valore che ci aspettiamo sarà 0: esso ELIMINA il contributo di grado k
            return 0

    def __setitem__(self, k, v):
        # C * x ^ k <-- modifica C
        # L'elemento è presente?
        if k in self.coeffs.keys(): # la chiave esiste
            self.coeffs[k] = v # modifico il coefficiente del k-esimo contributo
        else:
            # se non c'è il valore che ci aspettiamo sarà 0: esso ELIMINA il contributo di grado k
            self.coeffs[k] =v # non cambia: tanto riassegno.

    def __call__(self, x):  # su che punto valutare il polinomio
        value = 0
        for i in range(self.degree+1): # per tutti i contributi (per ogni grado fino a max-1)
            value += self[i] * x **i # aggiungo il coefficiente * x, con x elevato alla i
        return value
# 
    def __add__(self, other): 
        # se devo fare la somma, sommo i coefficienti
        for i in range(0, max(self.degree, other.degree) +1 ):
            self[i] += other[i]
        return self

    def __sub__(self, other):
        # se devo fare la somma, sommo i coefficienti
        for i in range(0, max(self.degree, other.degree) +1 ):
            self[i] -= other[i]
        return self

    def __mul__(self, other):
        new = Polynomial({})

        for i in self.coeffs.keys():
            for j in self.coeffs.keys():
                #print(f"coefficiente {i+j}, quindi sum de {self[i] * other[j]}, con {new[i+j]}", end = "")
                new_deg = i+j
                new[new_deg] += self[i] * other[j]
                #print(f"ora {new[new_deg]}")
        
        return Polynomial(new.coeffs)


        
        # Required update
        return Polynomial(new.coeffs)

    def __pow__(self, n):
        for i in range(n):
            self = self*self
        
#
    def derivative(self): # ritorna un oggetto polinomio che ritorna la derivata di un polinomio.
                          # nota che puoi usare i metodi definiti prima.
        # La derivata fa cadere grado, lo abbassa di uno e  il coefficiente ottenuto si moltiplica col grado caduto
        # Se il grado è 0, va a 0
        #
        # x^3 + 4x^2 -> 3x^2 + 2*4x^1
        
        ## NO <0 ##

        new = Polynomial({})
        for i in self.coeffs.keys():
            if i != 0:
                new[i - 1] += i * self[i] # self di i perchè è lo stesso di quello di partenza, ma moltiplicato per il grado prima e messo nel grado -1
            if i ==0: # se il grado è 0, non c'è x e quindi va tutto a zero: non metto quella chiave
                pass
        return Polynomial(new.coeffs)

    def __str__(self):    # stampa coeff x^deg
        # devo stampare
        print(self.coeffs)
        stringa = f"{self[self.mindeg]}*x^{self.mindeg}"
        for i in range(self.mindeg+1, self.degree+1): # per ogni grado
            # SE IL GRADO HA UN COEFFICIENTE NON NULLO
            if self[i] != 0:
                stringa += f" + {self[i]}*x^{i}"
            else: 
                pass # altrimenti non spreco spazio
        return stringa
        

def newton_raphson(p, x, n_iter=20): 
    # x è punto iniziale
    
    x_t = x
    pd = p.derivative()

    for i in range(n_iter): # per tante volte quante n
        x_t = x_t - (p(x_t)/pd(x_t))
    
    return x_t




p1 = Polynomial({4: 2, 3: 5, 1: 6, 0: -2})
p2 = Polynomial({3: 1, 2: 0.5, 1: -1, 0: 3})
p2 = Polynomial({0:3, 1:-1, 2:0.5, 3:1})
p3 = Polynomial({-1: 3})

print("Stampa", p1)
print("Stampa", p2)
print("Stampa Somma", p1 + p2)
print("Stampa Prodotto", p1 * p2)
#print(p1(3))
#print((p1+p2)(20))
print(p3.derivative())
x = newton_raphson(p1, 5)
print(f"p({x}) = {p1(x)}")