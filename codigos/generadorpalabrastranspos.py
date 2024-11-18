# Función para generar los pares
def generar_pares(x):
    # Generar la primera línea con x pares de "ab"
    linea1 = "ab" * x
    
    # Generar la segunda línea con x pares de "ba"
    linea2 = "ba" * x
    
    return linea1, linea2

# Crear y escribir en el archivo
def generar_archivo(x):
    # Generar las líneas
    linea1, linea2 = generar_pares(x)
    
    # Abrir el archivo y escribir las dos líneas
    with open("palabrastranspos2.txt", "w") as file:
        file.write(linea1 + "\n")  # Escribir la primera línea
        file.write(linea2 + "\n")  # Escribir la segunda línea
    
    print(f"Archivo generado con éxito con {x} pares.")

# Ejecutar la función para generar el archivo
generar_archivo(2)
