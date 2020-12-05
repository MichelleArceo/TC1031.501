# Evidencia Competencia - Actividad Integral 5.2 #
> Actividad Integral sobre el uso de códigos hash

### Tareas ###
1. Lea el archivo de entrada "bitacora3.txt" (Formato del archivo bitacora.pdf).
2. Crear una tabla hash cuya llave sea el puerto y cuyo valor sea un resumen de ese puerto. Este resumen deberá incluir, el número de accesos, el número de conexiones (ip únicos) así como las ips de origen.
3. Realiza un método que dado un nombre del puerto regrese el valor asociado a él desplegando la información de una manera adecuada

### Subcompetencias Evaluadas ###
> SICT0301B - Evalúa los componentes que integran una problemática de acuerdo a principios y procesos computacionales.
> SICT0302B - Toma decisiones en la solución de problemas en condiciones de incertidumbre y diferentes niveles de complejidad con base metodologías de investigación y de cómputo.
> SICT0303B - Implementa acciones científicas e ingenieriles o procesos computacionales que cumplen con el tipo de solución requerida.
> SEG0702A - Tecnologías de Vanguardia. Evalúa diversas tecnologías con apertura a la búsqueda e implementación de alternativas relevantes en la transformación de la práctica profesional.

### Estuctura de Archivos ###
- main.cpp
- input
    - bitacora3.txt
- output
    - (acá se generarán el TXT con las tablas Hash y el resultado de busqueda del puerto)
- .gitignore
- README.md
- reflexiones

### Compilación y Ejecución ###
* Descargar repositorio
* Realizar compilación: macOS + Linux
```
$ ~ clang++ main.cpp -o bitacora
```
* Realizar compilación: Windows
```
$ ~ g++ main.cpp -o bitacora
```
* Correr archivo compilado 
```
$ ~ ./bitacora
```
