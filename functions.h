#include "Arduino.h"

const char SLASH = '/';

bool dispatch_to_SPIFFS(const char* addr, int length, String path) {
    File file = SPIFFS.open(path, "w+");

    if(!file) {
        return false;
    }

    for(int i = 0; i < length; i++) {
        file.write(pgm_read_byte_near(addr + i));
    }
    file.close();
    return true;
}

bool write_file(String path, String& buffer) {
    if(path.charAt(0) != SLASH) {
        path = String(SLASH) + path;
    }
    File file = SPIFFS.open(path, "w+");

    if(!file) {
        return false;
    }

    uint32_t length = buffer.length();
    for(uint32_t i = 0; i < length; i++) {
        file.write(buffer.charAt(i));
    }
    file.close();

    return true;
}

String str(const char* ptr) {
    char key_word[strlen_P(ptr)];

    strcpy_P(key_word, ptr);
    return String(key_word);
}

char *str_const_copy(char *dest, const char * src) {
    size_t size = strlen(dest);
    if(size > 0) {
        size_t i;
        for(i = 0; i < size - 1 && src[i]; i++) {
            dest[i] = src[i];
        }
        dest[i] = '\0';
    }
    return dest;
}

String get_file_name(String data, char separator, int index) {
    int found = 0;
    int str_index[] = {0, -1};
    int max_index = data.length() - 1;

    for(int i = 0; i <= max_index && found <= index; i++) {
        if(data.charAt(i) == separator || i == max_index) {
            found++;
            str_index[0] = str_index[1] + 1;
            str_index[1] = (i== max_index) ? i + 1 : i;
        }
    }

    return found > index ? data.substring(str_index[0], str_index[1]) : "";
}