import pandas as pd
import matplotlib.pyplot as plt

# Cargar CSV
df = pd.read_csv("resultados.csv")

# Diccionario para mapear columnas al nombre del método
metodos = {
    "neh": ("makespan_neh", "tiempo_neh"),
    "palmer": ("makespan_palmer", "tiempo_palmer"),
    "neh+swap": ("makespan_neh_swap", "tiempo_neh_swap"),
    "neh+insertion": ("makespan_neh_insert", "tiempo_neh_insert"),
    "palmer+swap": ("makespan_palmer_swap", "tiempo_palmer_swap"),
    "palmer+insertion": ("makespan_palmer_insert", "tiempo_palmer_insert"),
    "neh+swap+insertion": ("makespan_neh_swap_insert", "tiempo_neh_swap_insert"),
    "neh+insertion+swap": ("makespan_neh_insert_swap", "tiempo_neh_insert_swap")
}

# Crear listas para construir un df "largo"
filas = []

for metodo, (col_mk, col_ti) in metodos.items():
    for _, row in df.iterrows():
        filas.append({
            "metodo": metodo,
            "makespan": row[col_mk],
            "tiempo": row[col_ti]
        })

df_largo = pd.DataFrame(filas)

# Agrupar por método
prom = df_largo.groupby("metodo").mean()

# ----- Gráfico Makespan -----
plt.figure(figsize=(10,5))
prom["makespan"].plot(kind="bar")
plt.title("Makespan promedio por método")
plt.ylabel("Makespan promedio")
plt.xlabel("Método")
plt.tight_layout()
plt.savefig("grafico_makespan.png")
plt.close()

# ----- Gráfico Tiempo -----
plt.figure(figsize=(10,5))
prom["tiempo"].plot(kind="bar")
plt.title("Tiempo promedio por método (ms)")
plt.ylabel("Tiempo promedio (ms)")
plt.xlabel("Método")
plt.tight_layout()
plt.savefig("grafico_tiempo.png")
plt.close()

print("Listo! Se generaron grafico_makespan.png y grafico_tiempo.png")
