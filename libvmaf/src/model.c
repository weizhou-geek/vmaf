#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "model.h"
#include "svm.h"
#include "unpickle.h"

int vmaf_model_load_from_path(VmafModel **model, const char *path)
{
    VmafModel *const m = *model = malloc(sizeof(*m));
    if (!m) goto fail;
    memset(m, 0, sizeof(*m));
    m->path = strdup(path);
    if (!m->path) goto free_m;

    // ugly, this shouldn't be implict (but it is)
    char *svm_path_suffix = ".model";
    char *svm_path = malloc(strlen(m->path) + strlen(svm_path_suffix) + 1
                            * sizeof(*svm_path));
    if (!svm_path) goto free_path;
    strcat(svm_path, m->path);
    strcat(svm_path, svm_path_suffix);
    m->svm = svm_load_model(svm_path);
    free(svm_path);
    if (!m->svm) goto free_path;

    int err = vmaf_unpickle_model(m, m->path);
    if (err) goto free_svm;

    return 0;

free_svm:
    svm_free_and_destroy_model(&(m->svm));
free_path:
    free(m->path);
free_m:
    free(m);
fail:
    return -ENOMEM;
}

void vmaf_model_destroy(VmafModel *model)
{
    if (!model) return;
    free(model->path);
    svm_free_and_destroy_model(&(model->svm));
    for (unsigned i = 0; i < model->n_features; i++)
        free(model->feature[i].name);
    free(model->feature);
    free(model);
}
