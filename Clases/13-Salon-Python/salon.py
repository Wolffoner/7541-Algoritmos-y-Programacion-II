#!/usr/bin/env python3

from pokemon import *
from entrenador import *

nombre = "salones/salon_estandar.txt"

class Salon:
    def __init__(self):
        self.entrenadores = {}

    def agregarEntrenadorSiExiste(self, entrenador):
        if entrenador:
            self.entrenadores[entrenador.nombre] =  entrenador

    def mostrarSalon(self):
        for entrenador in self.entrenadores.values():
            print("Entrenador: {} ({})".format(entrenador.nombre, entrenador.victorias))
            for pokemon in entrenador.equipo:
                print("\tPokemon: " + pokemon.nombre)

    def obtenerEntrenadorSi(self, condicion):
        return list(filter(condicion, self.entrenadores.values()))

    def obtenerMasGanadores(self, n):
        return self.obtenerEntrenadorSi(lambda e: e.victorias >= n)


def leer_salon(nombre):
    archivo = open(nombre, "r")
    salon = Salon()
    entrenadorActual = None

    for linea in archivo:
        campos = linea.split(";")
        pokemon = parsearPokemon(campos)
        entrenador = parsearEntrenador(campos)

        if pokemon and entrenadorActual:
            entrenadorActual.agregarPokemon(pokemon)
        elif entrenador:
            salon.agregarEntrenadorSiExiste(entrenadorActual)
            entrenadorActual = entrenador
        else:
            print("Esto no deberia pasar")

    salon.agregarEntrenadorSiExiste(entrenadorActual)
    archivo.close()

    return salon

salon = leer_salon(nombre)

salon.mostrarSalon()
