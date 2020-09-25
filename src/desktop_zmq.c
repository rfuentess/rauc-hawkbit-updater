/**
 * \file desktop_zmq.c
 * \brief Module in charge of getting DesktopApp server address
 */

#include <json-glib/json-glib.h>
#include <string.h>
#include <zmq.h>
#include "log.h"
#include "json-helper.h"
#include "zmq_helper.h"

#define DESKTOP_ZMQ_PORT 3000

zmq_desc_t desktop_subscriber = INVALID_ZMQ_DESCR;

int desktop_zmq_destroy()
{
        return zmq_pub_sub_destroy(desktop_subscriber);
}

int get_desktop_server(gchar** host, gint64* port)
{
        int ret = -1;
        zmq_msg_t msg;

        while (desktop_subscriber == INVALID_ZMQ_DESCR) {
                zmq_sub_create_and_connect(&desktop_subscriber, DESKTOP_ZMQ_PORT);
        }

        /* connect our subscriber to the zmq remote publisher (blocking) */
        if (zmq_msg_init(&msg) == -1) {
                g_printerr("%s:zmq_msg_init error\n", __func__);
                return -1;
        }

        /* receive single part messages only */
        if (zmq_msg_recv(&msg, desktop_subscriber->connection, 0) == -1) {
                g_printerr("%s:zmq_recvmsg error\n", __func__);
                return -1;
        }

        /* now decode zmq payload */
        JsonParser *parser = json_parser_new();
        if (json_parser_load_from_data(parser, zmq_msg_data(&msg), zmq_msg_size(&msg), NULL)) {
                JsonNode *root = json_parser_get_root(parser);

                *host = json_get_string(root, "$.http_server");
                *port = json_get_int(root, "$.http_port");

                g_message("%s: host=%s port=%"G_GINT64_FORMAT "\n", __func__, *host, *port);
                ret = 0;

        }

        (void)zmq_msg_close(&msg);

        return ret;
}
