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
test.txt
````
No te olvides de siempre incluir la extensión .txt

