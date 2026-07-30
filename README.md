# Control de motor Paso a Paso con Arduino
**Autor:** Iván Yopolo.   
**Co-autor y docente a cargo:** Oscar Pugliese.   
_UTN.FRBA - Ingeniería Electrónica_   

---

# Objetivo   
Se desea controlar un motor paso a paso unipolar (de 5 cables) de modo que
se pueda variar su velocidad y sentido de giro.   

# Principio de funcionamiento   
Un motor paso a paso es aquel que consta de varios bobinados o enrrollamientos de cables que son utilizados con el fin de generar imanes artificiales o electroimanes al hacerles circular corriente eléctrica, induciendo fuerzas según dictan las leyes de Faraday-Lenz. Al tener 5 cables (uno siendo el común), se energiza una bobina a la vez en secuencia. 

En el circuito planteado, de las 4 bobinas, una toma la referencia de Tierra o _GND_ (0V), mientras el resto de bobinas y el pin común están permanentemente a **+Vmotor** (la tensión con la que trabaja dicho motor). La conexión hace que un 1 lógico se traduzca a 0V, invirtiendo la salida del micro, recibida por el motor.   

Se utilizan pulsadores para controlar el sentido de giro más un potenciómetro para variar su velocidad.

## Software   
El código lee constantemente el potenciómetro para variar la velocidad del motor en tiempo real. Los pulsadores funcionan como interrupciones que cambian una variable tipo "bandera" (_flag_) que indica el sentido de giro. 
