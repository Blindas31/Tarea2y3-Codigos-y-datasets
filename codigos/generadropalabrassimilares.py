import random

# Función para generar una palabra aleatoria que incluya 'string' de manera implícita
def generar_palabra_aleatoria(x):
    # Letras base de "string"
    base = "string"
    
    # Repeticiones aleatorias de las letras de la palabra "string"
    repeticiones = {
        's': random.randint(1, x),  # Repetir 's' entre 1 y 3 veces
        't': random.randint(1, x),  # Repetir 't' entre 1 y 3 veces
        'r': random.randint(1, x),  # Repetir 'r' entre 2 y 4 veces
        'i': random.randint(1, x),  # Repetir 'i' entre 2 y 4 veces
        'n': random.randint(1, x),  # Repetir 'n' entre 2 y 4 veces
        'g': random.randint(1, x)   # Repetir 'g' entre 2 y 3 veces
    }
    
    # Crear las palabras con las repeticiones generadas
    palabra1 = ''.join([char * repeticiones[char] for char in base])
    
    # Para la segunda palabra, repetimos el proceso de manera similar pero aleatoria
    palabra2 = ''.join([char * random.randint(1, 8) for char in base])

    return palabra1, palabra2

# Crear y escribir en el archivo
def generar_archivo(x):
    # Generar las palabras
    palabra1, palabra2 = generar_palabra_aleatoria(x)
    
    # Abrir el archivo y escribir las dos palabras
    with open("palabrassimilares8.txt", "w") as file:
        file.write(palabra1 + "\n")  # Escribir la primera palabra
        file.write(palabra2 + "\n")  # Escribir la segunda palabra
    
    print(f"Archivo generado con éxito con las palabras S1 y S2.")

# Ejecutar la función para generar el archivo
generar_archivo(8)
