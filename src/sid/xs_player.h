#ifndef XS_PLAYER_H
#define XS_PLAYER_H

#include "xmms-sid.h"
#include "xs_config.h"

#ifdef __cplusplus
extern "C" {
#endif

struct xs_status_t;

typedef struct {
    gint        plrIdent;
    gboolean    (*plrProbe)(xs_file_t *);
    gboolean    (*plrInit)(struct xs_status_t *);
    void        (*plrClose)(struct xs_status_t *);
    gboolean    (*plrInitSong)(struct xs_status_t *);
    guint        (*plrFillBuffer)(struct xs_status_t *, gchar *, guint);
    gboolean    (*plrLoadSID)(struct xs_status_t *, gchar *);
    void        (*plrDeleteSID)(struct xs_status_t *);
    xs_tuneinfo_t*    (*plrGetSIDInfo)(const gchar *);
    gboolean    (*plrUpdateSIDInfo)(struct xs_status_t *);
    void        (*plrFlush)(struct xs_status_t *);
} xs_player_t;


typedef struct xs_status_t {
    gint        audioFrequency,        /* Audio settings */
            audioChannels,
            audioBitsPerSample,
            oversampleFactor;    /* Factor of oversampling */
    AFormat        audioFormat;
    gboolean    oversampleEnable;    /* TRUE after sidEngine initialization,
                        if xs_cfg.oversampleEnable == TRUE and
                        emulation backend supports oversampling.
                        */
    void        *sidEngine;        /* SID-emulation internal engine data */
    xs_player_t    *sidPlayer;        /* Selected player engine */
    gboolean    isError, isPlaying, isInitialized;
    gint        currSong,        /* Current sub-tune */
            lastTime;

    xs_tuneinfo_t    *tuneInfo;
} xs_status_t;


/* Global variables
 */
extern InputPlugin    xs_plugin_ip;

extern xs_status_t    xs_status;
XS_MUTEX_H(xs_status);


#ifdef __cplusplus
}
#endif
#endif /* XS_PLAYER_H */
