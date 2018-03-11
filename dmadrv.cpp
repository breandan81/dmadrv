#include "dmadrv.h"
using namespace std;


axiDMA::axiDMA(char *uioDev, char * rxBufDev, uint32_t myRxBufSize, char *txBufDev, uint32_t myTxBufSize)
{
  
  int fd; 
  uint32_t *addr;

  fd = open(uioDev,O_RDWR);
  if(fd == -1)
  {
    cout << "failed to open device" << endl;
    exit(1);
  }
  map = (dmaMap *)mmap(NULL, 65536, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
  if(addr == MAP_FAILED)
  {
    cout << "mmap failed";
    exit(1);
  }
  fd = open(rxBufDev,O_RDWR);
  if(fd == -1)
  {
    cout << "failed to open device" << endl;
    exit(1);
  }
  rxBuf = (uint32_t *)mmap(NULL, myRxBufSize, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
  if(addr == MAP_FAILED)
  {
    cout << "mmap failed";
    exit(1);
  }
  fd = open(txBufDev,O_RDWR);
  if(fd == -1)
  {
    cout << "failed to open device" << endl;
    exit(1);
  }
  txBuf = (uint32_t *)mmap(NULL, myTxBufSize, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
  if(addr == MAP_FAILED)
  {
    cout << "mmap failed";
    exit(1);
  }
  rxBufSize = myRxBufSize;
  txBufSize = myTxBufSize;
}

void axiDMA::setDest(uint64_t dest)
{
  map->s2mm_da_lsb =  (uint32_t)dest & 0xFFFFFFFF;
  map->s2mm_da_msb =  (uint32_t)(dest >> 32);
}
void axiDMA::setSrc(uint64_t src)
{
  map->mm2s_sa_lsb = (uint32_t)src & 0xFFFFFFFF;
  map->mm2s_sa_msb = (uint32_t)(src >> 32);
}
void axiDMA::setTxLen(uint32_t len)
{
  map->s2mm_len = len;
}
void axiDMA::setRxLen(uint32_t len)
{
  map->mm2s_len = len;
}
void axiDMA::beginTx()
{
  map->s2mm_dmacr = map-> s2mm_dmacr | 1;
}
void axiDMA::beginRx()
{
  map->mm2s_dmacr = map-> mm2s_dmacr | 1;
}
