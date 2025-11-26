#include <iostream>
#include <vector>

#include "include/parser.hpp"
#include "include/heuristicas.hpp"   // para calculate_makespan
#include "include/solution.hpp"

using namespace std;

/*******************************************************************
 * TEST 1: Testear la clase FSSPInstance y el parser.
 * 
 * Se crea un archivo temporal con una instancia simple (3x3),
 * se parsea usando parse_fssp_file, y se chequea si los datos
 * cargados coinciden con lo esperado.
 *******************************************************************/
bool test_parser_instance() {
    const char* filename = "test_instance.txt";
    FILE* f = fopen(filename, "w");

    fprintf(f, "instance test\n");
    fprintf(f, "3 3\n");

    // Primera fila se la come el parser
    fprintf(f, "0 1 1 2 2 3\n");

    // Segunda fila será la REAL fila 0
    fprintf(f, "0 1 1 2 2 3\n");

    // Estas serán fila 1 y fila 2
    fprintf(f, "0 4 1 5 2 6\n");
    fprintf(f, "0 7 1 8 2 9\n");

    fclose(f);

    vector<FSSPInstance> insts = parse_fssp_file(filename);
    if (insts.empty()) {
        cout << "TEST PARSER: ERROR - no se parseó ninguna instancia.\n";
        return false;
    }

    const FSSPInstance& inst = insts[0];

    if (inst.n_jobs != 3 || inst.m_machines != 3) {
        cout << "TEST PARSER: ERROR dimensiones incorrectas.\n";
        return false;
    }

    vector<vector<int>> expected = {
        {1,2,3},
        {4,5,6},
        {7,8,9}
    };

    for (int i = 0; i < 3; i++) {
        for (int k = 0; k < 3; k++) {
            if (inst.processing_times[i][k] != expected[i][k]) {
                cout << "FAIL en (" << i << "," << k << ") "
                     << "esperado=" << expected[i][k]
                     << " obtenido=" << inst.processing_times[i][k] << "\n";
                return false;
            }
        }
    }

    cout << "TEST PARSER: OK\n";
    return true;
}



/*******************************************************************
 * TEST 2: Testear calculate_makespan
 * 
 * Usamos la misma instancia simple y probamos una secuencia fija:
 *   orden = {0, 1, 2}
 * El makespan esperado es 29.
 *******************************************************************/
bool test_makespan() {
    FSSPInstance inst;
    inst.n_jobs = 3;
    inst.m_machines = 3;
    inst.processing_times = {
        {1,2,3},
        {4,5,6},
        {7,8,9}
    };

    vector<int> sequence = {0,1,2};
    int result = calculate_makespan(inst, sequence);

    if (result != 29) {
        cout << "TEST MAKESPAN: ERROR - esperado 29, obtenido " 
             << result << "\n";
        return false;
    }

    cout << "TEST MAKESPAN: OK\n";
    return true;
}


/*******************************************************************
 * MAIN DE TESTS
 *******************************************************************/
int main() {
    bool ok1 = test_parser_instance();
    bool ok2 = test_makespan();

    if (ok1 && ok2) {
        cout << "\n>>> TODOS LOS TESTS PASARON CORRECTAMENTE <<<\n";
        return 0;
    } else {
        cout << "\n>>> ALGÚN TEST FALLÓ <<<\n";
        return 1;
    }
}
