#include <iostream>
#include "dmadrv.h"
#include <unistd.h>
#include <fstream>


using namespace std;
///sys/class/u-dma-buf/udmabuf0/phys_addr


int main()
{
  uint32_t pattern = 0xfeedbeef;
  uint32_t lenWords = 65536/4;
  uint64_t udma0Addr, udma1Addr;


  ifstream udma0AddrFile;
  ifstream udma1AddrFile;
  udma0AddrFile.open("/sys/class/u-dma-buf/udmabuf0/phys_addr");
  udma1AddrFile.open("/sys/class/u-dma-buf/udmabuf1/phys_addr");
   
  udma0AddrFile >> hex >> udma0Addr;
  udma0AddrFile >> hex >> udma0Addr;
  udma1AddrFile >> hex >> udma1Addr;
  udma1AddrFile >> hex >> udma1Addr;
  

  cout << "enter a pattern >";
  cin >> hex >> pattern;
  cout << "sizeof(dmaMap) = " << hex << "0x" << sizeof(dmaMap) << endl;
   
  if(!udma0AddrFile.is_open() || !udma1AddrFile.is_open()) 
  {
    cout << "address files not open" <<endl;
  }
  cout << "udma addresses " << udma0Addr << "  " << udma1Addr << endl;
  
  axiDMA myDMA("/dev/uio0", "/dev/udmabuf0", udma0Addr, 65536, "/dev/udmabuf1", udma1Addr, 65536);
   
  for(int i = 0; i < lenWords; i++)
  {
    myDMA.txBuf[i] = pattern;
  }
  msync(myDMA.txBuf, myDMA.txBufSize, MS_SYNC);
  cout << "wrote data txBuf[0] = " << myDMA.txBuf[0] << " rxBuf[0]= "<< myDMA.rxBuf[0] << endl;
  myDMA.beginRx();
  cout << "beginrx txBuf[0] = " << myDMA.txBuf[0] << " rxBuf[0]= "<< myDMA.rxBuf[0] << endl;
  myDMA.beginTx();
  cout << "begintx txBuf[0] = " << myDMA.txBuf[0] << " rxBuf[0]= "<< myDMA.rxBuf[0] << endl;
  myDMA.setRxLen(256);
  cout << "setrxlen txBuf[0] = " << myDMA.txBuf[0] << " rxBuf[0]= "<< myDMA.rxBuf[0] << endl;
  myDMA.setTxLen(256);
  sleep(1); 
  cout << "settxlen txBuf[0] = " << myDMA.txBuf[0] << " rxBuf[0]= "<< myDMA.rxBuf[0] << endl;

	
}
