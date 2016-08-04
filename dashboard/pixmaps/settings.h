#ifndef SETTINGS_H
#define SETTINGS_H


#define PIXMAP_WIDTH   1024
#define PIXMAP_HEIGHT  600

#define FONT    "Consolas"

// Letters per Text-Label
#define LABEL_LETTERS       5
#define VALUE_LETTERS       9

// Label-Text size in points
#define FONT_SIZE_TEXT      30
#define FONT_SIZE_STATUS    100
#define FONT_SIZE_GEAR      200

// Border-space
#define BORDER_SPACE        10



//#define MIN_Y   STATUS_PT_SIZE+(2*BORDER_SPACE)
#define MIN_Y   FONT_SIZE_STATUS+50
#define MAX_Y   PIXMAP_HEIGHT-20
#define MIN_X   BORDER_SPACE
#define MAX_X   PIXMAP_WIDTH-BORDER_SPACE


#endif // SETTINGS_H

