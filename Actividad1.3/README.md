# Evidencia Competencia - Actividad Integral 1.3 #
> Conceptos Básicos y Algoritmos Fundamentales
### Tareas ###
1. Abra el archivo de entrada llamado "bitacora.txt" lealo y almacene los datos en un vector.
2. Ordene la información por fecha para la realización de las búsquedas.
3. Solicite al usuario las fechas de inicio y fin de búsqueda de información.
4. Despliegue los registros correspondientes a esas fechas.
5. Almacenar en un archivo el resultado del ordenamiento.
6. Realizar una investigación y reflexión en forma individual de la importancia y eficiencia del uso de los diferentes algoritmos de ordenamiento y búsqueda en una situación problema de esta naturaleza, generando un documento llamado "ReflexAct1.3.pdf"
### Subcompetencias Evaluadas ###
> SICT0301B - Evalúa los componentes que integran una problemática de acuerdo a principios y procesos computacionales.

> SICT0302B - Toma decisiones en la solución de problemas en condiciones de incertidumbre y diferentes niveles de complejidad con base metodologías de investigación y de cómputo.

> SICT0303B - Implementa acciones científicas e ingenieriles o procesos computacionales que cumplen con el tipo de solución requerida.

> SEG0702A - Tecnologías de Vanguardia. Evalúa diversas tecnologías con apertura a la búsqueda e implementación de alternativas relevantes en la transformación de la práctica profesional.
### Estuctura de Archivos ###
- main.cpp
- input
    - bitacora.txt
- output
    - (acá se generarán los CSV con resultados de búsquedas)
- .gitignore
- README.md
- reflexiones
    - actividad1_3.pdf
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