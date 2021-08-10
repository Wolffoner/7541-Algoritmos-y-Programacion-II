#!/usr/bin/env python3

class Pokemon:
    def __init__(self, nombre, nivel, defensa, fuerza):
        self.nombre = nombre
        self.nivel = nivel
        self.defensa = defensa
        self.fuerza = fuerza

def parsearPokemon(campos):
    if(len(campos) != 6):
        return None
    return Pokemon(campos[0], int(campos[1]), int(campos[2]), int(campos[3]))
