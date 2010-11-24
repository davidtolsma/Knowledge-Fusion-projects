// -*- C++ -*-
#if !defined(DPH_KFFUN_H)
#define DPH_KFFUN_H

#ifdef WIN32
#if EXPORT_KFFUN
#define KFFUN_API __declspec(dllexport)
#define KFFUN_TEMPLATE
#else
#define KFFUN_API __declspec(dllimport)
#define KFFUN_TEMPLATE extern
#endif
#else
#define KFFUN_API
#define KFFUN_TEMPLATE
#endif

extern "C"
{
    void KFFUN_API DPH_KF_set_layer( UF_KF_value_t *data, int num,
                                    UF_KF_value_t *returnValue );
    void KFFUN_API DPH_KF_get_layer( UF_KF_value_t *data, int num,
                                    UF_KF_value_t *returnValue );
}

#endif
