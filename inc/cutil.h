#ifndef _CUTIL_
#define _CUTIL_

#ifdef __cplusplus
extern "C" {
#endif

#define cutil_log_level  cutil_log_level_d

#define cutil_log_level_v    (1)
#define cutil_log_level_d    (2)
#define cutil_log_level_i    (3)
#define cutil_log_level_w    (4)
#define cutil_log_level_e    (5)

#if cutil_log_level <= cutil_log_level_v
#define cutil_logv(fmt...) cutil_log(__FILE__, __FUNCTION__, __LINE__, cutil_log_level_v, fmt)
#else
#define cutil_logv(fmt...)
#endif

#if cutil_log_level <= cutil_log_level_d
#define cutil_logd(fmt...) cutil_log(__FILE__, __FUNCTION__, __LINE__, cutil_log_level_d, fmt)
#else
#define cutil_logd(fmt...)
#endif

#if cutil_log_level <= cutil_log_level_i
#define cutil_logi(fmt...) cutil_log(__FILE__, __FUNCTION__, __LINE__, cutil_log_level_i, fmt)
#else
#define cutil_logi(fmt...)
#endif

#if cutil_log_level <= cutil_log_level_w
#define cutil_logw(fmt...) cutil_log(__FILE__, __FUNCTION__, __LINE__, cutil_log_level_w, fmt)
#else
#define cutil_logw(fmt...)
#endif

#if cutil_log_level <= cutil_log_level_e
#define cutil_loge(fmt...) cutil_log(__FILE__, __FUNCTION__, __LINE__, cutil_log_level_e, fmt)
#else
#define cutil_loge(fmt...)
#endif


void cutil_log(const char* file, const char* func, int line, int level, const char *cmd, ...);

void* cutil_malloc(int size);
void cutil_free(void* ptr);

#ifdef __cplusplus
}
#endif

#endif