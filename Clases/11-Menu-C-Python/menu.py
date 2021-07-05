contador=0



class Juego:
    def __init__(self):
        self.contador = 0

class Comando:
    def __init__(self, nombre, doc, funcion):
        self.nombre=nombre
        self.documentacion=doc
        self.ejecutar=funcion

    def mostrar_documentacion(self):
        print("Esta es mi documentacion")
        print(self.documentacion)

print("Ya se crearon las clases Juego y Comando")

class Menu:
    def __init__(self):
        self.nombre = ""
        self.comandos = {}

    def agregar_comando(self, comando):
        self.comandos[comando.nombre] = comando

    def ejecutar_comandos(self, linea):
        if linea in self.comandos:
            comando = self.comandos[linea]
            comando.ejecutar("molesto")
        else:
            print('No te entendi')


def incrementar(argumento):
    print('Incremento el contador ', argumento)
    global contador
    contador += 1

def decrementar():
    print('Decremento el contador')
    global contador
    contador -= 1

def mostrar():
    print('Contador: ', contador)


menu = Menu()
menu.agregar_comando(Comando('I', 'Incrementar el contador', incrementar))
menu.agregar_comando(Comando('D', 'Decrementar el contador', decrementar))
menu.agregar_comando(Comando('P', 'Mostrar el contador', mostrar))

linea=""
while(linea != "quit"):
    linea = input('> ')
    menu.ejecutar_comandos(linea)
