# Trabajo Práctico: Tipos Abstractos de Datos y Complejidad Computacional

**Materia:** TD III - Algoritmos y Estructuras de Datos
**Temática Principal:** Optimización Algorítmica, TAD y Análisis de Complejidad

## Descripción del Proyecto

Este proyecto consiste en la optimización y reestructuración de un prototipo funcional de **billetera virtual (Wallet)** que opera sobre una **blockchain rudimentaria**. 

Si bien la implementación inicial del sistema cuenta con todas las funcionalidades requeridas, presenta graves problemas ante el escalamiento de datos. El objetivo central del trabajo es adaptar, 
rediseñar e implementar las estructuras de datos subyacentes necesarias para que el sistema cumpla con lasrestricciones de complejidad temporal exigidas.



## Componentes y Arquitectura del Sistema

El sistema se modela a través de dos clases principales que interactúan entre sí:

### 1. Clase `Blockchain`
Constituye la capa base y el registro central del sistema. Maneja una interfaz interna y rudimentaria encargada de:
* **Almacenamiento de transacciones:** Registro histórico y secuencial de los movimientos financieros.
* **Apertura de nuevas billeteras:** Gestión del alta de cuentas en el sistema.
* **Ejecución de transferencias:** Validación y procesamiento de transacciones entre billeteras registradas.

El flujo de creación se realiza mediante el método `blockchain.abrir_billetera()`, el cual ejecuta tres acciones críticas:
1. Registra la nueva billetera en la estructura interna de la blockchain.
2. Realiza una transacción semilla (*seed*) automática de 100 unidades monetarias como saldo inicial.
3. Retorna un puntero/referencia a la billetera creada para interactuar con ella.

### 2. Clase `Billetera`
Funciona como la capa de abstracción avanzada y proporciona la interfaz de servicios que consumirá la aplicación móvil del cliente. Es el núcleo donde se deben optimizar 
los algoritmos para resolver las siguientes consultas:
* **Balance actual:** Obtención del saldo disponible en tiempo real.
* **Historial reciente:** Recuperación de las últimas transacciones ejecutadas por el usuario.
* **Evolución histórica de saldo:** Cálculo eficiente del saldo disponible al cierre de cualquier día específico.
* **Análisis de frecuencia:** Generación de un listado de las billeteras a las que el usuario transfiere dinero con mayor frecuencia.



## Objetivos de Optimización y Complejidad

El desafío principal del proyecto radica en la transición de estructuras de datos simples (como arreglos o listas enlazadas) hacia estructuras avanzadas eficientes (tablas hash, árboles de búsqueda balanceados, heaps/colas de prioridad) según corresponda. 

Cada funcionalidad de la clase `Billetera` debe ser analizada minuciosamente para reducir su complejidad temporal desde un orden ineficiente (ej. $O(n)$ o $O(n^2)$) hacia los límites óptimos requeridos por la consigna (ej. $O(1)$ o $O(\log n)$).

