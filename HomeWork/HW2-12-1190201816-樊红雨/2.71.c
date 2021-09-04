int xbyte(packed_t word, int bytenum)
{
    int un_byte; //无符号扩展
    int exp_byte; //有符号扩展
    int flag; //标志符号位是否为1
    int h = 0xffffffff;
    un_byte = word >> (bytenum << 3) & 0xff;
    flag = un_byte >> 7;
    exp_byte = un_byte;
    h = h << 8;
    h = h & ((!flag)-1);
    exp_byte = un_byte | h; //如果符号位为1，则将其他位变为1
    return exp_byte;
}