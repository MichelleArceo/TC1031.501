# Evidencia Competencia - Actividad Integral 4.3 #
> Actividad Integral de Grafos

### Tareas ###
1. Abra el archivo de entrada llamado "bitacora3.txt" lealo y almacene los datos en en una lista de adyacencia organizada por dirección de ip origen (Formato del archivo bitacora.pdf).
2. Determine los puertos con intentos de acceso
3. ¿Qué puertos  presentan la mayor cantidad de intentos de acceso (ataques)?
4. ¿Qué dirección ip presumiblemente se encuentra más vulnerable?

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
    - (acá se generarán el CSV con las cinco IPs con más accesos)
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
