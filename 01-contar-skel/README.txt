Integrantes:
    Miguel Espinoza       Miguel.espinoza@alumnos.uv.cl 	19773392-6
    Silvio Vera			  Silvio.vera@alumnos.uv.cl      	19339408-6
    
Solución:
    Para la solución de la tarea N°2 lo que realizamos fue generar un arreglo el cual 
    monitorea el avance en el proceso revisando que porcentaje del archivo se lleva
    escaneado, esto gracias al numero de caracteres deseados ingresados por consola por
  	el usuario.

  	Para la realizacion de lo anterior lo que hicismos fue modificar un for() el cual tomara
  	el numero de caracteres leidos por el programa y lo dividiese por el total de elementos
  	de esta manera obteniendo el porcentaje de avance de este, ademas en este mismo agregar
  	mediante una arreglo de caracteres una barra de carga simple para que fuese visible el 
  	avance del proceso, la cual se va llenando a medida que se calcula el porcentaje de 
  	avance, rellenando asi un arreglo a la vez que este se muestra en la terminal.


	for(size_t i=0; i < totalElementos; i++){
		double porcentaje = double(i)/double(totalElementos-1)*100.;
		for(auto j=1 ; j<porcentaje; j++){
			carga[j]='\\';
		}
		std::cout << "\r\033[K" << carga << int(porcentaje) <<'%'; //linea qla
		fflush(stdout);
		uint8_t tmpLetra = nRandom(rng);
		v.push_back( tmpLetra );
	}

