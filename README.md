# Control de motor Paso a Paso con Arduino

<p align="center">
<img src="media/UTN-logo.png" alt="UTN-logo" width="200" style="display: block; margin: 5 auto"/>
</p>

<div style="text-align:center">
UTN.FRBA - Ingeniería Electrónica   
</div>    

**Autor:** Iván Yopolo.     
**Co-autor y docente a cargo:** Oscar Pugliese.      

---

> Se recomienda leer el informe técnico con explicación detallada del proyecto entero, su funcionamiento, circuito + PCB, ensamble, entre otras cuestiones. Así, se evitan errores y se puede utilizar esta demostración (o demo) funcional.

# Objetivo   
Se desea controlar un motor paso a paso unipolar (de 5 cables) de modo que se pueda variar su velocidad y sentido de giro, utilizando hardware simple y programación en Arduino (C/C++).   

# Principio de funcionamiento   
Un motor paso a paso es aquel que consta de varios bobinados o enrrollamientos de cables que son utilizados con el fin de generar imanes artificiales o electroimanes al hacerles circular corriente eléctrica, induciendo fuerzas según dictan las leyes de Faraday-Lenz. Al tener 5 cables (uno siendo el común), se energiza una bobina a la vez en secuencia. 

## Hardware
En el circuito planteado, de las 4 bobinas, una toma la referencia de Tierra o _GND_ (0V), mientras el resto de bobinas y el pin común están permanentemente a **+Vmotor** (la tensión con la que trabaja dicho motor). La conexión hace que un 1 lógico se traduzca a 0V, invirtiendo la salida del micro, recibida por el motor.   

Se utilizan pulsadores para controlar tanto el sentido de giro como su estado (en marcha o parado), más un potenciómetro para variar su velocidad.
Por no utilizar un software de antirrebote, se optó por una solución por hardware, con capacitores.

## Software   
El código lee constantemente el potenciómetro para variar la velocidad del motor en tiempo real.    
Se establecen valores mínimos como macros para poder variar en tiempos apreciables al ojo humano, además de valores máximos para no estresar ni al motor ni al microprocesador.

Los pulsadores funcionan como interrupciones que cambian una variable tipo "bandera" (_flag_) de la siguiente manera:   
- `PIN__DIR`      -> Cambia `sentidoDeGiro`.   
- `PIN__MARCHA`   -> Cambia `estadoMotor`.   

Mientras el sistema esté en `estadoMotor = ENCENDIDO`, se ejecuta `Marcha()`, donde este lee una máscara de bits que prende y apaga las bobinas según el primer "nibble" o medio Byte (los 4 bits menos significativos); al leer un 1 en cierto bit, prende la bobina correspondiente; al leer un 0 en cierto bit, apaga la bobina correspondiente. Luego, al ejecutarse un cambio del estado de las bobinas, con su retardo según el potenciómetro indique, se ejecuta `ShiftMask()`, que desplaza el bit de la máscara a la siguiente posición según indique `sentidoDeGiro`.

