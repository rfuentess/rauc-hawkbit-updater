/**
 * \file ws-version.h
 * \brief get the device id as the hardware unique serial number
 * \author louis.rubet@wattsense.com
 * \date 2018/02/27
 */

#ifndef WS_VERSION_H
#define WS_VERSION_H

#include <glib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define APP_VERSION_FILENAME "/opt/wattsense/app-version.txt"
#define ROOTFS_VERSION_FILENAME "/etc/os-release"


gchar *hw_name_get(void);
gchar *app_version_get(void);
gchar *rootfs_version_get(void);

#ifdef __cplusplus
}
#endif

#endif /* WS_VERSION_H */
