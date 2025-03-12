    char gal_mult(unsigned char byte, unsigned char tab_val){
	unsigned char ret = 0;
	unsigned char high_bit;
  for (char counter = 0; counter < 8; counter++){
        if ((tab_val & 1) == 1){
            ret ^= byte;
				}
        high_bit = (byte & 0x80);
        byte <<= 1;
        if (high_bit == 0x80){
            byte ^= 0x1b;
				}
        tab_val >>= 1;
    }
    return ret;
}
