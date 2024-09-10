#!/bin/bash

# Ejecutar el ejecutable
make run

# Comprobar si el ejecutable ha tenido éxito antes de ejecutar el script Python
if [ $? -eq 0 ]; then
    echo "El ejecutable se ejecutó con éxito. Ejecutando el script de Python."
    python3 /home/alberto/Documentos/bbbss/src/graficas_python.py
else
    echo "El ejecutable falló. No se ejecutará el script de Python."
fi
