/*
 * Copyright Wattsense 2019
 */

/**
 * \file include/return-codes.h
 * \brief Main modules structures for our Gateway
 */

#ifndef __RETURN_CODES_H__
#define __RETURN_CODES_H__

#ifdef __cplusplus
extern "C" {
#endif

/** Common enumeration of returning values for most of the API functions */
typedef enum {
        ret_ok,          /**< The function finished with success */
        ret_failure,     /**< The function failed to be completed with success */
        ret_abort,       /**<  The function finished with an abortion status */
        ret_wrong_parameter, /**< One or more paremeters give to the function were wrong */
        ret_file_not_found,
        ret_file_map_error,
        ret_json_syntax_error, /**< The parsing of one or more json config file failed */
        ret_not_found,
        ret_not_enough_memory, /**< The function had to be aborted due to memory exhaustion */
        ret_disconnected,  /**< The network linked to the function is on disconnect status */
        ret_timeout,       /**< The function failed due to timeout expired (on the remote side) */
        ret_not_implemented, /**< The operation requested is not supported yet by the function */
        ret_invalid_value, /**< The function finished due the value given is invalid */
        ret_outside_range, /**< The function finished due the value given is outside of a valid range */
        ret_invalid_input_size, /**< The function finished due the value given is invalid (on bytes size) */
        ret_max
} ret_t;

#ifdef __cplusplus
}
#endif

#endif  // __RETURN_CODES_H__
