#include <iostream>
#include "dmadrv.h"
#include <unistd.h>

using namespace std;



int main()
{
  uint32_t pattern = 0xdeadbeef;
  uint32_t lenWords = 65536/4;
  axiDMA myDMA("/dev/uio0", "/dev/udmabuf0", 65536, "/dev/udmabuf1", 65536);

  for(int i = 0; i < lenWords; i++)
  {
    myDMA.txBuf[i] = pattern;
  }

  cout << "txBuf[0] = " << myDMA.txBuf[0] << " rxBuf[0]= "<< myDMA.rxBuf[0] << endl;

  myDMA.beginRx();
  myDMA.beginTx();
  myDMA.setTxLen(65536);
  myDMA.setRxLen(65536);
  sleep(1);
  cout << "txBuf[0] = " << myDMA.txBuf[0] << " rxBuf[0]= "<< myDMA.rxBuf[0] << endl;
	
}
