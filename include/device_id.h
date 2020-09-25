/**
 * \file device_id.h
 * \brief get the device id as the hardware unique serial number
 * \author louis.rubet@wattsense.com
 * \date 2018/02/27
 */

#ifndef DEVICE_ID_H
#define DEVICE_ID_H

/*
 * includes
 */
#include <glib.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * interface
 */

#define DEVICE_ID_LENGTH_MAX 1024

/**
 * \brief Generate the device id from the source file
 *
 * The Device ID is extracted from /data/wattsense/device_id
 * \return true if succeeded
 */
bool device_id_init(void);

/**
 * \brief Retrieves the Device ID
 * \return the device id as a string terminated by \\x00
 */
const char* device_id_get(void);

/**
 * \brief Replace device ID placeholder by the real one
 * \param[in] in: String to replace device ID in
 * \return the string with replacements (must be g_freed)
 */
gchar* device_id_replace(const char* in);

#ifdef __cplusplus
}
#endif

#endif /* DEVICE_ID_H */
