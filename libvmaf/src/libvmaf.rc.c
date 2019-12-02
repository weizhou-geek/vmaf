#include <errno.h>
#include <stdlib.h>

#include "libvmaf/libvmaf.rc.h"

struct VmafContext {
    VmafConfiguration cfg;
};

int vmaf_default_configuration(VmafConfiguration *cfg)
{
    (void)cfg;
    return 0;
}

int vmaf_init(VmafContext **vmaf, VmafConfiguration cfg)
{
    VmafContext *const v = *vmaf = malloc(sizeof(*v));
    if (!v) goto fail;

    v->cfg = cfg;
    return 0;

fail:
    return -ENOMEM;
}

int vmaf_close(VmafContext *vmaf)
{
    free(vmaf);
    return 0;
}
