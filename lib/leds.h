#ifndef LEDS_LIB
#define LEDS_LIB
#define OFF 0
#define ON 1
#define TOGGLE 2

// BRIDGE TAFFIC LIGHT
#define BRIDGE_RED_BOTTOM_LED PL0   // RED      #FF0000
#define BRIDGE_RED_TOP_LED PL1      // RED      #FF0000
#define BRIDGE_GREEN_TOP_LED PL2    // GREEN    #00FF00
#define BRIDGE_GREEN_BOTTOM_LED PL3 // GREEN    #00FF00
#define BRIDGE_YELLOW_LED PL4       // YELLOW   #FFFF00
#define TAFFIC_RED_LED PL5          // RED      #FF0000

// PANEL
#define PANEL_COUNTER_1_LED PB0     // GREEN    #00FF00
#define PANEL_COUNTER_2_LED PB1     // GREEN    #00FF00
#define PANEL_COUNTER_3_LED PB2     // GREEN    #00FF00
#define PANEL_BARRIER_LED PB3       // RED      #FF0000
#define PANEL_BRIDGE_CLOSED_LED PC0 // RED      #FF0000
#define PANEL_MODE_LED PC1          // YELLOW   #FFFF00
#define PANEL_BRIDGE_RED_LED PC2    // RED      #FF0000
#define PANEL_BRIDGE_YELLOW_LED PC3 // YELLOW   #FFFF00
#define EMERGENCY_LED PC4           // RED      #FF0000
#define PANEL_BRIDGE_OPEN_LED PC5   // GREEN    #00FF00

// PENDING
#define PANEL_YELLOW_2_LED PA7 // YELLOW   #FFFF00 (open met dubbelrood) voor testen
#define PANEL_YELLOW_3_LED PE5 // YELLOW   #FFFF00 (gele lamp aan/uit)
#define PANEL_YELLOW_4_LED PK1 // YELLOW   #FFFF00 (boot voor de brug)

// configure led pins as output
void initLeds(void);

void setEmergencyLed(int status);
void setBridgeRedBottomLed(int status);
void setBridgeRedTopLed(int status);
void setPanelBridgeClosedLed(int status);
void setPanelBarrierLed(int status);
void setPanelYellow3Led(int status);
void setBridgeYellowLed(int status);
void setBridgeGreenTopLed(int status);
void setBridgeGreenBottomLed(int status);
void setPanelBridgeOpenLed(int status);
void setPanelCounterLed(int number);

void setTrafficRedLed(int status);     // TODO: to be used
void setPanelModeLed(int status);      // TODO: to be used
void setPanelYellow2Led(int status);   // TODO: to be used
void setPanelYellow1Led(int status);   // TODO: to be used
void setPanelBridgeRedLed(int status); // TODO: to be used
#endif                                 // !LEDS_LIB