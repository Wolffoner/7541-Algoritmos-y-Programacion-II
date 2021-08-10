#!/usr/bin/env python3

class Entrenador:
    def __init__(self, nombre, victorias):
        self.nombre = nombre
        self.victorias = victorias
        self.equipo = []

    def agregarPokemon(self, pokemon):
        self.equipo.append(pokemon)

def parsearEntrenador(campos):
    if(len(campos) != 2):
        return None
    return Entrenador(campos[0], int(campos[1]))
