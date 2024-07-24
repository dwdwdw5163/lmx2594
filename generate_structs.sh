gawk 'BEGIN { print "typedef struct {\n    uint8_t addr;\n    uint16_t data;\n} Config;\n\nConfig configs[] = {" } 
{ 
    hex = strtonum($1);
    addr = and(rshift(hex, 16), 0xFF);
    data = and(hex, 0xFFFF);
    printf("    {0x%02X, 0x%04X},\n", addr, data); 
} 
END { print "};" }' lmx2594.txt

