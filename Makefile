# Variables
CXX = g++
CXXFLAGS = -Wall -O2 -std=c++17 -Ilibs/Arcade-Learning-Environment-0.6.1/src
LDFLAGS = -Llibs/Arcade-Learning-Environment-0.6.1 -lale_interface -lz -lSDL
SRC_DIR = src
BUILD_DIR = build
SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
OUT = $(BUILD_DIR)/demon_bot

# Reglas principales
all: check_lib $(OUT)

$(OUT): $(OBJ)
	@echo "Compilando el proyecto..."
	$(CXX) $(OBJ) -o $(OUT) $(LDFLAGS)
	@echo "Proyecto compilado exitosamente: $(OUT)"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Verificar que libale_interface.so existe
check_lib:
	@echo "Verificando la biblioteca libale.so..."
	@if [ ! -f libs/Arcade-Learning-Environment-0.6.1/libale_interface.so ]; then \
		ln -s libs/Arcade-Learning-Environment-0.6.1/libale.so libs/Arcade-Learning-Environment-0.6.1/libale_interface.so; \
	fi

# Limpiar compilaciones previas
clean:
	@echo "Limpiando archivos compilados..."
	rm -rf $(BUILD_DIR)/*.o $(OUT)
	@echo "Limpieza completada."

# Ejecutar el programa
run: all
	@echo "Ejecutando el proyecto..."
	./$(OUT)

