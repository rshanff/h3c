#ifndef _STUB_H_
#define _STUB_H_

#ifdef  __cplusplus
extern "C"{
#endif

/* --------------------������׮����-------------------- */
VOID stub_init_all(VOID);
VOID stub_set_one(IN VOID *pOldFn, IN VOID *pNewFn);
VOID stub_reset_all(VOID);

/* --------------------�ڴ��׮����-------------------- */
VOID *stub_malloc_ok(size_t ulLen);
VOID *stub_malloc_ok_ng(size_t ulLen);
VOID *stub_malloc_ok_ng_ok(size_t ulLen);
VOID *stub_malloc_ng(size_t ulLen);

#ifdef __cplusplus
}
#endif

#endif /* _STUB_H_ */

