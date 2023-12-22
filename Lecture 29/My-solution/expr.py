class EmptyStackException(Exception):
    pass


class Stack:

    def __init__(self): # Costruzione di uno stack vuoto
        self.data = []

    def push(self, x):  # Aggiunge elementi allo stack (in coda)
        self.data.append(x) 

    def pop(self):      # estraggo un elemento dallo stack
        if self.data == []:  # Se non vi sono altri elementi, allora lancio un Empty Stack
            raise EmptyStackException
        res = self.data[-1]  # Altrimenti, prendo l'ultimo elemento (coda)
        self.data = self.data[0:-1] # Aggiorno: il contenuto dello stack ora saranno solo gli elementi da 0 a i
        return res # ritorno l'elemento estratto dallo stack 

    def __str__(self):  # Stampa
        return " ".join([str(s) for s in self.data])


class Expression:

    def __init__(self):
        # Inizializzo uno stack per una espressione generica
        self.expression_stack = Stack()

    @classmethod
    def from_program(cls, text, dispatch):
        # Supponiamo di avere a disposizione un intera stringa di operazioni e volerla inserire
        # nello stack al momento della creazione (dati di partenza)

        expr = cls()
        print("Creazione dello stack")
        # RIEMPIRE LO STACK
                # Supponiamo che riceva un testo in notazione polacca inversa.
        # Quello che dobrà fare sarà inserire nello stack

        # 1. inizializzo uno stack per questa funzione
        split_expression = text.split(" ") 

        for i in split_expression:
            print(f"> Considero {i}")
            try:
                # se posso renderla una int
                int_i = int(i)
                print(">> Considerato come costante")
                saved = Constant(int_i)

            except:
                # se è una stringa non convertibile in numero
                # controllo se è una operazione nota
                if i in dispatch.keys(): 
                    print(f">> {i} è una operazione")
                    # La funzione chiede K elementi
                    args = []
                    current_operation = dispatch[i] # ma è una classe!                    
                    K = current_operation.arity
        
                    print(f">>> L'operazione è della classe {current_operation}, con arità {K}")

                    try: # rischio che elementi non ci siano
                        for i in range(K): # per tante volte quanti sono gli elementi che richiede
                            element = expr.expression_stack.pop()
                            args.append(element)

                        print(f"args: estrazione completata")
                        
                        # Posso inserire in stack il risultato di quella operazione! (oggetto)
                        # Il fatto è che quello che si ha quando conosco "i"
                        saved = current_operation(args) # l'operazione e la stringa di argomenti
                        
                    except:
                        print("Not well...")
                        return None

                else:
                    # variable
                    saved = Variable(i)
        
            expr.expression_stack.push(saved) # inserisco in ordine (-->)
    
        return expr # ritorno questa istanza che ho modificato



    def evaluate(self, env):
        # Si tratta del primo:
        # Supponendo di avere uno stack (foto 5) con un elemento definitivo, allora devo solo 
        # mandare la valutazione su di questo. A sua volta, avrà valutazioni ricorsive
        
        # Prendo (l'ultimo) elemento dallo stack
        elem = self.expression_stack.pop()
        return elem.evaluate(env)
        


class MissingVariableException(Exception):
    pass


class Variable(Expression):

    def __init__(self, name):
        self.name = name

    def evaluate(self, env):
        if self.name not in env:
            raise MissingVariableException
        elif env[self.name] ==None:
            raise MissingVariableException
        else:
            # è presente con un valore, il suo valore sarà quindi direttamente quello noto in env
            return env[self.name]


    def __str__(self):
        return self.name


class Constant(Expression):

    def __init__(self, value):
        self.value = value

    def evaluate(self, env):
        return self.value # una costante è una costante

    def __str__(self):
        return self.value


class Operation(Expression):

    def __init__(self, args):
        self.args = args # ricevo argomenti come lista

    def evaluate(self, env):
        # Supporremo di conoscere gli argomenti. (arity = len(args) )
        # Una evaluation della operazione si ha con l'operazione tra 
        # le due parti. Dipende però se sono direttamente accessibili:

        return self.op([i.evaluate(env) for i in self.args]) # rimando la valutazione alle sottoparti e ritorno il
                                                          # delle operazioni su queste 

    def op(self, *args):
        raise NotImplementedError()
        # Sarà lasciato alle speifiche sottoclassi!

    def __str__(self):
        pass


class BinaryOp(Operation):
    arity = 2


class UnaryOp(Operation):
    arity = 1 # arità della classe


class Addition(BinaryOp):
    
    def op(self, args): # riscritto dal figlio
        # posso supporre che in args ora ci siano le valutazioni 
        # dato che le ho chiamate prima di rimandare qua
        
        return args[0] + args[1]


class Subtraction(BinaryOp):

    def op(self, args): # riscritto dal figlio
        # posso supporre che in args ora ci siano le valutazioni 
        # dato che le ho chiamate prima di rimandare qua
        
        return args[0] - args[1]


class Division(BinaryOp):
    
    def op(self, args): # riscritto dal figlio
        # posso supporre che in args ora ci siano le valutazioni 
        # dato che le ho chiamate prima di rimandare qua
        
        return args[0] / args[1]


class Multiplication(BinaryOp):

    def op(self, args): # riscritto dal figlio
        # posso supporre che in args ora ci siano le valutazioni 
        # dato che le ho chiamate prima di rimandare qua
        
        return args[0] * args[1]


class Power(BinaryOp):
    

    def op(self, args): # riscritto dal figlio
        # posso supporre che in args ora ci siano le valutazioni 
        # dato che le ho chiamate prima di rimandare qua
        
        return args[0] ** args[1]


class Modulus(BinaryOp):
    
    def op(self, args): # riscritto dal figlio
        # posso supporre che in args ora ci siano le valutazioni 
        # dato che le ho chiamate prima di rimandare qua
        
        return args[0] % args[1]


class Reciprocal(UnaryOp):
    
    def op(self, arg): # riscritto dal figlio
        # posso supporre che in args ora ci siano le valutazioni 
        # dato che le ho chiamate prima di rimandare qua
        
        return 1/arg[0]


class AbsoluteValue(UnaryOp):
    
    def op(self, arg): # riscritto dal figlio
        # posso supporre che in args ora ci siano le valutazioni 
        # dato che le ho chiamate prima di rimandare qua
        
        return abs(arg[0])


d = {"+": Addition, "*": Multiplication, "**": Power, "-": Subtraction,
     "/": Division, "1/": Reciprocal, "abs": AbsoluteValue}
example = "1 4 + 2 *"
example = "2 3 + x * 6 5 - / abs 2 ** y 1/ + 1/"
example = "2 3 + x * 6 5 - / abs 2 ** y 1/ + 1/"

e = Expression.from_program(example, d)
print(e)
res = e.evaluate({"x": 3, "y": 7})
print(res)

# Ouput atteso:
# (1/ (+ (1/ y) (** 2 (abs (/ (- 5 6) (* x (+ 3 2)))))))
# 0.84022932953024
