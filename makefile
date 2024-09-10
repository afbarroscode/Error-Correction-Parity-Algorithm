# Definir el compilador
CXX = g++
# Definir las banderas de compilación
CXXFLAGS = -Wall -Wextra -std=c++11

# Directorios
SRC_DIR = /home/alberto/Documentos/bbbss/src
BIN_DIR = /home/alberto/Documentos/bbbss/bin
FIG_DIR = /home/alberto/Documentos/bbbss/figures

# Definir los archivos fuente y el ejecutable
SOURCES = $(SRC_DIR)/bbbss_main.cpp \
          $(SRC_DIR)/initialization.cpp \
          $(SRC_DIR)/algorithms.cpp \
          $(SRC_DIR)/graphics.cpp \
          $(SRC_DIR)/backtracking_function.cpp \
          $(SRC_DIR)/permutation_function.cpp \
          $(SRC_DIR)/management_function.cpp \
          $(SRC_DIR)/bbbss_function.cpp \
          $(SRC_DIR)/cascade_function.cpp \
          $(SRC_DIR)/cascade_optimized_function.cpp \
          $(SRC_DIR)/pbPlots.cpp \
          $(SRC_DIR)/supportLib.cpp

EXECUTABLE = $(BIN_DIR)/executable

PHOTOS = $(FIG_DIR)/*.png

# Crear el directorio "bin" si no existe
.PHONY: all clean $(BIN_DIR)

# Crear el directorio "figures" si no existe
.PHONY: all clean $(FIG_DIR)

# Regla para compilar el ejecutable y dar permisos
$(EXECUTABLE): $(SOURCES) 
	@echo "Compilando el ejecutable..."
	$(CXX) $(CXXFLAGS) -o $(EXECUTABLE) $(SOURCES)
	chmod 755 $(EXECUTABLE)
	@echo "Compilación completa: Ejecutable generado en $(EXECUTABLE)"

# Regla para limpiar el ejecutable y las fotos en "figures"
clean:
	rm -rf $(EXECUTABLE) $(PHOTOS)
	@echo "Limpieza completa: Ejecutable y fotos eliminados"

# Regla para ejecutar el programa
run: $(EXECUTABLE)
	$(EXECUTABLE)
