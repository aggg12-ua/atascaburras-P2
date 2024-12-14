#include <ale_interface.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include "perceptron.hpp"


using namespace std;

int main() {
    ALEInterface ale;

    // entorno
    ale.setBool("display_screen", true);
    ale.setInt("random_seed", 123);
    ale.setFloat("repeat_action_probability", 0.25);  

    //ROM
    string romPath = "/home/cpc/Escritorio/atascaburrasStudios-P2/roms/demon_attack.bin";
    try {
        ale.loadROM(romPath);
        cout << "ROM cargada con éxito: " << romPath <<endl;
    } catch (const exception &e) {
        cerr << "Error al cargar la ROM: " << e.what() <<endl;
        return 1;
    }

    
    vector<Action> legalActions = ale.getLegalActionSet();

    ofstream dataFile("data/game_data.csv");
    if (!dataFile.is_open()) {
        cerr<<"Error al abrir el archivo de datos."<<endl;
        return 1;
    }
    dataFile<<"frame,player_x,enemy_x,enemy_y,action\n";

    int score = 0;

    while (!ale.game_over()) {
    //estado desde RAM
    auto ram = ale.getRAM();
    int player_x = ram.get(50);  // Ajusta este índice según sea necesario
    int enemy_x = ram.get(60);  // Ajusta este índice según sea necesario
    int enemy_y = ram.get(61);  // Ajusta este índice según sea necesario

    //acción aleatoria
    Action action = legalActions[rand() % legalActions.size()];
    score += ale.act(action);

  
    dataFile << ale.getEpisodeFrameNumber() << ","
             << player_x << ","
             << enemy_x << ","
             << enemy_y << ","
             << action << "\n";

 
    cout << "Frame: " << ale.getEpisodeFrameNumber()
         << " | Puntuación: " << score << endl;
}


    dataFile.close();
    
    ale.reset_game();

    cout << "Fin del juego. Puntuación final: " <<score <<endl;
    return 0;
}
