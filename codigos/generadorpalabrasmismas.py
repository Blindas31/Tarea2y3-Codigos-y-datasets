import random
import string

def generar_palabras_iguales_en_txt(largo, nombre_archivo="palabrasiguales2.txt"):
    """Genera dos palabras iguales aleatorias y las guarda en un archivo de texto."""
    # Genera una palabra aleatoria
    palabra = ''.join(random.choices(string.ascii_lowercase, k=largo))
    
    # Guarda las dos palabras iguales en un archivo
    with open(nombre_archivo, "w") as archivo:
        archivo.write(f"{palabra}\n{palabra}")
    
    print(f"Las palabras han sido guardadas en {nombre_archivo}")

# Ejemplo de uso
largo_deseado = 2  # Cambia este valor al largo deseado
generar_palabras_iguales_en_txt(largo_deseado)
