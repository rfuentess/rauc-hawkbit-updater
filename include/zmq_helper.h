/**
 * \file zmq_helper.h
 * \brief zmq helper function
 */

#ifndef ZMQ_HELPER_H
#define ZMQ_HELPER_H

#include <stddef.h>
#include <stdint.h>
#include "return-codes.h"

/**
 * \brief zmq connection descriptor, to be used like a handle
 *
 */
/* internal struct for connection */
typedef struct zmq_connection_t {
        void* context;
        void* connection;
} zmq_connection_t;

typedef struct zmq_connection_t* zmq_desc_t;
#define INVALID_ZMQ_DESCR (NULL)

/**
 * \brief trace and notify an error
 *
 * \param code the error code
 * \param network the network
 * \param msg the msg to notify
 */
void zmq_notify_error(uint32_t code, const char* msg);

/**
 * \brief create a zmq pub connection on the passed TCP port and bind it
 *
 * \param[out] publisher the publisher descriptor. Must be freed after use
 * \param[in] publisher_port the publisher TCP port
 * \return ret_t see this type
 */
ret_t zmq_pub_create_and_bind(zmq_desc_t* publisher, unsigned short publisher_port);

/**
 * \brief create a zmq sub connection and connect to it (blcking with inner timeout)
 *
 * \param[out] subscriber the subscriber descriptor. Must be freed after use
 * \param[in] subscriber_port the subscriber TCP port
 * \return ret_t see this type
 */
ret_t zmq_sub_create_and_connect(zmq_desc_t* subscriber, unsigned short subscriber_port);

/**
 * \brief close and destroy a zmq pub or sub connection
 *
 * \param[in] publisher the publisher descriptor
 * \return ret_t see this type
 */
ret_t zmq_pub_sub_destroy(zmq_desc_t publisher);

#endif
