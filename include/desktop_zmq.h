/**
 * \file desktop_zmq.h
 * \brief Module in charge of getting DesktopApp server address
 */

#ifndef _DESKTOP_ZMQ_H_
#define _DESKTOP_ZMQ_H_

#ifdef __cplusplus
extern "C" {
#endif

int get_desktop_server(gchar** host, gint64* port);
int desktop_zmq_destroy();

#ifdef __cplusplus
}
#endif

#endif
