#ifndef GPIO_H
#define GPIO_H
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstdint>
#include <iostream>

struct dmaMap
{
  uint32_t mm2s_dmacr;
  uint32_t mm2s_dmasr;
  uint32_t pad[4];
  uint32_t mm2s_sa_lsb;
  uint32_t mm2s_sa_msb;
  uint32_t pad2[2];
  uint32_t mm2s_len;
  uint32_t pad3;
  uint32_t s2mm_dmacr;
  uint32_t s2mm_dmasr;
  uint32_t pad4[4];
  uint32_t s2mm_da_lsb;
  uint32_t s2mm_da_msb;
  uint32_t pad5[2];
  uint32_t s2mm_len;
};
class axiDMA
{
  dmaMap *map;

  public:
  uint32_t rxBufSize;
  uint32_t txBufSize;
    uint32_t *rxBuf; 
    uint32_t *txBuf;
    axiDMA(char *uioDev, char *rxBufDev,  uint64_t dst, uint32_t myRxBufSize, char *txBufDev, uint64_t src, uint32_t myTxBufSize);
    void setDest(uint64_t dest);
    void setSrc(uint64_t src);
    void setTxLen(uint32_t len);
    void setRxLen(uint32_t len);
    void beginTx();
    void beginRx();
    uint32_t getRx(int idx);
    uint32_t getTx(int idx);
     
};


#endif

