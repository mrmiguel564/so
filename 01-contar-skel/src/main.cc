#include <global.h>
#include <checkArgs.hpp>

uint8_t  g_letraObjetivo;
std::vector<uint8_t> v;
std::vector<std::thread> threadVect;//vector para lanzar los threads y luego hacer el join
std::mutex BlockVect;//mutex para la zona critica
int contador = 0;//contador global

void contarParcial(char x,unsigned int inicio, unsigned int final) {
	
	for(unsigned int i = inicio; i<=final; i++){
		if(x == v[i]){
			BlockVect.lock();
			contador+=1;//zona critica
			BlockVect.unlock();
		}
	}


}


int main(int argc, char** argv){
	
	uint32_t totalElementos;
	uint32_t numThreads;
	
    uint32_t contarSerial = 0;
	uint32_t contarTotal = 0;
	
	std::shared_ptr<checkArgs> argumentos = (std::shared_ptr<checkArgs>) new checkArgs(argc, argv);
	
	totalElementos = argumentos->getArgs().tamProblema;
	numThreads     = argumentos->getArgs().numThreads;
	g_letraObjetivo  = argumentos->getArgs().letra;
	
	std::cout << "Nro. Elementos: " << totalElementos << std::endl;
	std::cout << "Threads       : " << numThreads     << std::endl;
	std::cout << "Letra         : " << g_letraObjetivo  << std::endl;
	
	static thread_local std::random_device device;
	static thread_local std::mt19937 rng(device());
	
	std::cout << "Llenando arreglo ..." << std::endl;
	std::uniform_int_distribution<uint8_t> nRandom('a', 'z');
	for(size_t i=0; i < totalElementos; i++){
		uint8_t tmpLetra = nRandom(rng);
		v.push_back( tmpLetra );
		//std::cout << tmpLetra << std::endl;
	}
	std::cout << "... OK" << std::endl;
	
	//======SERIAL======
	auto start = std::chrono::high_resolution_clock::now();
	
	// Busca en forma serial
	for(auto& tmpLetra : v){
		if(tmpLetra == g_letraObjetivo){
			contarSerial++;
		}
	}
	
	//
	auto end     = std::chrono::high_resolution_clock::now(); 
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	auto totalTimeSerial = elapsed.count();
	
	std::cout << "Apariciones de '" << g_letraObjetivo << "': "<< contarSerial << std::endl;
	std::cout << "Tiempo de busqueda Secuencial: " << totalTimeSerial << "[ms]" << std::endl;

	
	//======THREADS======
	start = std::chrono::high_resolution_clock::now();
	//(1) Separación del trabajo
	unsigned int inicio = 0;
	unsigned int particiones = totalElementos/numThreads;
	unsigned int resto =totalElementos%numThreads;
	unsigned int nuevoFinal = inicio + particiones -1;
	for(unsigned int i = 0; i< numThreads-1; i++){		
		threadVect.emplace_back(contarParcial,g_letraObjetivo, inicio, nuevoFinal);			
		inicio += particiones;
		nuevoFinal += particiones;
	}
	threadVect.emplace_back(contarParcial,g_letraObjetivo, inicio, nuevoFinal+resto);			
	inicio += particiones;
	nuevoFinal += particiones;

	
	//(2) Reducción (Consolidación de resultados parciales)
	for(auto& thread : threadVect){
		thread.join();		
	}
	// Completar
	contarTotal = contador;
	//
	end     = std::chrono::high_resolution_clock::now(); 
	elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	auto totalTimeThread = elapsed.count();
	
	std::cout << "Apariciones de '" << g_letraObjetivo << "': "<< contarTotal << std::endl;
	std::cout << "Tiempo de busqueda P/C: " << totalTimeThread << "[ms]" << std::endl;
	
	

	return(EXIT_SUCCESS);
}

