#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_LINE_LENGTH 1024
#define MAX_MESSAGES 128

/* Delays */
#define LETTER_DELAY 80000 /* Letter delay (microseconds) */
#define MESSAGE_DELAY 2 /* Message delay (seconds) */

/* Cursor position */
#define ROW 0
#define COL 0

/* Globals */
const char *custom_messages[MAX_MESSAGES];
static char message_storage[MAX_MESSAGES][MAX_LINE_LENGTH];
size_t num_custom_messages = 0;
bool custom_message = false;

int load_messages_from_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        return 1;
    }

    size_t i = 0;
    while (i < MAX_MESSAGES && fgets(message_storage[i], MAX_LINE_LENGTH, file)) {
        message_storage[i][strcspn(message_storage[i], "\r\n")] = '\0';
        custom_messages[i] = message_storage[i];
        i++;
    }

    num_custom_messages = i;
    custom_message = true;

    fclose(file);
    return 0;
}

void typewriter(const char *text, useconds_t delay) {
    move(COL, ROW);
    for (size_t i = 0; i < strlen(text); i++) {
        addch(text[i]);
        refresh();
        usleep(delay);
    }
}

const char *default_messages[] = {
    "Wake up, Neo...",
    "The Matrix has you...",
    "Follow the white rabbit.",
    "Knock, knock, Neo."
};

const size_t num_messages = sizeof(default_messages) / sizeof(default_messages[0]);

void write_messages(const char **messages, size_t count) {
    for (size_t i = 0; i < count; i++) {
        clear();
        refresh();
        typewriter(messages[i], LETTER_DELAY);
        sleep(MESSAGE_DELAY);
    }
}

int main(int argc, char *argv[]) {
    const char *filename = NULL;

    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-m") == 0 || strcmp(argv[i], "--message") == 0) {
            if (i + 1 < argc) {
                filename = argv[i + 1];
                break;
            } else {
                fprintf(stderr, "error: missing file path\n");
                return 1;
            }
        }
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            printf("-m, --message <file path> - Specify file path and its content will be displayed.\n");
            return 0;
        }
    }

    if (filename) {
        if (load_messages_from_file(filename) != 0) {
            return 1;
        }
    }

    initscr();
    start_color();
    use_default_colors();
    init_pair(1, COLOR_GREEN, -1); /* Color can be changed */
    attron(COLOR_PAIR(1));
    curs_set(2);
    echo();

    if (custom_message) {
        write_messages(custom_messages, num_custom_messages);
    } else {
        write_messages(default_messages, num_messages);
    }

    endwin();
    return 0;
}
