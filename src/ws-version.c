/**
 * \file ws-version.c
 * \brief wattsense version
 * \date 2020/05/04
 */

/*
 * includes
 */
#include <stdio.h>
#include <glib/gstdio.h>
#include <sys/utsname.h>

#include "ws-version.h"


gchar *hw_name_get(void)
{
        struct utsname unameData;
        int err;

        err = uname(&unameData);
        if (err == 0)
                return g_strdup(unameData.nodename);
        else
                return g_strdup("unknown");
}

gchar *app_version_get(void)
{
        const gchar* filename = APP_VERSION_FILENAME;
        gchar* version;
        gsize len;
        GError* error = NULL;

        if (!g_file_get_contents(filename, &version, &len, &error)) {
                if (error != NULL) {
                        g_printerr("Unable to read file: %s\n", error->message);
                        g_error_free(error);
                }
                return g_strdup("0.0.0");
        }
        if (len == 0) {
                return g_strdup("0.0.0");
        } else
                return g_strdup(g_strstrip(version));
}

gchar *rootfs_version_get(void)
{
        const gchar* filename = ROOTFS_VERSION_FILENAME;
        gchar line[128];
        FILE* fp;

        fp = g_fopen(filename, "r");
        if (fp == NULL) {
                return g_strdup("0.0.0");
        }
        while (!feof(fp)) {
                char version[32];

                fgets(line, 128, fp);
                if (sscanf(line, "VERSION_ID=\"%32[^\"]\"", version) != 0) {
                        fclose(fp);
                        return g_strdup(version);
                }
        }

        fclose(fp);
        return g_strdup("0.0.0");
}
