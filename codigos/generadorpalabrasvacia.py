import random
import string

# Función para generar una palabra aleatoria
def generar_palabra_aleatoria(longitud):
    return ''.join(random.choices(string.ascii_lowercase, k=longitud))

# Crear y escribir en el archivo
def generar_archivo(longitud):
    # Abrir el archivo en modo escritura
    with open("palabrasvacia10000.txt", "w") as file:
        # Escribir la primera línea vacía
        file.write("\n")
        
        # Generar la palabra aleatoria
        palabra_aleatoria = generar_palabra_aleatoria(longitud)
        
        # Escribir la palabra aleatoria en la segunda línea
        file.write(palabra_aleatoria + "\n")
        
    print(f"Archivo generado con éxito. Segunda palabra: {palabra_aleatoria}")

# Ejecutar la función para generar el archivo
generar_archivo(100)
