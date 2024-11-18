def generate_fixed_costs(filename, size, cost):
    """
    Genera un archivo de costos unidimensional con un costo fijo.
    - filename: nombre del archivo a generar.
    - size: cantidad de caracteres (26 para el alfabeto inglés).
    - cost: costo fijo a asignar a cada carácter.
    """
    with open(filename, 'w') as file:
        file.write(" ".join([str(cost)] * size))

def generate_fixed_costs_2d(filename, size, cost):
    """
    Genera un archivo de costos bidimensional con un costo fijo.
    - filename: nombre del archivo a generar.
    - size: cantidad de caracteres (26 para el alfabeto inglés).
    - cost: costo fijo a asignar a cada par de caracteres.
    """
    with open(filename, 'w') as file:
        for _ in range(size):
            file.write(" ".join([str(cost)] * size) + "\n")

# Generar archivos de costos con valores fijos
generate_fixed_costs("cost_insert.txt", 26, 1)          # Costos de inserción con valor 1
generate_fixed_costs("cost_delete.txt", 26, 1)          # Costos de eliminación con valor 1
generate_fixed_costs_2d("cost_replace.txt", 26, 1)      # Costos de sustitución con valor 2
generate_fixed_costs_2d("cost_transpose.txt", 26,1)    # Costos de transposición con valor 1

print("Archivos de costos generados exitosamente con valores fijos.")
