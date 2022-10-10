#include "dmadrv.h"
using namespace std;


axiDMA::axiDMA(char *uioDev, char * rxBufDev, uint64_t dst, uint32_t myRxBufSize, char *txBufDev, uint64_t src, uint32_t myTxBufSize)
{
  
  int fd; 
  uint32_t *addr;

  fd = open(uioDev,O_RDWR|O_SYNC);
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
  fd = open(rxBufDev,O_RDWR | O_SYNC);
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
  fd = open(txBufDev,O_RDWR | O_SYNC);
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
  setDest(dst);
  setSrc(src);
}

void axiDMA::setDest(uint64_t dest)
{

  cout << hex << "setting dest to 0x" << dest << endl;
  cout << "lsb " << (uint32_t)(dest & 0xFFFFFFFF) <<endl;
  map->s2mm_da_lsb =  (uint32_t)(dest & 0xFFFFFFFF);
  map->s2mm_da_msb =  (uint32_t)(dest >> 32);

  cout << "dest = 0x" << hex << map->s2mm_da_msb << map->s2mm_da_lsb << endl;
}
void axiDMA::setSrc(uint64_t src)
{
  cout << hex << "setting src to 0x" << src << endl;

  uint64_t offset = (uint64_t) map;
  cout << "mm2s_sa_lsb address = " << ((uint64_t) &map->mm2s_sa_lsb )-offset << endl;
  
  map->mm2s_sa_lsb = (uint32_t)(src & 0xFFFFFFFF);
  map->mm2s_sa_msb = (uint32_t)(src >> 32);

  cout << (uint32_t)(src & 0xFFFFFFFF) << endl;
  cout <<  (uint32_t)(src >> 32) << endl;
  cout << "src = 0x" << hex << map->mm2s_sa_msb << map->mm2s_sa_lsb << endl;
}
void axiDMA::setTxLen(uint32_t len)
{
  
  uint64_t offset = (uint64_t) map;
  cout << "s2mm_len address = " << ((uint64_t) &map->s2mm_len )-offset << endl;
  map->s2mm_len = len;
}
void axiDMA::setRxLen(uint32_t len)
{
  uint64_t offset = (uint64_t) map;
  cout << "mm2s_len address = " << ((uint64_t) &map->mm2s_len )-offset << endl;
  map->mm2s_len = len;
}
void axiDMA::beginTx()
{
  map->s2mm_dmacr = map->s2mm_dmacr | 1;
}
void axiDMA::beginRx()
{
  map->mm2s_dmacr = map->mm2s_dmacr | 1;
}
