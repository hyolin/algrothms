#include <stdio.h>
#include <string.h>
#include <stdint.h>



uint32_t get_utf8_bytes(char c) 
{
    if ((c & 0x80) == 0) return 1;
    
    uint32_t bytes = 0;
    for (; c & 0x80; c = (c << 1)) bytes++;
    
    return bytes;
}

uint32_t get_utf8_unicode(const char* str) 
{
    uint32_t code = 0;
    
    register uint8_t *bits = &code;
    register uint8_t c1, c2, c3;
    
    uint32_t bytes = get_utf8_bytes(*str);
    
    switch(bytes) {
        case 1:
            *bits = *str;
            break;
        case 2:
            c1 = *str; c2 = *(str + 1);
            *bits = (c1 << 6) + (c2 & 0x3f);
            *(bits + 1) = (c1 >> 2) & 0x07;//(c1 & 0x1f) >> 2;
            break;
        case 3:
            c1 = *str;
            c2 = *(str + 1);
            c3 = *(str + 2);
            *bits = (c2 << 6) + (c3 & 0x3f);
            *(bits + 1) = ((c2 & 0x3f) >> 2) + ((c1 & 0x0f) << 4);
            break;
    }

    return code;
}


int main(int argc, char** argv)
{
    char* str = "你";
    //get_utf8_unicode(str);
    fprintf(stdout, "%s:\n\t%x\n", str, get_utf8_unicode(str));
    return 0;
}
