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
    #define 	T_BOBINAS		(1/(8 * MAX_FREQ))	// T = 8t  =>  t = 1/8 T  =>  t = 1/8 1/F  =>  t = 1/400

    typedef enum direccion_e {
        ADELANTE = 0,
        ATRAS = 1
    } direccion_t;
    
    typedef enum estado_e {
        APAGADO = 0,
        ENCENDIDO = 1
    } estado_t;

    // # GLOBAL #
    extern uint8_t				sentidoDeGiro;
    extern uint32_t				tBobinas;
    extern uint32_t 			tAct;
    extern uint8_t				estadoMotor;


    // ##########################################
    // ### FUNCIONES & RUTINAS PÚBLICAS ###
    // ##########################################
    // # ISR: Interrupt Service Routine (función asincrónica) #
    //~ void    CambiarMarchaAdelante();
    //~ void    CambiarMarchaAtras();
    void    CambiarMarcha();
    void	CambiarEstado();

    int   	LeerPotAFrec();
    void	Stop();
    void	Marcha();

    //void    A();    // Hace la lógica de si incrementa o decrementa el índice, reiniciando correspondientemente.
    //void    B();    // Manda la señal las bobinas correspondientes.
#endif
