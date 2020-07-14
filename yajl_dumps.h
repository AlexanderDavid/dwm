#ifndef YAJL_DUMPS_H_
#define YAJL_DUMPS_H_

#include "types.h"
#include <string.h>
#include <yajl/yajl_gen.h>

#define YSTR(str) yajl_gen_string(gen, (unsigned char *)str, strlen(str))
#define YINT(num) yajl_gen_integer(gen, num)
#define YDOUBLE(num) yajl_gen_double(gen, num)
#define YBOOL(v) yajl_gen_bool(gen, v)
#define YNULL() yajl_gen_null(gen)
#define YARR(body) { yajl_gen_array_open(gen); body yajl_gen_array_close(gen); }
#define YMAP(body) { yajl_gen_map_open(gen); body yajl_gen_map_close(gen); }

int dump_tags(yajl_gen gen, const char *tags[], int tags_len);

int dump_client(yajl_gen gen, Client *c);

int dump_monitor(yajl_gen gen, Monitor *mon);

int dump_layouts(yajl_gen gen, const Layout layouts[], const int layouts_len);

int dump_tag_state(yajl_gen gen, TagState state);

int dump_tag_event(yajl_gen gen, int mon_num, TagState old_state,
                   TagState new_state);

int dump_client_change_event(yajl_gen gen, Client *old_client,
                             Client *new_client, int mon_num);

int dump_layout_change_event(yajl_gen gen, const int mon_num,
                             const char *old_symbol, const Layout *old_layout,
                             const char *new_symbol, const Layout *new_layout);

int dump_monitor_change_event(yajl_gen gen, const int last_mon_num,
                              const int new_mon_num);

int dump_error_message(yajl_gen gen, const char *reason);

#endif // YAJL_DUMPS_H_
