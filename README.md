# NEKOLANG

## INTRODUCCIÓN
Se implementó un **analizador léxico** que va a identificar los tokens y símbolos de nuestro lenguaje de programación simplificado que hemos creado llamado **Nekolang**.
También se desarrolló un **analizador sintáctico**, para ello  se implementó manualmente un parser descendente en C++, se encargará de verificar y consumir los tokens del analizador léxico.

## REQUISITOS
- Un compilador de C++ compatible con C++11 o superior (como `g++`).
- Un editor de texto o IDE (VSCode, Code::Blocks, etc.).
- Terminal o consola para compilar y ejecutar.
## COMPILACIÓN
Abre una terminal en la carpeta del proyecto y ejecuta:
```bash
g++ neko.cpp -o neko
````
Para ejecutar el programa:
```bash
./neko
````
El programa pedirá el nombre del archivo txt donde estará el código fuente en lenguaje Nekolang:
```bash
    Ingrese el nombre del archivo fuente NekoLang:
```
Ejemplo de entrada:
```bash
valido.txt
````
No te olvides de siempre incluir la extensión .txt
## SALIDA GENERADA
Al ejecutar el analizador, se generan los siguientes archivos:
- tokens.txt: Lista de tokens detectados con tipo, lexema y número de línea.
- simbolos.txt: Tabla de símbolos con identificadores declarados, tipo, valor, línea y dirección.
- errores.txt: Errores sintácticos encontrados.
## CÓDIGOS DE PRUEBA
Se incluye una carpeta con archivos de prueba:
- valido.txt : código fuente sin errores.
- invalido.txt : código fuente con errores sintácticos.
