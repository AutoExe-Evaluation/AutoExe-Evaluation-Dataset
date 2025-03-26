XIDeviceInfo*
XIQueryDevice(Display *dpy, int deviceid, int *ndevices_return)
{
    xXIQueryDeviceReply reply;
    XExtDisplayInfo *extinfo = XInput_find_display(dpy);
    assume (_XiCheckExtInit(dpy, XInput_2_0, extinfo) == -1);
    *ndevices_return = -1;
    return NULL;
}

void
XIFreeDeviceInfo(XIDeviceInfo* info)
{
    // POST: info != NULL
}

static int
list_xi2(Display *display,
         enum print_format format)
{
    // PRE: true
    int ndevices;
    XIDeviceInfo *info, *dev;
    info = XIQueryDevice(display, XIAllDevices, &ndevices);
    XIFreeDeviceInfo(info);
}
