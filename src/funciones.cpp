/* ### Manejo de motor paso a paso ###
 * ## Laboratorio Abierto: Primeros Pasos en Electrónica ##
 * # Módulo 03 - Código en Arduino (cableado) #
 *
 * Autor:       Iván Yopolo.
 * UTN-FRBA     Ingeniería Electrónica.
 */


/* ### OBJETIVO ###
 * 1) Leer datos del potenciómetro para variar frecuencia.
 * 2) Interrumpir por pulsador 1 o 2 para dirección (cambia fila de una matriz de datos, pasando al otro array).
 * 3) Hacer la matemática para mapear los valores de 0 a 50 Hz.     T = 8t      /  t: delay entre bobina y bobina.
 * 4) Utilizar millis() para elegir si mandar una señal baja o alta.
 * 5) 
 * X) 
 * X) 
 */

/* ###########################################
 * ### INCLUDES ###
 * ########################################### */
#include        "../inc/includes.h"


/* ###########################################
 * ### MACROS & TIPOS DE DATOS PRIVADOS ###
 * ########################################### */
//~ #define		FREQ_SYSTICK	1000000
//~ #define 	DELAY_A			1500


/* ###########################################
 * ### PROTOTIPOS DE FUNCIONES PRIVADAS ###
 * ########################################### */
//


/* ###########################################
 * ### VARIABLES GLOBALES PRIVADAS ###
 * ########################################### */
uint8_t 		__bitMask = 0x1;


/* ###########################################
 * ### FUNCIONES PRIVADAS ###
 * ########################################### */
//


/* ###########################################
 * ### FUNCIONES PÚBLICAS ###
 * ########################################### */
//


/* ###########################################
 * ### VARIABLES GLOBALES PÚBLICAS ###
 * ########################################### */
uint8_t		 	sentidoDeGiro = ADELANTE;
uint8_t			estadoMotor = APAGADO;
uint32_t		tBobinas = 1; 
uint32_t 		tAct = 0;



void ShiftMask();
void MarchaDelantera();
void MarchaTrasera();



//~ // ##########################################
//~ // CambiarMarchaAdelante (IRS)
//~ // ##########################################
//~ /* Función asíncona (IRS = Interrupt Service Routine).
 //~ * Cambia la lógica de los pines (sentido en el cual
 //~ * se van prendiendo/apagando).
 //~ */
//~ void CambiarMarchaAdelante() {
    //~ sentidoDeGiro = ADELANTE;
//~ }


//~ // ##########################################
//~ // CambiarMarchaAtras (IRS)
//~ // ##########################################
//~ /* Función asíncona (IRS = Interrupt Service Routine).
 //~ */
//~ void CambiarMarchaAtras() {
    //~ sentidoDeGiro = ATRAS;
//~ }


// ##########################################
// CambiarMarcha (IRS)
// ##########################################
/* Función asíncona (IRS = Interrupt Service Routine).
 */
void CambiarMarcha() {
    sentidoDeGiro++;
    sentidoDeGiro %= 2;
    
	Serial.print( "# Sentido = " );
	Serial.print( sentidoDeGiro );
	Serial.print( " #\n\n" );
}


// ##########################################
// CambiarEstado (IRS)
// ##########################################
/* Función asíncona (IRS = Interrupt Service Routine).
 */
void CambiarEstado() {
    estadoMotor++;
    estadoMotor %= 2;
    
	Serial.print( "# Estado = " );
	Serial.print( estadoMotor );
	Serial.print( " #\n\n" );
}


// ##########################################
// LeerPotAFrec
// ##########################################
/* Lee datos del potenciómetro y los traduce a frecuencia. 
 */
uint32_t LeerPotAFrec() {
    return ( map( analogRead( PIN__POT ), 0, 1023, MIN_DELAY_MS, MAX_DELAY_MS ) );
    //~ return ( map( analogRead( PIN__POT ), 0, 1023, 0, 10000 ) );
}


// ##########################################
// Stop
// ##########################################
/* Frena el motor.
 */
void Stop() {
	// Serial.print( "> Parando...\n" );
	
	digitalWrite( PIN__A1, LOW );
	digitalWrite( PIN__B1, LOW );
	digitalWrite( PIN__A2, LOW );
	digitalWrite( PIN__B2, LOW ); 
	
	// Serial.print( "> Motor parado.\n\n" );
}


// ##########################################
// Marcha
// ##########################################
/* Marcha con sentido "dinámico". Cambia según flags.
 * 
 * Lee un Byte (char) donde lee sus bits en binario y prende bobinas
 * según los primeros 4 bits.
 */
void Marcha() {
	
	if ( tAct + tBobinas <= millis() ) {
		Serial.print( "> Cambio de bobina...\n" );
		
		if ( __bitMask & (1 << 0) ) {			// 0x1 = 0b0001
			digitalWrite( PIN__A1, HIGH );
			digitalWrite( LED_BUILTIN, HIGH );	// DEBUG
		} else {
			digitalWrite( PIN__A1, LOW );
			digitalWrite( LED_BUILTIN, LOW );
		}
		
		if ( __bitMask & (1 << 1) ) {			// 0x2 = 0b0010
			digitalWrite( PIN__B1, HIGH );
		} else {
			digitalWrite( PIN__B1, LOW );
		}
		
		if ( __bitMask & (1 << 2) ) {			// 0x4 = 0b0100
			digitalWrite( PIN__A2, HIGH );
		} else {
			digitalWrite( PIN__A2, LOW );
		}
		
		if ( __bitMask & (1 << 3) ) {			// 0x8 = 0b1000
			digitalWrite( PIN__B2, HIGH );
		} else {
			digitalWrite( PIN__B2, LOW );
		}
		
		//~ // # Apagado de bobinas #
		//~ if ( !(__bitMask | ~(1)) ) {
			//~ digitalWrite( PIN__A1, LOW );
		//~ }
		//~ if ( !(__bitMask | ~(1 << 1)) ) {
			//~ digitalWrite( PIN__B1, LOW );
		//~ }
		//~ if ( !(__bitMask | ~(1 << 2)) ) {
			//~ digitalWrite( PIN__A2, LOW );
		//~ }
		//~ if ( !(__bitMask | ~(1 << 3)) ) {
			//~ digitalWrite( PIN__B2, LOW );
		//~ }
		
		tAct = millis();	// Se actualiza el tiempo actual.
		ShiftMask();		// Se desplaza la máscara según sentido de giro.
	}
	
	
}


// ##########################################
// ShiftMask
// ##########################################
/* Cambia la máscara y desplaza bits según sentido
 * de giro.
 * 
 * SECUENCIA (horario):
 * 00: 0b0000 0001
 * 01: 0b0000 0010 
 * 02: 0b0000 0100 
 * 03: 0b0000 1000 
 * 
 * SECUENCIA (anti-horario):
 * 03: 0b0000 1000 
 * 02: 0b0000 0100 
 * 01: 0b0000 0010 
 * 00: 0b0000 0001
 */
void ShiftMask() {
	switch ( sentidoDeGiro ) {
		case ADELANTE:
			__bitMask = __bitMask << 1;
			
			if ( __bitMask >= MAX_MASK_VALUE )	// Superó el rango máximo de máscara.
				__bitMask = 0b0001;
				//~ __bitMask = 0x1;	// Alternativa por si el compilador no reconoce el formato en binario "AbCCCC".
		break;
		
		
		case ATRAS:
			__bitMask = __bitMask >> 1;
			
			if ( !__bitMask )			// Generalmente, se toma siempre el 0 como falso.
				__bitMask = 0b1000;
				//~ __bitMask = 0x8;
		break; 
	}
	
	Serial.print( "> Nueva máscara de bits = 0x" );
	Serial.print( __bitMask, HEX );
	Serial.print( "\n\n" );
}


// ##########################################
// MarchaDelantera
// ##########################################
/* Marcha en sentido "delantero".
 * EN DESUSO.
 */
void MarchaDelantera() {
	digitalWrite( PIN__A1, HIGH );
	digitalWrite( PIN__B1, LOW );
	digitalWrite( PIN__A2, LOW );
	digitalWrite( PIN__B2, LOW );
	
	delay(tBobinas);
	
	digitalWrite( PIN__A1, HIGH );
	digitalWrite( PIN__B1, HIGH );
	digitalWrite( PIN__A2, LOW );
	digitalWrite( PIN__B2, LOW );
	
	delay(tBobinas);
	
	digitalWrite( PIN__A1, LOW );
	digitalWrite( PIN__B1, HIGH );
	digitalWrite( PIN__A2, LOW );
	digitalWrite( PIN__B2, LOW );
	
	delay(tBobinas);
	
	digitalWrite( PIN__A1, LOW );
	digitalWrite( PIN__B1, HIGH );
	digitalWrite( PIN__A2, HIGH );
	digitalWrite( PIN__B2, LOW );
	
	delay(tBobinas);
	
	digitalWrite( PIN__A1, LOW );
	digitalWrite( PIN__B1, LOW );
	digitalWrite( PIN__A2, HIGH );
	digitalWrite( PIN__B2, LOW );
	
	delay(tBobinas);
	
	digitalWrite( PIN__A1, LOW );
	digitalWrite( PIN__B1, LOW );
	digitalWrite( PIN__A2, HIGH );
	digitalWrite( PIN__B2, HIGH );
	
	delay(tBobinas);
	
	digitalWrite( PIN__A1, LOW );
	digitalWrite( PIN__B1, LOW );
	digitalWrite( PIN__A2, LOW );
	digitalWrite( PIN__B2, HIGH );
	
	delay(tBobinas);
	
	digitalWrite( PIN__A1, HIGH );
	digitalWrite( PIN__B1, LOW );
	digitalWrite( PIN__A2, LOW );
	digitalWrite( PIN__B2, HIGH );
	
	delay(tBobinas);
}


// ##########################################
// MarchaTrasera
// ##########################################
/* Marcha en sentido "trasero".
 * EN DESUSO.
 */
void MarchaTrasera() {
	digitalWrite( PIN__A1, HIGH );
	digitalWrite( PIN__B1, LOW );
	digitalWrite( PIN__A2, LOW );
	digitalWrite( PIN__B2, HIGH );
	
	delay(tBobinas);
	
	digitalWrite( PIN__A1, LOW );
	digitalWrite( PIN__B1, LOW );
	digitalWrite( PIN__A2, LOW );
	digitalWrite( PIN__B2, HIGH );
	
	delay(tBobinas);
	
	digitalWrite( PIN__A1, LOW );
	digitalWrite( PIN__B1, LOW );
	digitalWrite( PIN__A2, HIGH );
	digitalWrite( PIN__B2, HIGH );
	
	delay(tBobinas);
	
	digitalWrite( PIN__A1, LOW );
	digitalWrite( PIN__B1, LOW );
	digitalWrite( PIN__A2, HIGH );
	digitalWrite( PIN__B2, LOW );
	
	delay(tBobinas);
	
	digitalWrite( PIN__A1, LOW );
	digitalWrite( PIN__B1, HIGH );
	digitalWrite( PIN__A2, HIGH );
	digitalWrite( PIN__B2, LOW );
	
	delay(tBobinas);
	
	digitalWrite( PIN__A1, LOW );
	digitalWrite( PIN__B1, HIGH );
	digitalWrite( PIN__A2, LOW );
	digitalWrite( PIN__B2, LOW );
	
	delay(tBobinas);
	
	digitalWrite( PIN__A1, HIGH );
	digitalWrite( PIN__B1, HIGH );
	digitalWrite( PIN__A2, LOW );
	digitalWrite( PIN__B2, LOW );
	
	delay(tBobinas);
	
	digitalWrite( PIN__A1, HIGH );
	digitalWrite( PIN__B1, LOW );
	digitalWrite( PIN__A2, LOW );
	digitalWrite( PIN__B2, LOW );
	
	delay(tBobinas);
}


