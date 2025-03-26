void closest_integer(const char* value, int len) {
    assert(len > 0);  // PRE
    if (*strchr(value, '.') != '\0') {
        // remove trailing zeros
        while (value[len - 1] == '0')
            --len;
    }
    float num = atof(value);
    float res;
    if (value[len - 2] == '.' && value[len - 1] == '5') {
        if (num > 0)
            res = ceil(num);
        else
            res = floor(num);
    } else if (len > 1 || value[0] != '0')
        res = int(round(num));
    else
        res = 0;

    assert(abs(res) <= abs(atof(value)));  // POST
}
