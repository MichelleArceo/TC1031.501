# Evidencia Competencia - Actividad Integral 2.3 #
> Estructura de Datos Lineales

### Tareas ###
1. Abra el archivo de entrada llamado "bitacora.txtVista previa del documento" lealo y almacene los datos en una lista doblemente ligada.
2. Ordene la información por IP para la realización de las búsquedas.
3. Solicite al usuario las IPs de inicio y fin de búsqueda de información.
4. Despliegue los registros correspondientes a esas IPs.
5. Almacenar en un archivo el resultado del ordenamiento.
6. Realizar en forma individual una investigación y reflexión de la importancia y eficiencia del uso de las listas doblemente ligadas en una situación problema de esta naturaleza,  generando un documento llamado "ReflexAct2.3.pdf"

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
    - actividad2_3.pdf
    
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