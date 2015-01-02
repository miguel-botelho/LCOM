#include "global_variables.h"

char OPTION = MAIN_MENU; /* @brief OPTION is the menu state*/

int radius = 10; /* @brief radius is the size of the square, brush or circle*/

char tool = PENCIL; /* @brief tool is the selected tool*/

int colour = 0x001F; /* @brief colour is the selected color*/

int RTC_COUNTER = START_RTC_COUNTER; /* @brief RTC_COUNTER is the time that has passed drawing*/

char name[11]; /* @brief name is the username*/

char word[11]; /* @brief word is the username's guess*/

char guess_ai[11]; /* @brief guess_ai is the pc's random word*/

int tries = 0; /* @brief tries number of tries*/

scores_t top_highscores;

int screen_abs = 0; //começa a 0 ||| MAX = 9 (incluindo)

int screen_current = 0; //começa a 0 ||| MAX = 9 (incluindo)
int espaco = 0;
int length = 0;
int length_word = 0;
int contador_high = 0;
int tentativas = 0;
int ai_or_pvp = 0; // 0 = ai; 1 = pvp
int contador_c = CANVAS_Y_F;
int verdadeiro = 0;

char day = 0;
char year = 0;
char month = 0;
char hour = 0;
char minutes = 0;
