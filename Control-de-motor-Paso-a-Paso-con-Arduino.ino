/* ### Manejo de motor paso a paso ###
 * ## Laboratorio Abierto: Primeros Pasos en Electrónica ##
 * # Módulo 03 - Código en Arduino (cableado) #
 *
 * Autor:       Iván Yopolo.
 * UTN-FRBA     Ingeniería Electrónica.
 */

/* Metemos todos los includes, macros (#defines) y prototipos útiles
 * en un solo archivo .h .
 */
#include        "inc/includes.h"

// # GLOBALES (privadas) #
//void   ( secuencias[2] )( void );       // 4 pasos + 4 "medio" pasos. Punteros a funciones.

// ##########################################
// setup
// ##########################################
void setup() {
    Serial.begin( 9600 );

    pinMode( PIN__DIR, INPUT_PULLUP );          // Input pullup = activo bajo = recibe un 1 al tener 0V en su pin.
    pinMode( PIN__MARCHA, INPUT_PULLUP );
    pinMode( PIN__POT, INPUT );                 // Varía frecuencia "F".
    
    pinMode( PIN__A1, OUTPUT );
    pinMode( PIN__B1, OUTPUT );
    pinMode( PIN__A2, OUTPUT );
    pinMode( PIN__B2, OUTPUT );

	Stop();
    estadoMotor = APAGADO;

    pinMode( LED_BUILTIN, OUTPUT );
    digitalWrite( LED_BUILTIN, LOW );           // DEBUG.

	tAct = millis();
    tBobinas = LeerPotAFrec();
       
    // Al detectar interrupción externa en el pin, va a la función.
    attachInterrupt( digitalPinToInterrupt( PIN__DIR ), CambiarMarcha, FALLING );    
    attachInterrupt( digitalPinToInterrupt( PIN__MARCHA ), CambiarEstado, FALLING );     
}



// ##########################################
// loop
// ##########################################
void loop() {
    switch ( estadoMotor ) {
        case APAGADO:
	        Stop();
        break;


        case ENCENDIDO:
            tBobinas = LeerPotAFrec();
            Marcha();
        break;
    }
}
