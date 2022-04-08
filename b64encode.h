/*
*   Include string and io before this.
*/

const char ALPHABET[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

struct chunk{
    char characters[4];
    std::string string()
    {
        std::string output = "";
        for (uint8_t i = 0; i < 4; i++)
        {
            output += characters[i];
        }
        return output;
    }

    chunk ( std::string _toEncode)
    {
        characters[0] = ALPHABET[ _toEncode[0] >> 2];
        characters[1] = ALPHABET[((_toEncode[0] & 0b11) << 4) | ((_toEncode[1] & 0b11110000) >> 4)];
        characters[2] = ALPHABET[(_toEncode[1] & 0x0F) << 2 | ( (_toEncode[2] & 0b11000000) >> 6)];
        characters[3] = ALPHABET[_toEncode[2] & 0b00111111];
    }

    chunk(){};
};

struct chunks{
    int count;
    int remainder;
};

struct plainString
{
    chunks chunk;
    std::string plainText;


    plainString(std::string _plainText){ 
        plainText = _plainText;
        chunk = chunks { (_plainText.length()/3), _plainText.length() % 3};
    };

    plainString(char* _plainText){
        plainText = _plainText;
        chunk = chunks { plainText.length()/3, plainText.length() % 3};
    }
};


chunk encodeChunk(std::string _string)
{
    chunk output;
    output.characters[0] = ALPHABET[ _string[0] >> 2];
    output.characters[1] = ALPHABET[((_string[0] & 0b11) << 4) | ((_string[1] & 0b11110000) >> 4)];
    output.characters[2] = ALPHABET[(_string[1] & 0x0F) << 2 | ( (_string[2] & 0b11000000) >> 6)];
    output.characters[3] = ALPHABET[_string[2] & 0b00111111];
    return output;
}

chunk encodeRemainder(std::string _string, int chars)
{
    chunk output;
    output.characters[0] = ALPHABET[ _string[0] >> 2];
    switch(chars)
    {
        case 1:
            output.characters[1] = ALPHABET[ ((_string[0] & 0b11) << 4)  ];
            output.characters[2] = '=';
            output.characters[3] = '=';
            break;
        case 2:
            output.characters[1] = ALPHABET[((_string[0] & 0b11) << 4) | ((_string[1] & 0b11110000) >> 4)];
            output.characters[2] = ALPHABET[(_string[1] & 0x0F) << 2];
            output.characters[3] = '=';
            break;
    }
    
    return output;
}

//encode takes a string and returns the b64 encoded string.
std::string encode(plainString _string)
{
    std::string output;
    for (int i = 0; i < _string.chunk.count; i++)
    {
        output += encodeChunk( _string.plainText.substr(i*3, 3)).string();
    }
    output += encodeRemainder(_string.plainText.substr(_string.chunk.count * 3), _string.chunk.remainder).string();
    return output;
}

