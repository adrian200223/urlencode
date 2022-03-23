#ifndef _PLAGEOJ_URLENCODE_H
#define _PLAGEOJ_URLENCODE_H

// error codes
#define BAD_ENCODING       ""
#define BAD_INPUT         -33

#include <Arduino.h>

/**
 * Percent-encodes a string.
 * @param msg UTF-8 string to encode.
 * @returns Percent-encoded string.
 */
inline String urlEncode(const char *msg)
{
    const char *hex = "0123456789ABCDEF";
    String encodedMsg = "";

    while (*msg != '\0')
    {
        if (('a' <= *msg && *msg <= 'z') || ('A' <= *msg && *msg <= 'Z') || ('0' <= *msg && *msg <= '9') || *msg == '-' || *msg == '_' || *msg == '.' || *msg == '~')
        {
            encodedMsg += *msg;
        }
        else
        {
            encodedMsg += '%';
            encodedMsg += hex[*msg >> 4];
            encodedMsg += hex[*msg & 0xf];
        }
        msg++;
    }
    return encodedMsg;
}
inline String urlEncode(String msg)
{
    return urlEncode(msg.c_str());
}
inline int decoderGetCharValue(char c) {
    if ((int)'0' <= (int)c && (int)c <= (int)'9')
    {
        return (int)c - (int)'0';
    } else
    {
        if ((int)'A' <= (int)c && (int)c <= (int)'F')
        {
            return (int)c - (int)'A' + 10;
        } else
        {
            return BAD_INPUT;
        }
    }
}
inline String urlDecode(const char *msg)
{
    String decodedMsg = "";
    int len = strlen(msg);
    int counter = 0;

    while (*msg != '\0')
    {
        if (('a' <= *msg && *msg <= 'z') || ('A' <= *msg && *msg <= 'Z') || ('0' <= *msg && *msg <= '9') || *msg == '-' || *msg == '_' || *msg == '.' || *msg == '~')
        {
            decodedMsg += *msg;
        } else
        {
            if (*msg == '%')
            {
                if (len - counter < 3) {
                    return BAD_ENCODING;
                }

                if ((('A' <= *(msg + 1) <= 'F') || ('0' <= *(msg + 1) <= '9'))
                 && (('A' <= *(msg + 2) <= 'F') || ('0' <= *(msg + 2) <= '9')))
                {
                    char letter = decoderGetCharValue(*(msg + 1)) << 4 | decoderGetCharValue(*(msg + 2));
                    decodedMsg += letter;
                    msg += 2;
                    counter += 2;
                } else
                {
                    return BAD_ENCODING;
                }
            } else
            {
                return BAD_ENCODING;
            }
        }
        msg++;
        counter++;
    }
    return decodedMsg;
}
inline String urlDecode(String msg)
{
    return urlDecode(msg.c_str());
}
#endif
