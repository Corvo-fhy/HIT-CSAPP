int my_int_size_is32()
{
    int set_msb = 1 << 31; //若1（二进制：1）左移31位set_msb为非零的数，则机器的int至少为32位。
    int set_lsb = 2 << 31; //若2（二进制：01）左移31位set_lsb为零，则机器的int最多为32位。
    return set_msb && (!set_lsb);
}

int my_int_size_is16()
{
    int set_msb = 1 << 15; //若1（二进制：1）左移15位set_msb为非零的数，则机器的int至少为16位。
    int set_lsb = 2 << 15; //若2（二进制：01）左移15位set_lsb为零，则机器的int最多为16位。
    return set_msb && (!set_lsb);
}

