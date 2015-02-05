/*----------------------------------------------------------------------------
 * CMSIS-RTOS 'main' function template
 *---------------------------------------------------------------------------*/

#define osObjectsPublic                     // define objects in main module
#include "osObjects.h"                      // RTOS object definitions
#include "bluetooth.h"
#include "sonar.h"
#include "servo.h"
#include "motors.h"

osMailQId qid_ProcessMessage;

/**
  @brief main: initialize and start the system
*/
int main (void) {
  /* Initialize CMSIS-RTOS */
  osKernelInitialize ();                    
  
  /* Initialize Mail queues */
  qid_ProcessMessage = osMailCreate(osMailQ(ProcessMessage),NULL);
  
  /* Initialize Timers */
  tid_DebounceTimer = osTimerCreate (osTimer(DebounceTimer), osTimerOnce,0);
  
  /* Initialize Peripherials */
  bt_init(9600u);
  Sonar_init(CONTINUOUS);
  Servo_init(MANUAL, SCAN_AND_LOCK);
  motors_init();
   
  /* Start coms thread */
  Init_comms();
  
  /* Start thread execuion */
	osKernelStart ();                          
}
