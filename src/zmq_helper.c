/**
 * \file zmq_helper.c
 * \brief zmq helper functions
 */

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <zmq.h>

#include "log.h"
#include "zmq_helper.h"

/**
 * \brief allocate then create parts of a descriptor (common to pub and sub)
 *
 * \param descr the descriptor to create. Must be freed after use
 * \param type zmq connection type as described in http://api.zeromq.org/2-1:zmq-socket
 * \return ret_t
 */
static ret_t _create_descr(zmq_desc_t* descr, int type)
{
        if (descr == NULL) {
                return ret_wrong_parameter;
        }

        *descr = malloc(sizeof(struct zmq_connection_t));
        if (*descr == NULL) {
                return ret_not_enough_memory;
        }

        (*descr)->context = NULL;
        (*descr)->connection = NULL;

        /* open the pub/sub zeromq */
        (*descr)->context = zmq_ctx_new();
        if ((*descr)->context == NULL) {
                g_critical("zmq_ctx_new failed");
                return ret_not_enough_memory;
        }

        (*descr)->connection = zmq_socket((*descr)->context, type);
        if ((*descr)->connection == NULL) {
                g_critical("zmq_socket failed");
                (void)zmq_pub_sub_destroy(*descr);
                return ret_failure;
        }

        return ret_ok;
}

ret_t zmq_pub_create_and_bind(zmq_desc_t* publisher, unsigned short publisher_port)
{
        char connection_str[64];
        ret_t ret = _create_descr(publisher, ZMQ_PUB);

        if (ret == ret_ok) {
                snprintf(connection_str, sizeof(connection_str), "tcp://127.0.0.1:%hu", publisher_port);
                if (zmq_bind((*publisher)->connection, connection_str) != 0) {
                        g_critical("zmq_bind failed");
                        (void)zmq_pub_sub_destroy(*publisher);
                        ret = ret_failure;
                }
        }

        return ret;
}

ret_t zmq_pub_sub_destroy(zmq_desc_t descr)
{
        if (descr == INVALID_ZMQ_DESCR) {
                return ret_wrong_parameter;
        }

        if (descr->connection != NULL) {
                (void)zmq_close(descr->connection);
        }

        if (descr->context != NULL) {
                (void)zmq_term(descr->context);
        }

        free(descr);

        return ret_ok;
}

ret_t zmq_sub_create_and_connect(zmq_desc_t* subscriber, unsigned short subscriber_port)
{
        if (subscriber == INVALID_ZMQ_DESCR) {
                return ret_wrong_parameter;
        }

        ret_t ret = _create_descr(subscriber, ZMQ_SUB);
        if (ret != ret_ok) {
                return ret;
        }

        char connection_str[64];
        int max_time_s = 60;

        snprintf(connection_str, sizeof(connection_str), "tcp://127.0.0.1:%hu", subscriber_port);
        while ((--max_time_s) >= 0) {
                if (zmq_connect((*subscriber)->connection, connection_str) == 0) {
                        /* subscribe to all (NULL) */
                        if (zmq_setsockopt((*subscriber)->connection, ZMQ_SUBSCRIBE, NULL, 0) != 0) {
                                g_critical("subscriber cannot subscribe to all messages");
                                return ret_failure;
                        }
                        return ret_ok;
                }
                sleep(1);
        }

        /* timeout or something bad in zmq_connect or zmq_setsockopt */
        return ret_failure;
}
