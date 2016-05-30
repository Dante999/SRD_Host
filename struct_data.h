#ifndef STRUCT_DATA_H
#define STRUCT_DATA_H


#include <cstdint>


// Tyres
enum
{
  TYRE_FRONT_LEFT = 0,
  TYRE_FRONT_RIGHT,
  TYRE_REAR_LEFT,
  TYRE_REAR_RIGHT,
  //--------------
  TYRE_MAX
};

// (Type#5) Flag Colours (to be used with 'mHighestFlagColour')
enum
{
  FLAG_COLOUR_NONE = 0,       // Not used for actual flags, only for some query functions
  FLAG_COLOUR_GREEN,          // End of danger zone, or race started
  FLAG_COLOUR_BLUE,           // Faster car wants to overtake the participant
  FLAG_COLOUR_WHITE,          // Approaching a slow car
  FLAG_COLOUR_YELLOW,         // Danger on the racing surface itself
  FLAG_COLOUR_DOUBLE_YELLOW,  // Danger that wholly or partly blocks the racing surface
  FLAG_COLOUR_BLACK,          // Participant disqualified
  FLAG_COLOUR_CHEQUERED,      // Chequered flag
  //-------------
  FLAG_COLOUR_MAX
};

// (Type#9) Car Flags (to be used with 'mCarFlags')
enum
{
  CAR_HEADLIGHT         = (1<<0),
  CAR_ENGINE_ACTIVE     = (1<<1),
  CAR_ENGINE_WARNING    = (1<<2),
  CAR_SPEED_LIMITER     = (1<<3),
  CAR_ABS               = (1<<4),
  CAR_HANDBRAKE         = (1<<5),
};

typedef struct dataPackage
{
    int8_t gear;                            // [ UNITS = NONE ]     [ RANGE = -128 -> +127 ]
    int8_t maxGear;                         // [ UNITS = NONE ]     [ RANGE = -128 -> +127 ]
    uint16_t rpm;                           // [ UNITS = rpm  ]     [ RANGE = 0 -> 65535 ]
    uint16_t maxRpm;                        // [ UNITS = rpm  ]     [ RANGE = 0 -> 65535 ]
    uint16_t speed;                         // [ UNITS = km/h ]     [ RANGE = 0 -> 65535 ]
    uint8_t fuelLevel;                      // [ UNITS = liters ]   [ RANGE = 0 -> 255 ]
    uint8_t fuelCapacity;                   // [ UNITS = liters ]   [ RANGE = 0 -> 255 ]

    uint8_t throttle;                       // [ UNITS = percent ]  [ RANGE = 0 -> 100 ]
    uint8_t clutch;                         // [ UNITS = percent ]  [ RANGE = 0 -> 100 ]
    uint8_t brake;                          // [ UNITS = percent ]  [ RANGE = 0 -> 100 ]

    uint16_t tempTyre[TYRE_MAX];            // [ UNITS = celsius ]  [ RANGE = 0 -> 65535 ]
    uint16_t tempBrake[TYRE_MAX];           // [ UNITS = celsius ]  [ RANGE = 0 -> 65535 ]
    uint16_t tempOil;                       // [ UNITS = celsius ]  [ RANGE = 0 -> 65535 ]
    uint16_t tempWater;                     // [ UNITS = celsius ]  [ RANGE = 0 -> 65535 ]

    uint8_t damageAero;                     // [ UNITS = NONE ]     [ RANGE = 0 -> 100 ]
    uint8_t damageEngine;                   // [ UNITS = NONE ]     [ RANGE = 0 -> 100 ]
    uint8_t damageBrake[TYRE_MAX];          // [ UNITS = NONE ]     [ RANGE = 0 -> 100 ]
    uint8_t damageSuspension[TYRE_MAX];     // [ UNITS = NONE ]     [ RANGE = 0 -> 100 ]

    uint8_t raceFlagColour;
    uint8_t carFlags;

    uint8_t racePlacement;

} struct_data;














#endif // STRUCT_DATA_H
