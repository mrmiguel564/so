Integrantes:
    Patricio Hinojosa   Patricio.hinojosa@alumnos.uv.cl
    Brandon Diaz        Brandon.Diaz@alumnos.uv.cl
Solución:
    Para la solucion lo que se realizo, primero fue generar la funcion contarParcial, 
    de forma tal que esta funcion funcione bajo el paradigma de dividir y vencer, 
    una vez realizada la funcion,se procedio a leer la documentacion de la libreria
    thread y mutex utilizada luego para generar los threads.
    
    para la division en threads lo que hicimosfue generar particiones en base a la cantidad 
    de  threads que se pasaban como argumento al main, luego se dividia el total de elementos
    en el vector por la cantidad de threads a utilizar, y luego se genera un vector de threads
    en cada vector se utiliza la funcion  contarParcial, luego de esto identificamos la zona critica
    esta estaba dentr de la funcion contarParcial:

    void contarParcial(char x,unsigned int inicio, unsigned int final) {
	
        for(unsigned int i = inicio; i<=final; i++){
            if(x == v[i]){
                contador+=1;//zona critica
            }
        }
    }
    Luego de identificarla se procedio a utilizar la libreria mutex:

    void contarParcial(char x,unsigned int inicio, unsigned int final) {
	
        for(unsigned int i = inicio; i<=final; i++){
            if(x == v[i]){
                BlockVect.lock();//bloqueo por mutex
                contador+=1;//zona critica
                BlockVect.unlock();//desbloqueo
            }
        }
    

    }



