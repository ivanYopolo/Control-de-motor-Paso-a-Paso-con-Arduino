/* ### Manejo de motor paso a paso ###
 * ## Laboratorio Abierto: Primeros Pasos en Electrónica ##
 * # Módulo 03 - Código en Arduino (cableado) #
 *
 * Autor:       Iván Yopolo.
 * UTN-FRBA     Ingeniería Electrónica.
 */
 
#ifndef __INCLUDES_H
    #define __INCLUDES_H

    // ##########################################
    // ### INCLUDES ###
    // ##########################################
    #include                    <Arduino.h>
    
    // ##########################################
    // ### DEFINES & PINOUT PÚBLICOS ###
    // ##########################################
    // # Inputs #
    #define 	PIN__DIR   		2       // Pulsador de cambio de dirección.
    #define 	PIN__MARCHA    	3       // Pulsador de marcha/parada.
    #define 	PIN__POT      	A1      // Potenciómetro variador de frecuencia.

    // Común -> 5 V.
    // # Outputs #
    #define 	PIN__A1         4       // A+
    #define 	PIN__B1			6       // B+
    #define 	PIN__A2         7       // A-
    #define 	PIN__B2         8       // B-
    
    // # Parámetros de tiempo #
    #define 	MAX_FREQ		50					// 50 Hz
    #define		MIN_DELAY_MS	(1000/MAX_FREQ)
    #define		MAX_DELAY_MS	1000
    #define 	T_BOBINAS		(1/(8 * MAX_FREQ))	// T = 8t  =>  t = 1/8 T  =>  t = 1/8 1/F  =>  t = 1/400
    #define		MAX_MASK_VALUE	0b10000

    typedef enum direccion_e {
        ADELANTE = 0,
        ATRAS = 1
    } direccion_t;
    
    typedef enum estado_e {
        APAGADO = 0,
        ENCENDIDO = 1
    } estado_t;

    // # GLOBAL #
    extern uint8_t				sentidoDeGiro;		// Los tipos de datos uint8_t, uint32_t, int8_t, etc, son enteros que 
    extern uint32_t				tBobinas;			// pueden ser signados o no, según el prefijo "u". Sirven para asignar
    extern uint32_t 			tAct;				// datos de un tamaño fijo, sin variar según implementación.
    extern uint8_t				estadoMotor;		// Pensar que no todos los sistemas definen al "int" o el tamaño de un puntero
													// del mismo tamaño; mucho menos en antaño.

    // ##########################################
    // ### FUNCIONES & RUTINAS PÚBLICAS ###
    // ##########################################
    // # ISR: Interrupt Service Routine (función asincrónica) #
    void    	CambiarMarcha();
    void		CambiarEstado();

    uint32_t	LeerPotAFrec();
    void		Stop();
    void		Marcha();
#endif
