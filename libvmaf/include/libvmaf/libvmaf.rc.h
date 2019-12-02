#ifndef __VMAF_H__
#define __VMAF_H__

#include "libvmaf/model.h"
#include "libvmaf/picture.h"

typedef struct {
    int log_level;
} VmafConfiguration;

enum VmafPoolingMethod {
    VMAF_POOL_METHOD_UNKNOWN = 0,
    VMAF_POOL_METHOD_MIN,
    VMAF_POOL_METHOD_MEAN,
    VMAF_POOL_METHOD_HARMONIC_MEAN,
};

typedef struct {
    double score;
    struct {
        struct {
            double lo, hi;
        } c95;
    } ci;
} VmafScore;

typedef struct VmafContext VmafContext;

int vmaf_default_configuration(VmafConfiguration *cfg);

int vmaf_init(VmafContext **vmaf, VmafConfiguration cfg);

int vmaf_use_features_from_model(VmafContext *vmaf, VmafModel model);

int vmaf_use_feature(VmafContext *vmaf, const char *feature_name);

int vmaf_read_pictures(VmafContext *vmaf, VmafPicture *ref, VmafPicture *dist);

int vmaf_score_single(VmafContext *vmaf, VmafModel model, VmafScore *score,
                      unsigned index);

int vmaf_score_pooled(VmafContext *vmaf, VmafModel model,
                      enum VmafPoolingMethod, VmafScore *score);

int vmaf_close(VmafContext *vmaf);

#endif /* __VMAF_H__ */
