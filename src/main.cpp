#include <ale_interface.hpp>
#include <iostream>
#include <vector>

int main() {
    ALEInterface ale;

    // entorno
    ale.setBool("display_screen", true);
    ale.setInt("random_seed", 123);
    ale.setFloat("repeat_action_probability", 0.25);  

    //ROM
    std::string romPath = "../roms/demon_attack.bin";
    try {
        ale.loadROM(romPath);
        std::cout << "ROM cargada con éxito: " << romPath << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error al cargar la ROM: " << e.what() << std::endl;
        return 1;
    }

    
    std::vector<Action> legalActions = ale.getLegalActionSet();

    int score = 0;

    while (!ale.game_over()) {
        //acción RANDOM
        Action action = legalActions[rand() % legalActions.size()];
        score += ale.act(action);

    
        std::cout << "Puntuación: " << score << std::endl;
    }

    ale.reset_game();

    std::cout << "Fin del juego. Puntuación final: " << score << std::endl;
    return 0;
}
